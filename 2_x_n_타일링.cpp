#include <vector>

using namespace std;

int solution(int n) {
	constexpr int MOD = 1'000'000'007;
	int answer = 0;

	vector<int> dp(n + 1, 0);
	dp[1] = 1;
	dp[2] = 2;

	for (int i = 3; i <= n; ++i)
	{
		dp[i] = (dp[i - 1] + dp[i - 2]) % MOD;
	}

	answer = dp[n];
	return answer;
}