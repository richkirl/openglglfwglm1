#include "Shader.hpp"

Shader::Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath)
{
	std::string vertexcode;
	std::string fragmentcode;
	std::string geometrycode;
	std::fstream vShaderFile;
	std::fstream fFragmentFile;
	std::fstream gShaderFile;
	vShaderFile.exceptions(std::fstream::failbit | std::fstream::badbit);
	fFragmentFile.exceptions(std::fstream::failbit | std::fstream::badbit);
	gShaderFile.exceptions(std::fstream::failbit | std::fstream::badbit);
	try
	{
		vShaderFile.open(vertexPath);
		fFragmentFile.open(fragmentPath);
		std::stringstream vShaderStream, fFragmentStream;

		vShaderStream << vShaderFile.rdbuf();
		fFragmentStream << fFragmentFile.rdbuf();

		vShaderFile.close();
		fFragmentFile.close();

		vertexcode = vShaderStream.str();
		fragmentcode = fFragmentStream.str();

		if (geometryPath != nullptr)
		{
			gShaderFile.open(geometryPath);
			std::stringstream gShaderStream;
			gShaderStream << gShaderFile.rdbuf();
			gShaderFile.close();
			geometrycode = gShaderStream.str();
		}

	}
	catch (std::fstream::failure& e)
	{
		std::cout << "ERROR::SHADER::FAILE_NOT_SUCCESFULLY_READ" << std::endl;

	}
	const char* vShaderCode = vertexcode.c_str();
	const char* fShaderCode = fragmentcode.c_str();

	unsigned int vertex, fragment;
	
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	checkCompileErrors(vertex,"VERTEX");

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	checkCompileErrors(fragment, "FRAGMENT");
	// check for shader compile errors
	unsigned int geometry;
	if (geometryPath != nullptr)
	{
		const char* gShadercode = geometrycode.c_str();
		geometry = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(geometry, 1, &gShadercode, NULL);
		glCompileShader(geometry);
		checkCompileErrors(fragment, "GEOMETRY");
	}

	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	if (geometryPath != nullptr)
		glAttachShader(ID, geometry);

	glLinkProgram(ID);
	checkCompileErrors(ID, "PROGRAM");
	
	glDeleteShader(vertex);
	glDeleteShader(fragment);
	if (geometryPath != nullptr)
		glDeleteShader(geometry);
}

Shader::~Shader()
{
}

void Shader::use()
{
	glUseProgram(ID);
}

void Shader::setBoll(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), (GLfloat)value);
}

void Shader::setVec2(const std::string& name, const glm::vec2 &value) const
{
	glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setVec2(const std::string& name, float x, float y) const
{
	glUniform2f(glGetUniformLocation(ID, name.c_str()), x,y);
}

void Shader::setVec3(const std::string& name, const glm::vec3 &value) const
{
	glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setVec3(const std::string& name, float x, float y, float z) const
{
	glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y,z);
}

void Shader::setVec4(const std::string& name, const glm::vec4 &value) const
{
	glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setVec4(const std::string& name, float x, float y, float z, float w) const
{
	glUniform4f(glGetUniformLocation(ID, name.c_str()), x,y,z,w);
}

void Shader::setMat2(const std::string& name, const glm::mat2 &value) const
{
	glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

void Shader::setMat3(const std::string& name, const glm::mat3 &value) const
{
	glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

void Shader::setMat4(const std::string& name, const glm::mat4 &value) const
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

void Shader::checkCompileErrors(GLuint shader, std::string types)
{
	GLint success;
	GLchar infolog[1024];
	if (types != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infolog);
			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << types << "\n" << infolog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infolog);
			std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << types << "\n" << infolog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
}
