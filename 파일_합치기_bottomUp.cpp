#include <iostream>
#include <vector>

using namespace std;


int min(int a, int b) { return a < b ? a : b; }

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

        vector<int> arr(n);
        vector<int> prefix(n+1, 0);
        vector<vector<int>> dp (n+1, vector<int>(n+1, 0));

        for (int i=0; i<n; ++i)
            cin >> arr[i];
        
        for (int i=0; i<n; ++i)
            prefix[i+1] = prefix[i] + arr[i];

        // for (int i=0; i+2<n; ++i)
        // {
        //     dp[i][i+2] = prefix[i+1] - prefix[i];
        // }


        for (int i=2; i<n+1; i++) // 파일 간격
        {
            for (int j=0; i+j<n+1; ++j) // 반복할 파일 시작번호
            {
                int left = j;
                int right = i+j;
                int minVal = INT32_MAX;
                for (int mid = left+1; mid < right; ++mid)
                {
                    minVal = min(minVal, dp[left][mid] + dp[mid][right] + prefix[right] - prefix[left]);
                }
                dp[left][right] = minVal;
            }
        }
        cout << dp[0][n] << "\n";
    }
    return 0;
}