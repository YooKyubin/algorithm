#include <iostream>
#include <vector>

using namespace std;

vector<int> arr;
vector<vector<int>> memo;
vector<int> prefix;

int min(int a, int b) { return a < b ? a : b; }

int dp(int a, int b)
{
    if (memo[a][b] != INT32_MAX)
        return memo[a][b];
    
    if ( b-a == 1) 
        return memo[a][b] = 0;
    else if (b-a == 2)
        return memo[a][b] = prefix[b] - prefix[a];

    int minVal = INT32_MAX;

    for (int i=a+1; i<b; ++i)
    {
        int dpA = dp(a, i);
        int dpB = dp(i, b);

        minVal = min( minVal, dpA + dpB + prefix[b] - prefix[a]);
    }

    return memo[a][b] = minVal;
}

int main() 
{
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    int testcase;
    cin >> testcase;
    while (testcase--)
    {
        int n;
        cin >> n;

        arr.resize(n);
        memo.assign(n+1, vector<int>(n+1, INT32_MAX));
        prefix.assign(n+1, 0);

        for (int i=0; i<n; ++i)
            cin >> arr[i];
        
        for (int i=0; i<n; ++i)
            prefix[i+1] = prefix[i] + arr[i];

        int answer = dp(0, n);
        
        cout << answer << "\n";

        arr.clear();
        memo.clear();
        prefix.clear();
    }
    return 0;
}