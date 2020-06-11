using System;
using System.Collections.Generic;
using System.Text;

namespace KataProfiler
{
	public class Mipmap
	{
		#region Properties

		private int m_width;
		public int Width { get { return m_width; } set { m_width = value; } }

		private int m_height;
		public int Height { get { return m_height; } set { m_height = value; } }

		private byte m_isCompressed;
		public byte IsCompressed { get { return m_isCompressed; } set { m_isCompressed = value; } }

		private int m_format;
		public int Format { get { return m_format; } set { m_format = value; } }

		public string FormatName
		{
			get
			{
				if (m_format == 0) return "UNKNOWN";
				if (m_isCompressed == 1) return gl.getString(m_format);

				switch (m_type)
				{
				case gl.GL_UNSIGNED_SHORT_4_4_4_4: return "RGBA 4444";
				case gl.GL_UNSIGNED_SHORT_5_5_5_1: return "RGBA 5551";
				case gl.GL_UNSIGNED_SHORT_5_6_5: return "RGB 565";

				case gl.GL_UNSIGNED_BYTE:
					{
						if (m_format == gl.GL_RGBA) return "RGBA 8888";
						if (m_format == gl.GL_RGB) return "RGB 888";
						break;
					}
				}

				// Don't support
				//if (m_format == gl2.GL_DEPTH_COMPONENT)
				//{
				//    if (m_type == gl2.GL_UNSIGNED_SHORT)		return "DEPTH 16 bit";
				//    if (m_type == gl2.GL_UNSIGNED_INT)		return "DEPTH 32 bit";
				//    Utils.assert(false);
				//}

				return gl.getString(m_format);
			}
		}

		private uint m_type;
		public uint Type { get { return m_type; } set { m_type = value; } }

		private byte[] m_pPixels;
		public byte[] Pixels { get { return m_pPixels; } set { m_pPixels = value; } }

		private bool m_hasData;
		public bool HasData { get { return m_hasData; } set { m_hasData = value; } }

		#endregion

		public Mipmap()
		{
			reset();
		}

		public void reset()
		{
			m_width = 0;
			m_height = 0;
			m_isCompressed = 0;
			m_format = 0;
			m_type = 0;
			m_pPixels = null;
			m_hasData = false;
		}

		public void copyFrom(Mipmap other)
		{
			reset();

			if (other.HasData)
			{
				m_width = other.m_width;
				m_height = other.m_height;
				m_isCompressed = other.m_isCompressed;
				m_format = other.m_format;
				m_type = other.m_type;
				m_hasData = true;

				int imageSize = calculateSize();

				if (imageSize > 0 && other.m_pPixels != null)
				{
					m_pPixels = new byte[imageSize];
					Utils.memcpy(m_pPixels, 0, other.m_pPixels, 0, imageSize);
				}
			}
		}

		public int calculateSize()
		{
			return m_isCompressed == 1 ? (int)m_type : calculateTexSize(m_format, m_width, m_height, m_type);
		}

		public int getBPP()
		{
			if (m_isCompressed == 1) return getCompressedTexBPP(m_format);
			return getTexBPP(m_format, m_type);
		}

		#region Static methods

		public static int calculateTexSize(int internalformat, int width, int height, uint type)
		{
			return width * height * getTexBPP(internalformat, type) / 8;
		}

		public static int getTexBPP(int internalformat, uint type)
		{
			switch (type)
			{
			case gl.GL_UNSIGNED_SHORT_4_4_4_4:
			case gl.GL_UNSIGNED_SHORT_5_5_5_1:
			case gl.GL_UNSIGNED_SHORT_5_6_5:
				return 16;
			}

			// Don't support
			//if (internalformat == gl2.GL_DEPTH_COMPONENT)
			//{
			//    if (type == gl2.GL_UNSIGNED_SHORT) return 16;
			//    if (type == gl2.GL_UNSIGNED_INT) return 32;
			//    Utils.assert(false);
			//    return 16;
			//}

			if (type == gl.GL_UNSIGNED_BYTE)
			{
				switch ((uint)internalformat)
				{
				case gl.GL_RGBA:
					return 32;
				case gl.GL_RGB:
					return 24;
				case gl.GL_LUMINANCE_ALPHA:
					return 16;
				case gl.GL_LUMINANCE:
				case gl.GL_ALPHA:
					return 8;
				}
			}

			return 0;
		}

		public static int getCompressedTexBPP(int internalformat)
		{
			switch ((uint)internalformat)
			{
			// PVRTC
			case gl.GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG:
			case gl.GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG:
				return 2;

			case gl.GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG:
			case gl.GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG:
				return 4;

			// ETC
			case gl.GL_ETC1_RGB8_OES:
			case gl.GL_COMPRESSED_RGB8_ETC2:
				return 4;
			case gl.GL_COMPRESSED_RGBA8_ETC2_EAC:
				return 8;

			// DXT
			case gl.GL_COMPRESSED_RGB_S3TC_DXT1_EXT:
			case gl.GL_COMPRESSED_RGBA_S3TC_DXT1_EXT:
				return 4;

			case gl.GL_COMPRESSED_RGBA_S3TC_DXT3_EXT:
			case gl.GL_COMPRESSED_RGBA_S3TC_DXT5_EXT:
				return 8;

			}
			return 0;
		}

		public static bool isCompressedFormat(int internalformat)
		{
			uint f = (uint)internalformat;
			return
				// PVRTC
				f == gl.GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG ||
				f == gl.GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG ||
				f == gl.GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG ||
				f == gl.GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG ||
				// ETC
				f == gl.GL_ETC1_RGB8_OES ||
				f == gl.GL_COMPRESSED_RGB8_ETC2 ||
				f == gl.GL_COMPRESSED_RGBA8_ETC2_EAC ||
				// DXT
				f == gl.GL_COMPRESSED_RGB_S3TC_DXT1_EXT ||
				f == gl.GL_COMPRESSED_RGBA_S3TC_DXT1_EXT ||
				f == gl.GL_COMPRESSED_RGBA_S3TC_DXT3_EXT ||
				f == gl.GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
		}

		#endregion
	}
}
