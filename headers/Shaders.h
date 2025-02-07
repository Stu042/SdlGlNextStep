//
// Created by stu on 27/07/23.
//
#ifndef SHADERS_H
#define SHADERS_H


typedef struct SHADER_PROGRAM {
	GLuint vertex;
	GLuint fragment;
	GLuint program;
} ShaderProgram;


// free a shader program and all attached shaders
extern void FreeShaderProgram(ShaderProgram* shaderProgram);

// Must be sent a null terminated array of filenames for each parameter
extern ShaderProgram* BuildShaderProgram(const char* vertexShaderFilenames[], const char* fragmentShaderFilenames[]);


#endif //SHADERS_H
