using System;
using System.Collections.Generic;
using System.Text;

namespace KataProfiler
{
	class Shader : GlObject
	{
		public Shader() : base()
		{
			clearData();
		}

		public Shader(uint id) : base(id)
		{
			clearData();
		}

		public void copyFrom(Shader shader)
		{
			m_id = shader.Id;
			m_type = shader.Type;
			m_source = shader.Source;
		}

		public override void clearData()
		{
			m_type = 0;
			m_source = null;
		}

		public override void fromMessage(Message msg)
		{
			Utils.assert(msg.Length >= 4 * 2);
			clearData();

			MyBinStream stream = new MyBinStream(msg.Data);
			m_id = stream.readUInt();
			m_type = stream.readUInt();
			m_source = stream.readString();
			stream.close();
		}

		public override bool isKindOf(KPGLObjectKind kind)
		{
			return kind == KPGLObjectKind.SHADER;
		}

		private string m_source;
		public string Source { get { return m_source; } set { m_source = value; } }

		private uint m_type;
		public uint Type { get { return m_type; } set { m_type = value; } }
	}
}
