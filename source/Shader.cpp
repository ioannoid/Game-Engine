#include "Shader.hpp"

namespace Engine 
{
    Shader::Shader() { }

    void Shader::loadVertex(const char* vertexPath)
    {
        vertex = glCreateShader(GL_VERTEX_SHADER);
        
        std::string VertexShaderCode;
        std::ifstream VertexShaderStream(vertexPath, std::ios::in);
        if(VertexShaderStream.is_open()){
            std::stringstream sstr;
            sstr << VertexShaderStream.rdbuf();
            VertexShaderCode = sstr.str();
            VertexShaderStream.close();
        }else{
            printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertexPath);
            getchar();
        }

        GLint Result = GL_FALSE;
	    int InfoLogLength;

        printf("Compiling shader : %s\n", vertexPath);
        char const* VertexSourcePointer = VertexShaderCode.c_str();
        glShaderSource(vertex, 1, &VertexSourcePointer , NULL);
        glCompileShader(vertex);

        glGetShaderiv(vertex, GL_COMPILE_STATUS, &Result);
        glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &InfoLogLength);
        if ( InfoLogLength > 0 ){
            std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
            glGetShaderInfoLog(vertex, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
            printf("%s\n", &VertexShaderErrorMessage[0]);
        }
    }

    void Shader::loadFragment(const char* fragmentPath) 
    {
        fragment = glCreateShader(GL_FRAGMENT_SHADER);

        std::string FragmentShaderCode;
        std::ifstream FragmentShaderStream(fragmentPath, std::ios::in);
        if(FragmentShaderStream.is_open()){
            std::stringstream sstr;
            sstr << FragmentShaderStream.rdbuf();
            FragmentShaderCode = sstr.str();
            FragmentShaderStream.close();
        }

        GLint Result = GL_FALSE;
	    int InfoLogLength;

        printf("Compiling shader : %s\n", fragmentPath);
        char const * FragmentSourcePointer = FragmentShaderCode.c_str();
        glShaderSource(fragment, 1, &FragmentSourcePointer , NULL);
        glCompileShader(fragment);

        // Check Fragment Shader
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &Result);
        glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &InfoLogLength);
        if ( InfoLogLength > 0 ){
            std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
            glGetShaderInfoLog(fragment, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
            printf("%s\n", &FragmentShaderErrorMessage[0]);
        }
    }

    void Shader::link()
    {
        if(!program) program = glCreateProgram();

        glAttachShader(program, vertex);
        glAttachShader(program, fragment);

        glLinkProgram(program);

        GLint Result = GL_FALSE;
	    int InfoLogLength;

        glGetProgramiv(program, GL_LINK_STATUS, &Result);
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &InfoLogLength);
        if ( InfoLogLength > 0 ){
            std::vector<char> ProgramErrorMessage(InfoLogLength+1);
            glGetProgramInfoLog(program, InfoLogLength, NULL, &ProgramErrorMessage[0]);
            printf("%s\n", &ProgramErrorMessage[0]);
        }

        glDetachShader(program, vertex);
        glDetachShader(program, fragment);

        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }

    void Shader::use()
    {
        glUseProgram(program);
    }
}