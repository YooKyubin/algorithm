#include <iostream>
#include <vector>

using namespace std;

int main()
{
    freopen("../../input.txt", "r", stdin);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;
    vector<int> wine(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> wine[i];
    }

    if (n < 2)
    {
        cout << wine[0];
    }
    else
    {
        // first: drink, second: pass
        vector<pair<int, int>> dp(n);
        dp[0].first = wine[0];
        dp[0].second = 0;

        dp[1].first = dp[0].first  + wine[1];
        dp[1].second = dp[0].first;
        
        for (int i = 2; i < n; ++i)
        {
            dp[i].first = max(dp[i-1].second + wine[i], dp[i-2].second + wine[i-1] + wine[i]);
            dp[i].second = max(dp[i-1].first, dp[i-1].second);
        }
        cout << max(dp.back().first, dp.back().second) << endl;

    }


    return 0;
}