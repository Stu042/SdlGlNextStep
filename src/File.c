//
// Created by stu on 30/07/23.
//
#include <stdio.h>
#include <malloc.h>
#include "File.h"
#include "Log.h"
#include "Std.h"


// adds one to file size to allow for \0 terminator.
long getFileSize(FILE *stream) {
	fseek(stream, 0L, SEEK_END);
	const long fileSize = ftell(stream);
	fseek(stream, 0L, SEEK_SET);
	return fileSize + 1;
}


/***********************************
 * global functions
 */



int CountStringPtrArraySize(const char **array) {
	int count = 0;
	const char **curArray = array;
	while (*curArray != NULL) {
		count++;
		curArray++;
	}
	return count;
}

const char *ReadFile(const char *fileName) {
	FILE *stream = fopen(fileName, "r");
	if (!stream) {
		LogError("Failed to open file `%s`\n", fileName);
		return NULL;
	}
	const long fileSize = getFileSize(stream);
	char *buffer = (char *) Alloc(fileSize);
	const size_t readSize = fread(buffer, sizeof(*buffer), fileSize, stream);
	buffer[readSize] = '\0';
	fclose(stream);
	return buffer;
}


void FreeFile(const char *fileContents) {
	free((void *)fileContents);
}



const char **ReadFiles(const char **filenames) {
	if (filenames == NULL) {
		LogError("Asked to read files from an empty array of filenames");
		return NULL;
	}
	const int count = CountStringPtrArraySize(filenames);
	const char **curFilename = filenames;
	const char **files = Alloc(sizeof(char *) * (count + 1));
	const char **curFile = files;
	for (int i = 0; i < count; i++) {
		*curFile++ = ReadFile(*curFilename++);
	}
	*curFile = NULL;
	return files;
}


void FreeFiles(const char **files) {
	if (files == NULL) {
		LogError("Asked to free files from an empty array of files");
		return;
	}
	int count = 0;
	const char **curFile = files;
	while (*curFile != NULL) {
		count++;
		curFile++;
	}
	for (int i = 0; i < count; i++) {
		if (*curFile != NULL) {
			FreeFile(*curFile);
		}
	}
	free(files);
}

