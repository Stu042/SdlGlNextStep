//
// Created by stu on 30/07/23.
//

#ifndef OPENGLSDL_FILE_H
#define OPENGLSDL_FILE_H


// count items in a null terminated array - not including the null
extern int CountStringPtrArraySize(const char **array);


// Load a file given filename/path, free contents with FreeFile()
extern const char *ReadFile(const char *fileName);

// Free a file after reading with ReadFile()
extern void FreeFile(const char *fileContents);

// Returns a null terminated array of pointers to strings read from files, clean up with FreeFiles()
extern const char **ReadFiles(const char **filenames);

// Free a file after reading with ReadFiles()
extern void FreeFiles(const char **files);


#endif //OPENGLSDL_FILE_H
