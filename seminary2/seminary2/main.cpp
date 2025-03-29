#include <stdlib.h>
#include <stdio.h>
#include "DA.h"

void dislay_int(const void* el)
{
	printf("%d", *(int*)el); // cast
}

void test_int()
{
	struct DynamicArray* arr = DynamicArray_Create(10);
	DynamicArray_Display(arr, dislay_int);

	int a[] = { 10, 20 ,30, 40, 50, 60 };
	for (int i = 0;i < 6;i++)
		DynamicArray_Append(arr, &a[i]);

	DynamicArray_Display(arr, dislay_int);
}

void main() 
{

}