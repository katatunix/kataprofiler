using System;
using System.Collections.Generic;
using System.Text;

namespace KataProfiler
{
	public enum KPMessageType
	{
		KMT_REQUEST_ERROR = 0,
		KMT_REQUEST_FINISH,

		//=================================================
		KMT_OBJECT_TEXTURE,
		KMT_OBJECT_SHADER,
		KMT_OBJECT_PROGRAM,
		KMT_OBJECT_VBO,

		//=================================================
		KMT_STATE_CURRENT_TEXTURES_STATUS,
		KMT_STATE_CURRENT_USING_PROGRAM,
		KMT_STATE_CURRENT_BINDING_VBOS,

		//=================================================
		KMT_glActiveTexture,
		KMT_glAttachShader,
		KMT_glBindAttribLocation,
		KMT_glBindBuffer,
		KMT_glBindFramebuffer,
		KMT_glBindRenderbuffer,
		KMT_glBindTexture,
		KMT_glBlendColor,
		KMT_glBlendEquation,
		KMT_glBlendEquationSeparate,
		KMT_glBlendFunc,
		KMT_glBlendFuncSeparate,
		KMT_glBufferData,
		KMT_glBufferSubData,
		KMT_glCheckFramebufferStatus,
		KMT_glClear,
		KMT_glClearColor,
		KMT_glClearDepthf,
		KMT_glClearStencil,
		KMT_glColorMask,
		KMT_glCompileShader,
		KMT_glCompressedTexImage2D,
		KMT_glCompressedTexSubImage2D,
		KMT_glCopyTexImage2D,
		KMT_glCopyTexSubImage2D,
		KMT_glCreateProgram,
		KMT_glCreateShader,
		KMT_glCullFace,
		KMT_glDeleteBuffers,
		KMT_glDeleteFramebuffers,
		KMT_glDeleteProgram,
		KMT_glDeleteRenderbuffers,
		KMT_glDeleteShader,
		KMT_glDeleteTextures,
		KMT_glDepthFunc,
		KMT_glDepthMask,
		KMT_glDepthRangef,
		KMT_glDetachShader,
		KMT_glDisable,
		KMT_glDisableVertexAttribArray,
		KMT_glDrawArrays,
		KMT_glDrawElements,
		KMT_glEnable,
		KMT_glEnableVertexAttribArray,
		KMT_glFinish,
		KMT_glFlush,
		KMT_glFramebufferRenderbuffer,
		KMT_glFramebufferTexture2D,
		KMT_glFrontFace,
		KMT_glGenBuffers,
		KMT_glGenerateMipmap,
		KMT_glGenFramebuffers,
		KMT_glGenRenderbuffers,
		KMT_glGenTextures,
		KMT_glGetActiveAttrib,
		KMT_glGetActiveUniform,
		KMT_glGetAttachedShaders,
		KMT_glGetAttribLocation,
		KMT_glGetBooleanv,
		KMT_glGetBufferParameteriv,
		KMT_glGetError,
		KMT_glGetFloatv,
		KMT_glGetFramebufferAttachmentParameteriv,
		KMT_glGetIntegerv,
		KMT_glGetProgramiv,
		KMT_glGetProgramInfoLog,
		KMT_glGetRenderbufferParameteriv,
		KMT_glGetShaderiv,
		KMT_glGetShaderInfoLog,
		KMT_glGetShaderPrecisionFormat,
		KMT_glGetShaderSource,
		KMT_glGetString,
		KMT_glGetTexParameterfv,
		KMT_glGetTexParameteriv,
		KMT_glGetUniformfv,
		KMT_glGetUniformiv,
		KMT_glGetUniformLocation,
		KMT_glGetVertexAttribfv,
		KMT_glGetVertexAttribiv,
		KMT_glGetVertexAttribPointerv,
		KMT_glHint,
		KMT_glIsBuffer,
		KMT_glIsEnabled,
		KMT_glIsFramebuffer,
		KMT_glIsProgram,
		KMT_glIsRenderbuffer,
		KMT_glIsShader,
		KMT_glIsTexture,
		KMT_glLineWidth,
		KMT_glLinkProgram,
		KMT_glPixelStorei,
		KMT_glPolygonOffset,
		KMT_glReadPixels,
		KMT_glReleaseShaderCompiler,
		KMT_glRenderbufferStorage,
		KMT_glSampleCoverage,
		KMT_glScissor,
		KMT_glShaderBinary,
		KMT_glShaderSource,
		KMT_glStencilFunc,
		KMT_glStencilFuncSeparate,
		KMT_glStencilMask,
		KMT_glStencilMaskSeparate,
		KMT_glStencilOp,
		KMT_glStencilOpSeparate,
		KMT_glTexImage2D,
		KMT_glTexParameterf,
		KMT_glTexParameterfv,
		KMT_glTexParameteri,
		KMT_glTexParameteriv,
		KMT_glTexSubImage2D,
		KMT_glUniform1f,
		KMT_glUniform1fv,
		KMT_glUniform1i,
		KMT_glUniform1iv,
		KMT_glUniform2f,
		KMT_glUniform2fv,
		KMT_glUniform2i,
		KMT_glUniform2iv,
		KMT_glUniform3f,
		KMT_glUniform3fv,
		KMT_glUniform3i,
		KMT_glUniform3iv,
		KMT_glUniform4f,
		KMT_glUniform4fv,
		KMT_glUniform4i,
		KMT_glUniform4iv,
		KMT_glUniformMatrix2fv,
		KMT_glUniformMatrix3fv,
		KMT_glUniformMatrix4fv,
		KMT_glUseProgram,
		KMT_glValidateProgram,
		KMT_glVertexAttrib1f,
		KMT_glVertexAttrib1fv,
		KMT_glVertexAttrib2f,
		KMT_glVertexAttrib2fv,
		KMT_glVertexAttrib3f,
		KMT_glVertexAttrib3fv,
		KMT_glVertexAttrib4f,
		KMT_glVertexAttrib4fv,
		KMT_glVertexAttribPointer,
		KMT_glViewport,
		//
		KMT_glMapBufferOES,
		KMT_glUnmapBufferOES,
		//
		KMT_glTexStorage2D,
		//=================================================

		KMT_NONE
	}

	public class Message
	{
		private int m_offset;

		private int m_type;
		public int Type { get { return m_type; } set { m_type = value; } }

		private int m_length;
		public int Length { get { return m_length; } }

		private byte[] m_pData;
		public byte[] Data { get { return m_pData; } }

		public Message()
		{
			reset();
		}

		public void reset()
		{
			m_offset = 0;
			m_type = (int)KPMessageType.KMT_NONE;
			m_length = 0;
			m_pData = null;
		}

		public void copyFrom(Message msg)
		{
			reset();

			m_offset = msg.m_offset;
			m_type = msg.m_type;
			m_length = msg.m_length;

			if (m_length > 0)
			{
				m_pData = new byte[m_length];
				Utils.memcpy(m_pData, 0, msg.m_pData, 0, m_length);
			}
		}

		public Message createNewClone()
		{
			Message clone = new Message();
			clone.copyFrom(this);
			return clone;
		}

		public int consume(byte[] buffer, int offsetStart, int offsetEnd)
		{
			int count = offsetEnd - offsetStart + 1;

			if (m_offset >= 8)
			{
				int k = Math.Min(m_length + 8 - m_offset, count);
				Utils.memcpy(m_pData, m_offset - 8, buffer, offsetStart, k);

				m_offset += k;
				return k;
			}

			if (m_offset < 4)
			{
				int k = Math.Min(4 - m_offset, count);
				for (int x = m_offset; x < m_offset + k; x++)
				{
					m_type = Utils.setByte(m_type, x, buffer[offsetStart + x - m_offset]);
				}

				m_offset += k;
				return k;
			}

			int t = Math.Min(8 - m_offset, count);
			for (int x = m_offset; x < m_offset + t; x++)
			{
				m_length = Utils.setByte(m_length, x - 4, buffer[offsetStart + x - m_offset]);
			}

			m_offset += t;

			if (m_offset >= 8 && m_length > 0 && m_pData == null)
			{
				m_pData = new byte[m_length];
			}

			return t;
		}

		public bool isFull()
		{
			return m_offset >= 8 && m_offset == 8 + m_length;
		}

		public bool isRequestFinishMessage()
		{
			Utils.assert(isFull());
			return m_type == (int)KPMessageType.KMT_REQUEST_FINISH;
		}

		public bool isRequestErrorMessage()
		{
			Utils.assert(isFull());
			return m_type == (int)KPMessageType.KMT_REQUEST_ERROR;
		}

		//=============================================================================================
		//=============================================================================================
		public string toString()
		{
			KPMessageType type = (KPMessageType)m_type;
			string res = "";
			switch (type)
			{
				case KPMessageType.KMT_NONE:
					{
						res = "[NONE]";
						break;
					}
				case KPMessageType.KMT_REQUEST_ERROR:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						res = stream.readString();
						stream.close();
						break;
					}
				//------------------------------------------
				case KPMessageType.KMT_glActiveTexture:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						uint texture = stream.readUInt();
						uint actualTexture = stream.readByte() + gl.GL_TEXTURE0;
						stream.close();

						res = string.Format("glActiveTexture(texture = {0}, actualTexture = {1});",
							gl.getString(texture),
							gl.getString(actualTexture)
						);

						break;
					}
				case KPMessageType.KMT_glAttachShader:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						byte error = stream.readByte();
						uint program = stream.readUInt();
						uint shader = stream.readUInt();
						stream.close();

						res = string.Format("glAttachShader(error = {0}, program = {1}, shader = {2});", error, program, shader);

						break;
					}
				case KPMessageType.KMT_glBindAttribLocation:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						uint program = stream.readUInt();
						uint index = stream.readUInt();
						string name = stream.readString();
						stream.close();

						res = string.Format("glBindAttribLocation(program = {0}, index = {1}, name = \"{2}\");",
							program, index, name);

						break;
					}
				case KPMessageType.KMT_glBindBuffer:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						byte error = stream.readByte();
						uint target = stream.readUInt();
						uint buffer = stream.readUInt();
						uint actualBoundBuffer = stream.readUInt();
						stream.close();

						res = string.Format("glBindBuffer(error = {0}, target = {1}, buffer = {2}, actualBoundBuffer = {3});",
							error, gl.getString(target), buffer, actualBoundBuffer);

						break;
					}
				case KPMessageType.KMT_glBindFramebuffer:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						uint target = stream.readUInt();
						uint framebuffer = stream.readUInt();
						stream.close();

						res = string.Format("glBindFramebuffer(target = {0}, framebuffer = {1});",
							gl.getString(target), framebuffer);

						break;
					}
				case KPMessageType.KMT_glBindRenderbuffer:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						uint target = stream.readUInt();
						uint renderbuffer = stream.readUInt();
						stream.close();

						res = string.Format("glBindRenderbuffer(target = {0}, renderbuffer = {1});",
							gl.getString(target), renderbuffer);

						break;
					}
				case KPMessageType.KMT_glBindTexture:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						byte error = stream.readByte();
						uint target = stream.readUInt();
						uint texture = stream.readUInt();
						uint actualBoundTexture = stream.readUInt();
						stream.close();

						res = string.Format("glBindTexture(error = {0}, target = {1}, texture = {2}, actualBoundTexture = {3});",
							error,
							gl.getString(target),
							texture,
							actualBoundTexture
						);

						break;
					}
				case KPMessageType.KMT_glBlendColor:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						float red = stream.readFloat();
						float green = stream.readFloat();
						float blue = stream.readFloat();
						float alpha = stream.readFloat();
						stream.close();

						res = string.Format("glBlendColor(red = {0}, green = {1}, blue = {2}, alpha = {3});",
							red, green, blue, alpha);

						break;
					}
				case KPMessageType.KMT_glBlendEquation:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						uint mode = stream.readUInt();
						stream.close();
						stream = null;

						res = string.Format("glBlendEquation(mode = {0});", gl.getString(mode));

						break;
					}
				case KPMessageType.KMT_glBlendEquationSeparate:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						uint modeRGB = stream.readUInt();
						uint modeAlpha = stream.readUInt();
						stream.close();
						stream = null;

						res = string.Format("glBlendEquationSeparate(modeRGB = {0}, modeAlpha = {1});"
							, gl.getString(modeRGB)
							, gl.getString(modeAlpha));

						break;
					}
				case KPMessageType.KMT_glBlendFunc:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						uint sfactor = stream.readUInt();
						uint dfactor = stream.readUInt();
						stream.close();
						stream = null;

						res = string.Format("glBlendFunc(sfactor = {0}, dfactor = {1});"
							, gl.getString(sfactor)
							, gl.getString(dfactor));

						break;
					}
				case KPMessageType.KMT_glBlendFuncSeparate:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						uint srcRGB = stream.readUInt();
						uint dstRGB = stream.readUInt();
						uint srcAlpha = stream.readUInt();
						uint dstAlpha = stream.readUInt();
						stream.close();
						stream = null;

						string[] tmp1 = new string[] {
												"GL_ZERO",
												"GL_ONE",
												"GL_SRC_COLOR",
												"GL_ONE_MINUS_SRC_COLOR",
												"GL_DST_COLOR",
												"GL_ONE_MINUS_DST_COLOR",
												"GL_SRC_ALPHA",
												"GL_ONE_MINUS_SRC_ALPHA",
												"GL_DST_ALPHA",
												"GL_ONE_MINUS_DST_ALPHA",
												"GL_CONSTANT_COLOR",
												"GL_ONE_MINUS_CONSTANT_COLOR",
												"GL_CONSTANT_ALPHA",
												"GL_ONE_MINUS_CONSTANT_ALPHA",
												"GL_SRC_ALPHA_SATURATE" };
						string[] tmp2 = new string[] {
												"GL_ZERO",
												"GL_ONE",
												"GL_SRC_COLOR",
												"GL_ONE_MINUS_SRC_COLOR",
												"GL_DST_COLOR",
												"GL_ONE_MINUS_DST_COLOR",
												"GL_SRC_ALPHA",
												"GL_ONE_MINUS_SRC_ALPHA",
												"GL_DST_ALPHA",
												"GL_ONE_MINUS_DST_ALPHA",
												"GL_CONSTANT_COLOR",
												"GL_ONE_MINUS_CONSTANT_COLOR",
												"GL_CONSTANT_ALPHA",
												"GL_ONE_MINUS_CONSTANT_ALPHA" };

						res = string.Format("glBlendFuncSeparate(srcRGB = {0}, dstRGB = {1}, srcAlpha = {2}, dstAlpha = {3});"
							, gl.getString(srcRGB, tmp1)
							, gl.getString(dstRGB, tmp2)
							, gl.getString(srcAlpha, tmp1)
							, gl.getString(dstAlpha, tmp2)
						);

						break;
					}
				case KPMessageType.KMT_glBufferData:
					{
						MyBinStream stream = new MyBinStream(m_pData);

						byte error = stream.readByte();
						uint vboId = stream.readUInt();
						uint target = stream.readUInt();
						int size = stream.readInt();
						int data = stream.readInt();
						uint usage = stream.readUInt();
						stream.close();

						res = string.Format("glBufferData(error = {0}, target = {1}, size = {2}, data = 0x{3}, usage = {4});"
							, error
							, gl.getString(target)
							, size
							, data.ToString("X")
							, gl.getString(usage));

						break;
					}
				case KPMessageType.KMT_glBufferSubData:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						byte error = stream.readByte();
						uint vboId = stream.readUInt();
						uint target = stream.readUInt();
						int offset = stream.readInt();
						int size = stream.readInt();
						int data = stream.readInt();
						stream.close();
						stream = null;

						res = string.Format("glBufferSubData(error = {0}, target = {1}, offset = {2}, size = {3}, data = 0x{4});"
							, error
							, gl.getString(target)
							, offset
							, size
							, data.ToString("X"));

						break;
					}
				case KPMessageType.KMT_glCheckFramebufferStatus:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						uint target = stream.readUInt();
						uint result = stream.readUInt();
						stream.close();
						stream = null;

						res = string.Format("glCheckFramebufferStatus(target = {0}, result = {1});"
							, gl.getString(target)
							, gl.getString(result));

						break;
					}
				case KPMessageType.KMT_glClear:
					{
						MyBinStream stream = new MyBinStream(m_pData);

						res = "[" + stream.readUInt() + "] " +
							"glClear(mask = " +
							gl.getMask(stream.readUInt(), new string[] {
																"GL_DEPTH_BUFFER_BIT",
																"GL_STENCIL_BUFFER_BIT",
																"GL_COLOR_BUFFER_BIT" }) +
							");";

						stream.close();
						stream = null;
						break;
					}
				case KPMessageType.KMT_glClearColor:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						float red = stream.readFloat();
						float green = stream.readFloat();
						float blue = stream.readFloat();
						float alpha = stream.readFloat();
						stream.close();
						stream = null;

						res = string.Format("glClearColor(red = {0}, green = {1}, blue = {2}, alpha = {3});"
							, red, green, blue, alpha);

						break;
					}
				case KPMessageType.KMT_glClearDepthf:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						float depth = stream.readFloat();
						stream.close();
						stream = null;

						res = string.Format("glClearDepthf(depth = {0});", depth);

						break;
					}
				case KPMessageType.KMT_glClearStencil:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						int s = stream.readInt();
						stream.close();
						stream = null;

						res = string.Format("glClearStencil(s = {0});", s);

						break;
					}
				case KPMessageType.KMT_glColorMask:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						byte red = stream.readByte();
						byte green = stream.readByte();
						byte blue = stream.readByte();
						byte alpha = stream.readByte();
						stream.close();
						stream = null;

						res = string.Format("glColorMask(red = {0}, green = {1}, blue = {2}, alpha = {3});"
							, red, green, blue, alpha);

						break;
					}
				case KPMessageType.KMT_glCompileShader:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						uint shader = stream.readUInt();
						stream.close();
						stream = null;

						res = string.Format("glCompileShader(shader = {0});", shader);

						break;
					}
				case KPMessageType.KMT_glCompressedTexImage2D:
					{
						MyBinStream stream = new MyBinStream(m_pData);

						byte error = stream.readByte();
						uint id = stream.readUInt();
						uint target = stream.readUInt();
						int level = stream.readInt();
						uint internalFormat = stream.readUInt();
						int width = stream.readInt();
						int height = stream.readInt();
						int border = stream.readInt();
						int imageSize = stream.readInt();
						int dataAddress = stream.readInt();

						stream.close();

						res = string.Format(
							"glCompressedTexImage2D(error = {0}, id = {1}, target = {2}, level = {3}, internalFormat = {4}, " +
							"width = {5}, height = {6}, border = {7}, imageSize = {8}, data = 0x{9});"
							, error
							, id
							, gl.getString(target)
							, level
							, gl.getString(internalFormat)
							, width
							, height
							, border
							, imageSize
							, dataAddress.ToString("X")
						);

						break;
					}
				case KPMessageType.KMT_glCompressedTexSubImage2D:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						byte error = stream.readByte();
						uint target = stream.readUInt();
						int level = stream.readInt();
						int xoffset = stream.readInt();
						int yoffset = stream.readInt();
						int width = stream.readInt();
						int height = stream.readInt();
						int format = stream.readInt();
						int imageSize = stream.readInt();
						int data = stream.readInt();
						stream.close();
						stream = null;

						res = string.Format("glCompressedTexSubImage2D(error = {0}, target = {1}, level = {2}, " +
							"xoffset = {3}, yoffset = {4}, width = {5}, height = {6}, format = {7}, imageSize = {8}, data = 0x{9};)"
							, error
							, gl.getString(target)
							, level
							, xoffset
							, yoffset
							, width
							, height
							, gl.getString(format)
							, imageSize
							, data);

						break;
					}
				case KPMessageType.KMT_glCopyTexImage2D:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						byte error = stream.readByte();
						uint id = stream.readUInt();
						uint target = stream.readUInt();
						int level = stream.readInt();
						uint internalFormat = stream.readUInt();
						int x = stream.readInt();
						int y = stream.readInt();
						int width = stream.readInt();
						int height = stream.readInt();
						int border = stream.readInt();
						stream.close();
						stream = null;

						res = string.Format("glCopyTexImage2D(error = {0}, id = {1}, target = {2}, level = {3}, " +
							"internalFormat = {4}, x = {5}, y = {6}, width = {7}, height = {8}, border = {9});"
							, error
							, id
							, gl.getString(target)
							, level
							, gl.getString(internalFormat)
							, x
							, y
							, width
							, height
							, border);

						break;
					}
				case KPMessageType.KMT_glCopyTexSubImage2D:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						byte error = stream.readByte();
						uint id = stream.readUInt();
						uint target = stream.readUInt();
						int level = stream.readInt();
						int xoffset = stream.readInt();
						int yoffset = stream.readInt();
						int x = stream.readInt();
						int y = stream.readInt();
						int width = stream.readInt();
						int height = stream.readInt();
						stream.close();
						stream = null;

						res = string.Format("glCopyTexSubImage2D(error = {0}, id = {1}, target = {2}, level = {3}, " +
							"xoffset = {4}, yoffset = {5}, x = {6}, y = {7}, width = {8}, height = {9});"
							, error
							, id
							, gl.getString(target)
							, level
							, xoffset
							, yoffset
							, x
							, y
							, width
							, height);

						break;
					}
				case KPMessageType.KMT_glCreateProgram:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						byte error = stream.readByte();
						uint result = stream.readUInt();
						stream.close();
						stream = null;

						res = string.Format("glCreateProgram(error = {0}, result = {1});", error, result);

						break;
					}
				case KPMessageType.KMT_glCreateShader:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						byte error = stream.readByte();
						uint shaderType = stream.readUInt();
						uint result = stream.readUInt();
						stream.close();
						stream = null;

						res = string.Format("glCreateShader(error = {0}, type = {1}, result = {2});"
							, error
							, gl.getString(shaderType)
							, result);

						break;
					}
				case KPMessageType.KMT_glCullFace:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						uint mode = stream.readUInt();
						stream.close();
						stream = null;

						res = string.Format("glCullFace(mode = {0});", gl.getString(mode));

						break;
					}
				case KPMessageType.KMT_glDeleteBuffers:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						int n = stream.readInt();
						res = "glDeleteBuffers(n = " + n + ", buffers = {";
						for (int i = 0; i < n; i++)
						{
							res += stream.readUInt();
							if (i < n - 1) res += ", ";
						}
						stream.close();
						res += "});";

						break;
					}
				case KPMessageType.KMT_glDeleteFramebuffers:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						int n = stream.readInt();
						res = "glDeleteFramebuffers(n = " + n + ", framebuffers = {";
						for (int i = 0; i < n; i++)
						{
							res += stream.readUInt();
							if (i < n - 1) res += ", ";
						}
						stream.close();
						res += "});";
						break;
					}
				case KPMessageType.KMT_glDeleteProgram:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						res = string.Format("glDeleteProgram(error = {0}, program = {1});", stream.readByte(), stream.readUInt());
						stream.close();
						break;
					}
				case KPMessageType.KMT_glDeleteRenderbuffers:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						int n = stream.readInt();
						res = "glDeleteRenderbuffers(n = " + n + ", renderbuffers = {";
						for (int i = 0; i < n; i++)
						{
							res += stream.readUInt();
							if (i < n - 1) res += ", ";
						}
						stream.close();
						res += "});";

						break;
					}
				case KPMessageType.KMT_glDeleteShader:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						res = string.Format("glDeleteShader(error = {0}, shader = {1});", stream.readByte(), stream.readUInt());
						stream.close();
						break;
					}
				case KPMessageType.KMT_glDeleteTextures:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						int n = stream.readInt();
						res = "glDeleteTextures(n = " + n + ", textures = {";
						for (int i = 0; i < n; i++)
						{
							res += stream.readUInt();
							if (i < n - 1) res += ", ";
						}
						stream.close();
						res += "});";
						break;
					}
				case KPMessageType.KMT_glDepthFunc:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						res = string.Format("glDepthFunc(func = {0});", gl.getString(stream.readUInt()));
						stream.close();
						break;
					}
				case KPMessageType.KMT_glDepthMask:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						res = string.Format("glDepthMask(flag = {0});", gl.getBoolean(stream.readByte()));
						stream.close();
						break;
					}
				case KPMessageType.KMT_glDepthRangef:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						res = string.Format("glDepthRangef(zNear = {0}, zFar = {1});", stream.readFloat(), stream.readFloat());
						stream.close();
						break;
					}
				case KPMessageType.KMT_glDetachShader:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						res = string.Format("glDetachShader(error = {0}, program = {1}, shader = {2});",
							stream.readByte(), stream.readUInt(), stream.readUInt());
						stream.close();
						break;
					}
				case KPMessageType.KMT_glDisable:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						res = string.Format("glDisable(cap = {0});", gl.getString(stream.readUInt()));
						stream.close();
						break;
					}
				case KPMessageType.KMT_glDisableVertexAttribArray:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						res = string.Format("glDisableVertexAttribArray(error = {0}, index = {1});",
							stream.readByte(), stream.readUInt());
						stream.close();
						break;
					}
				case KPMessageType.KMT_glDrawArrays:
					{
						string[] modes = new string[] {
						"GL_POINTS",
						"GL_LINE_STRIP",
						"GL_LINE_LOOP",
						"GL_LINES",
						"GL_TRIANGLE_STRIP",
						"GL_TRIANGLE_FAN",
						"GL_TRIANGLES"
					};
						MyBinStream stream = new MyBinStream(m_pData);
						res = "[" + stream.readUInt() + "] " +
									"glDrawArrays(" +
									"mode = " + gl.getString(stream.readUInt(), modes) +
									", first = " + stream.readInt() +
									", count = " + stream.readInt() +
									", zNear = " + stream.readFloat() +
									", zFar = " + stream.readFloat() +
									", W = " + stream.readInt() +
									", H = " + stream.readInt() +
									");";
						stream.close();
						stream = null;
						break;
					}
				case KPMessageType.KMT_glDrawElements:
					{
						string[] modes = new string[] {
						"GL_POINTS",
						"GL_LINE_STRIP",
						"GL_LINE_LOOP",
						"GL_LINES",
						"GL_TRIANGLE_STRIP",
						"GL_TRIANGLE_FAN",
						"GL_TRIANGLES"
					};
						MyBinStream stream = new MyBinStream(m_pData);
						res = "[" + stream.readUInt() + "] " +
									"glDrawElements(" +
									"mode = " + gl.getString(stream.readUInt(), modes) +
									", count = " + stream.readInt() +
									", type = " + gl.getString(stream.readUInt()) +
									", indices = 0x" + stream.readInt().ToString("X") +
									", zNear = " + stream.readFloat() +
									", zFar = " + stream.readFloat() +
									", W = " + stream.readInt() +
									", H = " + stream.readInt() +
									");";
						stream.close();
						stream = null;
						break;
					}
				case KPMessageType.KMT_glEnable:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						res = string.Format("glEnable(cap = {0});", gl.getString(stream.readUInt()));
						stream.close();
						break;
					}
				case KPMessageType.KMT_glEnableVertexAttribArray:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						res = string.Format("glEnableVertexAttribArray(error = {0}, index = {1});",
							stream.readByte(), stream.readUInt());
						stream.close();
						break;
					}
				case KPMessageType.KMT_glFinish:
					{
						res = "glFinish();";
						break;
					}
				case KPMessageType.KMT_glFlush:
					{
						res = "glFlush();";
						break;
					}
				case KPMessageType.KMT_glFramebufferRenderbuffer:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						res = string.Format("glFramebufferRenderbuffer(target = {0}, attachment = {1}, " +
							"renderbuffertarget = {2}, renderbuffer = {3});",
							gl.getString(stream.readUInt()),
							gl.getString(stream.readUInt()),
							gl.getString(stream.readUInt()),
							stream.readUInt()
						);
						stream.close();
						break;
					}
				case KPMessageType.KMT_glFramebufferTexture2D:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						res = string.Format("glFramebufferTexture2D(target = {0}, attachment = {1}, " +
							"textarget = {2}, texture = {3}, level = {4});",
							gl.getString(stream.readUInt()),
							gl.getString(stream.readUInt()),
							gl.getString(stream.readUInt()),
							stream.readUInt(),
							stream.readInt()
						);
						stream.close();
						break;
					}
				case KPMessageType.KMT_glFrontFace:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						res = string.Format("glFrontFace(mode = {0});", gl.getString(stream.readUInt()));
						stream.close();
						break;
					}
				case KPMessageType.KMT_glGenBuffers:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						int n = stream.readInt();
						res = "glGenBuffers(n = " + n + ", buffers = {";
						for (int i = 0; i < n; i++)
						{
							res += stream.readUInt();
							if (i < n - 1) res += ", ";
						}
						stream.close();
						res += "});";
						break;
					}
				case KPMessageType.KMT_glGenerateMipmap:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						res = string.Format("glGenerateMipmap(target = {0});", gl.getString(stream.readUInt()));
						stream.close();
						break;
					}
				case KPMessageType.KMT_glGenFramebuffers:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						int n = stream.readInt();
						res = "glGenFramebuffers(n = " + n + ", framebuffers = {";
						for (int i = 0; i < n; i++)
						{
							res += stream.readUInt();
							if (i < n - 1) res += ", ";
						}
						stream.close();
						res += "});";
						break;
					}
				case KPMessageType.KMT_glGenRenderbuffers:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						int n = stream.readInt();
						res = "glGenRenderbuffers(n = " + n + ", renderbuffers = {";
						for (int i = 0; i < n; i++)
						{
							res += stream.readUInt();
							if (i < n - 1) res += ", ";
						}
						stream.close();
						res += "});";
						break;
					}
				case KPMessageType.KMT_glGenTextures:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						int n = stream.readInt();
						res = "glGenTextures(n = " + n + ", textures = {";
						for (int i = 0; i < n; i++)
						{
							res += stream.readUInt();
							if (i < n - 1) res += ", ";
						}
						stream.close();
						res += "});";
						break;
					}
				case KPMessageType.KMT_glGetActiveAttrib:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						res = string.Format("glGetActiveAttrib(program = {0}, index = {1}, bufsize = {2}, " +
							"length = 0x{3}, size = 0x{4}, type = 0x{5}, name = 0x{6});",
							stream.readUInt(), // program
							stream.readUInt(), // index
							stream.readInt(), // bufsize
							stream.readInt().ToString("X"), // length
							stream.readInt().ToString("X"), // size
							stream.readInt().ToString("X"), // type
							stream.readInt().ToString("X") // name
						);
						stream.close();
						break;
					}
				case KPMessageType.KMT_glGetActiveUniform:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						res = string.Format("glGetActiveUniform(program = {0}, index = {1}, bufsize = {2}, " +
							"length = 0x{3}, size = 0x{4}, type = 0x{5}, name = 0x{6});",
							stream.readUInt(), // program
							stream.readUInt(), // index
							stream.readInt(), // bufsize
							stream.readInt().ToString("X"), // length
							stream.readInt().ToString("X"), // size
							stream.readInt().ToString("X"), // type
							stream.readInt().ToString("X") // name
						);
						stream.close();
						break;
					}
				case KPMessageType.KMT_glGetAttachedShaders:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						res = string.Format("glGetAttachedShaders(program = {0}, maxcount = {1}, count = 0x{2}, shaders = 0x{3});",
							stream.readUInt(),
							stream.readInt(),
							stream.readInt().ToString("X"),
							stream.readInt().ToString("X")
						);

						stream.close();
						break;
					}
				case KPMessageType.KMT_glGetAttribLocation:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						res = string.Format("glGetAttribLocation(program = {0}, name = \"{1}\", result = {2});",
							stream.readUInt(),
							stream.readString(m_length - 4 - 4),
							stream.readInt()
						);
						stream.close();
						break;
					}
				case KPMessageType.KMT_glGetBooleanv:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						res = string.Format("glGetBooleanv(pname = {0}, params = {1});",
							gl.getString(stream.readUInt()),
							gl.getBoolean(stream.readByte())
						);
						stream.close();
						break;
					}
				case KPMessageType.KMT_glGetBufferParameteriv:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						res = string.Format("glGetBufferParameteriv(target = {0}, pname = {1}, params = {2});",
							gl.getString(stream.readUInt()),
							gl.getString(stream.readUInt()),
							stream.readInt()
						);
						stream.close();
						break;
					}
				case KPMessageType.KMT_glGetError:
					{
						string[] errors = {
										  "GL_NO_ERROR",
										  "GL_INVALID_ENUM",
										  "GL_INVALID_VALUE",
										  "GL_INVALID_OPERATION",
										  "GL_INVALID_FRAMEBUFFER_OPERATION",
										  "GL_OUT_OF_MEMORY"
									  };
						MyBinStream stream = new MyBinStream(m_pData);
						res = string.Format("glGetError() = {0};", gl.getString(stream.readUInt(), errors));
						stream.close();
						break;
					}
				case KPMessageType.KMT_glGetFloatv:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						res = string.Format("glGetFloatv(pname = {0}, params = {1});",
							gl.getString(stream.readUInt()),
							stream.readFloat()
						);
						stream.close();
						break;
					}
				case KPMessageType.KMT_glGetFramebufferAttachmentParameteriv:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						res = string.Format("glGetFramebufferAttachmentParameteriv(target = {0}, " +
							"attachment = {1}, pname = {2}, params = {3});",
							gl.getString(stream.readUInt()),
							gl.getString(stream.readUInt()),
							gl.getString(stream.readUInt()),
							stream.readInt()
						);
						stream.close();
						break;
					}
				case KPMessageType.KMT_glGetIntegerv:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						res = string.Format("glGetIntegerv(pname = {0}, params = {1});",
							gl.getString(stream.readUInt()),
							stream.readInt()
						);
						stream.close();
						break;
					}
				case KPMessageType.KMT_glGetProgramiv:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						res = string.Format("glGetProgramiv(program = {0}, pname = {1}, params = {2});",
							stream.readUInt(),
							gl.getString(stream.readUInt()),
							stream.readInt()
						);
						stream.close();
						break;
					}
				case KPMessageType.KMT_glGetProgramInfoLog:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						res = string.Format("glGetProgramInfoLog(program = {0}, bufsize = {1}, length = 0x{2}, infolog = 0x{3});",
							stream.readUInt(),
							stream.readInt(),
							stream.readInt().ToString("X"),
							stream.readInt().ToString("X")
						);
						stream.close();
						break;
					}
				case KPMessageType.KMT_glGetRenderbufferParameteriv:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						res = string.Format("glGetRenderbufferParameteriv(target = {0}, pname = {1}, params = {2});",
							gl.getString(stream.readUInt()),
							gl.getString(stream.readUInt()),
							stream.readInt()
						);
						stream.close();
						break;
					}
				case KPMessageType.KMT_glGetShaderiv:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						res = string.Format("glGetShaderiv(shader = {0}, pname = {1}, params = {2});",
							stream.readUInt(),
							gl.getString(stream.readUInt()),
							stream.readInt()
						);
						stream.close();
						break;
					}
				case KPMessageType.KMT_glGetShaderInfoLog:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						res = string.Format("glGetShaderInfoLog(shader = {0}, bufsize = {1}, length = 0x{2}, infolog = 0x{3});",
							stream.readUInt(),
							stream.readInt(),
							stream.readInt().ToString("X"),
							stream.readInt().ToString("X")
						);
						stream.close();
						break;
					}
				case KPMessageType.KMT_glGetShaderPrecisionFormat:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						res = string.Format("glGetShaderPrecisionFormat(shadertype = {0}, precisiontype = {1}, " +
							"range = ({2}, {3}), precision = {4});",
							gl.getString(stream.readUInt()),
							gl.getString(stream.readUInt()),
							stream.readInt(), stream.readInt(),
							stream.readInt()
						);
						stream.close();
						break;
					}
				case KPMessageType.KMT_glGetShaderSource:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						res = string.Format("glGetShaderSource(shader = {0}, bufsize = {1}, length = 0x{2}, source = 0x{3});",
							stream.readUInt(),
							stream.readInt(),
							stream.readInt().ToString("X"),
							stream.readInt().ToString("X")
						);
						stream.close();
						break;
					}
				case KPMessageType.KMT_glGetString:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						res = string.Format("glGetString(name = {0}) = \"{1}\";",
							gl.getString(stream.readUInt()),
							stream.readString()
						);
						stream.close();
						break;
					}
				case KPMessageType.KMT_glGetTexParameterfv:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						res = string.Format("glGetTexParameterfv(target = {0}, pname = {1}, params = {2});",
							gl.getString(stream.readUInt()),
							gl.getString(stream.readUInt()),
							gl.getString((uint)stream.readFloat())
						);
						break;
					}
				case KPMessageType.KMT_glGetTexParameteriv:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						res = string.Format("glGetTexParameteriv(target = {0}, pname = {1}, params = {2});",
							gl.getString(stream.readUInt()),
							gl.getString(stream.readUInt()),
							gl.getString(stream.readInt())
						);
						break;
					}
				case KPMessageType.KMT_glGetUniformfv:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						res = string.Format("glGetUniformfv(program = {0}, location = {1}, params = 0x{2});",
							stream.readUInt(),
							stream.readInt(),
							stream.readInt().ToString("X")
						);
						stream.close();
						break;
					}
				case KPMessageType.KMT_glGetUniformiv:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						res = string.Format("glGetUniformiv(program = {0}, location = {1}, params = 0x{2});",
							stream.readUInt(),
							stream.readInt(),
							stream.readInt().ToString("X")
						);
						stream.close();
						break;
					}
				case KPMessageType.KMT_glGetUniformLocation:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						uint program = stream.readUInt();
						int result = stream.readInt();
						string name = stream.readString();

						res = string.Format("glGetUniformLocation(program = {0}, name = \"{1}\") = {2};",
							program, name, result
						);
						stream.close();
						break;
					}
				case KPMessageType.KMT_glGetVertexAttribfv:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						res = string.Format("glGetVertexAttribfv(index = {0}, pname = {1}, params = 0x{2});",
							stream.readUInt(),
							gl.getString(stream.readUInt()),
							stream.readInt().ToString("X")
						);
						stream.close();
						break;
					}
				case KPMessageType.KMT_glGetVertexAttribiv:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						res = string.Format("glGetVertexAttribiv(index = {0}, pname = {1}, params = 0x{2});",
							stream.readUInt(),
							gl.getString(stream.readUInt()),
							stream.readInt().ToString("X")
						);
						stream.close();
						break;
					}
				case KPMessageType.KMT_glGetVertexAttribPointerv:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						res = string.Format("glGetVertexAttribPointerv(index = {0}, pname = {1}, pointer = 0x{2});",
							stream.readUInt(),
							gl.getString(stream.readUInt()),
							stream.readInt().ToString("X")
						);
						stream.close();
						break;
					}
				case KPMessageType.KMT_glHint:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						res = string.Format("glHint(target = {0}, mode = {1});",
							gl.getString(stream.readUInt()),
							gl.getString(stream.readUInt())
						);
						stream.close();
						break;
					}
				case KPMessageType.KMT_glIsBuffer:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						res = string.Format("glIsBuffer(buffer = {0}) = {1};",
							stream.readUInt(),
							gl.getBoolean(stream.readByte())
						);
						stream.close();
						break;
					}
				case KPMessageType.KMT_glIsEnabled:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						res = string.Format("glIsEnabled(cap = {0}) = {1};",
							stream.readUInt(),
							gl.getBoolean(stream.readByte())
						);
						stream.close();
						break;
					}
				case KPMessageType.KMT_glIsFramebuffer:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						res = string.Format("glIsFramebuffer(framebuffer = {0}) = {1};",
							stream.readUInt(),
							gl.getBoolean(stream.readByte())
						);
						stream.close();
						break;
					}
				case KPMessageType.KMT_glIsProgram:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						res = string.Format("glIsProgram(program = {0}) = {1};",
							stream.readUInt(),
							gl.getBoolean(stream.readByte())
						);
						stream.close();
						break;
					}
				case KPMessageType.KMT_glIsRenderbuffer:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						res = string.Format("glIsRenderbuffer(renderbuffer = {0}) = {1};",
							stream.readUInt(),
							gl.getBoolean(stream.readByte())
						);
						stream.close();
						break;
					}
				case KPMessageType.KMT_glIsShader:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						res = string.Format("glIsShader(shader = {0}) = {1};",
							stream.readUInt(),
							gl.getBoolean(stream.readByte())
						);
						stream.close();
						break;
					}
				case KPMessageType.KMT_glIsTexture:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						res = string.Format("glIsTexture(texture = {0}) = {1};",
							stream.readUInt(),
							gl.getBoolean(stream.readByte())
						);
						stream.close();
						break;
					}
				case KPMessageType.KMT_glLineWidth:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						res = string.Format("glLineWidth(width = {0});", stream.readFloat());
						stream.close();
						break;
					}
				case KPMessageType.KMT_glLinkProgram:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						res = string.Format("glLinkProgram(error = {0}, program = {1});", stream.readByte(), stream.readUInt());
						stream.close();
						break;
					}
				case KPMessageType.KMT_glPixelStorei:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						res = string.Format("glPixelStorei(pname = {0}, param = {1});",
							gl.getString(stream.readUInt()),
							stream.readInt()
						);
						stream.close();
						break;
					}
				case KPMessageType.KMT_glPolygonOffset:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						res = string.Format("glPolygonOffset(factor = {0}, units = {1});", stream.readFloat(), stream.readFloat());
						stream.close();
						break;
					}
				case KPMessageType.KMT_glReadPixels:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						res = string.Format("glReadPixels(x = {0}, y = {1}, width = {2}, height = {3}, " +
							"format = {4}, type = {5}, pixels = 0x{6});",
							stream.readInt(), // x
							stream.readInt(), // y
							stream.readInt(), // width
							stream.readInt(), // height
							gl.getString(stream.readUInt()), // format
							gl.getString(stream.readUInt()), // type
							stream.readInt().ToString("X") // pixels
						);
						stream.close();
						break;
					}
				case KPMessageType.KMT_glReleaseShaderCompiler:
					{
						res = "glReleaseShaderCompiler();";
						break;
					}
				case KPMessageType.KMT_glRenderbufferStorage:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						res = string.Format("glRenderbufferStorage(target = {0}, internalformat = {1}, width = {2}, height = {3});",
							gl.getString(stream.readUInt()), // target
							gl.getString(stream.readUInt()), // internalformat
							stream.readInt(), // width
							stream.readInt() // height
						);
						stream.close();
						break;
					}
				case KPMessageType.KMT_glSampleCoverage:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						res = string.Format("glSampleCoverage(value = {0}, invert = {1});",
							stream.readFloat(),
							gl.getBoolean(stream.readByte())
						);
						stream.close();
						break;
					}
				case KPMessageType.KMT_glScissor:
					{
						MyBinStream stream = new MyBinStream(m_pData);

						res = "glScissor(" +
							"x = " + stream.readInt() +
							", y = " + stream.readInt() +
							", width = " + stream.readInt() +
							", height = " + stream.readInt() +
							");";

						stream.close();
						stream = null;

						break;
					}
				case KPMessageType.KMT_glShaderBinary:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						res = string.Format(
							"glShaderBinary(n = {0}, shaders = 0x{1}, binaryformat = 0x{2}, binary = 0x{3}, length = {4});",
							stream.readInt(),
							stream.readInt().ToString("X"),
							stream.readInt().ToString("X"),
							stream.readInt().ToString("X"),
							stream.readInt()
						);
						stream.close();
						break;
					}
				case KPMessageType.KMT_glShaderSource:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						res = string.Format("glShaderSource(error = {0}, shader = {1}, source = ...);",
							stream.readByte(), stream.readUInt());
						stream.close();
						break;
					}
				case KPMessageType.KMT_glStencilFunc:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						res = string.Format("glStencilFunc(func = {0}, ref = 0x{1}, mask = 0x{2});",
							gl.getString(stream.readUInt()),
							stream.readInt().ToString("X"),
							stream.readUInt().ToString("X")
						);
						stream.close();
						break;
					}
				case KPMessageType.KMT_glStencilFuncSeparate:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						res = string.Format("glStencilFuncSeparate(face = {0}, func = {1}, ref = 0x{1}, mask = 0x{2});",
							gl.getString(stream.readUInt()),
							gl.getString(stream.readUInt()),
							stream.readInt().ToString("X"),
							stream.readUInt().ToString("X")
						);
						stream.close();
						break;
					}
				case KPMessageType.KMT_glStencilMask:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						res = string.Format("glStencilMask(mask = 0x{0});",
							stream.readUInt().ToString("X")
						);
						stream.close();
						break;
					}
				case KPMessageType.KMT_glStencilMaskSeparate:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						res = string.Format("glStencilMaskSeparate(face = {0}, mask = 0x{1});",
							gl.getString(stream.readUInt()),
							stream.readUInt().ToString("X")
						);
						stream.close();
						break;
					}
				case KPMessageType.KMT_glStencilOp:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						res = string.Format("glStencilOp(fail = {0}, zfail = {1}, zpass = {2});",
							gl.getString(stream.readUInt()),
							gl.getString(stream.readUInt()),
							gl.getString(stream.readUInt())
						);
						stream.close();
						break;
					}
				case KPMessageType.KMT_glStencilOpSeparate:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						string face = gl.getString(stream.readUInt());
						string fail = gl.getString(stream.readUInt());
						string zfail = gl.getString(stream.readUInt());
						string zpass = gl.getString(stream.readUInt());
						res = string.Format("glStencilOpSeparate(face = {0}, fail = {1}, zfail = {2}, zpass = {3})"
							, face
							, fail
							, zfail
							, zpass);
						stream.close();
						stream = null;
						break;
					}
				case KPMessageType.KMT_glTexImage2D:
					{
						MyBinStream stream = new MyBinStream(m_pData);

						byte error = stream.readByte();
						uint id = stream.readUInt();
						uint target = stream.readUInt();
						int level = stream.readInt();
						int internalformat = stream.readInt();
						int width = stream.readInt();
						int height = stream.readInt();
						int border = stream.readInt();
						uint format = stream.readUInt();
						uint _type = stream.readUInt();
						int address = stream.readInt();

						stream.close();

						res = string.Format("glTexImage2D(error = {0}, id = {1}, target = {2}, level = {3}, " +
							"internalformat = {4}, width = {5}, height = {6}, border = {7}, " +
							"format = {8}, type = {9}, pixels = 0x{10});"
							, error
							, id
							, gl.getString(target)
							, level
							, gl.getString(internalformat)
							, width
							, height
							, border
							, gl.getString(format)
							, gl.getString(_type)
							, address.ToString("X")
						);

						break;
					}
				case KPMessageType.KMT_glTexParameterf:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						string target = gl.getString(stream.readUInt());
						string pname = gl.getString(stream.readUInt());
						string param = gl.getString((uint)stream.readFloat());
						res = string.Format("glTexParameterf(target = {0}, pname = {1}, param = {2})"
							, target
							, pname
							, param);
						stream.close();
						stream = null;
						break;
					}
				case KPMessageType.KMT_glTexParameterfv:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						string target = gl.getString(stream.readUInt());
						string pname = gl.getString(stream.readUInt());
						string _params = gl.getString((uint)stream.readFloat());
						res = string.Format("glTexParameterfv(target = {0}, pname = {1}, params = {2})"
							, target
							, pname
							, _params);
						stream.close();
						stream = null;
						break;
					}
				case KPMessageType.KMT_glTexParameteri:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						string target = gl.getString(stream.readUInt());
						string pname = gl.getString(stream.readUInt());
						string param = gl.getString(stream.readInt());
						res = string.Format("glTexParameteri(target = {0}, pname = {1}, param = {2})"
							, target
							, pname
							, param);
						stream.close();
						stream = null;
						break;
					}
				case KPMessageType.KMT_glTexParameteriv:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						string target = gl.getString(stream.readUInt());
						string pname = gl.getString(stream.readUInt());
						string _params = gl.getString(stream.readInt());
						res = string.Format("glTexParameteriv(target = {0}, pname = {1}, params = {2})"
							, target
							, pname
							, _params);
						stream.close();
						stream = null;
						break;
					}
				case KPMessageType.KMT_glTexSubImage2D:
					{
						MyBinStream stream = new MyBinStream(m_pData);

						byte error = stream.readByte();
						uint id = stream.readUInt();
						uint target = stream.readUInt();
						int level = stream.readInt();
						int xoffset = stream.readInt();
						int yoffset = stream.readInt();
						int width = stream.readInt();
						int height = stream.readInt();
						uint format = stream.readUInt();
						uint _type = stream.readUInt();
						int address = stream.readInt();

						res = string.Format("glTexSubImage2D(error = {0}, id = {1}, target = {2}, level = {3}, " +
							"xoffset = {4}, yoffset = {5}, width = {6}, height = {7}, " +
							"format = {8}, type = {9}, pixels = 0x{10});"
							, error
							, id
							, gl.getString(target)
							, level
							, xoffset
							, yoffset
							, width
							, height
							, gl.getString(format)
							, gl.getString(_type)
							, address.ToString("X")
						);

						stream.close();
						break;
					}
				//==============================================================================
				// glUniform***
				//==============================================================================
				#region
				case KPMessageType.KMT_glUniform1f:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						byte error = stream.readByte();
						stream.skip(4); // program id
						int location = stream.readInt();
						float x = stream.readFloat();
						res = string.Format("glUniform1f(error = {0}, location = {1}, x = {2});", error, location, x);
						stream.close();
						break;
					}
				case KPMessageType.KMT_glUniform1fv:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						byte error = stream.readByte();
						stream.skip(4); // program id
						int location = stream.readInt();
						int count = stream.readInt();

						res = string.Format("glUniform1fv(error = {0}, location = {1}, count = {2}, v = ", error, location, count);

						res += "{";
						for (int i = 0; i < count; i++)
						{
							res += string.Format("({0})", stream.readFloat());
							if (i < count - 1) res += ", ";
						}
						res += "});";

						stream.close();
						break;
					}
				case KPMessageType.KMT_glUniform1i:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						byte error = stream.readByte();
						stream.skip(4); // program id
						int location = stream.readInt();
						int x = stream.readInt();
						res = string.Format("glUniform1i(error = {0}, location = {1}, x = {2});", error, location, x);
						stream.close();
						break;
					}
				case KPMessageType.KMT_glUniform1iv:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						byte error = stream.readByte();
						stream.skip(4); // program id
						int location = stream.readInt();
						int count = stream.readInt();

						res = string.Format("glUniform1iv(error = {0}, location = {1}, count = {2}, v = ", error, location, count);

						res += "{";
						for (int i = 0; i < count; i++)
						{
							res += string.Format("({0})", stream.readInt());
							if (i < count - 1) res += ", ";
						}
						res += "});";

						stream.close();
						break;
					}
				case KPMessageType.KMT_glUniform2f:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						byte error = stream.readByte();
						stream.skip(4); // program id
						int location = stream.readInt();
						float x = stream.readFloat();
						float y = stream.readFloat();
						res = string.Format("glUniform2f(error = {0}, location = {1}, x = {2}, y = {3});", error, location, x, y);
						stream.close();
						break;
					}
				case KPMessageType.KMT_glUniform2fv:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						byte error = stream.readByte();
						stream.skip(4); // program id
						int location = stream.readInt();
						int count = stream.readInt();

						res = string.Format("glUniform2fv(error = {0}, location = {1}, count = {2}, v = ", error, location, count);

						res += "{";
						for (int i = 0; i < count; i++)
						{
							res += string.Format("({0}, {1})", stream.readFloat(), stream.readFloat());
							if (i < count - 1) res += ", ";
						}
						res += "});";

						stream.close();
						break;
					}
				case KPMessageType.KMT_glUniform2i:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						byte error = stream.readByte();
						stream.skip(4); // program id
						int location = stream.readInt();
						int x = stream.readInt();
						int y = stream.readInt();
						res = string.Format("glUniform2i(error = {0}, location = {1}, x = {2}, y = {3});", error, location, x, y);
						stream.close();
						break;
					}
				case KPMessageType.KMT_glUniform2iv:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						byte error = stream.readByte();
						stream.skip(4); // program id
						int location = stream.readInt();
						int count = stream.readInt();

						res = string.Format("glUniform2iv(error = {0}, location = {1}, count = {2}, v = ", error, location, count);

						res += "{";
						for (int i = 0; i < count; i++)
						{
							res += string.Format("({0}, {1})", stream.readInt(), stream.readInt());
							if (i < count - 1) res += ", ";
						}
						res += "});";

						stream.close();
						break;
					}
				case KPMessageType.KMT_glUniform3f:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						byte error = stream.readByte();
						stream.skip(4); // program id
						int location = stream.readInt();
						float x = stream.readFloat();
						float y = stream.readFloat();
						float z = stream.readFloat();
						res = string.Format("glUniform3f(error = {0}, location = {1}, x = {2}, y = {3}, z = {4});", error, location, x, y, z);
						stream.close();
						break;
					}
				case KPMessageType.KMT_glUniform3fv:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						byte error = stream.readByte();
						stream.skip(4); // program id
						int location = stream.readInt();
						int count = stream.readInt();

						res = string.Format("glUniform3fv(error = {0}, location = {1}, count = {2}, v = ", error, location, count);

						res += "{";
						for (int i = 0; i < count; i++)
						{
							res += string.Format("({0}, {1}, {2})", stream.readFloat(), stream.readFloat(), stream.readFloat());
							if (i < count - 1) res += ", ";
						}
						res += "});";

						stream.close();
						break;
					}
				case KPMessageType.KMT_glUniform3i:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						byte error = stream.readByte();
						stream.skip(4); // program id
						int location = stream.readInt();
						int x = stream.readInt();
						int y = stream.readInt();
						int z = stream.readInt();
						res = string.Format("glUniform3i(error = {0}, location = {1}, x = {2}, y = {3}, z = {4});", error, location, x, y, z);
						stream.close();
						break;
					}
				case KPMessageType.KMT_glUniform3iv:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						byte error = stream.readByte();
						stream.skip(4); // program id
						int location = stream.readInt();
						int count = stream.readInt();

						res = string.Format("glUniform3iv(error = {0}, location = {1}, count = {2}, v = ", error, location, count);

						res += "{";
						for (int i = 0; i < count; i++)
						{
							res += string.Format("({0}, {1}, {2})", stream.readInt(), stream.readInt(), stream.readInt());
							if (i < count - 1) res += ", ";
						}
						res += "});";

						stream.close();
						break;
					}
				case KPMessageType.KMT_glUniform4f:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						byte error = stream.readByte();
						stream.skip(4); // program id
						int location = stream.readInt();
						float x = stream.readFloat();
						float y = stream.readFloat();
						float z = stream.readFloat();
						float w = stream.readFloat();
						res = string.Format("glUniform4f(error = {0}, location = {1}, x = {2}, y = {3}, z = {4}, w = {5});",
							error, location, x, y, z, w);
						stream.close();
						break;
					}
				case KPMessageType.KMT_glUniform4fv:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						byte error = stream.readByte();
						stream.skip(4); // program id
						int location = stream.readInt();
						int count = stream.readInt();

						res = string.Format("glUniform4fv(error = {0}, location = {1}, count = {2}, v = ", error, location, count);

						res += "{";
						for (int i = 0; i < count; i++)
						{
							res += string.Format("({0}, {1}, {2}, {3})", stream.readFloat(), stream.readFloat(), stream.readFloat(), stream.readFloat());
							if (i < count - 1) res += ", ";
						}
						res += "});";

						stream.close();
						break;
					}
				case KPMessageType.KMT_glUniform4i:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						byte error = stream.readByte();
						stream.skip(4); // program id
						int location = stream.readInt();
						int x = stream.readInt();
						int y = stream.readInt();
						int z = stream.readInt();
						int w = stream.readInt();
						res = string.Format("glUniform4i(error = {0}, location = {1}, x = {2}, y = {3}, z = {4}, w = {5});",
							error, location, x, y, z, w);
						stream.close();
						break;
					}
				case KPMessageType.KMT_glUniform4iv:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						byte error = stream.readByte();
						stream.skip(4); // program id
						int location = stream.readInt();
						int count = stream.readInt();

						res = string.Format("glUniform4iv(error = {0}, location = {1}, count = {2}, v = ", error, location, count);

						res += "{";
						for (int i = 0; i < count; i++)
						{
							res += string.Format("({0}, {1}, {2}, {3})", stream.readInt(), stream.readInt(), stream.readInt(), stream.readInt());
							if (i < count - 1) res += ", ";
						}
						res += "});";

						stream.close();
						break;
					}
				case KPMessageType.KMT_glUniformMatrix2fv:
					{
						res = toString_Matrix(2);
						break;
					}
				case KPMessageType.KMT_glUniformMatrix3fv:
					{
						res = toString_Matrix(3);
						break;
					}
				case KPMessageType.KMT_glUniformMatrix4fv:
					{
						res = toString_Matrix(4);
						break;
					}
				#endregion
				case KPMessageType.KMT_glUseProgram:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						uint program = stream.readUInt();
						uint actualProgram = stream.readUInt();
						res = string.Format("glUseProgram(program = {0}, actualProgram = {1});", program, actualProgram);
						stream.close();
						break;
					}
				case KPMessageType.KMT_glValidateProgram:
					{
						MyBinStream stream = new MyBinStream(m_pData);
						uint program = stream.readUInt();
						res = string.Format("glValidateProgram(program = {0});", program);
						stream.close();
						stream = null;
						break;
					}

				case KPMessageType.KMT_glVertexAttrib1f:
				case KPMessageType.KMT_glVertexAttrib1fv:
					{
						string func = type == KPMessageType.KMT_glVertexAttrib1f ? "glVertexAttrib1f" : "glVertexAttrib1fv";
						MyBinStream stream = new MyBinStream(m_pData);
						byte error = stream.readByte();
						uint indx = stream.readUInt();
						float x = stream.readFloat();
						res = func + string.Format("(error = {0}, indx = {1}, x = {2});", error, indx, x);
						stream.close();
						break;
					}

				case KPMessageType.KMT_glVertexAttrib2f:
				case KPMessageType.KMT_glVertexAttrib2fv:
					{
						string func = type == KPMessageType.KMT_glVertexAttrib2f ? "glVertexAttrib2f" : "glVertexAttrib2fv";
						MyBinStream stream = new MyBinStream(m_pData);
						byte error = stream.readByte();
						uint indx = stream.readUInt();
						float x = stream.readFloat();
						float y = stream.readFloat();
						res = func + string.Format("(error = {0}, indx = {1}, x = {2}, y = {3});", error, indx, x, y);
						stream.close();
						break;
					}

				case KPMessageType.KMT_glVertexAttrib3f:
				case KPMessageType.KMT_glVertexAttrib3fv:
					{
						string func = type == KPMessageType.KMT_glVertexAttrib3f ? "glVertexAttrib3f" : "glVertexAttrib3fv";
						MyBinStream stream = new MyBinStream(m_pData);
						byte error = stream.readByte();
						uint indx = stream.readUInt();
						float x = stream.readFloat();
						float y = stream.readFloat();
						float z = stream.readFloat();
						res = func + string.Format("(error = {0}, indx = {1}, x = {2}, y = {3}, z = {4});", error, indx, x, y, z);
						stream.close();
						break;
					}

				case KPMessageType.KMT_glVertexAttrib4f:
				case KPMessageType.KMT_glVertexAttrib4fv:
					{
						string func = type == KPMessageType.KMT_glVertexAttrib4f ? "glVertexAttrib4f" : "glVertexAttrib4fv";
						MyBinStream stream = new MyBinStream(m_pData);
						byte error = stream.readByte();
						uint indx = stream.readUInt();
						float x = stream.readFloat();
						float y = stream.readFloat();
						float z = stream.readFloat();
						float w = stream.readFloat();
						res = func + string.Format("(error = {0}, indx = {1}, x = {2}, y = {3}, z = {4}, w = {5});",
							error, indx, x, y, z, w);
						stream.close();
						break;
					}

				case KPMessageType.KMT_glVertexAttribPointer:
					{
						MyBinStream stream = new MyBinStream(m_pData);

						res = "glVertexAttribPointer(" +
							"error = " + stream.readByte() +
							", indx = " + stream.readUInt() +
							", size = " + stream.readInt() +
							", type = " + gl.getString(stream.readUInt()) +
							", normalized = " + gl.getBoolean(stream.readByte()) +
							", stride = " + stream.readInt() +
							", ptr = 0x" + stream.readInt().ToString("X") +
							");";

						stream.close();
						stream = null;

						break;
					}
				case KPMessageType.KMT_glViewport:
					{
						MyBinStream stream = new MyBinStream(m_pData);

						res = "glViewport(" +
							"x = " + stream.readInt() +
							", y = " + stream.readInt() +
							", width = " + stream.readInt() +
							", height = " + stream.readInt() +
							");";

						stream.close();
						stream = null;
						break;
					}

				// Extensions
				case KPMessageType.KMT_glMapBufferOES:
					{
						MyBinStream stream = new MyBinStream(m_pData);

						byte error = stream.readByte();
						uint vboId = stream.readUInt();
						uint target = stream.readUInt();
						uint access = stream.readUInt();
						int ptr = stream.readInt();
						stream.close();

						res = string.Format("glMapBufferOES(error = {0}, target = {1}, access = 0x{2}, ptr = 0x{3});"
							, error
							, gl.getString(target)
							, access.ToString("X")
							, ptr.ToString("X")
						);

						break;
					}
				case KPMessageType.KMT_glUnmapBufferOES:
					{
						MyBinStream stream = new MyBinStream(m_pData);

						byte error = stream.readByte();
						uint vboId = stream.readUInt();
						uint target = stream.readUInt();
						stream.close();

						res = string.Format("glUnmapBufferOES(error = {0}, target = {1});"
							, error
							, gl.getString(target)
						);

						break;
					}
				// OpenGLES 3.0
				case KPMessageType.KMT_glTexStorage2D:
					{
						MyBinStream stream = new MyBinStream(m_pData);

						byte error = stream.readByte();
						uint id = stream.readUInt();
						uint target = stream.readUInt();
						int levels = stream.readInt();
						int internalformat = stream.readInt();
						int width = stream.readInt();
						int height = stream.readInt();

						stream.close();

						res = string.Format("glTexStorage2D(error = {0}, id = {1}, target = {2}, levels = {3}, " +
							"internalformat = {4}, width = {5}, height = {6});"
							, error
							, id
							, gl.getString(target)
							, levels
							, gl.getString(internalformat)
							, width
							, height
						);

						break;
					}
			} // switch

			const int max = 2048;
			if (res.Length > max)
			{
				res = res.Substring(0, max);
			}

			return res;
		}

		private string toString_Matrix(int size)
		{
			MyBinStream stream = new MyBinStream(m_pData);
			byte error = stream.readByte();
			stream.skip(4); // program id

			int location = stream.readInt();
			int count = stream.readInt();
			byte transpose = stream.readByte();

			string res = string.Format("glUniformMatrix{0}fv(error = {1}, location = {2}, count = {3}, transpose = {4}, "
				, size
				, error
				, location
				, count
				, transpose
			);

			res += "value = {";
			res += Utils.makeMatrixString(stream, count, size);
			res += "});";

			stream.close();
			return res;
		}
	}
}
