using System;
using System.Collections.Generic;
using System.Text;

namespace KataProfiler
{
	public class Var
	{
		#region Properties
		private string m_name;
		public string Name { get { return m_name; } set { m_name = value; } }

		private string m_value;
		public string Value { get { return m_value; } set { m_value = value; } }

		private int m_location;
		public int Location { get { return m_location; } set { m_location = value; } }

		private int m_size;
		public int Size { get { return m_size; } set { m_size = value; } }

		private uint m_type;
		public uint Type { get { return m_type; } set { m_type = value; } }
		#endregion

		public Var()
		{
			m_name		= null;
			m_value		= null;
			m_location	= -1;
			m_size		= -1;
			m_type		= 0;
		}

		public void copyFrom(Var var)
		{
			m_name		= var.Name;
			m_value		= var.Value;
			m_location	= var.Location;
			m_size		= var.Size;
			m_type		= var.Type;
		}

		public string toString()
		{
			if (string.IsNullOrEmpty(m_value))
				return "● " + m_location + ". " + gl.getString(m_type) + " " + m_name;
			else
				return "● " + m_location + ". " + gl.getString(m_type) + " " + m_name + " = " + m_value;
		}
	}

	public class Program : GlObject
	{
		public const int MAX_ATTRIBUTES_NUMBER = 128;
		public const int MAX_UNIFORMS_NUMBER = 128;

		public Program() : base()
		{
			clearData();
			init();
		}

		public Program(uint id) : base(id)
		{
			clearData();
			init();
		}

		private void init()
		{
			m_attributes = new Var[MAX_ATTRIBUTES_NUMBER];
			for (int i = 0; i < MAX_ATTRIBUTES_NUMBER; i++) m_attributes[i] = new Var();
			m_uniforms = new Var[MAX_UNIFORMS_NUMBER];
			for (int i = 0; i < MAX_UNIFORMS_NUMBER; i++) m_uniforms[i] = new Var();
		}

		public override void clearData()
		{
			m_vsId				= 0;
			m_fsId				= 0;
			m_attributesCount	= 0;
			m_uniformsCount		= 0;
		}

		public override void fromMessage(Message msg)
		{
			Utils.assert(msg.Type == (int)KPMessageType.KMT_OBJECT_PROGRAM);

			clearData();

			MyBinStream stream = new MyBinStream(msg.Data);
			this.fromStream(stream);
			stream.close();
		}

		public void fromBytes(byte[] bytes, int offset, int count)
		{
			MyBinStream stream = new MyBinStream(bytes, offset, count);
			this.fromStream(stream);
			stream.close();
		}

		public void fromStream(MyBinStream stream)
		{
			m_id		= stream.readUInt();
			m_vsId		= stream.readUInt();
			m_fsId		= stream.readUInt();

			//
			m_attributesCount = stream.readInt();
			for (int i = 0; i < m_attributesCount; i++)
			{
				Var var = m_attributes[i];

				var.Location = stream.readInt();
				var.Size = stream.readInt();
				var.Type = stream.readUInt();

				int strLen = stream.readInt();
				var.Name = stream.readString(strLen);
			}

			//
			m_uniformsCount = stream.readInt();
			
			for (int i = 0; i < m_uniformsCount; i++)
			{
				Var var = m_uniforms[i];

				var.Location = stream.readInt();
				var.Size = stream.readInt();
				var.Type = stream.readUInt();
				
				int strLen = stream.readInt();
				var.Name = stream.readString(strLen);

				int dataLen = stream.readInt();
				string res = "";

				if (dataLen > 0)
				{
					switch (var.Type)
					{
						#region FLOAT
						case gl.GL_FLOAT:
							{
								Utils.assert(dataLen % 4 == 0);
								int count = dataLen / 4;
								for (int j = 0; j < count; j++)
								{
									res += stream.readFloat();
									if (j < count - 1) res += ", ";
								}
								break;
							}
						case gl.GL_FLOAT_VEC2:
							{
								Utils.assert(dataLen % 8 == 0);
								int count = dataLen / 8;
								for (int j = 0; j < count; j++)
								{
									res += string.Format("({0}, {1})", stream.readFloat(), stream.readFloat());
									if (j < count - 1) res += ", ";
								}
								break;
							}
						case gl.GL_FLOAT_VEC3:
							{
								Utils.assert(dataLen % 12 == 0);
								int count = dataLen / 12;
								for (int j = 0; j < count; j++)
								{
									res += string.Format("({0}, {1}, {2})", stream.readFloat(), stream.readFloat(), stream.readFloat());
									if (j < count - 1) res += ", ";
								}
								break;
							}
						case gl.GL_FLOAT_VEC4:
							{
								Utils.assert(dataLen % 16 == 0);
								int count = dataLen / 16;
								for (int j = 0; j < count; j++)
								{
									res += string.Format("({0}, {1}, {2}, {3})", stream.readFloat(), stream.readFloat(), stream.readFloat(), stream.readFloat());
									if (j < count - 1) res += ", ";
								}
								break;
							}
						#endregion

						#region INT, BOOL, SAMPLER
						case gl.GL_INT:
						case gl.GL_SAMPLER_2D:
						case gl.GL_SAMPLER_3D:
						case gl.GL_SAMPLER_CUBE:
						case gl.GL_BOOL:
							{
								Utils.assert(dataLen % 4 == 0);
								int count = dataLen / 4;
								for (int j = 0; j < count; j++)
								{
									res += stream.readInt();
									if (j < count - 1) res += ", ";
								}
								break;
							}
						case gl.GL_INT_VEC2:
						case gl.GL_BOOL_VEC2:
							{
								Utils.assert(dataLen % 8 == 0);
								int count = dataLen / 8;
								for (int j = 0; j < count; j++)
								{
									res += string.Format("({0}, {1})", stream.readInt(), stream.readInt());
									if (j < count - 1) res += ", ";
								}
								break;
							}
						case gl.GL_INT_VEC3:
						case gl.GL_BOOL_VEC3:
							{
								Utils.assert(dataLen % 12 == 0);
								int count = dataLen / 12;
								for (int j = 0; j < count; j++)
								{
									res += string.Format("({0}, {1}, {2})", stream.readInt(), stream.readInt(), stream.readInt());
									if (j < count - 1) res += ", ";
								}
								break;
							}
						case gl.GL_INT_VEC4:
						case gl.GL_BOOL_VEC4:
							{
								Utils.assert(dataLen % 16 == 0);
								int count = dataLen / 16;
								for (int j = 0; j < count; j++)
								{
									res += string.Format("({0}, {1}, {2}, {3})", stream.readInt(), stream.readInt(), stream.readInt(), stream.readInt());
									if (j < count - 1) res += ", ";
								}
								break;
							}
						#endregion

						#region MATRIX
						case gl.GL_FLOAT_MAT2:
						case gl.GL_FLOAT_MAT3:
						case gl.GL_FLOAT_MAT4:
							{
								int size = (var.Type == gl.GL_FLOAT_MAT2) ? 2 : (var.Type == gl.GL_FLOAT_MAT3 ? 3 : 4);
								int bytes = size * size * 4;
								Utils.assert(dataLen % bytes == 0);
								int count = dataLen / bytes;
								res = Utils.makeMatrixString(stream, count, size);
								break;
							}
						#endregion

						default:
							{
								Utils.assert(false);
								break;
							}
					} // switch (var.Type)
				}

				var.Value = res;
			}
		}

		public override bool isKindOf(KPGLObjectKind kind)
		{
			return kind == KPGLObjectKind.PROGRAM;
		}

		public void copyFrom(Program prog)
		{
			m_id = prog.Id;
			m_vsId = prog.VsId;
			m_fsId = prog.FsId;

			m_attributesCount = prog.AttributesCount;
			m_uniformsCount = prog.UniformsCount;

			for (int i = 0; i < m_attributesCount; i++)
			{
				m_attributes[i].copyFrom(prog.Attributes[i]);
			}

			for (int i = 0; i < m_uniformsCount; i++)
			{
				m_uniforms[i].copyFrom(prog.Uniforms[i]);
			}
		}

		#region on_glUniform

		public void on_glUniform1f(MyBinStream stream)
		{
			int location = stream.readInt();
			if (location < 0) return;
			for (int i = 0; i < m_uniformsCount; i++)
			{
				Var uni = m_uniforms[i];

				if (uni.Location == location)
				{
					uni.Value = string.Format("{0}", stream.readFloat());
					break;
				}
			}
		}
		public void on_glUniform1fv(MyBinStream stream)
		{
			int location = stream.readInt();
			int count = stream.readInt();
			if (location < 0 || count <= 0) return;
			for (int i = 0; i < m_uniformsCount; i++)
			{
				Var uni = m_uniforms[i];

				if (uni.Location == location)
				{
					var res = "";
					for (int j = 0; j < count; j++)
					{
						res += string.Format("{0}", stream.readFloat());
						if (j < count - 1) res += ", ";
					}
					uni.Value = res;
					break;
				}
			}
		}
		public void on_glUniform1i(MyBinStream stream)
		{
			int location = stream.readInt();
			if (location < 0) return;
			for (int i = 0; i < m_uniformsCount; i++)
			{
				Var uni = m_uniforms[i];

				if (uni.Location == location)
				{
					uni.Value = string.Format("{0}", stream.readInt());
					break;
				}
			}
		}
		public void on_glUniform1iv(MyBinStream stream)
		{
			int location = stream.readInt();
			int count = stream.readInt();
			if (location < 0 || count <= 0) return;
			for (int i = 0; i < m_uniformsCount; i++)
			{
				Var uni = m_uniforms[i];

				if (uni.Location == location)
				{
					var res = "";
					for (int j = 0; j < count; j++)
					{
						res += string.Format("{0}", stream.readInt());
						if (j < count - 1) res += ", ";
					}
					uni.Value = res;
					break;
				}
			}
		}

		public void on_glUniform2f(MyBinStream stream)
		{
			int location = stream.readInt();
			if (location < 0) return;
			for (int i = 0; i < m_uniformsCount; i++)
			{
				Var uni = m_uniforms[i];

				if (uni.Location == location)
				{
					uni.Value = string.Format("{0}, {1}", stream.readFloat(), stream.readFloat());
					break;
				}
			}
		}
		public void on_glUniform2fv(MyBinStream stream)
		{
			int location = stream.readInt();
			int count = stream.readInt();
			if (location < 0 || count <= 0) return;
			for (int i = 0; i < m_uniformsCount; i++)
			{
				Var uni = m_uniforms[i];

				if (uni.Location == location)
				{
					var res = "";
					for (int j = 0; j < count; j++)
					{
						res += string.Format("({0}, {1})", stream.readFloat(), stream.readFloat());
						if (j < count - 1) res += ", ";
					}
					uni.Value = res;
					break;
				}
			}
		}
		public void on_glUniform2i(MyBinStream stream)
		{
			int location = stream.readInt();
			if (location < 0) return;
			for (int i = 0; i < m_uniformsCount; i++)
			{
				Var uni = m_uniforms[i];

				if (uni.Location == location)
				{
					uni.Value = string.Format("{0}, {1}", stream.readInt(), stream.readInt());
					break;
				}
			}
		}
		public void on_glUniform2iv(MyBinStream stream)
		{
			int location = stream.readInt();
			int count = stream.readInt();
			if (location < 0 || count <= 0) return;
			for (int i = 0; i < m_uniformsCount; i++)
			{
				Var uni = m_uniforms[i];

				if (uni.Location == location)
				{
					var res = "";
					for (int j = 0; j < count; j++)
					{
						res += string.Format("({0}, {1})", stream.readInt(), stream.readInt());
						if (j < count - 1) res += ", ";
					}
					uni.Value = res;
					break;
				}
			}
		}

		public void on_glUniform3f(MyBinStream stream)
		{
			int location = stream.readInt();
			if (location < 0) return;
			for (int i = 0; i < m_uniformsCount; i++)
			{
				Var uni = m_uniforms[i];

				if (uni.Location == location)
				{
					uni.Value = string.Format("{0}, {1}, {2}", stream.readFloat(), stream.readFloat(), stream.readFloat());
					break;
				}
			}
		}
		public void on_glUniform3fv(MyBinStream stream)
		{
			int location = stream.readInt();
			int count = stream.readInt();
			if (location < 0 || count <= 0) return;
			for (int i = 0; i < m_uniformsCount; i++)
			{
				Var uni = m_uniforms[i];

				if (uni.Location == location)
				{
					var res = "";
					for (int j = 0; j < count; j++)
					{
						res += string.Format("({0}, {1}, {2})", stream.readFloat(), stream.readFloat(), stream.readFloat());
						if (j < count - 1) res += ", ";
					}
					uni.Value = res;
					break;
				}
			}
		}
		public void on_glUniform3i(MyBinStream stream)
		{
			int location = stream.readInt();
			if (location < 0) return;
			for (int i = 0; i < m_uniformsCount; i++)
			{
				Var uni = m_uniforms[i];

				if (uni.Location == location)
				{
					uni.Value = string.Format("{0}, {1}, {2}", stream.readInt(), stream.readInt(), stream.readInt());
					break;
				}
			}
		}
		public void on_glUniform3iv(MyBinStream stream)
		{
			int location = stream.readInt();
			int count = stream.readInt();
			if (location < 0 || count <= 0) return;
			for (int i = 0; i < m_uniformsCount; i++)
			{
				Var uni = m_uniforms[i];

				if (uni.Location == location)
				{
					var res = "";
					for (int j = 0; j < count; j++)
					{
						res += string.Format("({0}, {1}, {2})", stream.readInt(), stream.readInt(), stream.readInt());
						if (j < count - 1) res += ", ";
					}
					uni.Value = res;
					break;
				}
			}
		}

		public void on_glUniform4f(MyBinStream stream)
		{
			int location = stream.readInt();
			if (location < 0) return;
			for (int i = 0; i < m_uniformsCount; i++)
			{
				Var uni = m_uniforms[i];

				if (uni.Location == location)
				{
					uni.Value = string.Format("{0}, {1}, {2}, {3}", stream.readFloat(), stream.readFloat(), stream.readFloat(), stream.readFloat());
					break;
				}
			}
		}
		public void on_glUniform4fv(MyBinStream stream)
		{
			int location = stream.readInt();
			int count = stream.readInt();
			if (location < 0 || count <= 0) return;
			for (int i = 0; i < m_uniformsCount; i++)
			{
				Var uni = m_uniforms[i];

				if (uni.Location == location)
				{
					var res = "";
					for (int j = 0; j < count; j++)
					{
						res += string.Format("({0}, {1}, {2}, {3})", stream.readFloat(), stream.readFloat(), stream.readFloat(), stream.readFloat());
						if (j < count - 1) res += ", ";
					}
					uni.Value = res;
					break;
				}
			}
		}
		public void on_glUniform4i(MyBinStream stream)
		{
			int location = stream.readInt();
			if (location < 0) return;
			for (int i = 0; i < m_uniformsCount; i++)
			{
				Var uni = m_uniforms[i];

				if (uni.Location == location)
				{
					uni.Value = string.Format("{0}, {1}, {2}, {3}", stream.readInt(), stream.readInt(), stream.readInt(), stream.readInt());
					break;
				}
			}
		}
		public void on_glUniform4iv(MyBinStream stream)
		{
			int location = stream.readInt();
			int count = stream.readInt();
			if (location < 0 || count <= 0) return;
			for (int i = 0; i < m_uniformsCount; i++)
			{
				Var uni = m_uniforms[i];

				if (uni.Location == location)
				{
					var res = "";
					for (int j = 0; j < count; j++)
					{
						res += string.Format("({0}, {1}, {2}, {3})", stream.readInt(), stream.readInt(), stream.readInt(), stream.readInt());
						if (j < count - 1) res += ", ";
					}
					uni.Value = res;
					break;
				}
			}
		}

		public void on_glUniformMatrix(MyBinStream stream, int size)
		{
			int location = stream.readInt();
			int count = stream.readInt();
			if (location < 0 || count <= 0) return;
			byte transpose = stream.readByte();
			
			for (int i = 0; i < m_uniformsCount; i++)
			{
				Var uni = m_uniforms[i];

				if (uni.Location == location)
				{
					uni.Value = Utils.makeMatrixString(stream, count, size);
					break;
				}
			}
		}

		#endregion

		#region Properties
		private uint m_vsId;
		public uint VsId
		{
			get { return m_vsId; }
			set
			{
				m_attributesCount = 0;
				m_uniformsCount = 0;
				m_vsId = value;
			}
		}

		private uint m_fsId;
		public uint FsId
		{
			get { return m_fsId; }
			set
			{
				m_attributesCount = 0;
				m_uniformsCount = 0;
				m_fsId = value;
			}
		}

		private int m_attributesCount;
		public int AttributesCount { get { return m_attributesCount; } }

		private Var[] m_attributes;
		public Var[] Attributes { get { return m_attributes; } }

		private int m_uniformsCount;
		public int UniformsCount { get { return m_uniformsCount; } }

		private Var[] m_uniforms;
		public Var[] Uniforms { get { return m_uniforms; } }
		#endregion

	}
}
