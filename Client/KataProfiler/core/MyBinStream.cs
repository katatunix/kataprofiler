using System;
using System.Collections.Generic;
using System.Text;

using System.IO;

namespace KataProfiler
{
	public class MyBinStream
	{
		private MemoryStream m_memoryStream;
		private BinaryReader m_reader;
		private byte[] m_bytes;
		private int m_offset;
		private int m_length;

		public MyBinStream(byte[] bytes) : this(bytes, bytes.Length)
		{
			
		}

		public MyBinStream(byte[] bytes, int length) : this(bytes, 0, length)
		{

		}

		public MyBinStream(byte[] bytes, int offset, int length)
		{
			m_offset = offset;
			m_bytes = bytes;
			m_length = length;
			m_memoryStream = new MemoryStream(bytes, offset, length);
			m_reader = new BinaryReader(m_memoryStream);
		}

		public int CurrentPosition
		{
			get
			{
				return (int)m_reader.BaseStream.Position;
			}
		}

		public void close()
		{
			m_bytes = null;
			m_length = 0;
			m_reader.Close();
			m_memoryStream.Close();
		}

		public byte readByte()
		{
			return m_reader.ReadByte();
		}

		public sbyte readSByte()
		{
			return m_reader.ReadSByte();
		}

		public Int16 readShort()
		{
			return m_reader.ReadInt16();
		}

		public UInt16 readUShort()
		{
			return m_reader.ReadUInt16();
		}

		public int readInt()
		{
			return m_reader.ReadInt32();
		}

		public uint readUInt()
		{
			return m_reader.ReadUInt32();
		}

		public float readFloat()
		{
			return m_reader.ReadSingle();
		}

		public int readBytes(byte[] bytes, int offset, int count)
		{
			return m_reader.Read(bytes, offset, count);
		}

		public string readString(int length)
		{
			if (length <= 0) return "";
			string result = Utils.getStringFromBytes(m_bytes, m_offset + (int)m_reader.BaseStream.Position, length);
			m_reader.BaseStream.Seek(length, SeekOrigin.Current);
			return result;
		}

		public string readString()
		{
			return readString(m_length - (int)m_reader.BaseStream.Position);
		}

		public void skip(int byteNumber)
		{
			m_reader.BaseStream.Seek(byteNumber, SeekOrigin.Current);
		}

		public int remainBytes()
		{
			return m_length - (int)m_reader.BaseStream.Position;
		}
	}
}
