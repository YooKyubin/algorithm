#include <iostream>
#include <vector>

using namespace std;

int main()
{
    freopen("../../input.txt", "r", stdin);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;
    if (n < m)
    {
        swap(n, m);
    }

    vector<bool> dp(n + 1, false);
    dp[1] = false;
    dp[2] = true;
    if (n > 2)
    {
        dp[3] = false;
        for (int i = 4; i <= n; ++i)
        {
            for (int j = 1; j < i / 2; ++j)
            {
                // i개의 돌을 j와 k개로 나눔
                int k = i - j; 
                // 상대는 k 혹은 j개의 돌이 들어있는 박스에서 선택
                bool oppositeResult = (dp[k] || dp[j]);
                // 상대의 승리는 나의 패배, 상대의 패배는 나의 승리
                dp[i] = dp[i] || !oppositeResult;
            }
        } 
    }
        
    if (dp[n] || dp[m])
    {
        cout << "A" << endl;
    }
    else
    {
        cout << "B" << endl;
    }

    return 0;
}