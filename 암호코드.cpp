#include <string>
#include <vector>
#include <iostream>

using namespace std;

// 1:59

constexpr int dividor = 1'000'000;

int main()
{
    freopen("input.txt", "r", stdin);

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string input;
    cin >> input;
    
    vector<int> dp(input.size(), 0);

    if (input[0] != '0')
    {
        dp[0] = 1;
    }

    if (input.size() >= 2)
    {
        int digitTwo = (input[0] - '0') * 10;
        int digitOne = (input[1] - '0');

        if (digitTwo != 0)
        {
            if (0 < digitOne + digitTwo && digitOne + digitTwo <= 26)
            {
                dp[1] += 1;
            }
        }

        if (digitOne != 0)
        {
            dp[1] += dp[0];
        }
    }

    for (int i = 2; i < input.size(); ++i)
    {
        if (input[i] != '0')
        {
            // dp[i].first = (dp[i-1].first + dp[i-1].second) % dividor;
            dp[i] += dp[i-1] % dividor;
        }
        
		int digitTwo = (input[i-1] - '0') * 10;
        int digitOne = (input[i] - '0');

        if (digitTwo != 0)
        {
	        int value = digitTwo + digitOne;
            if (0 < value && value <= 26)
            {
                // dp[i].second = (dp[i-2].first + dp[i-2].second) % dividor;
                dp[i] += dp[i-2] % dividor;
            }
        }
    }

    // cout << (dp.back().first + dp.back().second) % dividor << endl;
    cout << (dp.back()) % dividor << endl;
        
    return 0;
}