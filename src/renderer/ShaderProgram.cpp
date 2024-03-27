#include "ShaderProgram.h"
#include <iostream>

namespace renderer {
	ShaderProgram::ShaderProgram(const std::string& vertexPath, const std::string& fragmentPath) {
		GLuint vertexShaderID;
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;
		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try {
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			std::stringstream vShaderStream, fShaderStream;
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			
			vertexCode = vShaderStream.str();

			fragmentCode = fShaderStream.str();
			vShaderFile.close();
			fShaderFile.close();

		}

		catch (std::ifstream::failure e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
			
		}
		if (!createShader(vertexCode,GL_VERTEX_SHADER, vertexShaderID)) {
			std::cerr << "VERTEX SHADER COMPILE TIME ERROR" << std::endl;
			return;
		}
		GLuint fragmentShaderID;
		if (!createShader(fragmentCode, GL_FRAGMENT_SHADER, fragmentShaderID)) {
			std::cerr << "FRAAGMENT SHADER COMPILE TIME ERROR" << std::endl;
			glCompileShader(vertexShaderID);
			return;
		}
		m_ID = glCreateProgram();
		glAttachShader(m_ID,vertexShaderID);
		glAttachShader(m_ID, fragmentShaderID);
		glLinkProgram(m_ID);

		GLint success;
		glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
		if (!success) {
			GLchar infoLog[1024];
			glGetShaderInfoLog(m_ID, 1024, nullptr, infoLog);
			std::cerr << "ERROR::SHADER: LINK TIME ERROR \n" << infoLog << std::endl;
		}
		else {
			m_isCompiled = true;
		}
		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);
	}
	bool ShaderProgram::createShader(const std::string& source, const GLenum shaderType, GLuint& shaderID) {
		shaderID = glCreateShader(shaderType);
		const char* code = source.c_str();
		glShaderSource(shaderID, 1, &code, nullptr);
		glCompileShader(shaderID);

		GLint success;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
		if (!success) {
			GLchar infoLog[1024];
			glGetShaderInfoLog(shaderID, 1024, nullptr, infoLog);
			std::cerr << "ERROR::SHADER: COMPILE TIME ERROR \n" << infoLog << std::endl;
			return false;
		}
		return true;
	}
	void ShaderProgram::use() const {
		glUseProgram(m_ID);
	}
	
	ShaderProgram::~ShaderProgram() {
		glDeleteProgram(m_ID);
	}

	ShaderProgram& ShaderProgram::operator = (ShaderProgram&& ShaderProgram) noexcept{
		glDeleteProgram(m_ID);
		m_ID = ShaderProgram.m_ID;
		m_isCompiled = ShaderProgram.m_isCompiled;
		ShaderProgram.m_ID = 0;
		ShaderProgram.m_isCompiled = false;
		return *this;
	}
	ShaderProgram::ShaderProgram(ShaderProgram&& ShaderProgram) noexcept{
		m_ID = ShaderProgram.m_ID;
		m_isCompiled = ShaderProgram.m_isCompiled;
		ShaderProgram.m_ID = 0;
		ShaderProgram.m_isCompiled = false;
	}
}