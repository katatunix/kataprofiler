using System;
using System.Collections.Generic;
using System.Text;

namespace KataProfiler
{
	class StateMachine
	{
		private List<Texture> m_listTextures = new List<Texture>();
		private List<Program> m_listPrograms = new List<Program>();
		private List<Shader> m_listShaders = new List<Shader>();
		private List<Vbo> m_listVbos = new List<Vbo>();

		public List<Texture> ListTextures { get { return m_listTextures; } }

		public List<Program> ListPrograms { get { return m_listPrograms; } }

		public List<Shader> ListShaders { get { return m_listShaders; } }

		public List<Vbo> ListVbos { get { return m_listVbos; } }

		//======================================================================================
		private uint[] m_listTexUnits_2D		= new uint[Client.MAX_TEX_UNITS_NUMBER];
		private uint[] m_listTexUnits_CubeMap	= new uint[Client.MAX_TEX_UNITS_NUMBER];
		public uint[] ListTexUnits_2D { get { return m_listTexUnits_2D; } }
		public uint[] ListTexUnits_CubeMap { get { return m_listTexUnits_CubeMap; } }

		private byte m_currentActiveTexUnit = 0;
		public byte CurrentActiveTexUnit
		{
			get	{ return m_currentActiveTexUnit; }
			set { m_currentActiveTexUnit = value; }
		}

		public uint CurrentTexId_2D
		{
			get { return m_listTexUnits_2D[m_currentActiveTexUnit]; }
			set { m_listTexUnits_2D[m_currentActiveTexUnit] = value; }
		}

		public uint CurrentTexId_CubeMap
		{
			get { return m_listTexUnits_CubeMap[m_currentActiveTexUnit]; }
			set { m_listTexUnits_CubeMap[m_currentActiveTexUnit] = value; }
		}

		private uint m_currentProgId = 0;
		public uint CurrentProgId { get { return m_currentProgId; } set { m_currentProgId = value; } }

		private uint m_currentVboId_ArrayBuffer = 0;
		public uint CurrentVboId_ArrayBuffer { get { return m_currentVboId_ArrayBuffer; } set { m_currentVboId_ArrayBuffer = value; } }

		private uint m_currentVboId_ElementArrayBuffer = 0;
		public uint CurrentVboId_ElementArrayBuffer { get { return m_currentVboId_ElementArrayBuffer; } set { m_currentVboId_ElementArrayBuffer = value; } }

		public Program CurrentProgramObject
		{
			get
			{
				if (m_currentProgId == 0) return null;
				return getProgramById(m_currentProgId);
			}
		}

		//======================================================================================

		public StateMachine()
		{
			reset();
		}

		public void reset()
		{
			m_listTextures.Clear();
			m_listPrograms.Clear();
			m_listShaders.Clear();
			m_listVbos.Clear();

			m_currentProgId = 0;
			m_currentActiveTexUnit = 0;
			m_currentVboId_ArrayBuffer = 0;
			m_currentVboId_ElementArrayBuffer = 0;

			for (int i = 0; i < m_listTexUnits_2D.Length; i++)
			{
				m_listTexUnits_2D[i] = 0;
			}

			for (int i = 0; i < m_listTexUnits_CubeMap.Length; i++)
			{
				m_listTexUnits_CubeMap[i] = 0;
			}
		}

		public Shader getShaderById(uint id)
		{
			foreach (Shader shader in m_listShaders)
			{
				if (shader.Id == id) return shader;
			}
			return null;
		}

		public Program getProgramById(uint id)
		{
			foreach (Program prog in m_listPrograms)
			{
				if (prog.Id == id) return prog;
			}
			return null;
		}

		public Texture getTextureById(uint id)
		{
			foreach (Texture tex in m_listTextures)
			{
				if (tex.Id == id) return tex;
			}
			return null;
		}

		public Vbo getVboById(uint id)
		{
			foreach (Vbo vbo in m_listVbos)
			{
				if (vbo.Id == id) return vbo;
			}
			return null;
		}

		//
		private List<uint> m_drawingTextures = new List<uint>();
		private static char[] m_sValueSeparate = new char[] { ',' };
		public List<uint> getDrawingTextures()
		{
			m_drawingTextures.Clear();
			
			Program prog = this.CurrentProgramObject;
			if (prog == null) return m_drawingTextures;

			for (int i = 0; i < prog.UniformsCount; i++)
			{
				Var uni = prog.Uniforms[i];
				if (uni.Type == gl.GL_SAMPLER_2D || uni.Type == gl.GL_SAMPLER_CUBE)
				{
					uint[] listTu = uni.Type == gl.GL_SAMPLER_2D ? m_listTexUnits_2D : m_listTexUnits_CubeMap;

					string[] texUnits = uni.Value.Split(m_sValueSeparate, StringSplitOptions.RemoveEmptyEntries);

					foreach (string texIdStr in texUnits)
					{
						uint tu = uint.Parse( texIdStr.Trim() );
						Utils.assert(tu >= 0 && tu < Client.MAX_TEX_UNITS_NUMBER);
						m_drawingTextures.Add(listTu[tu]);
					}
				}
			}
			return m_drawingTextures;
		}

		public string getTexUnitsOfTexId(uint texId)
		{
			Texture tex = getTextureById(texId);
			if (tex == null) return "";

			string result = null;
			uint[] listTu = tex.TexType == KPTextureType.TEX_2D ? m_listTexUnits_2D : m_listTexUnits_CubeMap;

			for (int i = 0; i < listTu.Length; i++)
			{
				if (listTu[i] == texId)
				{
					if (result == null) result = i.ToString();
					else result += ", " + i.ToString();
				}
			}
			return result;
		}

	}
}
