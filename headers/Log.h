//
// Created by stu on 31/07/23.
//

#ifndef OPENGLSDL_LOG_H
#define OPENGLSDL_LOG_H



typedef enum LogLevel {
    LOG_UNKNOWN,
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR,
    LOG_FATAL,
    LOG_LEVEL_COUNT
}LOGLEVEL;


extern const char APP_NAME[];
extern const char APP_VERSION[];


extern void LogInit(void);									/* Initialises logging. */
extern void LogSetLevel(LOGLEVEL level);					/* request a specific level of logging */
extern void LogEnd(void);									/* Close logging */

extern int LogIsDebug(void);								/* true if we are in debug loglevel (or deeper, currently debug is deepest level). */

extern void LogStart(LOGLEVEL level, const char *file, int line);		// output the start of a log line
extern void LogDescription(LOGLEVEL level, const char *format, ...);	// log the descript part of the line
extern void LogStartDescription(LOGLEVEL level, const char *file, int line, const char *format, ...);

// log a message
extern void Log(LOGLEVEL level, const char *szFormat, ...);

extern void LogDebug(const char *szFormat, ...);
extern void LogInfo(const char *szFormat, ...);
extern void LogWarn(const char *szFormat, ...);
extern void LogError(const char *szFormat, ...);
extern void LogFatal(const char *szFormat, ...);

extern void LogGLDebug(const char* format, ...);			// log gl error only if in debug mode
extern void LogGL(const char *format, ...);
extern void LogGLParams();									// gonna move this...

// Log a GL error IF in debug mode and file name and line nbr
extern void LogGLDebugFL(const char *file, int line, const char *format, ...);

// Log a GL error and file name and line nbr
extern void LogGlFl(const char *file, int line, const char *format, ...);


#endif //OPENGLSDL_LOG_H
