#include <iostream>
#include <cmath>
#include <chrono>

using namespace std;

template<size_t size>
int getMax(int(&arr)[size])
{
	int max = arr[0];
	for (int i = 1; i < size; i++)
		if (arr[i] > max)
			max = arr[i];
	return max;
}

template<size_t size>
void countSort(int(&arr)[size], int rank)
{
	int output[size];
	int i, count[10] = { 0 };

	for (i = 0; i < size; ++i)
	{
		++count[((arr[i] / rank) % 10)];
	}

	for (i = 1; i < 10; ++i)
	{
		count[i] += count[i - 1];
	}

	for (i = size - 1; i >= 0; --i)
	{
		output[count[((arr[i] / rank) % 10)] - 1] = arr[i];
		--count[((arr[i] / rank) % 10)];
	}

	for (i = 0; i < size; ++i)
	{
		arr[i] = output[i];
	}
}

template<size_t size>
void radixSortByModule(int(&arr)[size])
{
	int max = getMax(arr);

	for (int rank = 1; max / rank > 0; rank *= 10)
	{
		countSort(arr, rank);
	}
}


bool bitMask(int number, int bitwise)
{
	int a = number;
	int x = 65536;
	int n;

	for (int i = 0; i < 16; i++)
	{
		if (i != 0)
			x = x >> 1;
		if (i == 16 - bitwise)
		{
			n = a & x;
			if (n != 0)
				return 1;
			else
				return 0;
		}
	}
}


void maskForEachBitwise(int arr[], const int& size, int bitwise)
{
	int* tempArr = new int[size];
	int temp = 0;
	for (int j = 0; j < 2; ++j)
		for (int i = 0; i < size; ++i)
			if (bitMask(arr[i], bitwise) == j)
				tempArr[temp++] = arr[i];

	for (int i = 0; i < size; ++i)
		arr[i] = tempArr[i];
}

void radixSortByBitmask(int arr[], const int& size)
{
	for (int i = 1; i <= 16; ++i)
	{
		maskForEachBitwise(arr, size, i);
	}
}



int main()
{
	const int size = 10000;
	int arr[size];

	for (int i = 0; i < size; ++i)
	{
		arr[i] = rand() % 10000;
	}

	chrono::steady_clock::time_point beginByModule = chrono::high_resolution_clock::now();
	radixSortByModule(arr);
	chrono::steady_clock::time_point endByModule = chrono::high_resolution_clock::now();
	cout << "Radix sort with modulo division: " << chrono::duration_cast<chrono::nanoseconds>(endByModule - beginByModule).count() << " nanoseconds." << endl << endl;

	for (int i = 0; i < size; ++i)
	{
		arr[i] = rand() % 1000;
	}

	chrono::steady_clock::time_point beginByBitmask = chrono::high_resolution_clock::now();
	radixSortByBitmask(arr,size);
	chrono::steady_clock::time_point endByBitmask = chrono::high_resolution_clock::now();
	cout << "Radix sort with bitmask: " << chrono::duration_cast<chrono::nanoseconds>(endByBitmask - beginByBitmask).count() << " nanoseconds." << endl << endl;

	return 0;
}