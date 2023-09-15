//
// Created by stu on 27/07/23.
//
#ifndef OPENGLTEST_SHADERS_H
#define OPENGLTEST_SHADERS_H


typedef struct {
	GLuint vertex;
	GLuint fragment;
	GLuint program;
}ShaderProgram;


// free a shader program and all attached shaders
extern void FreeShaderProgram(ShaderProgram* shaderProgram);

extern ShaderProgram *BuildShader(const char *vertexShaderFilenames[], const char *fragmentShaderFilenames[]);


#endif //OPENGLTEST_SHADERS_H
