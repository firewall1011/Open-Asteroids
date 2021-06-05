#pragma once
#include <string>

#include "tvector.h"

namespace TLibrary {

	struct ShaderCode {
		const std::string vertex;
		const std::string fragment;
	};

	class Shader
	{
	private:
		unsigned int _uid;

	public:
		unsigned int loc_transform;
		unsigned int loc_color;
		unsigned int loc_position;

		Shader(const std::string& filepath);
		~Shader();

		void Bind() const;
		void Unbind() const;
		
		void SetColor(vec3 color) const;

		unsigned int GetID() const;

		static ShaderCode ParseShader(const std::string& filepath);
		static void WriteShader(const std::string& filepath, const char* vertex, const char* fragment);
		static unsigned int CreateProgram(const ShaderCode& shaderCode);
		static unsigned int CompileShader(const std::string& source, const unsigned int shaderType);
	};
}


