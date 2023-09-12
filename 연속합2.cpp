#include <iostream>
#include <vector>

using namespace std;

int max(int a, int b) { return a > b ? a : b; }
int max(int a, int b, int c) { return max(a, max(b, c)); }

int main()
{
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;
    vector<int> arr(n);
    vector<int> dp(n, 0);
    vector<int> exclude(n, 0);
    for (int i=0; i<n; ++i)
        cin >> arr[i];

    dp[0] = arr[0];
    exclude[0] = arr[0];

    for (int i=1; i<n; ++i)
    {
        dp[i] = max(dp[i-1] + arr[i], arr[i]);
        //i번째 수가 빠진경우, i번째 수 전에 다른 수가 먼저 빠져있는 경우, (arr[i])
        exclude[i] = max(dp[i-1], exclude[i-1]+arr[i]);
    }

    int maxVal = INT32_MIN;
    for (int i=0; i<n; ++i)
        maxVal = max(maxVal, dp[i], exclude[i]);

    cout << maxVal << endl;
    return 0;
}