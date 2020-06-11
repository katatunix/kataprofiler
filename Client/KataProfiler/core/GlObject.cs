using System;
using System.Collections.Generic;
using System.Text;

namespace KataProfiler
{
	public enum KPGLObjectKind
	{
		TEXTURE = 0,
		PROGRAM,
		SHADER,
		VBO,
		NONE
	}

	public abstract class GlObject
	{
		public abstract void clearData();
		public abstract void fromMessage(Message msg);
		public abstract bool isKindOf(KPGLObjectKind kind);

		public GlObject()
		{
			m_id = 0;
			m_lifeTimeBegin = 0;
			m_lifeTimeEnd = 0;
		}

		public GlObject(uint id)
		{
			m_id = id;
			m_lifeTimeBegin = 0;
			m_lifeTimeEnd = 0;
		}

		public bool isLiveAt(int indexCommand)
		{
			return m_lifeTimeBegin <= indexCommand && indexCommand <= m_lifeTimeEnd;
		}

		public uint Id
		{
			get { return m_id; }
			set { m_id = value; }
		}

		public int LifeTimeBegin
		{
			get { return m_lifeTimeBegin; }
			set { m_lifeTimeBegin = value; }
		}

		public int LifeTimeEnd
		{
			get { return m_lifeTimeEnd; }
			set { m_lifeTimeEnd = value; }
		}

		protected uint m_id;
		protected int m_lifeTimeBegin;
		protected int m_lifeTimeEnd;
	}
}
