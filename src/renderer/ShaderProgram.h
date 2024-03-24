#pragma once
#include <string>
#include <glad/glad.h>
namespace renderer {
	class ShaderProgram {
	public:
		ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader);
		~ShaderProgram();
		bool isCompiled() const { return m_isCompiled; };
		bool use() const {};
	private:
		bool m_isCompiled;
		GLuint m_ID;
	};
}