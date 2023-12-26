#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define PATH "./nums.txt"

int quickSelect(int*, int, int);

void printArr(int* arr, int arrSize)
{
	printf("[");
	for (int i = 0; i < arrSize-1; i++)
	{
		printf("%d,", arr[i]);
	}
	printf("%d]\n", arr[arrSize-1]);

}



int main(int argc, char** argv)
{
	int nthToFind = atoi(argv[1]);
	FILE *nums;

	nums = fopen(PATH, "r");
	if (nums == NULL)
	{
		fprintf(stderr, "Unable To Resolve Path: \"%s\"\n", PATH);
		return -1;
	}

	int arraySize = 0;
	fscanf(nums, "%d", &arraySize);

	int* array = calloc(arraySize, sizeof(*array));

	for (int i = 0; i < arraySize; i++)
	{
		fscanf(nums, "%d", array+i);
	}

	//We now have array[] and arraySize
	
	//printf("input array = ");
	//printArr(array, arraySize);	
	int nthSmallest = quickSelect(array, arraySize, nthToFind);

	printf("%d\n", nthSmallest);

	fclose(nums);	

	return 0;
}

int quickSelect(int* arr, int arrSize, int nth) //nth smallest element
{
	if (nth > arrSize || nth <= 0)
	{
		fprintf(stderr, "out of bounds!\n");
		free(arr);
		return -1;
	}
	if (arrSize == 1)
	{
		int trivial = *arr;
		free(arr);
		return trivial;
	}
	srand(time(NULL));
	int pivot = (rand() % arrSize);
	//printf("pivot = %d, arr[pivot] = %d\n", pivot, arr[pivot]);

	//It's possible to pivot in place, perhaps try this, as it uses less heap
	int* tempArr = calloc(arrSize-1, sizeof(*tempArr));

	int linc = 0;
	int rinc = 0;

	for (int i = 0; i < pivot; i++)
	{
		if (arr[i] <= arr[pivot])
		{
			tempArr[linc++] = arr[i];
		}
		else
		{
			tempArr[arrSize-(rinc++)-2] = arr[i];
		}
	}

	for (int j = pivot+1; j < arrSize; j++)
	{

		if (arr[j] <= arr[pivot])
		{
			tempArr[linc++] = arr[j];
		}
		else
		{
			tempArr[arrSize-(rinc++)-2] = arr[j];
		}
	}
	//printf("arr = ");
	//printArr(arr, arrSize);
	//printf("tempArr = ");
	//printArr(tempArr, arrSize-1);

	if (nth < linc+1)
	{
		int* leftArr = calloc(linc, sizeof(*leftArr));
		memcpy(leftArr, tempArr, linc*sizeof(*leftArr));
		free(tempArr);
		free(arr);
		//printf("sorting leftArr, linc = %d\n", linc);
		return quickSelect(leftArr, linc, nth); 
	}
	if (nth == linc+1)
	{
		free(tempArr);
		//printf("returning arr[pivot] = %d\n", arr[pivot]);
		int toReturn = arr[pivot];
		free(arr);
		return toReturn;
	}
	if (nth > linc+1)
	{
		int* rightArr = calloc(rinc, sizeof(*rightArr));
		memcpy(rightArr, tempArr+linc, rinc*sizeof(*rightArr));
		free(tempArr);
		free(arr);
		//printf("sorting rightArr, rinc = %d\n", rinc);
		return quickSelect(rightArr, rinc, nth-(linc+1));
	}
}


