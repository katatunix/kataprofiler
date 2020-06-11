using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;

namespace KataProfiler
{
	public partial class UcTexture : UserControl
	{
		private Texture m_tex;
		private int[] m_mipLevels;
		private int m_mipCount;

		private Bitmap[] m_bitmaps;

		private int m_maxWidth;
		private int m_maxHeight;

		private int m_currentLevel = -1;

		public UcTexture()
		{
			InitializeComponent();

			this.Dock = DockStyle.Fill;

			m_tex = new Texture();
			m_mipLevels = new int[Texture.MAX_MIPMAP_LEVEL_NUMBER];
			m_mipCount = 0;

			m_bitmaps = new Bitmap[Texture.MAX_MIPMAP_LEVEL_NUMBER];
		}

		private string getTitle()
		{
			return "Texture :: id = " + (m_tex == null ? "ZERO" : m_tex.Id.ToString());
		}

		public void applyTex(Texture tex)
		{
			if (tex == null)
			{
				m_tex.clearData();
				this.Visible = false;
				return;
			}

			m_tex.copyFrom(tex);
			this.Parent.Text = getTitle();

			listBoxMipmaps.Items.Clear();

			Mipmap[] mips = m_tex.Mipmaps;
			m_mipCount = 0;

			m_maxWidth = -1;
			m_maxHeight = -1;

			int firstLevel = -1;

			for (int i = 0; i < mips.Length; i++)
			{
				Mipmap mip = mips[i];
				if (mip.HasData)
				{
					if (m_maxWidth == -1 || mip.Width > m_maxWidth) m_maxWidth = mip.Width;
					if (m_maxHeight == -1 || mip.Height > m_maxHeight) m_maxHeight = mip.Height;

					if (firstLevel == -1) firstLevel = m_mipCount;
					
					listBoxMipmaps.Items.Add("Level " + i);
					m_mipLevels[m_mipCount++] = i;
				}
			}

			if (m_maxWidth == -1 || m_maxHeight == -1)
			{
				this.Visible = false;
				return;
			}

			for (int i = 0; i < Texture.MAX_MIPMAP_LEVEL_NUMBER; i++)
			{
				m_bitmaps[i] = null;
			}

			listBoxMipmaps.SelectedIndex = firstLevel;
		}
		
		private void showLevel(int level)
		{
			Mipmap mip = m_tex.Mipmaps[level];
			
			if (m_bitmaps[level] == null)
			{
				if (mip.Pixels == null)
				{
					m_bitmaps[level] = global::KataProfiler.Properties.Resources.not_recorded;
				}
				else
				{
					switch ((uint)mip.Format)
					{
						case gl.GL_RGBA:
							{
							switch (mip.Type)
							{
								case gl.GL_UNSIGNED_BYTE:
									m_bitmaps[level] = Utils.makeBitmap_RGBA(mip.Width, mip.Height, mip.Pixels, 0, false);
									break;
								case gl.GL_UNSIGNED_SHORT_4_4_4_4:
									m_bitmaps[level] = Utils.makeBitmap_RGBA4444(mip.Width, mip.Height, mip.Pixels, 0, false);
									break;
								case gl.GL_UNSIGNED_SHORT_5_5_5_1:
									m_bitmaps[level] = Utils.makeBitmap_RGBA5551(mip.Width, mip.Height, mip.Pixels, 0, false);
									break;
								default:
									Utils.assert(false);
									break;
							}

							break;
						}

						case gl.GL_RGB:
						{
							switch (mip.Type)
							{
								case gl.GL_UNSIGNED_BYTE:
									m_bitmaps[level] = Utils.makeBitmap_RGB(mip.Width, mip.Height, mip.Pixels, 0, false);
									break;
								case gl.GL_UNSIGNED_SHORT_5_6_5:
									m_bitmaps[level] = Utils.makeBitmap_RGB565(mip.Width, mip.Height, mip.Pixels, 0, false);
									break;
								default:
									Utils.assert(false);
									break;
							}

							break;
						}

						case gl.GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG:
						case gl.GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG:
							m_bitmaps[level] = Utils.makeBitmap_PVR(0, mip.Width, mip.Height, mip.Pixels);
							break;
						case gl.GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG:
						case gl.GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG:
							m_bitmaps[level] = Utils.makeBitmap_PVR(1, mip.Width, mip.Height, mip.Pixels);
							break;

						case gl.GL_ETC1_RGB8_OES:
							m_bitmaps[level] = Utils.makeBitmap_ETC(mip.Width, mip.Height, mip.Pixels);
							break;

						case gl.GL_COMPRESSED_RGB8_ETC2:
						case gl.GL_COMPRESSED_RGBA8_ETC2_EAC:
							m_bitmaps[level] = Utils.makeBitmap_ETC2((uint)mip.Format, mip.Width, mip.Height, mip.Pixels);
							break;

						case gl.GL_COMPRESSED_RGB_S3TC_DXT1_EXT:
						case gl.GL_COMPRESSED_RGBA_S3TC_DXT1_EXT:
							m_bitmaps[level] = Utils.makeBitmap_DXT(1, mip.Width, mip.Height, mip.Pixels);
							break;
						case gl.GL_COMPRESSED_RGBA_S3TC_DXT3_EXT:
							m_bitmaps[level] = Utils.makeBitmap_DXT(3, mip.Width, mip.Height, mip.Pixels);
							break;
						case gl.GL_COMPRESSED_RGBA_S3TC_DXT5_EXT:
							m_bitmaps[level] = Utils.makeBitmap_DXT(5, mip.Width, mip.Height, mip.Pixels);
							break;

						case gl.GL_ALPHA:
							m_bitmaps[level] = Utils.makeBitmap_ALPHA(mip.Width, mip.Height, mip.Pixels, 0, false);
							break;

						case gl.GL_LUMINANCE:
							m_bitmaps[level] = Utils.makeBitmap_LUMINANCE(mip.Width, mip.Height, mip.Pixels, 0, false);
							break;

						case gl.GL_LUMINANCE_ALPHA:
							m_bitmaps[level] = Utils.makeBitmap_LUMINANCE_ALPHA(mip.Width, mip.Height, mip.Pixels, 0, false);
							break;

						default:
							Utils.assert(false);
							break;
					} // switch
				}
			}

			m_currentLevel = level;

			pictureBox.Image = m_bitmaps[level];
			pictureBox.Width = mip.Width;
			pictureBox.Height = mip.Height;

			labelSize.Text = mip.Width + " x " + mip.Height;
			labelFormat.Text = mip.FormatName;
			int imageSize = mip.calculateSize();
			labelLength.Text = Utils.getDynamicSize(mip.calculateSize());
		}

		private void listBoxMipmaps_SelectedIndexChanged(object sender, EventArgs e)
		{
			int index = listBoxMipmaps.SelectedIndex;
			if (index < 0 || index >= m_mipCount) return;

			showLevel(m_mipLevels[index]);
		}

		private void pictureBox_MouseMove(object sender, MouseEventArgs e)
		{
			if (m_currentLevel > -1)
			{
				Bitmap bmp = m_bitmaps[m_currentLevel];
				if (bmp != null)
				{
					Mipmap mip = m_tex.Mipmaps[m_currentLevel];
					int x = (int) ( 1.0f * e.X / mip.Width * bmp.Width );
					int y = (int) ( 1.0f * e.Y / mip.Height * bmp.Height );
					if (x >= bmp.Width) x = bmp.Width - 1;
					if (y >= bmp.Height) y = bmp.Height - 1;

					Color color = bmp.GetPixel(x, y);
					this.Parent.Text = getTitle() +
							string.Format(" :: Level = {0} :: (x, y) = ({1}, {2}) :: (R, G, B, A) = ({3}, {4}, {5}, {6})",
							m_currentLevel, e.X, e.Y, color.R, color.G, color.B, color.A);
				}
			}
		}

		private void pictureBox_MouseClick(object sender, MouseEventArgs e)
		{
			panelTexture.Focus();
		}

	}
}
