using System;
using System.Collections.Generic;
using System.Text;
using System.Diagnostics;
using System.Drawing;
using System.Drawing.Imaging;
using System.Runtime.InteropServices;
using System.Windows.Forms;

namespace KataProfiler
{
	//==========================================================================================
	// Delegates
	public delegate void CaptureCancelEventHandler();
	//==========================================================================================

	class Utils
	{
		private enum Platform
		{
			ANDROID,
			TIZEN,
			WIN32
		}


		private static Platform m_sCurrentPlatform = Platform.ANDROID;

		//==========================================================================================
		//==========================================================================================

		public static void gc()
		{
			GC.Collect();
			GC.WaitForPendingFinalizers();
		}

		public static void assert(bool b)
		{
			if (!b)
			{
				// Print the error
				//MessageBox.Show(null, Environment.StackTrace, "Assert error", MessageBoxButtons.OK, MessageBoxIcon.Error);
			}
		}

		public static void usePlatform_Android()
		{
			m_sCurrentPlatform = Platform.ANDROID;
		}

		public static void usePlatform_Tizen()
		{
			m_sCurrentPlatform = Platform.TIZEN;
		}

		public static void usePlatform_Win32()
		{
			m_sCurrentPlatform = Platform.WIN32;
		}

		public static string getCurrentDbTool()
		{
			switch (m_sCurrentPlatform)
			{
				case Platform.ANDROID:
					return "adb";
				case Platform.TIZEN:
					return "sdb";
				default:
					return null;
			}
		}

		public static bool startDbTool()
		{
			var tool = getCurrentDbTool();
			if (tool == null) return true;
			try
			{
				Process p = new Process();
				p.StartInfo.FileName = tool;
				p.StartInfo.Arguments = "start-server";

				p.Start();
				return p.WaitForExit(10000);
			}
			catch (Exception)
			{
				return false;
			}
		}

		public static bool runForwardCmd(int port)
		{
			var tool = getCurrentDbTool();
			if (tool == null) return true;

			if (!startDbTool()) return false;

			try
			{
				Process p = new Process();
				p.StartInfo.FileName = getCurrentDbTool();
				p.StartInfo.Arguments = string.Format("forward tcp:{0} tcp:{0}", port);

				p.StartInfo.CreateNoWindow = true;
				p.StartInfo.UseShellExecute = false;
				p.StartInfo.RedirectStandardOutput = true;

				p.Start();
				if (!p.WaitForExit(10000)) return false;

				return p.StandardOutput.ReadToEnd().Trim().Length == 0;
			}
			catch (Exception)
			{
				return false;
			}
		}

		public static void memcpy(byte[] dst, int dstOffset, byte[] src, int srcOffset, int len)
		{
			if (len <= 0) return;

			Buffer.BlockCopy(src, srcOffset, dst, dstOffset, len);
		}

		public static void memset(byte[] dst, int offset, int len, byte val)
		{
			for (int i = offset; i < offset + len; i++)
			{
				dst[i] = val;
			}
		}

		public static int setByte(int x, int offset, byte value)
		{
			x = ( ~(0xFF << (offset * 8)) ) & x;
			int tmp = (int)value;
			return ( tmp << (offset * 8) ) | x;
		}

		public static void int2bytes(int x, byte[] bytes)
		{
			if (bytes.Length < 4) return;
			int mask = 0xFF;
			bytes[0] = (byte)(x & mask);
			bytes[1] = (byte)((x & (mask << 8)) >> 8);
			bytes[2] = (byte)((x & (mask << 16)) >> 16);
			bytes[3] = (byte)((x & (mask << 24)) >> 24);
		}

		public static void uint2bytes(uint x, byte[] bytes)
		{
			if (bytes.Length < 4) return;
			int mask = 0xFF;
			bytes[0] = (byte)(x & mask);
			bytes[1] = (byte)((x & (mask << 8)) >> 8);
			bytes[2] = (byte)((x & (mask << 16)) >> 16);
			bytes[3] = (byte)((x & (mask << 24)) >> 24);
		}

		public static string getStringFromBytes(byte[] bytes)
		{
			return ASCIIEncoding.ASCII.GetString(bytes);
		}

		public static string getStringFromBytes(byte[] bytes, int offset, int count)
		{
			return ASCIIEncoding.ASCII.GetString(bytes, offset, count);
		}

		public static void getBytesFromString(string str, byte[] bytes)
		{
			ASCIIEncoding.ASCII.GetBytes(str, 0, str.Length, bytes, 0);
		}

		public static string getDynamicSize(int bytes)
		{
			if (bytes < 1024) return bytes + " bytes";
			if (bytes < 1024 * 1024) return ((double)bytes / 1024.0).ToString("F2") + " KB";
			if (bytes < 1024 * 1024 * 1024) return ((double)bytes / (1024.0 * 1024.0)).ToString("F2") + " MB";

			return ((double)bytes / (1024.0 * 1024.0 * 1024.0)).ToString("F2") + " GB";
		}

		public static int getSizeInBytesOfGLDataType(uint type)
		{
			switch (type)
			{
				case gl.GL_BYTE:
				case gl.GL_UNSIGNED_BYTE:
					return 1;
				case gl.GL_SHORT:
				case gl.GL_UNSIGNED_SHORT:
					return 2;
				case gl.GL_INT:
				case gl.GL_UNSIGNED_INT:
				case gl.GL_FLOAT:
				case gl.GL_FIXED:
					return 4;
			}
			assert(false);
			return 0;
		}

		public static string makeMatrixString(MyBinStream stream, int count, int size)
		{
			string res = "";
			for (int i = 0; i < count; i++)
			{
				res += "[";
				for (int row = 0; row < size; row++)
				{
					res += "(";
					for (int col = 0; col < size; col++)
					{
						res += stream.readFloat();
						if (col < size - 1) res += ", ";
					}
					res += ")";
					if (row < size - 1) res += ", ";
				}
				res += "]";
				if (i < count - 1) res += ", ";
			}
			return res;
		}

		public static IntPtr getIntPtr(byte[] buffer, int offset)
		{
			return System.Runtime.InteropServices.Marshal.UnsafeAddrOfPinnedArrayElement(buffer, offset);
		}

		public static bool isPowerOf2(int x)
		{
			return (x & (x - 1)) == 0;
		}

		#region Texture format

		public static Bitmap makeBitmap_RGB(int width, int height, byte[] data, int offset, bool flipY)
		{
			if (width <= 0 || height <= 0 || data == null || offset >= data.Length)
			{
				return null;
			}
			
			int bytesPerRow = 3 * width;
			int bytePerRowAligned = bytesPerRow;

			PixelFormat format = PixelFormat.Format24bppRgb;
			int len = bytePerRowAligned * height;
			Bitmap bmp = new Bitmap(width, height, format);
			BitmapData bitmapData = bmp.LockBits(new Rectangle(0, 0, width, height), ImageLockMode.ReadWrite, format);
			Marshal.Copy(data, offset, bitmapData.Scan0, len);
			bmp.UnlockBits(bitmapData);

			if (flipY) bmp.RotateFlip(RotateFlipType.RotateNoneFlipY);
			return bmp;
		}

		public static Bitmap makeBitmap_RGBA(int width, int height, byte[] data, int offset, bool flipY)
		{
			if (width <= 0 || height <= 0 || data == null || offset >= data.Length)
			{
				return null;
			}

			PixelFormat format = PixelFormat.Format32bppArgb;
			int len = width * height * 4;
			Bitmap bmp = new Bitmap(width, height, format);
			BitmapData bitmapData = bmp.LockBits(new Rectangle(0, 0, width, height), ImageLockMode.ReadWrite, format);
			Marshal.Copy(data, offset, bitmapData.Scan0, len);
			bmp.UnlockBits(bitmapData);

			if (flipY) bmp.RotateFlip(RotateFlipType.RotateNoneFlipY);
			return bmp;
		}

		public static Bitmap makeBitmap_PVR(int is2bpp, int width, int height, byte[] data)
		{
			if (width <= 0 || height <= 0 || data == null)
			{
				return null;
			}
			byte[] tmpBuffer = new byte[width * height * 4];
			unsafe
			{
				fixed (byte* src = data, dst = tmpBuffer)
				{
					TexDecomp.Class1.Decompress_PVRTC(src, is2bpp, width, height, dst, 1);
				}
			}

			return Utils.makeBitmap_RGBA(width, height, tmpBuffer, 0, false);
		}

		public static Bitmap makeBitmap_ETC(int width, int height, byte[] data)
		{
			if (width <= 0 || height <= 0 || data == null)
			{
				return null;
			}
			byte[] tmpBuffer = new byte[width * height * 4];
			unsafe
			{
				fixed (byte* src = data, dst = tmpBuffer)
				{
					TexDecomp.Class1.Decompress_ETC(dst, src, width, height, 1);
				}
			}

			return Utils.makeBitmap_RGBA(width, height, tmpBuffer, 0, false);
		}

		public static Bitmap makeBitmap_ETC2(uint srcFormat, int width, int height, byte[] data)
		{
			if (width <= 0 || height <= 0 || data == null)
			{
				return null;
			}
			byte[] tmpBuffer = new byte[width * height * 4];
			unsafe
			{
				fixed (byte* src = data, dst = tmpBuffer)
				{
					TexDecomp.Class1.Decompress_ETC2(srcFormat, dst, src, width, height, 1);
				}
			}

			return Utils.makeBitmap_RGBA(width, height, tmpBuffer, 0, false);
		}

		public static Bitmap makeBitmap_DXT(int dxtType, int width, int height, byte[] data)
		{
			if (width <= 0 || height <= 0 || data == null)
			{
				return null;
			}
			byte[] tmpBuffer = new byte[width * height * 4];
			unsafe
			{
				fixed (byte* src = data, dst = tmpBuffer)
				{
					TexDecomp.Class1.Decompress_DXT(dxtType, dst, src, width, height, 1);
				}
			}

			return Utils.makeBitmap_RGBA(width, height, tmpBuffer, 0, false);
		}

		public static Bitmap makeBitmap_ALPHA(int width, int height, byte[] data, int offset, bool flipY)
		{
			if (width <= 0 || height <= 0 || data == null || offset >= data.Length)
			{
				return null;
			}
			Bitmap bmp = new Bitmap(width, height);
			for (int x = 0; x < width; x++)
			{
				for (int y = 0; y < height; y++)
				{
					int y2 = flipY ? height - 1 - y : y;

					int k = offset + (y2 * width + x);

					if (data == null)
					{
						bmp.SetPixel(x, y, Color.FromArgb(0, 0, 0, 0));
					}
					else
					{
						bmp.SetPixel(x, y, Color.FromArgb(255, data[k], data[k], data[k]));
					}
				}
			}

			return bmp;
		}

		public static Bitmap makeBitmap_LUMINANCE(int width, int height, byte[] data, int offset, bool flipY)
		{
			if (width <= 0 || height <= 0 || data == null || offset >= data.Length)
			{
				return null;
			}
			Bitmap bmp = new Bitmap(width, height);
			for (int x = 0; x < width; x++)
			{
				for (int y = 0; y < height; y++)
				{
					int y2 = flipY ? height - 1 - y : y;

					int k = offset + (y2 * width + x);

					if (data == null)
					{
						bmp.SetPixel(x, y, Color.FromArgb(0, 0, 0, 0));
					}
					else
					{
						bmp.SetPixel(x, y, Color.FromArgb(255, data[k], data[k], data[k]));
					}
				}
			}
			return bmp;
		}

		public static Bitmap makeBitmap_LUMINANCE_ALPHA(int width, int height, byte[] data, int offset, bool flipY)
		{
			if (width <= 0 || height <= 0 || data == null || offset >= data.Length)
			{
				return null;
			}
			Bitmap bmp = new Bitmap(width, height);
			for (int x = 0; x < width; x++)
			{
				for (int y = 0; y < height; y++)
				{
					int y2 = flipY ? height - 1 - y : y;

					int k = offset + (y2 * width + x) * 2;

					if (data == null)
					{
						bmp.SetPixel(x, y, Color.FromArgb(0, 0, 0, 0));
					}
					else
					{
						bmp.SetPixel(x, y, Color.FromArgb(data[k + 1], data[k], data[k], data[k]));
					}
				}
			}
			return bmp;
		}

		public static Bitmap makeBitmap_RGBA4444(int width, int height, byte[] data, int offset, bool flipY)
		{
			if (width <= 0 || height <= 0 || data == null || offset >= data.Length)
			{
				return null;
			}
			Bitmap bmp = new Bitmap(width, height);
			for (int x = 0; x < width; x++)
			{
				for (int y = 0; y < height; y++)
				{
					int y2 = flipY ? height - 1 - y : y;

					int k = offset + (y2 * width + x) * 2;

					byte p = data[k];
					byte q = data[k + 1];

					int R = (int)CONVERT(p >> 4, 4, 8);
					int G = (int)CONVERT(p & 0xF, 4, 8);
					int B = (int)CONVERT(q >> 4, 4, 8);
					int A = (int)CONVERT(q & 0xF, 4, 8);

					if (data == null)
					{
						bmp.SetPixel(x, y, Color.FromArgb(0, 0, 0, 0));
					}
					else
					{
						bmp.SetPixel(x, y, Color.FromArgb(A, R, G, B));
					}
				}
			}
			return bmp;
		}

		public static Bitmap makeBitmap_RGBA5551(int width, int height, byte[] data, int offset, bool flipY)
		{
			if (width <= 0 || height <= 0 || data == null || offset >= data.Length)
			{
				return null;
			}
			Bitmap bmp = new Bitmap(width, height);
			for (int x = 0; x < width; x++)
			{
				for (int y = 0; y < height; y++)
				{
					int y2 = flipY ? height - 1 - y : y;

					int k = offset + (y2 * width + x) * 2;

					UInt16 p = (UInt16)data[k];
					UInt16 q = (UInt16)data[k + 1];

					UInt16 value = (UInt16)( (p << 8) | q );

					int R = (int)CONVERT(value >> 11, 5, 8);
					int G = (int)CONVERT((value >> 6) & 0x1F, 5, 8);
					int B = (int)CONVERT((value >> 1) & 0x1F, 5, 8);
					int A = (int)CONVERT(value & 0x1, 1, 8);

					if (data == null)
					{
						bmp.SetPixel(x, y, Color.FromArgb(0, 0, 0, 0));
					}
					else
					{
						bmp.SetPixel(x, y, Color.FromArgb(A, R, G, B));
					}
				}
			}
			return bmp;
		}

		public static Bitmap makeBitmap_RGB565(int width, int height, byte[] data, int offset, bool flipY)
		{
			if (width <= 0 || height <= 0 || data == null || offset >= data.Length)
			{
				return null;
			}
			Bitmap bmp = new Bitmap(width, height);
			for (int x = 0; x < width; x++)
			{
				for (int y = 0; y < height; y++)
				{
					int y2 = flipY ? height - 1 - y : y;

					int k = offset + (y2 * width + x) * 2;

					UInt16 p = (UInt16)data[k];
					UInt16 q = (UInt16)data[k + 1];

					UInt16 value = (UInt16)( (p << 8) | q );

					int R = (int)CONVERT( (value >> 11) & 0x1F, 5, 8 );
					int G = (int)CONVERT( (value >> 5) & 0x3F, 6, 8 );
					int B = (int)CONVERT( value & 0x1F, 5, 8 );
					int A = 255;

					bmp.SetPixel(x, y, Color.FromArgb(A, R, G, B));
				}
			}
			return bmp;
		}

		#endregion

		public static void convertTexSubPixel(byte[] dst, int dstOffset, byte[] src, int srcOffset,
			uint format, uint dstType, uint srcType)
		{
			int dst_bytesPP = Mipmap.getTexBPP((int)format, dstType) / 8;
			if (dstType == srcType)
			{
				Utils.memcpy(dst, dstOffset, src, srcOffset, dst_bytesPP);
				return;
			}

			int src_bytesPP = Mipmap.getTexBPP((int)format, srcType) / 8;

			if (format == gl.GL_RGBA)
			{
				if (srcType == gl.GL_UNSIGNED_BYTE && dstType == gl.GL_UNSIGNED_SHORT_4_4_4_4)
				{
					UInt16 dst16;
						
					// Note: swap RB
					dst16 =		(UInt16)(CONVERT(src[srcOffset + 2],	8, 4) << 12);
					dst16 |=	(UInt16)(CONVERT(src[srcOffset + 1],	8, 4) <<  8);
					dst16 |=	(UInt16)(CONVERT(src[srcOffset    ],	8, 4) <<  4);
					dst16 |=	(UInt16)(CONVERT(src[srcOffset + 3],	8, 4)      );

					dst[dstOffset]		= (byte)((dst16 >> 8) & 0xFF);
					dst[dstOffset + 1]	= (byte)((dst16     ) & 0xFF);
				}
				else if (srcType == gl.GL_UNSIGNED_BYTE && dstType == gl.GL_UNSIGNED_SHORT_5_5_5_1)
				{
					UInt16 dst16;

					// Note: swap RB
					dst16 =		(UInt16)(CONVERT(src[srcOffset + 2],	8, 5) << 11);
					dst16 |=	(UInt16)(CONVERT(src[srcOffset + 1],	8, 5) <<  6);
					dst16 |=	(UInt16)(CONVERT(src[srcOffset    ],	8, 5) <<  1);
					dst16 |=	(UInt16)(CONVERT(src[srcOffset + 3],	8, 1)      );

					dst[dstOffset]		= (byte)((dst16 >> 8) & 0xFF);
					dst[dstOffset + 1]	= (byte)((dst16     ) & 0xFF);
				}

				else if (srcType == gl.GL_UNSIGNED_SHORT_4_4_4_4 && dstType == gl.GL_UNSIGNED_BYTE)
				{
					UInt16 tmp0 = (UInt16)src[srcOffset];
					UInt16 tmp1 = (UInt16)src[srcOffset + 1];
					UInt16 src16 = (UInt16)((tmp0 << 8) | tmp1);

					// Note: swap RB
					dst[dstOffset + 2]	= (byte)CONVERT((src16 >> 12) & 0xF, 4, 8);
					dst[dstOffset + 1]	= (byte)CONVERT((src16 >>  8) & 0xF, 4, 8);
					dst[dstOffset    ]	= (byte)CONVERT((src16 >>  4) & 0xF, 4, 8);
					dst[dstOffset + 3]	= (byte)CONVERT((src16      ) & 0xF, 4, 8);
				}
				else if (srcType == gl.GL_UNSIGNED_SHORT_4_4_4_4 && dstType == gl.GL_UNSIGNED_SHORT_5_5_5_1)
				{
					UInt16 tmp0 = (UInt16)src[srcOffset];
					UInt16 tmp1 = (UInt16)src[srcOffset + 1];
					UInt16 src16 = (UInt16)((tmp0 << 8) | tmp1);

					UInt16 dst16;

					dst16 =		(UInt16)(CONVERT((src16 >> 12) & 0xF, 4, 5) << 11);
					dst16 |=	(UInt16)(CONVERT((src16 >>  8) & 0xF, 4, 5) <<  6);
					dst16 |=	(UInt16)(CONVERT((src16 >>  4) & 0xF, 4, 5) <<  1);
					dst16 |=	(UInt16)(CONVERT((src16      ) & 0xF, 4, 1)      );

					dst[dstOffset]		= (byte)((dst16 >> 8) & 0xFF);
					dst[dstOffset + 1]	= (byte)((dst16     ) & 0xFF);
				}

				else if (srcType == gl.GL_UNSIGNED_SHORT_5_5_5_1 && dstType == gl.GL_UNSIGNED_BYTE)
				{
					UInt16 tmp0 = (UInt16)src[srcOffset];
					UInt16 tmp1 = (UInt16)src[srcOffset + 1];
					UInt16 src16 = (UInt16)((tmp0 << 8) | tmp1);

					// Note: swap RB
					dst[dstOffset + 2]	= (byte)CONVERT((src16 >> 11) & 0x1F, 5, 8);
					dst[dstOffset + 1]	= (byte)CONVERT((src16 >>  6) & 0x1F, 5, 8);
					dst[dstOffset    ]	= (byte)CONVERT((src16 >>  1) & 0x1F, 5, 8);
					dst[dstOffset + 3]	= (byte)CONVERT((src16      ) & 0x01, 1, 8);
				}
				else if (srcType == gl.GL_UNSIGNED_SHORT_5_5_5_1 && dstType == gl.GL_UNSIGNED_SHORT_4_4_4_4)
				{
					UInt16 tmp0 = (UInt16)src[srcOffset];
					UInt16 tmp1 = (UInt16)src[srcOffset + 1];
					UInt16 src16 = (UInt16)((tmp0 << 8) | tmp1);

					UInt16 dst16;

					dst16 =		(UInt16)(CONVERT((src16 >> 11) & 0x1F, 5, 4) << 12);
					dst16 |=	(UInt16)(CONVERT((src16 >>  6) & 0x1F, 5, 4) <<  8);
					dst16 |=	(UInt16)(CONVERT((src16 >>  1) & 0x1F, 5, 4) <<  4);
					dst16 |=	(UInt16)(CONVERT((src16      ) & 0x01, 1, 4)      );

					dst[dstOffset]		= (byte)((dst16 >> 8) & 0xFF);
					dst[dstOffset + 1]	= (byte)((dst16     ) & 0xFF);
				}
			}
			else // (format == gl2.GL_RGB)
			{
				if (srcType == gl.GL_UNSIGNED_BYTE && dstType == gl.GL_UNSIGNED_SHORT_5_6_5)
				{
					UInt16 dst16;
						
					// Note: swap RB
					dst16 =		(UInt16)(CONVERT(src[srcOffset + 2], 8, 5) << 11);
					dst16 |=	(UInt16)(CONVERT(src[srcOffset + 1], 8, 6) <<  5);
					dst16 |=	(UInt16)(CONVERT(src[srcOffset    ], 8, 5)      );

					dst[dstOffset    ]	= (byte)((dst16 >> 8) & 0xFF);
					dst[dstOffset + 1]	= (byte)((dst16     ) & 0xFF);
				}
				else if (srcType == gl.GL_UNSIGNED_SHORT_5_6_5 && dstType == gl.GL_UNSIGNED_BYTE)
				{
					UInt16 tmp0 = (UInt16)src[srcOffset];
					UInt16 tmp1 = (UInt16)src[srcOffset + 1];
					UInt16 src16 = (UInt16)((tmp0 << 8) | tmp1);//25700

					// Note: swap RB
					dst[dstOffset + 2] = (byte)CONVERT((src16 >> 11) & 0x1F, 5, 8);
					dst[dstOffset + 1] = (byte)CONVERT((src16 >>  5) & 0x3F, 6, 8);
					dst[dstOffset    ] = (byte)CONVERT((src16      ) & 0x1F, 5, 8);
				}
			}
		}

		public static UInt16 CONVERT(UInt16 srcValue, int srcBits, int dstBits)
		{
			return (UInt16)(
				srcValue *
				(UInt16)((1 << dstBits) - 1) /
				(UInt16)((1 << srcBits) - 1)
			);
		}

		public static UInt16 CONVERT(byte srcValue, int srcBits, int dstBits)
		{
			return CONVERT((UInt16)srcValue, srcBits, dstBits);
		}

		public static UInt16 CONVERT(int srcValue, int srcBits, int dstBits)
		{
			return CONVERT((UInt16)srcValue, srcBits, dstBits);
		}

	}
}
