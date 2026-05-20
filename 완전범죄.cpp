#include <iostream>
#include <string>
#include <vector>

using namespace std;

int solution(vector<vector<int>> info, int n, int m) {
	const int numObj = (int)info.size();
	const int INF = n;
	int answer = INF;

	vector<vector<int>> dp(numObj, vector<int>(m, INF));
	dp[0][0] = info[0][0];
	for (int i = 0; i < m; ++i)
	{
		dp[0][i] = info[0][0];
	}
	if (info[0][1] < m)
	{
		dp[0][info[0][1]] = 0;
	}

	for (int i = 1; i < numObj; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			int evidenceA = INF;
			int evidenceB = INF;

			if (dp[i - 1][j] + info[i][0] < n)
			{
				evidenceA = dp[i - 1][j] + info[i][0];
			}

			if (j - info[i][1] >= 0)
			{
				evidenceB = dp[i - 1][j - info[i][1]];
			}

			dp[i][j] = min(evidenceA, evidenceB);
		}
	}

	for (int i = 0; i < m; ++i)
	{
		answer = min(answer, dp.back()[i]);
	}

	return answer != INF ? answer : -1;
}

int main()
{
	// freopen("output.txt", "w", stdout);

	// cin.tie(nullptr);
	// ios_base::sync_with_stdio(false);

	vector<vector<int>> info = {
		{1, 2}, {2, 3}, {2, 1}
	};

	int n = 4;
	int m = 4;

	cout << solution(info, n, m) << endl;
	return 0;
}