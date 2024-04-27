#include <iostream>
#include <vector>
#include <string>

using namespace std;

int n;
string str;
vector<vector<bool>> isPalindrome;
vector<int> dp;

int min(int a, int b) { return a < b ? a : b; }

void printPalindrome()
{
    for (int i=0; i<n; ++i)
    {
        for (int j=0; j<n; ++j)
        {
            cout << isPalindrome[i][j] << " ";
        }
        cout << endl;
    }
}

void FillPalindrome()
{
    for (int i=0; i<n; ++i)
    {
        isPalindrome[i][i] = true;
    }

    for (int i=1; i<n; ++i)
    {
        isPalindrome[i-1][i] = str[i-1] == str[i];
    }

    for (int interval = 2; interval < n; ++interval)
    {
        for (int start=0; start + interval < n; ++start)
        {
            int end = start + interval;
            
            bool result = str[start] == str[end];
            result = result && isPalindrome[start+1][end-1];
            isPalindrome[start][end] = result;
        }
    }
}

void CountDivision()
{
    // dp[0] = 0;
    // dp[0] = 1;
    for (int i=0; i<n; ++i)
    {
        if (isPalindrome[0][i])
            dp[i] = 1;
    }

    for (int end = 0; end < n; ++end)
    {
        for (int start = 1; start <= end; ++start)
        {
            if (isPalindrome[start][end]) 
            {
                dp[end] = min(dp[end], dp[start-1] + 1);
            }
        }
    }
}

int main()
{
    freopen("../../input.txt", "r", stdin);
    cin >> str;
    n = str.length();

    isPalindrome.resize(n+1, vector<bool>(n+1, false));
    dp.resize(n+1, 2501);

    FillPalindrome();

    CountDivision();

    cout << dp[n-1] << endl;

    return 0;
}