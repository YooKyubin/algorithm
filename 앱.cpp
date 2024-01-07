#include <iostream>
#include <vector>

using namespace std;

struct App
{
	int cost;
	int memory;
};

int max(int a, int b) { return a > b ? a : b; }
int min(int a, int b) { return a < b ? a : b; }

int main()
{
	int n, m;
	int totalCost = 0;
	int answer = INT32_MAX;
	vector<vector<int>> dp;
	vector<App> app;
	cin >> n >> m;
	app.resize(n+1);
	for (int i = 1; i <= n; ++i)
	{
		cin >> app[i].memory; // memory
	}
	for (int i = 1; i <= n; ++i)
	{
		cin >> app[i].cost; // cost
		totalCost += app[i].cost;
	}
	dp.resize(n+1, vector<int>(totalCost + 1, 0));

	for (int i = 1; i <= n; ++i) // app number
	{
		for (int j = 0; j <= totalCost; ++j) // cost
		{
			// 한정된 cost 안에서 최대 메모리
			//비용이 j일 때 최대 메모리 
			if (j < app[i].cost)
			{
				dp[i][j] = dp[i - 1][j];
			}
			else
			{
				dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - app[i].cost] + app[i].memory);
			}

			if (dp[i][j] >= m)
			{
				answer = min(answer, j);
			}
		}
	}

	cout << answer << endl;

	return 0;
}