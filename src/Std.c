//
// Created by stu on 31/07/23.
//
#include <stddef.h>
#include <stdlib.h>
#include<sys/time.h>
#include <stdio.h>
#include "Log.h"


void *Alloc(size_t memSize) {
	void *mem = malloc(memSize);
	if (mem == NULL) {
		LogFatal("Unable to allocate memory...\n\tDaisy, Daisy, give mee yooouur aaansweeeer doooooo... ");
		exit(-1);
	}
	return mem;
}



long long TimeInMilliseconds() {
	struct timeval tv;
	gettimeofday(&tv,NULL);
	return (((long long)tv.tv_sec)*1000)+(tv.tv_usec/1000);
}


void Timestamp(char *out, int maxLength) {
	struct timeval tv;
	gettimeofday(&tv,NULL);
	long long time = tv.tv_sec;
	long seconds = time % 60;
	time /= 60;
	long minutes = time % 60;
	time /= 60;
	long hours = time % 24;
	snprintf(out, maxLength, "%02ld:%02ld:%02ld.%ld", hours, minutes, seconds, tv.tv_usec);
}

