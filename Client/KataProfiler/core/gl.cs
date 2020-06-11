using System;
using System.Collections.Generic;
using System.Text;

namespace KataProfiler
{
	class gl
	{
		private const string NOT_AVAILABLE = "N/A";
		private const bool DEBUG = false;

		private static Dictionary<string, uint> m_sDict;

		public static void init()
		{
			m_sDict = new Dictionary<string, uint>();

			/* OpenGL ES core versions */
			m_sDict.Add("GL_ES_VERSION_2_0", 1);

			/* ClearBufferMask */
			m_sDict.Add("GL_DEPTH_BUFFER_BIT", 0x00000100);
			m_sDict.Add("GL_STENCIL_BUFFER_BIT", 0x00000400);
			m_sDict.Add("GL_COLOR_BUFFER_BIT", 0x00004000);

			/* Boolean */
			m_sDict.Add("GL_FALSE", 0);
			m_sDict.Add("GL_TRUE", 1);

			/* BeginMode */
			m_sDict.Add("GL_POINTS", 0x0000);
			m_sDict.Add("GL_LINES", 0x0001);
			m_sDict.Add("GL_LINE_LOOP", 0x0002);
			m_sDict.Add("GL_LINE_STRIP", 0x0003);
			m_sDict.Add("GL_TRIANGLES", 0x0004);
			m_sDict.Add("GL_TRIANGLE_STRIP", 0x0005);
			m_sDict.Add("GL_TRIANGLE_FAN", 0x0006);

			/* AlphaFunction (not supported in ES20) */
			/*	  GL_NEVER */
			/*	  GL_LESS */
			/*	  GL_EQUAL */
			/*	  GL_LEQUAL */
			/*	  GL_GREATER */
			/*	  GL_NOTEQUAL */
			/*	  GL_GEQUAL */
			/*	  GL_ALWAYS */

			/* BlendingFactorDest */
			m_sDict.Add("GL_ZERO", 0);
			m_sDict.Add("GL_ONE", 1);
			m_sDict.Add("GL_SRC_COLOR", 0x0300);
			m_sDict.Add("GL_ONE_MINUS_SRC_COLOR", 0x0301);
			m_sDict.Add("GL_SRC_ALPHA", 0x0302);
			m_sDict.Add("GL_ONE_MINUS_SRC_ALPHA", 0x0303);
			m_sDict.Add("GL_DST_ALPHA", 0x0304);
			m_sDict.Add("GL_ONE_MINUS_DST_ALPHA", 0x0305);

			/* BlendingFactorSrc */
			/*	  GL_ZERO */
			/*	  GL_ONE */
			m_sDict.Add("GL_DST_COLOR", 0x0306);
			m_sDict.Add("GL_ONE_MINUS_DST_COLOR", 0x0307);
			m_sDict.Add("GL_SRC_ALPHA_SATURATE", 0x0308);
			/*	  GL_SRC_ALPHA */
			/*	  GL_ONE_MINUS_SRC_ALPHA */
			/*	  GL_DST_ALPHA */
			/*	  GL_ONE_MINUS_DST_ALPHA */

			/* BlendEquationSeparate */
			m_sDict.Add("GL_FUNC_ADD", 0x8006);
			m_sDict.Add("GL_BLEND_EQUATION", 0x8009);
			m_sDict.Add("GL_BLEND_EQUATION_RGB", 0x8009);	/* same as BLEND_EQUATION */
			m_sDict.Add("GL_BLEND_EQUATION_ALPHA", 0x883D);

			/* BlendSubtract */
			m_sDict.Add("GL_FUNC_SUBTRACT", 0x800A);
			m_sDict.Add("GL_FUNC_REVERSE_SUBTRACT", 0x800B);

			/* Separate Blend Functions */
			m_sDict.Add("GL_BLEND_DST_RGB", 0x80C8);
			m_sDict.Add("GL_BLEND_SRC_RGB", 0x80C9);
			m_sDict.Add("GL_BLEND_DST_ALPHA", 0x80CA);
			m_sDict.Add("GL_BLEND_SRC_ALPHA", 0x80CB);
			m_sDict.Add("GL_CONSTANT_COLOR", 0x8001);
			m_sDict.Add("GL_ONE_MINUS_CONSTANT_COLOR", 0x8002);
			m_sDict.Add("GL_CONSTANT_ALPHA", 0x8003);
			m_sDict.Add("GL_ONE_MINUS_CONSTANT_ALPHA", 0x8004);
			m_sDict.Add("GL_BLEND_COLOR", 0x8005);

			/* Buffer Objects */
			m_sDict.Add("GL_ARRAY_BUFFER", 0x8892);
			m_sDict.Add("GL_ELEMENT_ARRAY_BUFFER", 0x8893);
			m_sDict.Add("GL_ARRAY_BUFFER_BINDING", 0x8894);
			m_sDict.Add("GL_ELEMENT_ARRAY_BUFFER_BINDING", 0x8895);

			m_sDict.Add("GL_STREAM_DRAW", 0x88E0);
			m_sDict.Add("GL_STATIC_DRAW", 0x88E4);
			m_sDict.Add("GL_DYNAMIC_DRAW", 0x88E8);

			m_sDict.Add("GL_BUFFER_SIZE", 0x8764);
			m_sDict.Add("GL_BUFFER_USAGE", 0x8765);

			m_sDict.Add("GL_CURRENT_VERTEX_ATTRIB", 0x8626);

			/* CullFaceMode */
			m_sDict.Add("GL_FRONT", 0x0404);
			m_sDict.Add("GL_BACK", 0x0405);
			m_sDict.Add("GL_FRONT_AND_BACK", 0x0408);

			/* DepthFunction */
			/*	  GL_NEVER */
			/*	  GL_LESS */
			/*	  GL_EQUAL */
			/*	  GL_LEQUAL */
			/*	  GL_GREATER */
			/*	  GL_NOTEQUAL */
			/*	  GL_GEQUAL */
			/*	  GL_ALWAYS */

			/* EnableCap */
			m_sDict.Add("GL_TEXTURE_2D", 0x0DE1);
			m_sDict.Add("GL_CULL_FACE", 0x0B44);
			m_sDict.Add("GL_BLEND", 0x0BE2);
			m_sDict.Add("GL_DITHER", 0x0BD0);
			m_sDict.Add("GL_STENCIL_TEST", 0x0B90);
			m_sDict.Add("GL_DEPTH_TEST", 0x0B71);
			m_sDict.Add("GL_SCISSOR_TEST", 0x0C11);
			m_sDict.Add("GL_POLYGON_OFFSET_FILL", 0x8037);
			m_sDict.Add("GL_SAMPLE_ALPHA_TO_COVERAGE", 0x809E);
			m_sDict.Add("GL_SAMPLE_COVERAGE", 0x80A0);

			/* ErrorCode */
			m_sDict.Add("GL_NO_ERROR", 0);
			m_sDict.Add("GL_INVALID_ENUM", 0x0500);
			m_sDict.Add("GL_INVALID_VALUE", 0x0501);
			m_sDict.Add("GL_INVALID_OPERATION", 0x0502);
			m_sDict.Add("GL_OUT_OF_MEMORY", 0x0505);

			/* FrontFaceDirection */
			m_sDict.Add("GL_CW", 0x0900);
			m_sDict.Add("GL_CCW", 0x0901);

			/* GetPName */
			m_sDict.Add("GL_LINE_WIDTH", 0x0B21);
			m_sDict.Add("GL_ALIASED_POINT_SIZE_RANGE", 0x846D);
			m_sDict.Add("GL_ALIASED_LINE_WIDTH_RANGE", 0x846E);
			m_sDict.Add("GL_CULL_FACE_MODE", 0x0B45);
			m_sDict.Add("GL_FRONT_FACE", 0x0B46);
			m_sDict.Add("GL_DEPTH_RANGE", 0x0B70);
			m_sDict.Add("GL_DEPTH_WRITEMASK", 0x0B72);
			m_sDict.Add("GL_DEPTH_CLEAR_VALUE", 0x0B73);
			m_sDict.Add("GL_DEPTH_FUNC", 0x0B74);
			m_sDict.Add("GL_STENCIL_CLEAR_VALUE", 0x0B91);
			m_sDict.Add("GL_STENCIL_FUNC", 0x0B92);
			m_sDict.Add("GL_STENCIL_FAIL", 0x0B94);
			m_sDict.Add("GL_STENCIL_PASS_DEPTH_FAIL", 0x0B95);
			m_sDict.Add("GL_STENCIL_PASS_DEPTH_PASS", 0x0B96);
			m_sDict.Add("GL_STENCIL_REF", 0x0B97);
			m_sDict.Add("GL_STENCIL_VALUE_MASK", 0x0B93);
			m_sDict.Add("GL_STENCIL_WRITEMASK", 0x0B98);
			m_sDict.Add("GL_STENCIL_BACK_FUNC", 0x8800);
			m_sDict.Add("GL_STENCIL_BACK_FAIL", 0x8801);
			m_sDict.Add("GL_STENCIL_BACK_PASS_DEPTH_FAIL", 0x8802);
			m_sDict.Add("GL_STENCIL_BACK_PASS_DEPTH_PASS", 0x8803);
			m_sDict.Add("GL_STENCIL_BACK_REF", 0x8CA3);
			m_sDict.Add("GL_STENCIL_BACK_VALUE_MASK", 0x8CA4);
			m_sDict.Add("GL_STENCIL_BACK_WRITEMASK", 0x8CA5);
			m_sDict.Add("GL_VIEWPORT", 0x0BA2);
			m_sDict.Add("GL_SCISSOR_BOX", 0x0C10);
			/*	  GL_SCISSOR_TEST */
			m_sDict.Add("GL_COLOR_CLEAR_VALUE", 0x0C22);
			m_sDict.Add("GL_COLOR_WRITEMASK", 0x0C23);
			m_sDict.Add("GL_UNPACK_ALIGNMENT", 0x0CF5);
			m_sDict.Add("GL_PACK_ALIGNMENT", 0x0D05);
			m_sDict.Add("GL_MAX_TEXTURE_SIZE", 0x0D33);
			m_sDict.Add("GL_MAX_VIEWPORT_DIMS", 0x0D3A);
			m_sDict.Add("GL_SUBPIXEL_BITS", 0x0D50);
			m_sDict.Add("GL_RED_BITS", 0x0D52);
			m_sDict.Add("GL_GREEN_BITS", 0x0D53);
			m_sDict.Add("GL_BLUE_BITS", 0x0D54);
			m_sDict.Add("GL_ALPHA_BITS", 0x0D55);
			m_sDict.Add("GL_DEPTH_BITS", 0x0D56);
			m_sDict.Add("GL_STENCIL_BITS", 0x0D57);
			m_sDict.Add("GL_POLYGON_OFFSET_UNITS", 0x2A00);
			/*	  GL_POLYGON_OFFSET_FILL */
			m_sDict.Add("GL_POLYGON_OFFSET_FACTOR", 0x8038);
			m_sDict.Add("GL_TEXTURE_BINDING_2D", 0x8069);
			m_sDict.Add("GL_SAMPLE_BUFFERS", 0x80A8);
			m_sDict.Add("GL_SAMPLES", 0x80A9);
			m_sDict.Add("GL_SAMPLE_COVERAGE_VALUE", 0x80AA);
			m_sDict.Add("GL_SAMPLE_COVERAGE_INVERT", 0x80AB);

			/* GetTextureParameter */
			/*	  GL_TEXTURE_MAG_FILTER */
			/*	  GL_TEXTURE_MIN_FILTER */
			/*	  GL_TEXTURE_WRAP_S */
			/*	  GL_TEXTURE_WRAP_T */

			m_sDict.Add("GL_NUM_COMPRESSED_TEXTURE_FORMATS", 0x86A2);
			m_sDict.Add("GL_COMPRESSED_TEXTURE_FORMATS", 0x86A3);

			/* HintMode */
			m_sDict.Add("GL_DONT_CARE", 0x1100);
			m_sDict.Add("GL_FASTEST", 0x1101);
			m_sDict.Add("GL_NICEST", 0x1102);

			/* HintTarget */
			m_sDict.Add("GL_GENERATE_MIPMAP_HINT", 0x8192);

			/* DataType */
			m_sDict.Add("GL_BYTE", 0x1400);
			m_sDict.Add("GL_UNSIGNED_BYTE", 0x1401);
			m_sDict.Add("GL_SHORT", 0x1402);
			m_sDict.Add("GL_UNSIGNED_SHORT", 0x1403);
			m_sDict.Add("GL_INT", 0x1404);
			m_sDict.Add("GL_UNSIGNED_INT", 0x1405);
			m_sDict.Add("GL_FLOAT", 0x1406);
			m_sDict.Add("GL_FIXED", 0x140C);

			/* PixelFormat */
			m_sDict.Add("GL_DEPTH_COMPONENT", 0x1902);
			m_sDict.Add("GL_ALPHA", 0x1906);
			m_sDict.Add("GL_RGB", 0x1907);
			m_sDict.Add("GL_RGBA", 0x1908);
			m_sDict.Add("GL_LUMINANCE", 0x1909);
			m_sDict.Add("GL_LUMINANCE_ALPHA", 0x190A);

			/* PixelType */
			/*	  GL_UNSIGNED_BYTE */
			m_sDict.Add("GL_UNSIGNED_SHORT_4_4_4_4", 0x8033);
			m_sDict.Add("GL_UNSIGNED_SHORT_5_5_5_1", 0x8034);
			m_sDict.Add("GL_UNSIGNED_SHORT_5_6_5", 0x8363);

			/* Shaders */
			m_sDict.Add("GL_FRAGMENT_SHADER", 0x8B30);
			m_sDict.Add("GL_VERTEX_SHADER", 0x8B31);
			m_sDict.Add("GL_MAX_VERTEX_ATTRIBS", 0x8869);
			m_sDict.Add("GL_MAX_VERTEX_UNIFORM_VECTORS", 0x8DFB);
			m_sDict.Add("GL_MAX_VARYING_VECTORS", 0x8DFC);
			m_sDict.Add("GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS", 0x8B4D);
			m_sDict.Add("GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS", 0x8B4C);
			m_sDict.Add("GL_MAX_TEXTURE_IMAGE_UNITS", 0x8872);
			m_sDict.Add("GL_MAX_FRAGMENT_UNIFORM_VECTORS", 0x8DFD);
			m_sDict.Add("GL_SHADER_TYPE", 0x8B4F);
			m_sDict.Add("GL_DELETE_STATUS", 0x8B80);
			m_sDict.Add("GL_LINK_STATUS", 0x8B82);
			m_sDict.Add("GL_VALIDATE_STATUS", 0x8B83);
			m_sDict.Add("GL_ATTACHED_SHADERS", 0x8B85);
			m_sDict.Add("GL_ACTIVE_UNIFORMS", 0x8B86);
			m_sDict.Add("GL_ACTIVE_UNIFORM_MAX_LENGTH", 0x8B87);
			m_sDict.Add("GL_ACTIVE_ATTRIBUTES", 0x8B89);
			m_sDict.Add("GL_ACTIVE_ATTRIBUTE_MAX_LENGTH", 0x8B8A);
			m_sDict.Add("GL_SHADING_LANGUAGE_VERSION", 0x8B8C);
			m_sDict.Add("GL_CURRENT_PROGRAM", 0x8B8D);

			/* StencilFunction */
			m_sDict.Add("GL_NEVER", 0x0200);
			m_sDict.Add("GL_LESS", 0x0201);
			m_sDict.Add("GL_EQUAL", 0x0202);
			m_sDict.Add("GL_LEQUAL", 0x0203);
			m_sDict.Add("GL_GREATER", 0x0204);
			m_sDict.Add("GL_NOTEQUAL", 0x0205);
			m_sDict.Add("GL_GEQUAL", 0x0206);
			m_sDict.Add("GL_ALWAYS", 0x0207);

			/* StencilOp */
			/*	  GL_ZERO */
			m_sDict.Add("GL_KEEP", 0x1E00);
			m_sDict.Add("GL_REPLACE", 0x1E01);
			m_sDict.Add("GL_INCR", 0x1E02);
			m_sDict.Add("GL_DECR", 0x1E03);
			m_sDict.Add("GL_INVERT", 0x150A);
			m_sDict.Add("GL_INCR_WRAP", 0x8507);
			m_sDict.Add("GL_DECR_WRAP", 0x8508);

			/* StringName */
			m_sDict.Add("GL_VENDOR", 0x1F00);
			m_sDict.Add("GL_RENDERER", 0x1F01);
			m_sDict.Add("GL_VERSION", 0x1F02);
			m_sDict.Add("GL_EXTENSIONS", 0x1F03);

			/* TextureMagFilter */
			m_sDict.Add("GL_NEAREST", 0x2600);
			m_sDict.Add("GL_LINEAR", 0x2601);

			/* TextureMinFilter */
			/*	  GL_NEAREST */
			/*	  GL_LINEAR */
			m_sDict.Add("GL_NEAREST_MIPMAP_NEAREST", 0x2700);
			m_sDict.Add("GL_LINEAR_MIPMAP_NEAREST", 0x2701);
			m_sDict.Add("GL_NEAREST_MIPMAP_LINEAR", 0x2702);
			m_sDict.Add("GL_LINEAR_MIPMAP_LINEAR", 0x2703);

			/* TextureParameterName */
			m_sDict.Add("GL_TEXTURE_MAG_FILTER", 0x2800);
			m_sDict.Add("GL_TEXTURE_MIN_FILTER", 0x2801);
			m_sDict.Add("GL_TEXTURE_WRAP_S", 0x2802);
			m_sDict.Add("GL_TEXTURE_WRAP_T", 0x2803);

			/* TextureTarget */
			/*	  GL_TEXTURE_2D */
			m_sDict.Add("GL_TEXTURE", 0x1702);

			m_sDict.Add("GL_TEXTURE_CUBE_MAP", 0x8513);
			m_sDict.Add("GL_TEXTURE_BINDING_CUBE_MAP", 0x8514);
			m_sDict.Add("GL_TEXTURE_CUBE_MAP_POSITIVE_X", 0x8515);
			m_sDict.Add("GL_TEXTURE_CUBE_MAP_NEGATIVE_X", 0x8516);
			m_sDict.Add("GL_TEXTURE_CUBE_MAP_POSITIVE_Y", 0x8517);
			m_sDict.Add("GL_TEXTURE_CUBE_MAP_NEGATIVE_Y", 0x8518);
			m_sDict.Add("GL_TEXTURE_CUBE_MAP_POSITIVE_Z", 0x8519);
			m_sDict.Add("GL_TEXTURE_CUBE_MAP_NEGATIVE_Z", 0x851A);
			m_sDict.Add("GL_MAX_CUBE_MAP_TEXTURE_SIZE", 0x851C);

			/* TextureUnit */
			m_sDict.Add("GL_TEXTURE0", 0x84C0);
			m_sDict.Add("GL_TEXTURE1", 0x84C1);
			m_sDict.Add("GL_TEXTURE2", 0x84C2);
			m_sDict.Add("GL_TEXTURE3", 0x84C3);
			m_sDict.Add("GL_TEXTURE4", 0x84C4);
			m_sDict.Add("GL_TEXTURE5", 0x84C5);
			m_sDict.Add("GL_TEXTURE6", 0x84C6);
			m_sDict.Add("GL_TEXTURE7", 0x84C7);
			m_sDict.Add("GL_TEXTURE8", 0x84C8);
			m_sDict.Add("GL_TEXTURE9", 0x84C9);
			m_sDict.Add("GL_TEXTURE10", 0x84CA);
			m_sDict.Add("GL_TEXTURE11", 0x84CB);
			m_sDict.Add("GL_TEXTURE12", 0x84CC);
			m_sDict.Add("GL_TEXTURE13", 0x84CD);
			m_sDict.Add("GL_TEXTURE14", 0x84CE);
			m_sDict.Add("GL_TEXTURE15", 0x84CF);
			m_sDict.Add("GL_TEXTURE16", 0x84D0);
			m_sDict.Add("GL_TEXTURE17", 0x84D1);
			m_sDict.Add("GL_TEXTURE18", 0x84D2);
			m_sDict.Add("GL_TEXTURE19", 0x84D3);
			m_sDict.Add("GL_TEXTURE20", 0x84D4);
			m_sDict.Add("GL_TEXTURE21", 0x84D5);
			m_sDict.Add("GL_TEXTURE22", 0x84D6);
			m_sDict.Add("GL_TEXTURE23", 0x84D7);
			m_sDict.Add("GL_TEXTURE24", 0x84D8);
			m_sDict.Add("GL_TEXTURE25", 0x84D9);
			m_sDict.Add("GL_TEXTURE26", 0x84DA);
			m_sDict.Add("GL_TEXTURE27", 0x84DB);
			m_sDict.Add("GL_TEXTURE28", 0x84DC);
			m_sDict.Add("GL_TEXTURE29", 0x84DD);
			m_sDict.Add("GL_TEXTURE30", 0x84DE);
			m_sDict.Add("GL_TEXTURE31", 0x84DF);
			m_sDict.Add("GL_ACTIVE_TEXTURE", 0x84E0);

			/* TextureWrapMode */
			m_sDict.Add("GL_REPEAT", 0x2901);
			m_sDict.Add("GL_CLAMP_TO_EDGE", 0x812F);
			m_sDict.Add("GL_MIRRORED_REPEAT", 0x8370);

			/* Uniform Types */
			m_sDict.Add("GL_FLOAT_VEC2", 0x8B50);
			m_sDict.Add("GL_FLOAT_VEC3", 0x8B51);
			m_sDict.Add("GL_FLOAT_VEC4", 0x8B52);
			m_sDict.Add("GL_INT_VEC2", 0x8B53);
			m_sDict.Add("GL_INT_VEC3", 0x8B54);
			m_sDict.Add("GL_INT_VEC4", 0x8B55);
			m_sDict.Add("GL_BOOL", 0x8B56);
			m_sDict.Add("GL_BOOL_VEC2", 0x8B57);
			m_sDict.Add("GL_BOOL_VEC3", 0x8B58);
			m_sDict.Add("GL_BOOL_VEC4", 0x8B59);
			m_sDict.Add("GL_FLOAT_MAT2", 0x8B5A);
			m_sDict.Add("GL_FLOAT_MAT3", 0x8B5B);
			m_sDict.Add("GL_FLOAT_MAT4", 0x8B5C);
			m_sDict.Add("GL_SAMPLER_2D", 0x8B5E);
			m_sDict.Add("GL_SAMPLER_CUBE", 0x8B60);

			/* Vertex Arrays */
			m_sDict.Add("GL_VERTEX_ATTRIB_ARRAY_ENABLED", 0x8622);
			m_sDict.Add("GL_VERTEX_ATTRIB_ARRAY_SIZE", 0x8623);
			m_sDict.Add("GL_VERTEX_ATTRIB_ARRAY_STRIDE", 0x8624);
			m_sDict.Add("GL_VERTEX_ATTRIB_ARRAY_TYPE", 0x8625);
			m_sDict.Add("GL_VERTEX_ATTRIB_ARRAY_NORMALIZED", 0x886A);
			m_sDict.Add("GL_VERTEX_ATTRIB_ARRAY_POINTER", 0x8645);
			m_sDict.Add("GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING", 0x889F);

			/* Read Format */
			m_sDict.Add("GL_IMPLEMENTATION_COLOR_READ_TYPE", 0x8B9A);
			m_sDict.Add("GL_IMPLEMENTATION_COLOR_READ_FORMAT", 0x8B9B);

			/* Shader Source */
			m_sDict.Add("GL_COMPILE_STATUS", 0x8B81);
			m_sDict.Add("GL_INFO_LOG_LENGTH", 0x8B84);
			m_sDict.Add("GL_SHADER_SOURCE_LENGTH", 0x8B88);
			m_sDict.Add("GL_SHADER_COMPILER", 0x8DFA);

			/* Shader Binary */
			m_sDict.Add("GL_SHADER_BINARY_FORMATS", 0x8DF8);
			m_sDict.Add("GL_NUM_SHADER_BINARY_FORMATS", 0x8DF9);

			/* Shader Precision-Specified Types */
			m_sDict.Add("GL_LOW_FLOAT", 0x8DF0);
			m_sDict.Add("GL_MEDIUM_FLOAT", 0x8DF1);
			m_sDict.Add("GL_HIGH_FLOAT", 0x8DF2);
			m_sDict.Add("GL_LOW_INT", 0x8DF3);
			m_sDict.Add("GL_MEDIUM_INT", 0x8DF4);
			m_sDict.Add("GL_HIGH_INT", 0x8DF5);

			/* Framebuffer Object. */
			m_sDict.Add("GL_FRAMEBUFFER", 0x8D40);
			m_sDict.Add("GL_RENDERBUFFER", 0x8D41);

			m_sDict.Add("GL_RGBA4", 0x8056);
			m_sDict.Add("GL_RGB5_A1", 0x8057);
			m_sDict.Add("GL_RGB565", 0x8D62);
			m_sDict.Add("GL_DEPTH_COMPONENT16", 0x81A5);
			m_sDict.Add("GL_STENCIL_INDEX", 0x1901);
			m_sDict.Add("GL_STENCIL_INDEX8", 0x8D48);

			m_sDict.Add("GL_RENDERBUFFER_WIDTH", 0x8D42);
			m_sDict.Add("GL_RENDERBUFFER_HEIGHT", 0x8D43);
			m_sDict.Add("GL_RENDERBUFFER_INTERNAL_FORMAT", 0x8D44);
			m_sDict.Add("GL_RENDERBUFFER_RED_SIZE", 0x8D50);
			m_sDict.Add("GL_RENDERBUFFER_GREEN_SIZE", 0x8D51);
			m_sDict.Add("GL_RENDERBUFFER_BLUE_SIZE", 0x8D52);
			m_sDict.Add("GL_RENDERBUFFER_ALPHA_SIZE", 0x8D53);
			m_sDict.Add("GL_RENDERBUFFER_DEPTH_SIZE", 0x8D54);
			m_sDict.Add("GL_RENDERBUFFER_STENCIL_SIZE", 0x8D55);

			m_sDict.Add("GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE", 0x8CD0);
			m_sDict.Add("GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME", 0x8CD1);
			m_sDict.Add("GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL", 0x8CD2);
			m_sDict.Add("GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE", 0x8CD3);

			m_sDict.Add("GL_COLOR_ATTACHMENT0", 0x8CE0);
			m_sDict.Add("GL_DEPTH_ATTACHMENT", 0x8D00);
			m_sDict.Add("GL_STENCIL_ATTACHMENT", 0x8D20);

			m_sDict.Add("GL_NONE", 0);

			m_sDict.Add("GL_FRAMEBUFFER_COMPLETE", 0x8CD5);
			m_sDict.Add("GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT", 0x8CD6);
			m_sDict.Add("GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT", 0x8CD7);
			m_sDict.Add("GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS", 0x8CD9);
			m_sDict.Add("GL_FRAMEBUFFER_UNSUPPORTED", 0x8CDD);

			m_sDict.Add("GL_FRAMEBUFFER_BINDING", 0x8CA6);
			m_sDict.Add("GL_RENDERBUFFER_BINDING", 0x8CA7);
			m_sDict.Add("GL_MAX_RENDERBUFFER_SIZE", 0x84E8);

			m_sDict.Add("GL_INVALID_FRAMEBUFFER_OPERATION", 0x0506);

			//====================================================================================
			// PVR
			m_sDict.Add("PVRTC4 RGB", 0x8C00);
			m_sDict.Add("PVRTC2 RGB", 0x8C01);
			m_sDict.Add("PVRTC4 RGBA", 0x8C02);
			m_sDict.Add("PVRTC2 RGBA", 0x8C03);
			// ETC1
			m_sDict.Add("ETC1", gl.GL_ETC1_RGB8_OES);
			// ETC2
			m_sDict.Add("ETC2 RGB", gl.GL_COMPRESSED_RGB8_ETC2);
			m_sDict.Add("ETC2 RGBA", gl.GL_COMPRESSED_RGBA8_ETC2_EAC);
			// DXT
			m_sDict.Add("DXT1 RGB", gl.GL_COMPRESSED_RGB_S3TC_DXT1_EXT);
			m_sDict.Add("DXT1 RGBA", gl.GL_COMPRESSED_RGBA_S3TC_DXT1_EXT);
			m_sDict.Add("DXT3", gl.GL_COMPRESSED_RGBA_S3TC_DXT3_EXT);
			m_sDict.Add("DXT5", gl.GL_COMPRESSED_RGBA_S3TC_DXT5_EXT);

			// OpenGLES 3.0
			m_sDict.Add("GL_SAMPLER_3D", gl.GL_SAMPLER_3D);
			m_sDict.Add("GL_RGBA8", gl.GL_RGBA8);
			m_sDict.Add("GL_RGB8", gl.GL_RGB8);
		}

		public static string getString(int value)
		{
			return getString((uint)value);
		}

		public static string getString(int value, string[] keys)
		{
			return getString((uint)value, keys);
		}

		public static string getString(uint value)
		{
			return getString(value, null);
		}

		public static string getString(uint value, string[] keys)
		{
			if (keys == null || keys.Length == 0)
			{
				string result = null;
				foreach (KeyValuePair<string, uint> pair in m_sDict)
				{
					if (pair.Value == value)
					{
							return pair.Key;
					}
				}

				if (result == null)
				{
					Utils.assert(false); //TODO
					return NOT_AVAILABLE;
				}
				return result;
			}

			foreach (KeyValuePair<string, uint> pair in m_sDict)
			{
				if (pair.Value == value)
				{
					foreach (string k in keys)
					{
						if (k == pair.Key) return k;
					}
				}
			}

			return NOT_AVAILABLE;
		}

		public static string getMask(uint mask, string[] keys)
		{
			string res = "";
			foreach (string k in keys)
			{
				if ((mask & m_sDict[k]) != 0) res += k + " | ";
			}
			res = res.Length > 0 ? res.Substring(0, res.Length - 3) : NOT_AVAILABLE;
			return res;
		}

		public static string getBoolean(byte v)
		{
			return v == 0 ? "GL_FALSE" : "GL_TRUE";
		}

		#region OpenGL ES 2.0 header

		/* OpenGL ES core versions */
		public const uint GL_ES_VERSION_2_0 = 1;

		/* ClearBufferMask */
		public const uint GL_DEPTH_BUFFER_BIT = 0x00000100;
		public const uint GL_STENCIL_BUFFER_BIT = 0x00000400;
		public const uint GL_COLOR_BUFFER_BIT = 0x00004000;

		/* Boolean */
		public const uint GL_FALSE = 0;
		public const uint GL_TRUE = 1;

		/* BeginMode */
		public const uint GL_POuintS = 0x0000;
		public const uint GL_LINES = 0x0001;
		public const uint GL_LINE_LOOP = 0x0002;
		public const uint GL_LINE_STRIP = 0x0003;
		public const uint GL_TRIANGLES = 0x0004;
		public const uint GL_TRIANGLE_STRIP = 0x0005;
		public const uint GL_TRIANGLE_FAN = 0x0006;

		/* AlphaFunction (not supported in ES20) */
		/*	  GL_NEVER */
		/*	  GL_LESS */
		/*	  GL_EQUAL */
		/*	  GL_LEQUAL */
		/*	  GL_GREATER */
		/*	  GL_NOTEQUAL */
		/*	  GL_GEQUAL */
		/*	  GL_ALWAYS */

		/* BlendingFactorDest */
		public const uint GL_ZERO = 0;
		public const uint GL_ONE = 1;
		public const uint GL_SRC_COLOR = 0x0300;
		public const uint GL_ONE_MINUS_SRC_COLOR = 0x0301;
		public const uint GL_SRC_ALPHA = 0x0302;
		public const uint GL_ONE_MINUS_SRC_ALPHA = 0x0303;
		public const uint GL_DST_ALPHA = 0x0304;
		public const uint GL_ONE_MINUS_DST_ALPHA = 0x0305;

		/* BlendingFactorSrc */
		/*	  GL_ZERO */
		/*	  GL_ONE */
		public const uint GL_DST_COLOR = 0x0306;
		public const uint GL_ONE_MINUS_DST_COLOR = 0x0307;
		public const uint GL_SRC_ALPHA_SATURATE = 0x0308;
		/*	  GL_SRC_ALPHA */
		/*	  GL_ONE_MINUS_SRC_ALPHA */
		/*	  GL_DST_ALPHA */
		/*	  GL_ONE_MINUS_DST_ALPHA */

		/* BlendEquationSeparate */
		public const uint GL_FUNC_ADD = 0x8006;
		public const uint GL_BLEND_EQUATION = 0x8009;
		public const uint GL_BLEND_EQUATION_RGB = 0x8009;	/* same as BLEND_EQUATION */
		public const uint GL_BLEND_EQUATION_ALPHA = 0x883D;

		/* BlendSubtract */
		public const uint GL_FUNC_SUBTRACT = 0x800A;
		public const uint GL_FUNC_REVERSE_SUBTRACT = 0x800B;

		/* Separate Blend Functions */
		public const uint GL_BLEND_DST_RGB = 0x80C8;
		public const uint GL_BLEND_SRC_RGB = 0x80C9;
		public const uint GL_BLEND_DST_ALPHA = 0x80CA;
		public const uint GL_BLEND_SRC_ALPHA = 0x80CB;
		public const uint GL_CONSTANT_COLOR = 0x8001;
		public const uint GL_ONE_MINUS_CONSTANT_COLOR = 0x8002;
		public const uint GL_CONSTANT_ALPHA = 0x8003;
		public const uint GL_ONE_MINUS_CONSTANT_ALPHA = 0x8004;
		public const uint GL_BLEND_COLOR = 0x8005;

		/* Buffer Objects */
		public const uint GL_ARRAY_BUFFER = 0x8892;
		public const uint GL_ELEMENT_ARRAY_BUFFER = 0x8893;
		public const uint GL_ARRAY_BUFFER_BINDING = 0x8894;
		public const uint GL_ELEMENT_ARRAY_BUFFER_BINDING = 0x8895;

		public const uint GL_STREAM_DRAW = 0x88E0;
		public const uint GL_STATIC_DRAW = 0x88E4;
		public const uint GL_DYNAMIC_DRAW = 0x88E8;

		public const uint GL_BUFFER_SIZE = 0x8764;
		public const uint GL_BUFFER_USAGE = 0x8765;

		public const uint GL_CURRENT_VERTEX_ATTRIB = 0x8626;

		/* CullFaceMode */
		public const uint GL_FRONT = 0x0404;
		public const uint GL_BACK = 0x0405;
		public const uint GL_FRONT_AND_BACK = 0x0408;

		/* DepthFunction */
		/*	  GL_NEVER */
		/*	  GL_LESS */
		/*	  GL_EQUAL */
		/*	  GL_LEQUAL */
		/*	  GL_GREATER */
		/*	  GL_NOTEQUAL */
		/*	  GL_GEQUAL */
		/*	  GL_ALWAYS */

		/* EnableCap */
		public const uint GL_TEXTURE_2D = 0x0DE1;
		public const uint GL_CULL_FACE = 0x0B44;
		public const uint GL_BLEND = 0x0BE2;
		public const uint GL_DITHER = 0x0BD0;
		public const uint GL_STENCIL_TEST = 0x0B90;
		public const uint GL_DEPTH_TEST = 0x0B71;
		public const uint GL_SCISSOR_TEST = 0x0C11;
		public const uint GL_POLYGON_OFFSET_FILL = 0x8037;
		public const uint GL_SAMPLE_ALPHA_TO_COVERAGE = 0x809E;
		public const uint GL_SAMPLE_COVERAGE = 0x80A0;

		/* ErrorCode */
		public const uint GL_NO_ERROR = 0;
		public const uint GL_INVALID_ENUM = 0x0500;
		public const uint GL_INVALID_VALUE = 0x0501;
		public const uint GL_INVALID_OPERATION = 0x0502;
		public const uint GL_OUT_OF_MEMORY = 0x0505;

		/* FrontFaceDirection */
		public const uint GL_CW = 0x0900;
		public const uint GL_CCW = 0x0901;

		/* GetPName */
		public const uint GL_LINE_WIDTH = 0x0B21;
		public const uint GL_ALIASED_POINT_SIZE_RANGE = 0x846D;
		public const uint GL_ALIASED_LINE_WIDTH_RANGE = 0x846E;
		public const uint GL_CULL_FACE_MODE = 0x0B45;
		public const uint GL_FRONT_FACE = 0x0B46;
		public const uint GL_DEPTH_RANGE = 0x0B70;
		public const uint GL_DEPTH_WRITEMASK = 0x0B72;
		public const uint GL_DEPTH_CLEAR_VALUE = 0x0B73;
		public const uint GL_DEPTH_FUNC = 0x0B74;
		public const uint GL_STENCIL_CLEAR_VALUE = 0x0B91;
		public const uint GL_STENCIL_FUNC = 0x0B92;
		public const uint GL_STENCIL_FAIL = 0x0B94;
		public const uint GL_STENCIL_PASS_DEPTH_FAIL = 0x0B95;
		public const uint GL_STENCIL_PASS_DEPTH_PASS = 0x0B96;
		public const uint GL_STENCIL_REF = 0x0B97;
		public const uint GL_STENCIL_VALUE_MASK = 0x0B93;
		public const uint GL_STENCIL_WRITEMASK = 0x0B98;
		public const uint GL_STENCIL_BACK_FUNC = 0x8800;
		public const uint GL_STENCIL_BACK_FAIL = 0x8801;
		public const uint GL_STENCIL_BACK_PASS_DEPTH_FAIL = 0x8802;
		public const uint GL_STENCIL_BACK_PASS_DEPTH_PASS = 0x8803;
		public const uint GL_STENCIL_BACK_REF = 0x8CA3;
		public const uint GL_STENCIL_BACK_VALUE_MASK = 0x8CA4;
		public const uint GL_STENCIL_BACK_WRITEMASK = 0x8CA5;
		public const uint GL_VIEWPORT = 0x0BA2;
		public const uint GL_SCISSOR_BOX = 0x0C10;
		/*	  GL_SCISSOR_TEST */
		public const uint GL_COLOR_CLEAR_VALUE = 0x0C22;
		public const uint GL_COLOR_WRITEMASK = 0x0C23;
		public const uint GL_UNPACK_ALIGNMENT = 0x0CF5;
		public const uint GL_PACK_ALIGNMENT = 0x0D05;
		public const uint GL_MAX_TEXTURE_SIZE = 0x0D33;
		public const uint GL_MAX_VIEWPORT_DIMS = 0x0D3A;
		public const uint GL_SUBPIXEL_BITS = 0x0D50;
		public const uint GL_RED_BITS = 0x0D52;
		public const uint GL_GREEN_BITS = 0x0D53;
		public const uint GL_BLUE_BITS = 0x0D54;
		public const uint GL_ALPHA_BITS = 0x0D55;
		public const uint GL_DEPTH_BITS = 0x0D56;
		public const uint GL_STENCIL_BITS = 0x0D57;
		public const uint GL_POLYGON_OFFSET_UNITS = 0x2A00;
		/*	  GL_POLYGON_OFFSET_FILL */
		public const uint GL_POLYGON_OFFSET_FACTOR = 0x8038;
		public const uint GL_TEXTURE_BINDING_2D = 0x8069;
		public const uint GL_SAMPLE_BUFFERS = 0x80A8;
		public const uint GL_SAMPLES = 0x80A9;
		public const uint GL_SAMPLE_COVERAGE_VALUE = 0x80AA;
		public const uint GL_SAMPLE_COVERAGE_INVERT = 0x80AB;

		/* GetTextureParameter */
		/*	  GL_TEXTURE_MAG_FILTER */
		/*	  GL_TEXTURE_MIN_FILTER */
		/*	  GL_TEXTURE_WRAP_S */
		/*	  GL_TEXTURE_WRAP_T */

		public const uint GL_NUM_COMPRESSED_TEXTURE_FORMATS = 0x86A2;
		public const uint GL_COMPRESSED_TEXTURE_FORMATS = 0x86A3;

		/* HuintMode */
		public const uint GL_DONT_CARE = 0x1100;
		public const uint GL_FASTEST = 0x1101;
		public const uint GL_NICEST = 0x1102;

		/* HuintTarget */
		public const uint GL_GENERATE_MIPMAP_Huint = 0x8192;

		/* DataType */
		public const uint GL_BYTE = 0x1400;
		public const uint GL_UNSIGNED_BYTE = 0x1401;
		public const uint GL_SHORT = 0x1402;
		public const uint GL_UNSIGNED_SHORT = 0x1403;
		public const uint GL_INT = 0x1404;
		public const uint GL_UNSIGNED_INT = 0x1405;
		public const uint GL_FLOAT = 0x1406;
		public const uint GL_FIXED = 0x140C;

		/* PixelFormat */
		public const uint GL_DEPTH_COMPONENT = 0x1902;
		public const uint GL_ALPHA = 0x1906;
		public const uint GL_RGB = 0x1907;
		public const uint GL_RGBA = 0x1908;
		public const uint GL_LUMINANCE = 0x1909;
		public const uint GL_LUMINANCE_ALPHA = 0x190A;

		/* PixelType */
		/*	  GL_UNSIGNED_BYTE */
		public const uint GL_UNSIGNED_SHORT_4_4_4_4 = 0x8033;
		public const uint GL_UNSIGNED_SHORT_5_5_5_1 = 0x8034;
		public const uint GL_UNSIGNED_SHORT_5_6_5 = 0x8363;

		/* Shaders */
		public const uint GL_FRAGMENT_SHADER = 0x8B30;
		public const uint GL_VERTEX_SHADER = 0x8B31;
		public const uint GL_MAX_VERTEX_ATTRIBS = 0x8869;
		public const uint GL_MAX_VERTEX_UNIFORM_VECTORS = 0x8DFB;
		public const uint GL_MAX_VARYING_VECTORS = 0x8DFC;
		public const uint GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS = 0x8B4D;
		public const uint GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS = 0x8B4C;
		public const uint GL_MAX_TEXTURE_IMAGE_UNITS = 0x8872;
		public const uint GL_MAX_FRAGMENT_UNIFORM_VECTORS = 0x8DFD;
		public const uint GL_SHADER_TYPE = 0x8B4F;
		public const uint GL_DELETE_STATUS = 0x8B80;
		public const uint GL_LINK_STATUS = 0x8B82;
		public const uint GL_VALIDATE_STATUS = 0x8B83;
		public const uint GL_ATTACHED_SHADERS = 0x8B85;
		public const uint GL_ACTIVE_UNIFORMS = 0x8B86;
		public const uint GL_ACTIVE_UNIFORM_MAX_LENGTH = 0x8B87;
		public const uint GL_ACTIVE_ATTRIBUTES = 0x8B89;
		public const uint GL_ACTIVE_ATTRIBUTE_MAX_LENGTH = 0x8B8A;
		public const uint GL_SHADING_LANGUAGE_VERSION = 0x8B8C;
		public const uint GL_CURRENT_PROGRAM = 0x8B8D;

		/* StencilFunction */
		public const uint GL_NEVER = 0x0200;
		public const uint GL_LESS = 0x0201;
		public const uint GL_EQUAL = 0x0202;
		public const uint GL_LEQUAL = 0x0203;
		public const uint GL_GREATER = 0x0204;
		public const uint GL_NOTEQUAL = 0x0205;
		public const uint GL_GEQUAL = 0x0206;
		public const uint GL_ALWAYS = 0x0207;

		/* StencilOp */
		/*	  GL_ZERO */
		public const uint GL_KEEP = 0x1E00;
		public const uint GL_REPLACE = 0x1E01;
		public const uint GL_INCR = 0x1E02;
		public const uint GL_DECR = 0x1E03;
		public const uint GL_INVERT = 0x150A;
		public const uint GL_INCR_WRAP = 0x8507;
		public const uint GL_DECR_WRAP = 0x8508;

		/* StringName */
		public const uint GL_VENDOR = 0x1F00;
		public const uint GL_RENDERER = 0x1F01;
		public const uint GL_VERSION = 0x1F02;
		public const uint GL_EXTENSIONS = 0x1F03;

		/* TextureMagFilter */
		public const uint GL_NEAREST = 0x2600;
		public const uint GL_LINEAR = 0x2601;

		/* TextureMinFilter */
		/*	  GL_NEAREST */
		/*	  GL_LINEAR */
		public const uint GL_NEAREST_MIPMAP_NEAREST = 0x2700;
		public const uint GL_LINEAR_MIPMAP_NEAREST = 0x2701;
		public const uint GL_NEAREST_MIPMAP_LINEAR = 0x2702;
		public const uint GL_LINEAR_MIPMAP_LINEAR = 0x2703;

		/* TextureParameterName */
		public const uint GL_TEXTURE_MAG_FILTER = 0x2800;
		public const uint GL_TEXTURE_MIN_FILTER = 0x2801;
		public const uint GL_TEXTURE_WRAP_S = 0x2802;
		public const uint GL_TEXTURE_WRAP_T = 0x2803;

		/* TextureTarget */
		/*	  GL_TEXTURE_2D */
		public const uint GL_TEXTURE = 0x1702;

		public const uint GL_TEXTURE_CUBE_MAP = 0x8513;
		public const uint GL_TEXTURE_BINDING_CUBE_MAP = 0x8514;
		public const uint GL_TEXTURE_CUBE_MAP_POSITIVE_X = 0x8515;
		public const uint GL_TEXTURE_CUBE_MAP_NEGATIVE_X = 0x8516;
		public const uint GL_TEXTURE_CUBE_MAP_POSITIVE_Y = 0x8517;
		public const uint GL_TEXTURE_CUBE_MAP_NEGATIVE_Y = 0x8518;
		public const uint GL_TEXTURE_CUBE_MAP_POSITIVE_Z = 0x8519;
		public const uint GL_TEXTURE_CUBE_MAP_NEGATIVE_Z = 0x851A;
		public const uint GL_MAX_CUBE_MAP_TEXTURE_SIZE = 0x851C;

		/* TextureUnit */
		public const uint GL_TEXTURE0 = 0x84C0;
		public const uint GL_TEXTURE1 = 0x84C1;
		public const uint GL_TEXTURE2 = 0x84C2;
		public const uint GL_TEXTURE3 = 0x84C3;
		public const uint GL_TEXTURE4 = 0x84C4;
		public const uint GL_TEXTURE5 = 0x84C5;
		public const uint GL_TEXTURE6 = 0x84C6;
		public const uint GL_TEXTURE7 = 0x84C7;
		public const uint GL_TEXTURE8 = 0x84C8;
		public const uint GL_TEXTURE9 = 0x84C9;
		public const uint GL_TEXTURE10 = 0x84CA;
		public const uint GL_TEXTURE11 = 0x84CB;
		public const uint GL_TEXTURE12 = 0x84CC;
		public const uint GL_TEXTURE13 = 0x84CD;
		public const uint GL_TEXTURE14 = 0x84CE;
		public const uint GL_TEXTURE15 = 0x84CF;
		public const uint GL_TEXTURE16 = 0x84D0;
		public const uint GL_TEXTURE17 = 0x84D1;
		public const uint GL_TEXTURE18 = 0x84D2;
		public const uint GL_TEXTURE19 = 0x84D3;
		public const uint GL_TEXTURE20 = 0x84D4;
		public const uint GL_TEXTURE21 = 0x84D5;
		public const uint GL_TEXTURE22 = 0x84D6;
		public const uint GL_TEXTURE23 = 0x84D7;
		public const uint GL_TEXTURE24 = 0x84D8;
		public const uint GL_TEXTURE25 = 0x84D9;
		public const uint GL_TEXTURE26 = 0x84DA;
		public const uint GL_TEXTURE27 = 0x84DB;
		public const uint GL_TEXTURE28 = 0x84DC;
		public const uint GL_TEXTURE29 = 0x84DD;
		public const uint GL_TEXTURE30 = 0x84DE;
		public const uint GL_TEXTURE31 = 0x84DF;
		public const uint GL_ACTIVE_TEXTURE = 0x84E0;

		/* TextureWrapMode */
		public const uint GL_REPEAT = 0x2901;
		public const uint GL_CLAMP_TO_EDGE = 0x812F;
		public const uint GL_MIRRORED_REPEAT = 0x8370;

		/* Uniform Types */
		public const uint GL_FLOAT_VEC2 = 0x8B50;
		public const uint GL_FLOAT_VEC3 = 0x8B51;
		public const uint GL_FLOAT_VEC4 = 0x8B52;
		public const uint GL_INT_VEC2 = 0x8B53;
		public const uint GL_INT_VEC3 = 0x8B54;
		public const uint GL_INT_VEC4 = 0x8B55;
		public const uint GL_BOOL = 0x8B56;
		public const uint GL_BOOL_VEC2 = 0x8B57;
		public const uint GL_BOOL_VEC3 = 0x8B58;
		public const uint GL_BOOL_VEC4 = 0x8B59;
		public const uint GL_FLOAT_MAT2 = 0x8B5A;
		public const uint GL_FLOAT_MAT3 = 0x8B5B;
		public const uint GL_FLOAT_MAT4 = 0x8B5C;
		public const uint GL_SAMPLER_2D = 0x8B5E;
		public const uint GL_SAMPLER_CUBE = 0x8B60;

		/* Vertex Arrays */
		public const uint GL_VERTEX_ATTRIB_ARRAY_ENABLED = 0x8622;
		public const uint GL_VERTEX_ATTRIB_ARRAY_SIZE = 0x8623;
		public const uint GL_VERTEX_ATTRIB_ARRAY_STRIDE = 0x8624;
		public const uint GL_VERTEX_ATTRIB_ARRAY_TYPE = 0x8625;
		public const uint GL_VERTEX_ATTRIB_ARRAY_NORMALIZED = 0x886A;
		public const uint GL_VERTEX_ATTRIB_ARRAY_POuintER = 0x8645;
		public const uint GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING = 0x889F;

		/* Read Format */
		public const uint GL_IMPLEMENTATION_COLOR_READ_TYPE = 0x8B9A;
		public const uint GL_IMPLEMENTATION_COLOR_READ_FORMAT = 0x8B9B;

		/* Shader Source */
		public const uint GL_COMPILE_STATUS = 0x8B81;
		public const uint GL_INFO_LOG_LENGTH = 0x8B84;
		public const uint GL_SHADER_SOURCE_LENGTH = 0x8B88;
		public const uint GL_SHADER_COMPILER = 0x8DFA;

		/* Shader Binary */
		public const uint GL_SHADER_BINARY_FORMATS = 0x8DF8;
		public const uint GL_NUM_SHADER_BINARY_FORMATS = 0x8DF9;

		/* Shader Precision-Specified Types */
		public const uint GL_LOW_FLOAT = 0x8DF0;
		public const uint GL_MEDIUM_FLOAT = 0x8DF1;
		public const uint GL_HIGH_FLOAT = 0x8DF2;
		public const uint GL_LOW_INT = 0x8DF3;
		public const uint GL_MEDIUM_INT = 0x8DF4;
		public const uint GL_HIGH_INT = 0x8DF5;

		/* Framebuffer Object. */
		public const uint GL_FRAMEBUFFER = 0x8D40;
		public const uint GL_RENDERBUFFER = 0x8D41;

		public const uint GL_RGBA4 = 0x8056;
		public const uint GL_RGB5_A1 = 0x8057;
		public const uint GL_RGB565 = 0x8D62;
		public const uint GL_DEPTH_COMPONENT16 = 0x81A5;
		public const uint GL_STENCIL_INDEX = 0x1901;
		public const uint GL_STENCIL_INDEX8 = 0x8D48;

		public const uint GL_RENDERBUFFER_WIDTH = 0x8D42;
		public const uint GL_RENDERBUFFER_HEIGHT = 0x8D43;
		public const uint GL_RENDERBUFFER_INTERNAL_FORMAT = 0x8D44;
		public const uint GL_RENDERBUFFER_RED_SIZE = 0x8D50;
		public const uint GL_RENDERBUFFER_GREEN_SIZE = 0x8D51;
		public const uint GL_RENDERBUFFER_BLUE_SIZE = 0x8D52;
		public const uint GL_RENDERBUFFER_ALPHA_SIZE = 0x8D53;
		public const uint GL_RENDERBUFFER_DEPTH_SIZE = 0x8D54;
		public const uint GL_RENDERBUFFER_STENCIL_SIZE = 0x8D55;

		public const uint GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE = 0x8CD0;
		public const uint GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME = 0x8CD1;
		public const uint GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL = 0x8CD2;
		public const uint GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE = 0x8CD3;

		public const uint GL_COLOR_ATTACHMENT0 = 0x8CE0;
		public const uint GL_DEPTH_ATTACHMENT = 0x8D00;
		public const uint GL_STENCIL_ATTACHMENT = 0x8D20;

		public const uint GL_NONE = 0;

		public const uint GL_FRAMEBUFFER_COMPLETE = 0x8CD5;
		public const uint GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT = 0x8CD6;
		public const uint GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT = 0x8CD7;
		public const uint GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS = 0x8CD9;
		public const uint GL_FRAMEBUFFER_UNSUPPORTED = 0x8CDD;

		public const uint GL_FRAMEBUFFER_BINDING = 0x8CA6;
		public const uint GL_RENDERBUFFER_BINDING = 0x8CA7;
		public const uint GL_MAX_RENDERBUFFER_SIZE = 0x84E8;

		public const uint GL_INVALID_FRAMEBUFFER_OPERATION = 0x0506;

		//====================================================================================
		// PVR
		public const uint GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG = 0x8C00;
		public const uint GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG = 0x8C01;
		public const uint GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG = 0x8C02;
		public const uint GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG = 0x8C03;
		// ETC1
		public const uint GL_ETC1_RGB8_OES = 0x8D64;
		// ETC2
		public const uint GL_COMPRESSED_RGB8_ETC2 = 0x9274;
		public const uint GL_COMPRESSED_RGBA8_ETC2_EAC = 0x9278;
		// DXT
		public const uint GL_COMPRESSED_RGB_S3TC_DXT1_EXT = 0x83F0;
		public const uint GL_COMPRESSED_RGBA_S3TC_DXT1_EXT = 0x83F1;
		public const uint GL_COMPRESSED_RGBA_S3TC_DXT3_EXT = 0x83F2;
		public const uint GL_COMPRESSED_RGBA_S3TC_DXT5_EXT = 0x83F3;

		//
		public const uint GL_SAMPLER_3D = 0x8B5F;

		// OpenGLES 3.0
		public const uint GL_RGB8 = 0x8051;
		public const uint GL_RGBA8 = 0x8058;

		#endregion
	}
}
