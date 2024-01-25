#include <iostream>
#include <vector>

using namespace std;

int n, m;
vector<int> arr;
vector<vector<bool>> dp;

int main()
{
	cin.tie(0);
	ios_base::sync_with_stdio(false);

	cin >> n;
	arr.resize(n);
	dp.resize(n, vector<bool>(n, false));
	for (int i = 0; i < n; ++i)
	{
		cin >> arr[i];
	}

	// init
	for (int i = 0; i < n; ++i)
	{
		dp[i][i] = true;
	}
	for (int i = 1; i < n; ++i)
	{
		if (arr[i] == arr[i - 1])
		{
			dp[i - 1][i] = true;
		}
	}

	// dp
	for (int diff = 2; diff < n; ++diff)
	{
		for (int i = 0; i+diff < n; ++i)
		{
			if (dp[i + 1][i + diff - 1] && arr[i] == arr[i+diff])
			{
				dp[i][i + diff] = true;
			}
		}
	}

	cin >> m;
	for (int i = 0; i < m; ++i)
	{
		int s, e;
		cin >> s >> e;
		cout << dp[s-1][e-1] << "\n";
	}
	return 0;
}
