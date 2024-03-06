#include <iostream>
#include <vector>

using namespace std;

bool DP(int target, int idx, const vector<int>& coinsArr, vector<int>& memo)
{
    if (target < 0)
        return false;

    if (idx >= coinsArr.size())
        return false;

    if (target - coinsArr[idx] == 0)
        return true;

    if (memo[target] != -1)
        return memo[ target ];

    return memo[target] = 
    (
        DP(target-coinsArr[idx], idx+1, coinsArr, memo) || 
        DP(target, idx+1, coinsArr, memo)
    );
}

int main()
{
    // freopen("../../input.txt", "r", stdin);
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    int testcase = 3;
    while(testcase--)
    {
        int n;
        int sum = 0;
        cin >> n;
        vector<pair<int, int>> coins(n);
        vector<int> coinsArr;
        for (int i=0; i<n; ++i)
        {
            cin >> coins[i].first >> coins[i].second;

            sum += coins[i].first * coins[i].second;
            for (int j=0; j<coins[i].second; ++j)
                coinsArr.push_back(coins[i].first);
        }

        if (sum % 2 == 1)
        {
            cout << 0 << "\n";
            continue;
        }

        int target = sum / 2;
        vector<int> memo(target + 1, -1);
        cout << DP(target, 0, coinsArr, memo) << "\n";
    }
    return 0;
}
/*
    int target = sum / 2;
    vector<bool> memo(target + 1, false);    
    memo[0] = true;

    for (int i=0; i<coinsArr.size(); ++i)
    {
        int value = coinsArr[i];
        for (int j= value; j <= target; ++j)
        {
            memo[j] = memo[j - value] || memo[j];
        }
    }
*/