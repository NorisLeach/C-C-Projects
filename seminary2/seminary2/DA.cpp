#include "DA.h"
#include <stdlib.h>
#include <stdio.h>

struct DynamicArray* DynamicArray_Create(unsigned int capacity) {
	struct DynamicArray* arr = (struct DynamicArray*)malloc(sizeof(struct DynamicArray));
	if (!arr)
		exit(-1);
	arr->capacity = capacity;
	arr->size = 0;
	arr->data = (void**)malloc(capacity * sizeof(void*));
	if (!arr)
		exit(-1);
	return arr;
}

void destroyDynamicArray(struct DynamicArray* arr) {
	if (arr)
	{
		free(arr->data);
		free(arr);
	}
}

void DynamicArray_Display(struct DynamicArray* arr, void(*display)(const void* arr)) {
	printf("Dynamic Array: capacity: %u, lenght: %u \n", arr->capacity, arr->size);
	for (unsigned int i = 0; i < arr->size; i++)
	{
		display(arr->data[i]);
	}
}

void DynamicArray_Append(struct DynamicArray* arr, void* value)
{
	if (arr->capacity == arr->size)
		arr->capacity *= 2;
	arr->data[arr->size++] = value;
}