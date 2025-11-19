#include <iostream>
#include <vector>

using namespace std;

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n; 
    cin >> n;

    vector<int> dp(n + 1, false);
    dp[1] = true;
    dp[2] = false;
    dp[3] = true;
    dp[4] = true;

    for (int i = 5; i <= n; ++i)
    {
        bool canWin = false;

        canWin |= !dp[i - 1];
        canWin |= !dp[i - 3];
        canWin |= !dp[i - 4];

        // cout << "i: " << i << ", canWin: " << (canWin ? "true" : "false") << endl;
        dp[i] = canWin;
    }

    cout << (dp[n] ? "SK" : "CY") << endl;
    return 0;
}