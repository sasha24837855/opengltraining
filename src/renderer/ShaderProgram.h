#pragma once
#include <string>
#include <glad/glad.h>
#include <iostream>
#include <sstream>
#include <fstream>

namespace renderer {
	class ShaderProgram {
	public:
		ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader);
		~ShaderProgram();
		bool isCompiled() const { return m_isCompiled; };
		void use() const;
		GLuint getm_ID() { return m_ID; };
		ShaderProgram() = delete;
		ShaderProgram(ShaderProgram&) = delete;
		ShaderProgram& operator =(const ShaderProgram&) = delete;
		ShaderProgram& operator = (ShaderProgram&& ShaderProgram)noexcept;
		ShaderProgram(ShaderProgram&& shaderProgram) noexcept;
	private:
		bool createShader(const std::string& source, const GLenum shaderType, GLuint& shaderID);
		bool m_isCompiled = false;
		GLuint m_ID = 0;

		

	};
}