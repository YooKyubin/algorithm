#include <iostream>
#include <vector>
#include <string>

using namespace std;

int max(int a, int b) { return a > b ? a : b; }

int main()
{
	string a;
	string b;
	vector<vector<int>> dp;

	cin >> a;
	cin >> b;
	dp.resize(a.length() + 1, vector<int>(b.length() + 1, 0));

	for (int i = 1; i < dp.size(); ++i)
	{
		for (int j = 1; j < dp[i].size(); ++j)
		{
			int idxStringA = i - 1;
			int idxStringB = j - 1;

			if (a[idxStringA] == b[idxStringB])
			{
				dp[i][j] = dp[i - 1][j - 1] + 1;
			}
			else
			{
				dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
			}
		}
	}


	pair<int, int> cur = { dp.size() - 1, dp[0].size() - 1 };
	int value = dp[cur.first][cur.second];
	vector<char> answer_reversed;
	while (value != 0)
	{
		int x = cur.first;
		int y = cur.second;

		int nx, ny;

		if (dp[x][y] == dp[x - 1][y])
		{
			nx = x - 1;
			ny = y;
		}
		else if (dp[x][y] == dp[x][y - 1])
		{			
			nx = x;
			ny = y - 1;
		}
		else
		{
			int idxStringA = x - 1;
			answer_reversed.push_back(a[idxStringA]);

			nx = x - 1;
			ny = y - 1;
		}

		value = dp[nx][ny];
		cur = { nx, ny };
	}

	cout << dp.back().back() << endl;
	for (int i = answer_reversed.size() - 1; i >= 0; --i)
	{
		cout << answer_reversed[i];
	}
	cout << endl;
	return 0;
}