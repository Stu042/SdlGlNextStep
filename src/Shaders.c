//
// Created by stu on 27/07/23.
//
#include <string.h>
#include <GL/glew.h>
#include "Shaders.h"
#include "File.h"
#include "Log.h"
#include "OpenGL.h"
#include "Std.h"


// create the shader program and link the vertex and fragment shaders
ShaderProgram *buildShaderProgram(GLuint vertexShaderHandle, GLuint fragmentShaderHandle) {
	GLuint glShaderProgram = glCreateProgram();
	if (glShaderProgram == 0) {
		LogError("Failed glCreateProgram %u", glShaderProgram);
		return 0;
	}
	glAttachShader(glShaderProgram, vertexShaderHandle);
	glAttachShader(glShaderProgram, fragmentShaderHandle);
	glLinkProgram(glShaderProgram);
	if (CheckErrorGL(glShaderProgram, ErrorType_ShaderLink)) {
		glDeleteShader(vertexShaderHandle);
		glDeleteShader(fragmentShaderHandle);
		glDeleteProgram(glShaderProgram);
		return 0;
	}
	ShaderProgram *shaderProgram = (ShaderProgram *) Alloc(sizeof(ShaderProgram));
	shaderProgram->vertex = vertexShaderHandle;
	shaderProgram->fragment = fragmentShaderHandle;
	shaderProgram->program = glShaderProgram;
	return shaderProgram;
}


GLuint compileShader(const char *shaderContents[], GLuint shaderType) {
	int shaderSrcCount = CountStringPtrArraySize(shaderContents);
	GLuint shaderHandle = glCreateShader(shaderType);
	glShaderSource(shaderHandle, shaderSrcCount, shaderContents, NULL);
	glCompileShader(shaderHandle);
	if (CheckErrorGL(shaderHandle, ErrorType_ShaderCompile)) {
		glDeleteShader(shaderHandle);
		return 0;
	}
	LogInfo("Compiled shader %u", shaderHandle);
	return shaderHandle;
}


GLuint compileShaderHandle(const char *shaderFilenames[], GLuint shaderType) {
	const char **shaderSrc = ReadFiles(shaderFilenames);
	GLuint shaderHandle = compileShader((const char **)shaderSrc, shaderType);
	FreeFiles(shaderSrc);
	if (shaderHandle == 0) {
		LogError("Failed compiling shader");
		return 0;
	}
	return shaderHandle;
}


/***********************************
 * global functions
 */


// must be sent a null terminated array of filenames for each parameter
ShaderProgram *BuildShader(const char *vertexShaderFilenames[], const char *fragmentShaderFilenames[]) {
	GLuint vertShaderHandle = compileShaderHandle(vertexShaderFilenames, GL_VERTEX_SHADER);
	if (vertShaderHandle == 0) {
		LogError("Failed compiling vertex shader");
		return NULL;
	}
	GLuint fragShaderHandle = compileShaderHandle(fragmentShaderFilenames, GL_FRAGMENT_SHADER);
	if (fragShaderHandle == 0) {
		glDeleteShader(vertShaderHandle);
		LogError("Failed compiling fragment shader");
		return NULL;
	}
	ShaderProgram* program = buildShaderProgram(vertShaderHandle, fragShaderHandle);
	if (program == NULL) {
		glDeleteShader(vertShaderHandle);
		glDeleteShader(fragShaderHandle);
		LogError("Failed linking shader");
		return NULL;
	}
	return program;
}


void FreeShaderProgram(ShaderProgram *shaderProgram) {
	if (shaderProgram == NULL) {
		LogError("Asked to free null shader program");
		return;
	}
	LogInfo("Freeing shader program %u", shaderProgram);
	glDeleteShader(shaderProgram->vertex);
	glDeleteShader(shaderProgram->fragment);
	glDeleteProgram(shaderProgram->program);
	free(shaderProgram);
}
