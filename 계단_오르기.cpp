#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int main()
{
    freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;
    vector<int> stairs(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> stairs[i];
    }

    vector<pair<int, int>> dp(n);
    // 이전 계단 그냥 밟고 올라왔을 때, 이전 계단 껑충했을 때.

    dp[0].first = stairs[0];
    dp[0].second = stairs[0];

    dp[1].first = dp[0].first + stairs[1];
    dp[1].second = stairs[1];

    for (int i = 2; i < n; ++i)
    {
        dp[i].first = dp[i-1].second + stairs[i];
        dp[i].second = max(dp[i-2].first, dp[i-2].second) + stairs[i];
    }

    cout << max(dp[n-1].first, dp[n-1].second) << endl;

    return 0;
}

/*
    0 1 2 _ 3
    0 1 _ 3 4 _
    0 _ 2 3 _ 4 5


    n
    n - 1 or n - 2
    n -1 : n-2는 선택되어서는 안됨
    
    이전 계단을 이미 밟았으면, 이번엔 껑충 해야함
    이전 계단 껑충했으면, 그냥밟아도 되고, 껑충해도됨
*/