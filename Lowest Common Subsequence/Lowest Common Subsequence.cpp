#include <string>
#include <map>
#include <utility>
#include <iostream>

using namespace std;

string lcs_helper(int i, int j, const string& x, const string& y, map<pair<int, int>, string>& memoizedSolutions)
{
	if (memoizedSolutions.count({ i, j })) return memoizedSolutions[{i, j}]; 

	if (i == 0 || j == 0) return "";

	if (x[i] == y[j]) 
	{
		string lcs = lcs_helper(i - 1, j - 1, x, y, memoizedSolutions);
		lcs.push_back(x[i]);
		memoizedSolutions[{i, j}] = lcs;

		return lcs;
	}

	string lcs1 = lcs_helper(i - 1, j, x, y, memoizedSolutions);
	string lcs2 = lcs_helper(i, j - 1, x, y, memoizedSolutions);

	if (lcs1.size() >= lcs2.size())
	{
		memoizedSolutions[{i, j}] = lcs1;
		return lcs1;
	}

	memoizedSolutions[{i, j}] = lcs2;
	return lcs2;
}

string lcs(string x, string y)
{
	map<pair<int, int>, string> memoizedSolutions;

	return lcs_helper(x.size() - 1, y.size() - 1, x, y, memoizedSolutions); 
}


string lcs_better(string x, string y)
{
	int** lengths = new int* [x.size()];

	for (int i = 0; i < x.size(); i++)
	{
		lengths[i] = new int[y.size()];
	}

	for (int i = 0; i < x.size(); i++)
	{
		for (int j = 0; j < y.size(); j++)
		{
			if (i == 0 || j == 0) lengths[i][j] = 0;
			else if (x[i] == y[j])
			{
				lengths[i][j] = 1 + lengths[i - 1][j - 1];
			}
			else
			{
				lengths[i][j] = max(lengths[i - 1][j], lengths[i][j - 1]);
			}
		}
	}

	string lcs; 

	int i = x.size() - 1;
	int j = y.size() - 1;

	while (i > 0 && j > 0)
	{
		if (x[i] == y[j])
		{
			lcs.push_back(x[i]);
			i--;
			j--; 
		}
		else
		{
			if (lengths[i-1][j] > lengths[i][j-1])
			{
				i--; 
			}
			else
			{
				j--; 
			}
		}
	}

	for (int i = 0; i < x.size(); i++)
	{
		delete lengths[i]; 
	}

	reverse(lcs.begin(), lcs.end()); 

	return lcs;
}

int main()
{
	cout << lcs("CATCGA", "GTACCGTCA");
}

