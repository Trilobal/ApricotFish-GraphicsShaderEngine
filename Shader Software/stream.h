#pragma once
//流读取以及GLFW着色器编译方面
#include "GlfwInit.h"
#include "baseInit.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class LoadShader
{
public:
	unsigned int ID;
	void rdStream(const char* vPath, const char* fPath)
	{
		vShader.exceptions(ifstream::failbit | ifstream::badbit);
		fShader.exceptions(ifstream::failbit | ifstream::badbit);
		try
		{
			stringstream vShaderStream, fShaderStream;

			vShader.open(vPath);
			fShader.open(fPath);

			vShaderStream << vShader.rdbuf();
			fShaderStream << fShader.rdbuf();

			vShader.close();
			fShader.close();

			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch (ifstream::failure& e)
		{
			cout << "ERROR::Shader::File_not_successfully_read: " << e.what() << endl;
		}

		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();

		unsigned int vertex, fragment;
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		checkCompileErrors(vertex, "vertex");

		fragment = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(fragment, 1, &vShaderCode, NULL);
		glCompileShader(fragment);
		checkCompileErrors(fragment, "vertex");
	}
public:
	void readStreamInfomation()
	{
		cout << "\n[ The Code of vertex]\n" << vertexCode << endl << endl;
		cout << "\n[ The Code of fragment]\n" << fragmentCode << endl << endl;
	}

	string readVertexStreamInfomation()
	{
		if (!vertexCode.size())
			return "Failed to read vertexCode!";
		return  vertexCode;
	}
	string readFragmentStreamInfomation()
	{
		if (!fragmentCode.size())
			return "Failed to read FragmentCode!";
		return fragmentCode;
	}
public:
	void use()
	{
		glUseProgram(ID);
	}
	void setBool(const std::string& name, bool value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
	}
	void setInt(const std::string& name, int value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}
	void setFloat(const std::string& name, float value) const
	{
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	}
	void setVec2(const std::string& name, const glm::vec2& value) const
	{
		glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
	}
	void setVec2(const std::string& name, float x, float y) const
	{
		glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
	}
	void setVec3(const std::string& name, const glm::vec3& value) const
	{
		glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
	}
	void setVec3(const std::string& name, float x, float y, float z) const
	{
		glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
	}
	void setVec4(const std::string& name, const glm::vec4& value) const
	{
		glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
	}
	void setVec4(const std::string& name, float x, float y, float z, float w)
	{
		glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
	}
	void setMat2(const std::string& name, const glm::mat2& mat) const
	{
		glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
	void setMat3(const std::string& name, const glm::mat3& mat) const
	{
		glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
	void setMat4(const std::string& name, const glm::mat4& mat) const
	{
		glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
private:
	void checkCompileErrors(GLuint shader, string type)
	{
		GLint success;
		GLchar infoLog[1024];
		if (type != "program")
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				cout << "ERROR::Shader_Compilation_Error of type: " << type << "\n" << infoLog << endl;
			}
		}
		else
		{
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				cout << "ERROR::Program_Compilation_Error of type: " << type << "\n" << infoLog << endl;
			}
		}
	}
private:
	string vertexCode;
	string fragmentCode;

	ifstream vShader;
	ifstream fShader;
};