//
// Created by stu on 31/07/23.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <GL/glew.h>
#include "Log.h"
#include "Std.h"
#include "Errors.h"


const char APP_NAME[] = "OpenGlSdl";
const char APP_VERSION[] = "0.1";
const char* LOG_FILE_PATHNAME = "OpenGlSdl.log";

const char* LogLevelStr[LOG_LEVEL_COUNT] = {"UNKNOWN LOG LEVEL: ", "DEBUG: ", "INFO: ", "WARN: ", "ERROR: ", "FATAL: "};


FILE* logFile;                   /* The File For Error Logging */
LogLevel logLevel = LOG_UNKNOWN; /* Level of logging */



/* Initializes Error Logging. */
void LogInit() {
	if (!((logFile = fopen(LOG_FILE_PATHNAME, "w")))) { /* If We Can't Open LOG_FILE For Writing */
		perror("Can't init Logfile!");                  /* Report With perror() (Standard + Explains Cause Of The Error) */
		exit(E_NO_LOGGING);                             /* And Exit, This Is Critical, We Want Logging */
	}
	LogInfo("%s V%s -- Log Init...", APP_NAME, APP_VERSION); /* Print The Name Of The App In The Log */
}


/* Closes Error Logging */
void LogEnd() {
	LogInfo("...Closing Log\n"); /* Print The End Mark */
	if (NULL != logFile) {       /* If The File Is Open */
		fclose(logFile);         /* Close It */
		logFile = NULL;          /* be safe */
	}
}


// output the start of a log line
void LogStart(const LogLevel level, const char* file, int line) {
	if ((logLevel <= level) && logFile) {
		char time[MAX_TIMESTAMP_LENGTH];
		Timestamp(time, MAX_TIMESTAMP_LENGTH);
		fprintf(logFile, "%s %sFile: %s, Line %d, ", time, LogLevelStr[level], file, line);
	}
}

// log the description part of the line
void LogDescription(const LogLevel level, const char* format, ...) {
	if ((logLevel <= level) && logFile) {
		va_list args;
		va_start(args, format);
		vfprintf(logFile, format, args);
		va_end(args);
		fputc('\n', logFile);
		fflush(logFile);
	}
}

void LogStartDescription(const LogLevel level, const char* file, const int line, const char* format, ...) {
	LogStart(level, file, line);
	if ((logLevel <= level) && logFile) {
		va_list args;
		va_start(args, format);
		vfprintf(logFile, format, args);
		va_end(args);
		fputc('\n', logFile);
		fflush(logFile);
	}
}


void LogVA(const LogLevel level, const char* szFormat, va_list arg) {
	//va_list a = arg;
	char time[MAX_TIMESTAMP_LENGTH];
	Timestamp(time, MAX_TIMESTAMP_LENGTH);
	fprintf(logFile, "%s %s", time, LogLevelStr[level]);
	vfprintf(logFile, szFormat, arg);
	fputc('\n', logFile);
	fflush(logFile);
	//if (LogLevel == LOG_DEBUG) {
	//	vprintf(szFormat, arg);
	//	fputc('\n', stdout);
	//	fflush(stdout);
	//}
}


/* Add A Line To The Log */
void Log(const LogLevel level, const char* szFormat, ...) {
	va_list arg;                          /* We're Using The Same As The printf() Family, A va_list */
	va_start(arg, szFormat);              /* We Start The List */
	if ((logLevel <= level) && logFile) { /* If The Log Is Open and requested to log in a level we are accepting... */
		LogVA(level, szFormat, arg);      /* And Ensure The Line Is Written, The Log Must Be Quick */
	}
	va_end(arg); /* We End The List */
	if (LOG_FATAL == level) {
		exit(E_UNKNOWN);
	}
}

void LogDebug(const char* szFormat, ...) {
	const LogLevel level = LOG_DEBUG;
	va_list arg;                          /* We're Using The Same As The printf() Family, A va_list */
	va_start(arg, szFormat);              /* We Start The List */
	if ((logLevel <= level) && logFile) { /* If The Log Is Open and requested to log in a level we are accepting... */
		LogVA(level, szFormat, arg);      /* And Ensure The Line Is Written, The Log Must Be Quick */
	}
	va_end(arg); /* We End The List */
}

void LogInfo(const char* szFormat, ...) {
	const LogLevel level = LOG_INFO;
	va_list arg;                          /* We're Using The Same As The printf() Family, A va_list */
	va_start(arg, szFormat);              /* We Start The List */
	if ((logLevel <= level) && logFile) { /* If The Log Is Open and requested to log in a level we are accepting... */
		LogVA(level, szFormat, arg);      /* And Ensure The Line Is Written, The Log Must Be Quick */
	}
	va_end(arg); /* We End The List */
}

void LogWarn(const char* szFormat, ...) {
	const LogLevel level = LOG_WARN;
	va_list arg;                          /* We're Using The Same As The printf() Family, A va_list */
	va_start(arg, szFormat);              /* We Start The List */
	if ((logLevel <= level) && logFile) { /* If The Log Is Open and requested to log in a level we are accepting... */
		LogVA(level, szFormat, arg);      /* And Ensure The Line Is Written, The Log Must Be Quick */
	}
	va_end(arg); /* We End The List */
}

void LogError(const char* szFormat, ...) {
	const LogLevel level = LOG_ERROR;
	va_list arg;                          /* We're Using The Same As The printf() Family, A va_list */
	va_start(arg, szFormat);              /* We Start The List */
	if ((logLevel <= level) && logFile) { /* If The Log Is Open and requested to log in a level we are accepting... */
		LogVA(level, szFormat, arg);      /* And Ensure The Line Is Written, The Log Must Be Quick */
	}
	va_end(arg); /* We End The List */
}

void LogFatal(const char* szFormat, ...) {
	const LogLevel level = LOG_FATAL;
	va_list arg;                          /* We're Using The Same As The printf() Family, A va_list */
	va_start(arg, szFormat);              /* We Start The List */
	if ((logLevel <= level) && logFile) { /* If The Log Is Open and requested to log in a level we are accepting... */
		LogVA(level, szFormat, arg);      /* And Ensure The Line Is Written, The Log Must Be Quick */
	}
	va_end(arg); /* We End The List */
	exit(E_UNKNOWN);
}


void LogSetLevel(LogLevel level) {
	if ((level > LOG_UNKNOWN) && (level < LOG_LEVEL_COUNT)) {
		logLevel = level;
	}
}


int LogIsDebug(void) {
	return logLevel == LOG_DEBUG;
}


void LogGLParams(void) {
	const GLenum params[] = {GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, GL_MAX_CUBE_MAP_TEXTURE_SIZE, GL_MAX_DRAW_BUFFERS, GL_MAX_FRAGMENT_UNIFORM_COMPONENTS, GL_MAX_TEXTURE_IMAGE_UNITS, GL_MAX_TEXTURE_SIZE, GL_MAX_VARYING_VECTORS, GL_MAX_VERTEX_ATTRIBS, GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS, GL_MAX_VERTEX_UNIFORM_COMPONENTS, GL_MAX_VIEWPORT_DIMS, GL_STEREO,};
	const char* names[] = {"GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS", "GL_MAX_CUBE_MAP_TEXTURE_SIZE", "GL_MAX_DRAW_BUFFERS", "GL_MAX_FRAGMENT_UNIFORM_COMPONENTS", "GL_MAX_TEXTURE_IMAGE_UNITS", "GL_MAX_TEXTURE_SIZE", "GL_MAX_VARYING_VECTORS", "GL_MAX_VERTEX_ATTRIBS", "GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS", "GL_MAX_VERTEX_UNIFORM_COMPONENTS", "GL_MAX_VIEWPORT_DIMS", "GL_STEREO",};
	LogInfo("GL Context Params:");
	// integers - only works if the order is 0-10 integer return types
	for (int i = 0; i < 10; i++) {
		int v = 0;
		glGetIntegerv(params[i], &v);
		LogInfo("%s %i", names[i], v);
		LogGLDebug("In LogGLParams() loop");
	}
	// others
	int v[2];
	v[0] = v[1] = 0;
	glGetIntegerv(params[10], v);
	LogInfo("%s %i %i", names[10], v[0], v[1]);
	LogGLDebug("In LogGLParams()");
	unsigned char s = 0;
	glGetBooleanv(params[11], &s);
	LogInfo("%s %i", names[11], (unsigned int)s);
	LogGLDebug("In LogGLParams() loop");
	LogInfo("-----------------------------");
}


const char* glErrorString(const GLenum error) {
	switch (error) {
	case GL_INVALID_ENUM:
		//An unacceptable value is specified for an enumerated argument.
		//The offending command is ignored
		//and has no other side effect than to set the error flag.
		return "Invalid enum.";
	case GL_INVALID_VALUE:
		//A numeric argument is out of range.
		//The offending command is ignored
		//and has no other side effect than to set the error flag.
		return "Invalid value.";
	case GL_INVALID_OPERATION:
		//The specified operation is not allowed in the current state.
		//The offending command is ignored
		//and has no other side effect than to set the error flag.
		return "Invalid operation.";
	case GL_STACK_OVERFLOW:
		//This command would cause a stack overflow.
		//The offending command is ignored
		//and has no other side effect than to set the error flag.
		return "Stack overflow.";
	case GL_STACK_UNDERFLOW:
		//This command would cause a stack underflow.
		//The offending command is ignored
		//and has no other side effect than to set the error flag.
		return "Stack underflow";
	case GL_OUT_OF_MEMORY:
		//There is not enough memory left to execute the command.
		//The state of the GL is undefined,
		//except for the state of the error flags,
		//after this error is recorded.
		return "Out of memory";
	case GL_TABLE_TOO_LARGE:
		//The specified table exceeds the implementation's maximum supported table
		//size.  The offending command is ignored and has no other side effect
		//than to set the error flag.
		return "Table is too large";
	case GL_NO_ERROR:
		//No error has been recorded.
		//The value of this symbolic constant is guaranteed to be 0.
		return "No error.";
	default:
		return "Unknown error";
	}
}


/* Log a GL error */
void LogGlVa(const char* format, va_list args) {
	const GLenum error = glGetError();
	if (error != GL_NO_ERROR) {
		char buffer[256];
		LogLevel level;
		if (error == GL_OUT_OF_MEMORY) {
			level = LOG_FATAL;
		} else {
			level = LOG_WARN;
		}
		vsnprintf(buffer, 256, format, args);
		Log(level, "GLError:%d, %s, %s", error, buffer, glErrorString(error));
	}
}


/* Log a GL error IF in debug mode */
void LogGLDebug(const char* format, ...) {
	if (LogIsDebug()) {
		va_list args;
		va_start(args, format);
		LogGlVa(format, args);
		va_end(args);
	}
}


/* Log a GL error */
void LogGL(const char* format, ...) {
	va_list args;
	va_start(args, format);
	LogGlVa(format, args);
	va_end(args);
}


/* Log description of a GL error */
void LogGlVaDescription(const char* format, va_list args) {
	const GLenum error = glGetError();
	if (error != GL_NO_ERROR) {
		char buffer[256];
		LogLevel level;
		if (error != GL_OUT_OF_MEMORY) {
			level = LOG_FATAL;
		} else {
			level = LOG_WARN;
		}
		vsnprintf(buffer, 256, format, args);
		LogDescription(level, "%s, %s", buffer, glErrorString(error));
	}
}


/* Log a GL error IF in debug mode and file name and line number. */
void LogGLDebugFL(const char* file, int line, const char* format, ...) {
	if (LogIsDebug()) {
		const GLenum error = glGetError();
		if (error != GL_NO_ERROR) {
			LogLevel level;
			va_list args;
			va_start(args, format);
			LogStart(LOG_WARN, file, line);
			char buffer[256];
			if (GL_OUT_OF_MEMORY == error) {
				level = LOG_FATAL;
			} else {
				level = LOG_WARN;
			}
			vsnprintf(buffer, 256, format, args);
			va_end(args);
			LogDescription(level, "%s, %s", buffer, glErrorString(error));
		} else {
			va_list args;
			va_start(args, format);
			LogVA(LOG_DEBUG, format, args);
			va_end(args);
		}
	}
}


/* Log a GL error and file name and line number. */
void LogGlFl(const char* file, int line, const char* format, ...) {
	const GLenum error = glGetError();
	if (error != GL_NO_ERROR) {
		LogLevel level;
		va_list args;
		va_start(args, format);
		LogStart(LOG_WARN, file, line);
		char buffer[256];
		if (error == GL_OUT_OF_MEMORY) {
			level = LOG_FATAL;
		} else {
			level = LOG_WARN;
		}
		vsnprintf(buffer, 256, format, args);
		va_end(args);
		LogDescription(level, "%s, %s", buffer, glErrorString(error));
	}
}
