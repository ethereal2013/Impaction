#include <impct_pch.h>
#include "Shader.h"

#include <glad/glad.h>

namespace impct
{

	Shader::Shader(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		//Vertex Shader
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		const GLchar* source = vertexSrc.c_str();
		glShaderSource(vertexShader, 1, &source, 0);

		glCompileShader(vertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glad_glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);
			glDeleteShader(vertexShader);

			IMPCT_CORE_ERROR("{0}", infoLog.data());
			IMPCT_CORE_ASSERT(false, "Vertex Shader Compilation Faliure!");
			return;
		}

		//Fragment Shader
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		source = fragmentSrc.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);

		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);

		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(fragmentShader);
			// Either of them. Don't leak shaders.
			glDeleteShader(vertexShader);

			IMPCT_CORE_ERROR("{0}", infoLog.data());
			IMPCT_CORE_ASSERT(false, "Fragment Shader Compilation Faliure!");
			return;
		}

		// Vertex and fragment shaders are successfully compiled.
		// Link them together into a program.
		// Get a program object.

		m_RendererID = glCreateProgram();

		//'program' makes more sense here.
		GLuint program = static_cast<GLuint>(m_RendererID);

		// Attach our shaders to our program
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);

		// Link our program
		glLinkProgram(program);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, &isLinked);

		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(program);

			// Shader not to be leaked
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			IMPCT_CORE_ERROR("{0}", infoLog.data());
			IMPCT_CORE_ASSERT(false, "Shader link Faliure!");
			return;
		}

		// Detach shaders after a successful link.
		glDetachShader(program, vertexShader);
		glDetachShader(program, fragmentShader);
	}

	Shader::~Shader() { glDeleteProgram(m_RendererID); }

	void Shader::Bind() const { glUseProgram(m_RendererID); }
	void Shader::Unbind() const { glUseProgram(0); }


}
