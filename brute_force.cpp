#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class Item
{
public:
	int price;
	int weight;
};

int getBestComb(vector<Item>& items, int weightLim)
{
	vector<Item> combs(pow(2, items.size()));
	for (int i = 0; i < pow(2, items.size()); ++i)
	{
		for (int j = 0; j < items.size(); ++j)
		{
			if (((int)(pow(2, j)) & i) > 0)
			{
				combs[i].price += items[j].price;
				combs[i].weight += items[j].weight;
			}
		}
	}
	int imax = 0;
	for (int i = 0; i < pow(2, items.size()); ++i)
	{
		Item a = combs[i];
		Item b = combs[imax];
		if (a.price > b.price && a.weight <= weightLim)
		{ imax = i; }
	}
	if (combs[imax].weight <= weightLim)
	{ 
		return imax; 
	}
	else
	{ 
		return -1; 
	}
}

int main()
{
	const int size = 5;
	vector<Item> items;
	for (int i = 0; i < size; ++i)
	{ 
		Item tmp;
		cout << "Input weight of " << i + 1 << ": ";
		cin >> tmp.weight;
		cout << "Input price of " << i + 1 << ": ";
		cin >> tmp.price;
		items.push_back(tmp);
	}
	int best = getBestComb(items, 15);
	for (int i = 0; i < size; ++i)
	{
		if (((int)(pow(2, i)) & best) > 0)
		{
			cout << "Take " << i + 1 << endl;
		}
	}
	return 0;
}