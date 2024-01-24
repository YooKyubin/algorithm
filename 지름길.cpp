#include <iostream>
#include <vector>

using namespace std;

constexpr int INF = INT32_MAX;

static int min(int a, int b) { return a < b ? a : b; }

int main()
{
	cin.tie(0);
	ios_base::sync_with_stdio(false);

	int n, d;
	cin >> n >> d;
	vector<vector<int>> inputs(n+1, vector<int>(3));
	vector<vector<int>> dp (d+1, vector<int>(n+1, 0));
	for (int i = 0; i <= d; ++i)
	{
		for (int j = 0; j <= n; ++j)
		{
			dp[i][j] = i;
		}
	}
	for (int i = 1; i <= n; ++i)
	{
		int from, to, dist;
		cin >> from >> to >> dist;
		inputs[i] = { from, to, dist };
	}

	for (int i = 1; i <= d; ++i)
	{
		for (int j=1; j<=n; ++j)
		{
			int from = inputs[j][0];
			int to = inputs[j][1];
			int dist = inputs[j][2];

			dp[i][j] = min(dp[i][j - 1], dp[i - 1][j] + 1);
			if (to == i)
			{
				dp[i][j] = min(dp[i][j], dp[from][n] + dist);
			}

		}
	}

	cout << dp[d][n] << endl;

	return 0;
}