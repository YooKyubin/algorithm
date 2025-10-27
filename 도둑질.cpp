#include <vector>
#include <iostream>

using namespace std;

int solution(vector<int> money) {
    int answer = 0;

    int n = (int)money.size();

    // dp[0][i]: 첫번째 집을 털고, i번째 집까지 털었을때의 최대값
    // dp[1][i]: 첫번째 집을 털지 않고, i번재 집가지 털었을때의 최대값
    vector<vector<int>> dp(2, vector<int>(n, 0));

    dp[0][0] = money[0];
    dp[0][1] = dp[0][0];
    for (int i = 2; i < n-1; ++i)
    {
        dp[0][i] = max(dp[0][i-1], money[i] + dp[0][i-2]);
    }
    dp[0][n-1] = dp[0][n-2];

    dp[1][0] = 0;
    dp[1][1] = money[1];
    for (int i = 2; i < n; ++i)
    {
        dp[1][i] = max(dp[1][i-1], money[i] + dp[1][i-2]);
    }

    answer = max(dp[0].back(), dp[1].back());
    
    return answer;
}

int main()
{
    vector<int> money = {3, 1, 1, 2};
    cout << solution(money) << endl;
    return 0;
}