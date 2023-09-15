//
// Created by stu on 28/07/23.
//

#ifndef OPENGLSDL_OPENGL_H
#define OPENGLSDL_OPENGL_H

#include <stdbool.h>
#include <SDL.h>


typedef struct {
    SDL_GLattr attribute;
    int value;
} SdlGlAttribute;


// definition of a new window to use with OpenWindow()
typedef struct {
    int width;
    int height;
    const char *title;
    bool depthBuffer;
    SdlGlAttribute *attributes;
} NewWindow;


typedef struct {
    SDL_Window *window;
    SDL_GLContext context;
} OpenGlEnvironment;


// data returned by GetGpuMemInfo()
typedef struct {
    GLint dedicatedVideoMemory;
    GLint totalVideoMemory;
    GLint currentAvailableVideoMemory;
    GLint evictionCountVideoMemory;
    GLint evictedVideoMemory;
    bool useGpuMemoryInfo;
} GpuMemoryInfo;


// OpenGL errors we can check for
typedef enum {
	ErrorType_ShaderCompile,
	ErrorType_ShaderLink
}ErrorType;



//Starts up SDL, creates window, and initializes OpenGL, call EndOpenGl() to tidy up
extern OpenGlEnvironment *StartOpenGl(NewWindow windowDefinition);

// Call to tidy up StartOpenGl() when finished with opengl
extern void EndOpenGl(OpenGlEnvironment *glEnv);

// get current gpu information
extern GpuMemoryInfo *GetGpuMemInfo();

// free resources from GetGpuMemInfo()
extern void FreeGpuMemInfo(GpuMemoryInfo *memInfo);

// return true if an error has occurred within OpenGL and report it
extern bool CheckErrorGL(GLuint shaderHandle, ErrorType errorType);


#endif //OPENGLSDL_OPENGL_H
