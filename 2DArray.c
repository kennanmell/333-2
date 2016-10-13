//
//  2DArray.c
//  
//
//  Created by Kennan Mell on 10/12/16.
//
//

#include "2DArray.h"
#include <stdlib.h>
#include <stdio.h>

#define PtrSize sizeof(Array2DIndexPtr)

typedef void* Array2DIndexPtr;

typedef struct array_head {
    int rows;
    int columns;
    Array2DIndexPtr head;
} Array2DHead;

int main() {
    int temp = 4;
    Array2D array = AllocateArray2D(3, 3);
    set(array, &temp, 1, 1);
    int* result = (int*) get(array, 1, 2);
    printf("%i\n", *result);
}

Array2DPayload_t get(Array2D array, int x, int y) {
    if (array == NULL || x > array->rows || y > array->columns || x < 0 || y < 0) {
        // Parameters out of bounds, or null array.
        return (Array2DPayload_t) NULL;
    }
    return (Array2DPayload_t) array->head + y * array->columns * PtrSize + x * PtrSize;

}

int swap(Array2D array, int x1, int y1, int x2, int y2) {
    if (array == NULL) {
        return 1;
    }
    
    if (x1 < 0 || y1 < 0 || x1 > array->rows || y1 > array->columns || x2 < 0 || y2 < 0 || x2 > array->rows || y2 >= array->columns) {
        // Index out of bounds.
        return 2;
    }

    Array2DPayload_t p = get(array, x1, y1);
    set(array, get(array, x2, y2), x1, y1);
    set(array, p, x2, y2);
    return 0;
}

int set(Array2D array, Array2DPayload_t value, int x, int y) {
    if (array == NULL) {
        return 1;
    }
    
    if (x < 0 || y < 0 || x > array->rows || y > array->columns) {
        // Index out of bounds.
        return 2;
    }
    
    long* index = (long*) array->head + y * array->columns * PtrSize + x * PtrSize;
    *index = (long) value;
    
    printf("%ld\n%ld\n", (long)array->head, (long)index);
    
    
    return 0;
}

Array2D AllocateArray2D(int x, int y) {
    if (x < 1 || y < 1) {
        // Parameters out of bounds.
        return (Array2D) NULL;
    }
    
    // allocate the 2D Array
    Array2D array = (Array2D) malloc(sizeof(Array2DHead));
    if (array == NULL) {
        // out of memory
        return (Array2D) NULL;
    }
    
    array->rows = x - 1;
    array->columns = y - 1;
    
    Array2DIndexPtr head = (Array2DIndexPtr) malloc(PtrSize * x * y);
    if (head == NULL) {
        // out of memory
        return (Array2D) NULL;
    }
    array->head = head;
    
    // return the array
    return array;
}

void FreeArray2D(Array2D array, Array2DPayloadFreeFnPtr payload_free_function) {
    for (Array2DIndexPtr x = array->head; x < array->head + array->rows * array->columns * PtrSize; x += PtrSize) {
        payload_free_function(x);
    }
    
    free(array->head);
    free(array);
}
