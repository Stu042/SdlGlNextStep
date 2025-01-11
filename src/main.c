#include <SDL.h>
#include <GL/glew.h>
#include "OpenGL.h"
#include "Shaders.h"
#include "Random.h"
#include "Log.h"


const SdlGlAttribute attributes[] = {
	  {SDL_GL_CONTEXT_MAJOR_VERSION, 4},
	  {SDL_GL_CONTEXT_MINOR_VERSION, 1},
	  {SDL_GL_DOUBLEBUFFER,          1},
	  {SDL_GL_DEPTH_SIZE,            24},
	  {SDL_GL_RED_SIZE,              8},
	  {SDL_GL_GREEN_SIZE,            8},
	  {SDL_GL_BLUE_SIZE,             8},
	  {SDL_GL_ALPHA_SIZE,            8},
	  {SDL_GL_ACCELERATED_VISUAL,    1},
	  {SDL_GL_CONTEXT_FLAGS,         SDL_GL_CONTEXT_PROFILE_CORE},
	  {-1,         -1}
};

const NewWindow windowDef = {
	  800,
	  600,
	  "App Title",
	  true,
	  (SdlGlAttribute *) attributes
};


// geometry to display
GLuint triangleVao;   // mesh/attribute descriptor handle
GLuint triangleVbo;   // handle to OpenGL copy of buffer

void createGeometry() {
	const float points[] = {
		 0.0f,  0.5f,  0.0f,
		 0.5f, -0.5f,  0.0f,
		-0.5f, -0.5f,  0.0f
	};
	glGenVertexArrays(1, &triangleVao);
	glGenBuffers(1, &triangleVbo);
	glBindVertexArray(triangleVao);
	glBindBuffer(GL_ARRAY_BUFFER, triangleVbo);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), points, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}


void done(OpenGlEnvironment *glEnv, ShaderProgram* shaderProgram) {
	glDeleteVertexArrays(1, &triangleVao);
	glDeleteBuffers(1, &triangleVbo);
    FreeShaderProgram(shaderProgram);
	EndOpenGl(glEnv);
}


int main(int argc, char *argv[]) {
	RandomSeed(1782467, 127486);
	LogInit();
	LogSetLevel(LOG_DEBUG);
	OpenGlEnvironment *glEnv = StartOpenGl(windowDef);
	if (glEnv == NULL) {
		LogFatal("Unable to start opengl");
		return 1;
	}
	LogGLParams();
	createGeometry();
	const char *vertexShaderFilenames[] = {"shaders/shader.vert", NULL};
	const char *fragmentShaderFilenames[] = {"shaders/shader.frag", NULL};
	ShaderProgram* shaderProgram = BuildShaderProgram(vertexShaderFilenames, fragmentShaderFilenames);
	if (!shaderProgram) {
		EndOpenGl(glEnv);
		return 2;
	}
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	bool appIsRunning = true;
	while (appIsRunning) {
		SDL_Event event;
		if (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				appIsRunning = false;
			}
		}
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(shaderProgram->program);
		glBindVertexArray(triangleVao);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
		glUseProgram(0);
		SDL_GL_SwapWindow(glEnv->window);
	}
	done(glEnv, shaderProgram);
	LogEnd();
	return 0;
}
