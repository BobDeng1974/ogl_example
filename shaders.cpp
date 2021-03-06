#include "shaders.h"

std::string const g_vertexShaderCodeSimple = R"(
		#version 330 core

		layout(location = 0) in vec3 vertexPosition_modelspace;

		uniform mat4 MVP;

		void main()
		{
			gl_Position =  MVP * vec4(vertexPosition_modelspace,1);
		}
	)";
std::string const g_fragmentShaderCodeSimple = R"(
		#version 330 core

		out vec3 color;
		void main()
		{
			color = vec3(1,0,0);
		}
	)";

std::string const g_vertexShaderCode360 = R"(
		#version 330 core

		layout(location = 0) in vec3 vertexPosition_modelspace;
		layout(location = 1) in vec2 vertexUV;

		out vec2 UV;

		uniform mat4 MVP;

		void main()
		{
			gl_Position =  MVP * vec4(vertexPosition_modelspace,1);
			UV = vertexUV;
		}
	)";

std::string const g_fragmentShaderCode360 = R"(
		#version 330 core

		in vec2 UV;

		out vec3 color;

		uniform sampler2D inSampler;

		void main()
		{
			color = texture(inSampler, UV).rgb;
		}
	)";

std::string const g_fragmentShaderCode360FB = R"(
		#version 330 core

		in vec2 UV;

		layout(location = 0) out vec3 color;

		uniform sampler2D inSampler;

		void main()
		{
			color = texture(inSampler, UV).rgb;
		}
	)";

std::string const g_fragmentShaderCode360FBCut = R"(
		#version 330 core

		in vec2 UV;

		layout(location = 0) out vec3 color;

		uniform sampler2D inSampler;

		void main()
		{
			if (all(lessThanEqual(UV, vec2(1.0f))) && all(greaterThanEqual(UV, vec2(0.0f))))
				color = texture(inSampler, UV).rgb;
			else
				color = vec3(0.0f, 0.0f, 1.0f);
		}
	)";

std::string const g_vertexShaderCode360DualFish = R"(
		#version 330 core

		layout(location = 0) in vec3 vertexPosition_modelspace;
		layout(location = 1) in vec2 vertexUV0;
		layout(location = 2) in vec2 vertexUV1;

		out vec2 UV0;
		out vec2 UV1;

		uniform mat4 MVP;

		void main()
		{
			gl_Position =  MVP * vec4(vertexPosition_modelspace,1);
			UV0 = vertexUV0;
			UV1 = vertexUV1;
		}
	)";

std::string const g_fragmentShaderCode360FBCutDualFish = R"(
		#version 330 core

		in vec2 UV0;
		in vec2 UV1;

		layout(location = 0) out vec3 color;

		uniform sampler2D inSampler;

		void main()
		{
			bool hasTex0 = false;
			bool hasTex1 = false;
			if (all(lessThanEqual(UV0, vec2(0.5f, 1.0f))) && all(greaterThanEqual(UV0, vec2(0.0f))))
				hasTex0 = true;
			if (all(lessThanEqual(UV1, vec2(1.0f))) && all(greaterThanEqual(UV1, vec2(0.5f, 0.0f))))
				hasTex1 = true;

			if (hasTex0 && hasTex1) {
				vec3 color0 = texture(inSampler, UV0).rgb;
				vec3 color1 = texture(inSampler, UV1).rgb;
				color = mix(color0, color1, 0.5f);
			}
			else if (hasTex0) {
				color = texture(inSampler, UV0).rgb;
			}
			else if (hasTex1) {
				color = texture(inSampler, UV1).rgb;
			}
			else {
				color = vec3(0.0f, 1.0f, 0.0f);
			}

//			if (hasTex1)
//				color = texture(inSampler, UV1).rgb;
//			else
//				color = vec3(0.0f, 0.0f, 1.0f);
		}


	)";
