#include <iostream>
#include <vector>
using namespace std;

int solution(vector<int> sticker)
{
	int answer = 0;

	if (sticker.size() == 1)
	{
		return sticker[0];
	}

	constexpr int INF = 100'000 * 100 + 1;

	// pair< 선택, 미선택 >
	{
		// 첫번재 선택
		vector<pair<int, int>> dp(sticker.size());
		dp[0].first = sticker[0];
		dp[0].second = -INF;
		
		for (int i = 1; i < dp.size(); ++i)
		{
			dp[i].first = dp[i - 1].second + sticker[i];
			dp[i].second = max(dp[i - 1].first, dp[i - 1].second);
		}
		
		// 마지막 선택 불가
		answer = dp.back().second;
	}
		
	{
		// 첫번째 미선택
		vector<pair<int, int>> dp(sticker.size());
		dp[0].first = -INF;
		dp[0].second = 0;
		
		for (int i = 1; i < dp.size(); ++i)
		{
			dp[i].first = dp[i - 1].second + sticker[i];
			dp[i].second = max(dp[i - 1].first, dp[i - 1].second);
		}
		
		answer = max(answer, max(dp.back().first, dp.back().second));
	}
		
	return answer;
}

int main()
{
	freopen("../../input.txt", "r", stdin);

	int n;
	cin >> n;

	vector<int> sticker(n);
	for (int i = 0; i < n; ++i)
	{
		cin >> sticker[i];
	}

	cout << solution(sticker) << endl;

	return 0;
}