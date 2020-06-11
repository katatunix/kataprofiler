using System;
using System.Collections.Generic;
using System.Text;

namespace KataProfiler
{
	public enum KPTextureType
	{
		TEX_NONE = 0,
		TEX_2D,
		TEX_CUBE_MAP
	}

	public class Texture : GlObject
	{
		public const int MAX_MIPMAP_LEVEL_NUMBER = 32;

		private Mipmap[] m_pMipmaps;
		public Mipmap[] Mipmaps { get { return m_pMipmaps; } }

		private KPTextureType m_texType;
		public KPTextureType TexType { get { return m_texType; } set { m_texType = value; } }

		public Texture() : base()
		{
			init();
		}

		public Texture(uint id) : base(id)
		{
			init();
		}

		private void init()
		{
			m_texType = KPTextureType.TEX_NONE;

			m_pMipmaps = new Mipmap[MAX_MIPMAP_LEVEL_NUMBER];
			for (int i = 0; i < MAX_MIPMAP_LEVEL_NUMBER; i++)
			{
				m_pMipmaps[i] = new Mipmap();
			}
		}

		public int MipmapCount
		{
			get
			{
				int count = 0;
				for (int i = 0; i < MAX_MIPMAP_LEVEL_NUMBER; i++)
				{
					if (m_pMipmaps[i].HasData) count++;
				}
				return count;
			}
		}

		public int SizeInBytes
		{
			get
			{
				int sum = 0;
				for (int i = 0; i < MAX_MIPMAP_LEVEL_NUMBER; i++) if (m_pMipmaps[i].HasData)
					{
						sum += m_pMipmaps[i].calculateSize();
					}
				return sum;
			}
		}

		public override void clearData()
		{
			m_texType = KPTextureType.TEX_NONE;
			for (int i = 0; i < MAX_MIPMAP_LEVEL_NUMBER; i++)
			{
				m_pMipmaps[i].reset();
			}
		}

		public override void fromMessage(Message msg)
		{
			clearData();

			MyBinStream stream = new MyBinStream(msg.Data);

			m_id = stream.readUInt();
			m_texType = (KPTextureType)stream.readInt();

			int mipmapCount = stream.readInt();

			for (int i = 0; i < mipmapCount; i++)
			{
				int level = stream.readInt();
				Utils.assert(level >= 0 && level < MAX_MIPMAP_LEVEL_NUMBER);
				Mipmap mip = m_pMipmaps[level];

				mip.reset();

				mip.Width = stream.readInt();
				mip.Height = stream.readInt();
				mip.IsCompressed = stream.readByte();
				mip.Format = stream.readInt();
				mip.Type = stream.readUInt();

				byte hasPixel = stream.readByte();
				if (hasPixel == 1)
				{
					int mipSize = mip.calculateSize();
					if (mipSize > 0)
					{
						mip.Pixels = new byte[mipSize];
						stream.readBytes(mip.Pixels, 0, mipSize);
					}
				}

				mip.HasData = true;
			}

			stream.close();
		}

		public void copyFrom(Texture tex)
		{
			clearData();
			m_id = tex.Id;
			m_texType = tex.TexType;

			Mipmap[] mips = tex.Mipmaps;
			for (int i = 0; i < MAX_MIPMAP_LEVEL_NUMBER; i++)
			{
				m_pMipmaps[i].copyFrom(mips[i]);
			}
		}

		public override bool isKindOf(KPGLObjectKind kind)
		{
			return kind == KPGLObjectKind.TEXTURE;
		}

		public void on_glCompressedTexImage2D(int level, uint internalformat, int width, int height,
					int border, int imageSize, byte[] data, int offset)
		{
			Mipmap mip = m_pMipmaps[level];
			mip.reset();

			mip.IsCompressed = 1;

			mip.Format = (int)internalformat;
			mip.Width = width;
			mip.Height = height;

			mip.Type = (uint)imageSize;

			if (imageSize > 0)
			{
				mip.Pixels = new byte[imageSize];
				Utils.memcpy(mip.Pixels, 0, data, offset, imageSize);
			}

			mip.HasData = true;
		}

		public void on_glTexImage2D(int level, int internalformat,
						int width, int height, int border, uint format, uint type, byte[] pixels, int offset)
		{
			Mipmap mip = m_pMipmaps[level];
			mip.reset();

			mip.IsCompressed = 0;

			mip.Format = (int)format;
			mip.Width = width;
			mip.Height = height;

			mip.Type = type;

			int imageSize = mip.calculateSize();
			if (imageSize > 0)
			{
				mip.Pixels = new byte[imageSize];
				Utils.memcpy(mip.Pixels, 0, pixels, offset, imageSize);
			}

			mip.HasData = true;
		}

		public void on_glTexStorage2D(int levels, int internalformat, int width, int height)
		{
			for (int level = 0; level < levels; ++level)
			{
				var mip = m_pMipmaps[level];
				mip.reset();

				mip.IsCompressed = Mipmap.isCompressedFormat(internalformat) ? (byte)1 : (byte)0;

				if (internalformat == gl.GL_RGB8)
					mip.Format = (int)gl.GL_RGB;
				else if (internalformat == gl.GL_RGBA8)
					mip.Format = (int)gl.GL_RGBA;
				else
					mip.Format = internalformat;

				mip.Type = mip.IsCompressed == 1 ? 16 : gl.GL_UNSIGNED_BYTE; // TODO

				mip.Width = width;
				mip.Height = height;

				int imageSize = mip.calculateSize();
				if (imageSize > 0)
				{
					mip.Pixels = new byte[imageSize];
					Utils.memset(mip.Pixels, 0, imageSize, 0);
				}

				mip.HasData = true;

				width = Math.Max(1, width / 2);
				height = Math.Max(1, height / 2);
			}
		}

		public void on_glTexSubImage2D(int level, int xoffset, int yoffset, int width, int height,
										uint format, uint type, byte[] pixels, int offset)
		{
			if (width <= 0 || height <= 0 || pixels.Length == offset) return;

			Mipmap mip = m_pMipmaps[level];

			if (mip.Width == 0 || mip.Height == 0 || mip.Pixels == null) return;

			int dst_bytesPP = mip.getBPP() / 8;
			int src_bytesPP = Mipmap.getTexBPP((int)format, type) / 8;

			for (int row = yoffset; row < yoffset + height; row++)
			{
				// TODO: row order???
				//int j2 = mip.Height - 1 - j;
				int row2 = row;
				for (int col = xoffset; col < xoffset + width; col++)
				{
					int pixelIndex = row2 * mip.Width + col;

					Utils.convertTexSubPixel(mip.Pixels, pixelIndex * dst_bytesPP, pixels, offset, format, mip.Type, type);

					//Utils.memcpy(mip.Pixels, pixelIndex * bytesPP, pixels, offset, bytesPP);

					offset += src_bytesPP;
				}
			}
		}

		public void on_glCompressedTexSubImage2D(int level, int xoffset, int yoffset,
													int width, int height, uint format, int imageSize, byte[] data, int offset)
		{
			// TODO
			Mipmap mip = m_pMipmaps[level];
			mip.Pixels = new byte[imageSize];
			Utils.memcpy(mip.Pixels, 0, data, offset, imageSize);
		}

	}
}
