//
//  2DArray.h
//  
//
//  Created by Kennan Mell on 10/12/16.
//
//

#ifndef _DArray_h
#define _DArray_h

#include <stdio.h>

typedef struct array_head *Array2D;
typedef void* Array2DPayload_t;
typedef void(*Array2DPayloadFreeFnPtr)(Array2DPayload_t payload);

Array2DPayload_t get(Array2D array, int x, int y);
int swap(Array2D array, int x1, int y1, int x2, int y2);
int set(Array2D array, void* value, int x, int y);
Array2D AllocateArray2D(int x, int y);
void FreeArray2D(Array2D array, Array2DPayloadFreeFnPtr payload_free_function);


#endif /* _DArray_h */
