//
// Created by stu on 28/07/23.
//
#include <SDL.h>
#include <GL/glew.h>
#include <stdbool.h>
#include "OpenGL.h"
#include "Log.h"
#include "Std.h"


bool initGL(NewWindow windowDefinition, SDL_Window *window) {
	GLenum error = GL_NO_ERROR;
	if (windowDefinition.depthBuffer) {
		glEnable(GL_DEPTH_TEST);
		error = glGetError();
		if (error != GL_NO_ERROR) {
			LogError("Error glEnable(GL_DEPTH_TEST) %s", glewGetErrorString(error));
			return false;
		}
		glDepthFunc(GL_LESS);
		error = glGetError();
		if (error != GL_NO_ERROR) {
			LogError("Error glDepthFunc %s", glewGetErrorString(error));
			return false;
		}
	}
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	error = glGetError();
	if (error != GL_NO_ERROR) {
		LogError("Error glClearColor %s", glewGetErrorString(error));
		return false;
	}
	return true;
}


void setGlAttributes(SdlGlAttribute attributes[]) {
	for (int i = 0; attributes[i].attribute != -1; i++) {
		int error = SDL_GL_SetAttribute(attributes[i].attribute, attributes[i].value);
		if (error != 0) {
			LogError("Error setting SDL attribute at index %d, %s", i, SDL_GetError());
		}
	}
}


OpenGlEnvironment *StartOpenGl(NewWindow windowDefinition) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		LogFatal("SDL could not initialize! SDL Error: %s", SDL_GetError());
		return NULL;
	}
	setGlAttributes(windowDefinition.attributes);
	OpenGlEnvironment *glEnv = (OpenGlEnvironment *)Alloc(sizeof(OpenGlEnvironment));
	glEnv->window = SDL_CreateWindow(windowDefinition.title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
										  windowDefinition.width, windowDefinition.height,
										  SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (glEnv->window == NULL) {
		LogFatal("Window could not be created! SDL Error: %s", SDL_GetError());
		EndOpenGl(glEnv);
		return NULL;
	}
	glEnv->context = SDL_GL_CreateContext(glEnv->window);
	if (glEnv->context == NULL) {
		LogFatal("OpenGL context could not be created! SDL Error: %s", SDL_GetError());
		EndOpenGl(glEnv);
		return NULL;
	}
	glewExperimental = GL_TRUE;
	GLenum glewError = glewInit();
	if (glewError != GLEW_OK) {
		LogFatal("Error initializing GLEW! %s", glewGetErrorString(glewError));
		EndOpenGl(glEnv);
		return NULL;
	}
	if (SDL_GL_SetSwapInterval(1) < 0) {
		LogError("Warning: Unable to set VSync. SDL Error: %s", SDL_GetError());
	}
	if (!initGL(windowDefinition, glEnv->window)) {
		LogFatal("Unable to initialize OpenGL!");
		EndOpenGl(glEnv);
		return NULL;
	}
	const GLubyte *renderer = glGetString(GL_RENDERER);
	const GLubyte *version = glGetString(GL_VERSION);
	LogInfo("Renderer: %s", renderer);
	LogInfo("OpenGL version inuse %s", version);
	return glEnv;
}


void EndOpenGl(OpenGlEnvironment *glEnv) {
	if (glEnv == NULL) {
		return;
	}
	if (glEnv->context) {
		SDL_GL_DeleteContext(glEnv->context);
	}
	if (glEnv->window) {
		SDL_DestroyWindow(glEnv->window);
	}
	free(glEnv);
	SDL_Quit();
}


GpuMemoryInfo *GetGpuMemInfo() {
	GpuMemoryInfo *memInfo = (GpuMemoryInfo *) Alloc(sizeof(GpuMemoryInfo));
	memInfo->dedicatedVideoMemory = 0;
	glGetIntegerv(GL_GPU_MEMORY_INFO_DEDICATED_VIDMEM_NVX, &(memInfo->dedicatedVideoMemory));
	memInfo->totalVideoMemory = 0;
	glGetIntegerv(GL_GPU_MEMORY_INFO_TOTAL_AVAILABLE_MEMORY_NVX, &(memInfo->totalVideoMemory));
	memInfo->currentAvailableVideoMemory = 0;
	glGetIntegerv(GL_GPU_MEMORY_INFO_CURRENT_AVAILABLE_VIDMEM_NVX, &(memInfo->currentAvailableVideoMemory));
	memInfo->evictionCountVideoMemory = 0;
	glGetIntegerv(GL_GPU_MEMORY_INFO_EVICTION_COUNT_NVX, &(memInfo->evictionCountVideoMemory));
	memInfo->evictedVideoMemory = 0;
	glGetIntegerv(GL_GPU_MEMORY_INFO_EVICTED_MEMORY_NVX, &(memInfo->evictedVideoMemory));
	memInfo->useGpuMemoryInfo = memInfo->totalVideoMemory != 0;
	return memInfo;
}

void FreeGpuMemInfo(GpuMemoryInfo *memInfo) {
	free(memInfo);
}


bool CheckErrorGL(GLuint item, ErrorType errorType) {
	int params = -1;
	switch (errorType) {
		case ErrorType_ShaderCompile:
			glGetShaderiv(item, GL_COMPILE_STATUS, &params);
			break;
		case ErrorType_ShaderLink:
			glGetProgramiv(item, GL_LINK_STATUS, &params);
			break;
		default:
			LogError("Unknown gl error type, %u", errorType);
			return false;
	}
	if (params != GL_TRUE) {
		const int maxLength = 2048;
		char slog[maxLength];
		int actualLength = 0;
		switch (errorType) {
			case ErrorType_ShaderCompile:
				glGetShaderInfoLog(item, maxLength, &actualLength, slog);
				LogError("Failed shader compilation, log for shader index %u:\n%s", item, slog);
				break;
			case ErrorType_ShaderLink:
				glGetProgramInfoLog(item, maxLength, &actualLength, slog);
				LogError("Failed shader Program link, log for shader program index %u:\n%s", item, slog);
				break;
			default:
				LogError("Unknown gl error type, %u", errorType);
				return false;
		}
		return true;
	}
	return false;
}
