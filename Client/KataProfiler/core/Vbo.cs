using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace KataProfiler
{
	class Vbo : GlObject
	{
		private int m_size;
		public int Size
		{
			get { return m_size; }
		}

		private int m_dataAddress;
		public int DataAddress
		{
			get { return m_dataAddress; }
		}

		private uint m_usage;
		public uint Usage
		{
			get { return m_usage; }
		}

		public Vbo() : base()
		{
			clearData();
		}

		public Vbo(uint id) : base(id)
		{
			clearData();
		}

		public override void clearData()
		{
			m_size			= 0;
			m_dataAddress	= 0;
			m_usage			= 0;
		}

		public void copyFrom(Vbo other)
		{
			clearData();

			m_id			= other.Id;
			m_size			= other.Size;
			m_dataAddress	= other.DataAddress;
			m_usage			= other.Usage;
		}

		public void on_glBufferData(int size, int dataAddress, uint usage)
		{
			m_size			= size;
			m_dataAddress	= dataAddress;
			m_usage			= usage;
		}

		public override void fromMessage(Message msg)
		{
			clearData();

			MyBinStream stream = new MyBinStream(msg.Data);

			m_id			= stream.readUInt();
			m_size			= stream.readInt();
			m_usage			= stream.readUInt();
			m_dataAddress	= stream.readInt();
			
			stream.close();
		}

		public override bool isKindOf(KPGLObjectKind kind)
		{
			return kind == KPGLObjectKind.VBO;
		}
	}
}
