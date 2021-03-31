#include <iostream>
#include <string>
#include <chrono>

using namespace std;

void usrSwapWithTmp(int& a, int& b)
{
	int& tmp = a;
	a = b;
	b = tmp;
}

void usrSwapWithoutTmp(int& a, int& b)
{
	a += b;
	b = a - b;
	a = a - b;
}

template<size_t size>
long long timeCounter(void(*sortFunc)(int(&)[size], void(*)(int&, int&), bool, bool), int(&arr)[size], void(*swapFunc)(int&, int&), bool tmp, bool isStop)
{
	chrono::steady_clock::time_point begin = chrono::high_resolution_clock::now();
	sortFunc(arr, swapFunc, tmp, isStop);
	chrono::steady_clock::time_point end = chrono::high_resolution_clock::now();
	return (chrono::duration_cast<chrono::nanoseconds>(end - begin).count());
}

template<size_t size>
void shakerSort(int (&arr)[size], void(*swapFunc)(int&, int&), bool tmp, bool isStop)
{
	for (int i = 0; i < size / 2; ++i)
	{
		bool stop = true;
		for (int j = i; j < size - 1 - i; ++j)
		{
			if (arr[j] > arr[j + 1])
			{
				if (swapFunc == nullptr)
				{
					if (tmp)
					{
						int tmp = arr[j + 1];
						arr[j + 1] = arr[j];
						arr[j] = tmp;
					}
					else
					{
						arr[j] += arr[j + 1];
						arr[j + 1] = arr[j] - arr[j + 1];
						arr[j] = arr[j] - arr[j + 1];
					}
				}
				else { swapFunc(arr[j], arr[j + 1]); }
				stop = false;
			}
		}
		for (int j = size - 2 - i; j > i; --j)
		{
			if (arr[j] < arr[j - 1])
			{
				if (swapFunc == nullptr)
				{
					if (tmp)
					{
						int tmp = arr[j - 1];
						arr[j - 1] = arr[j];
						arr[j] = tmp;
					}
					else
					{
						arr[j] += arr[j - 1];
						arr[j - 1] = arr[j] - arr[j - 1];
						arr[j] = arr[j] - arr[j - 1];
					}
				}
				else { swapFunc(arr[j], arr[j - 1]); }
				stop = false;
			}
		}
		if (stop && isStop) { break; }
	}
}

template<size_t size>
void bubbleSort(int (&arr)[size], void(*swapFunc)(int&, int&), bool tmp, bool nonused)
{
	for (int i = 0; i < size - 1; ++i)
	{
		for (int j = 0; j < size - 1 - i; ++j)
		{
			if (arr[j] > arr[j + 1])
			{
				if (swapFunc == nullptr)
				{
					if (tmp)
					{
						int tmp = arr[j + 1];
						arr[j + 1] = arr[j];
						arr[j] = tmp;
					}
					else
					{
						arr[j] += arr[j + 1];
						arr[j + 1] = arr[j] - arr[j + 1];
						arr[j] = arr[j] - arr[j + 1];
					}
				}
				else { swapFunc(arr[j], arr[j + 1]); }
			}
		}
	}
}

int main()
{
	srand(time(NULL));
	const int arrSize = 1500;
	int srcArr[arrSize], testArr[arrSize];
	void(*chosenSwap[])(int&, int&) = { swap, usrSwapWithTmp, usrSwapWithoutTmp };
	void(*chosenSort[])(int(&arr)[arrSize], void(*swapFunc)(int&, int&), bool tmp, bool nonused) = { bubbleSort, shakerSort };
	for (int i = 0; i < arrSize; ++i)
	{
		srcArr[i] = rand() % 10001;
	}
	for (int i = 0; i < 100; ++i)
	{
		memcpy(testArr, srcArr, sizeof(int) * 50);
		bubbleSort(testArr, swap, 1, 1);
	}
	string rows[] = { "Default swap", "User swap with temporary sorage", "User swap without temporary storage", "Direct embedding with temporary storage",
		"Direct embedding without temporary storage" };
	string columns[] = { "Bubble sort: ", "Shaker sort: ", "Shaker sort(stops when ready): " };
	for (int i = 0; i < 5; ++i)
	{
		cout << rows[i] << endl;
		for (int j = 0; j < 3; ++j)
		{
			memcpy(testArr, srcArr, sizeof(int) * 50);
			if (i <= 2)
			{
				cout << '\t' << columns[j] << timeCounter(chosenSort[(j > 1) ? 1 : 0], testArr, chosenSwap[i % 4], (bool)i % 2, (j == 2) ? true : false) << " milliseconds" << endl;
			}
			else
			{
				cout << '\t' << columns[j] << timeCounter(chosenSort[(j > 1) ? 1 : 0], testArr, nullptr, (bool)i % 2, (j == 2) ? true : false) << " milliseconds" << endl;
			}
		}
	}
	return 0;
}