#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    constexpr int div = 15746;

    int n;
    cin >> n;

    vector<int> dp(n + 1, 0);

    dp[1] = 1;
    dp[2] = 2;
    for (int i = 3; i <=n; ++i)
    {
        dp[i] = (dp[i-2] + dp[i-1]) % div;

    }

    cout << dp[n] << endl;

    return 0;
}