#ifndef MYLIB_H
#define MYLIB_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#define BILLION 1E9

typedef float dataType_t;

void myFunc_Accel_4(unsigned int size, unsigned int dim, dataType_t threshold, dataType_t * data0, dataType_t * data1, dataType_t * data2);
void myFunc_Accel_16(unsigned int size, unsigned int dim, dataType_t threshold, dataType_t * data0, dataType_t * data1, dataType_t * data2);

#endif

