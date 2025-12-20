#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int main()
{
    freopen("../../input.txt", "r", stdin);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;

    vector<int> times(n +1);
    vector<int> costs(n + 1);
    for (int i = 1; i <= n; ++i)
    {
        cin >> times[i] >> costs[i];
    }

    int currMax = 0;
    vector<int> dp(n + 2, 0);
    for (int i = 1; i <= n; ++i)
    {
        int nextDay = i + times[i];

        dp[i] = max(dp[i-1], dp[i]);
        if (nextDay <= n + 1)
        {
            dp[nextDay] = max(dp[nextDay], costs[i] + dp[i]);
        }
    }
    
    cout << max(dp[n], dp[n+1]) << endl;

    return 0;
}
