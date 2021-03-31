#include <iostream>
#include <chrono>

using namespace std;

template<size_t size>
void insertionSort(int (&arr)[size])
{
	for (int i = 1; i < size; ++i)
	{
		for (int j = i; i > 0 && arr[j - 1] > arr[j]; --j)
		{
			int tmp = arr[j - 1];
			arr[j - 1] = arr[j];
			arr[j] = tmp;
		}
	}
}

int main()
{
	const int size = 1000;
	int a[size];
	for (int i = 0; i < size; ++i)
	{
		a[i] = rand() % 2001 - 1000;
	}

	chrono::steady_clock::time_point start = chrono::high_resolution_clock::now();
	insertionSort(a);
	chrono::steady_clock::time_point end = chrono::high_resolution_clock::now();
	for (int i = 0; i < size; ++i)
	{
		cout << a[i] << ' ';
	}
	cout << endl << "Time elapsed: " << chrono::duration_cast<chrono::microseconds>(end - start).count()  << " mcs" << endl;
	return 0;
}