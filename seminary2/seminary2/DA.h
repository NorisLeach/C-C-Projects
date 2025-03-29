#pragma once
#include<stdbool.h>

struct DynamicArray {
	unsigned int capacity, size;
	void** data;  // points to void pointer ; data is a pointer to void pointer
};

struct DynamicArray* DynamicArray_Create(unsigned int capacity);
void DynamicArray_Destroy(struct DynamicArray* arr);
void DynamicArray_Append(struct DynamicArray* arr, void* value);// void* pt ca fiecare elem din data un un void pointer
int DynamicArray_Find(struct DynamicArray* arr, void* value, bool(*compare)(const void* data1, const void* data2));
void DynamicArray_Display(struct DynamicArray* arr, void(*display)(const void* arr));