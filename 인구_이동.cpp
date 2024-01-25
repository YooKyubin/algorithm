#include <iostream>
#include <vector>

using namespace std;

int n, r, l;
vector<vector<int>> population;

int abs(int a) { return a < 0 ? -a : a; }

int Find(int x, vector<vector<int>>& parent)
{
	int i = x / n;
	int j = x % n;

	if (x == parent[i][j])
		return x;

	return parent[i][j] = Find(parent[i][j], parent);
}

void Union(int x, int y, vector<vector<int>>& parent)
{
	x = Find(x, parent);
	y = Find(y, parent);

	parent[x / n][x % n] = parent[y / n][y % n];
}

int main()
{
	cin.tie(0);
	ios_base::sync_with_stdio(false);

	cin >> n >> l >> r;
	population.resize(n, vector<int>(n));
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			cin >> population[i][j];
		}
	}

	vector<vector<int>> index(n, vector<int>(n));
	int answer = 0;
	while (true)
	{
		int change = 0;
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				index[i][j] = i * n + j;
			}
		}

		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
			{

				if (i + 1 < n)
				{
					int bottom = abs(population[i + 1][j] - population[i][j]);
					if (l <= bottom && bottom <= r)
					{
						Union((i + 1) * n + j, i * n + j, index);
						++change;
					}
				}

				if (j + 1 < n)
				{
					int right = abs(population[i][j + 1] - population[i][j]);
					if (l <= right && right <= r)
					{
						Union(i * n + (j + 1), i * n + j, index);
						++change;
					}
				}
			}
		}

		if (change == 0)
			break;

		vector<pair<int, int>> temp(n * n); // cnt, population
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				int idx = Find(i * n + j, index);
				temp[idx].first += 1;
				temp[idx].second += population[i][j];
			}
		}

		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				int idx = Find(i * n + j, index);
				population[i][j] = temp[idx].second / temp[idx].first;
			}
		}

		++answer;
	}

	cout << answer << endl;
	return 0;
}