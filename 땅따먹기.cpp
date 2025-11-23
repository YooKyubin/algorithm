#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

bool solution(long long n, long long k)
{
    if (n > k)
    {
        return false;
    }

    long long low = -1;
    long long high = n - (n / 2) + 1;


    while (low + 1 < high)
    {
        long long mid =(low + high) >> 1;

        long long computedK = (n - mid + 1) * mid;
        if (computedK < k)
        {
            low = mid;
        }
        else if (computedK == k)
        {
            return true;
        }
        else // target > k 
        {
            high = mid;
        }
    }

    return false;
}

int main()
{
    freopen("../../input.txt", "r", stdin);
    freopen("../../output.txt", "w", stdout);
    
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int a;
    cin >> a;

    vector<int> dp(a + 1); // is P1 win?
    dp[0] = false;
    dp[1] = false;
    dp[2] = true;

    dp[3] = true;
    dp[4] = false;


    
    return 0;
}