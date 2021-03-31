#include <iostream>
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

template<size_t size>
int sequentialSearch(int (&arr)[size], int searchingElement)
{
	for (int i = 0; i < size; ++i)
	{
		if (arr[i] == searchingElement)
		{ return i; }
		else
		{ continue; }
	}
	cout << "Can't find element." << endl;
	return -1;
}

template<size_t size>
int binarySearch(int (&arr)[size], int searchingElement)
{
	int l = 0;
	int r = size - 1;
	int m;

	if (arr[l] == searchingElement)
	{ return l; }
	else if (arr[r] == searchingElement)
	{ return r; }

	while (((r - l) / 2) != 0)
	{
		m = (r - l) / 2;
		if (arr[l + m] == searchingElement)
		{ return l + m; }
		else if (arr[l + m] > searchingElement)
		{
			r = l + m;
			continue;
		}
		else if (arr[l + m] < searchingElement)
		{
			l += m;
			continue;
		}
	}
	cout << "Can't find element." << endl;
	return -1;
}

int main()
{
	const int size = 1000;
	int a[size];

	for (int i = 0; i < size; ++i)
	{
		a[i] = rand() % 1000;
	}

	chrono::steady_clock::time_point sequentialBegin = chrono::high_resolution_clock::now();
	cout << sequentialSearch(a, a[rand() % size]) << endl;
	chrono::steady_clock::time_point sequentialEnd = chrono::high_resolution_clock::now();
	cout << "Serial sort: " << chrono::duration_cast<chrono::nanoseconds>(sequentialEnd - sequentialBegin).count() << " nanoseconds" << endl << endl;

	for (int i = 0; i < size; ++i)
	{
		a[i] = rand() % 1000;
	}

	radixSortByModule(a);

	chrono::steady_clock::time_point binaryBegin = chrono::high_resolution_clock::now();
	cout << binarySearch(a, a[rand() % size]) << endl;
	chrono::steady_clock::time_point binaryEnd = chrono::high_resolution_clock::now();
	cout << "Binary sort: " << chrono::duration_cast<chrono::nanoseconds>(binaryEnd - binaryBegin).count() << " nanoseconds" << endl << endl;
	return 0;
}