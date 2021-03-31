#include <iostream>
#include <vector>

using namespace std;

void printTowers(vector<int>& firstTower, vector<int>& secTower, vector<int>& thirdTower)
{
	cout << "First tower" << endl;
	for (int i = firstTower.size() - 1; i >= 0; --i)
	{
		if (firstTower[i] != 0)
		{
			for (int j = 0; j < 5 - firstTower[i]; ++j)
			{ cout << ' '; }
			cout << '(';
			for (int j = 0; j < firstTower[i] * 2; ++j)
			{ cout << '='; }
			cout << ')';
		}
		cout << endl;
	}
	cout << endl << endl;
	cout << "Second tower" << endl;
	for (int i = secTower.size() - 1; i >= 0; --i)
	{
		if (secTower[i] != 0)
		{
			for (int j = 0; j < 5 - secTower[i]; ++j)
			{
				cout << ' ';
			}
			cout << '(';
			for (int j = 0; j < secTower[i] * 2; ++j)
			{
				cout << '=';
			}
			cout << ')';
		}
		cout << endl;
	}
	cout << endl << endl;
	cout << "Third tower" << endl;
	for (int i = thirdTower.size() - 1; i >= 0; --i)
	{
		if (thirdTower[i] != 0)
		{
			for (int j = 0; j < 5 - thirdTower[i]; ++j)
			{
				cout << ' ';
			}
			cout << '(';
			for (int j = 0; j < thirdTower[i] * 2; ++j)
			{
				cout << '=';
			}
			cout << ')';
		}
		cout << endl;
	}
	cout << endl << endl;
}

void restore(vector<int>& firstTower, vector<int>& secTower, vector<int>& thirdTower, int from, int to, int quant)
{
	vector<int>* towers[] = { &firstTower, &secTower, &thirdTower };
	if (quant == 1)
	{
		int mv = (*towers[from]).back();
		(*towers[from]).pop_back();
		(*towers[to]).push_back(mv);
	}
	else
	{
		int tmpTo;
		for (int i = 0; i < 3; ++i)
		{
			if (i != from && i != to)
			{ tmpTo = i; }
		}
		restore(firstTower, secTower, thirdTower, from, tmpTo, quant - 1);
		restore(firstTower, secTower, thirdTower, from, to, 1);
		cout << "From " << from + 1 << " to " << to + 1 << endl;
		restore(firstTower, secTower, thirdTower, tmpTo, to, quant - 1);
	}
}


int main()
{
	vector<int> firstTower = { 5,4,3,2,1 };
	vector<int> secTower(5);
	vector<int> thirdTower(5);
	printTowers(firstTower, secTower, thirdTower);
	restore(firstTower, secTower, thirdTower, 0, 2, 5);
	cout << "Restore" << endl;
	printTowers(firstTower, secTower, thirdTower);
	return 0;
}    

