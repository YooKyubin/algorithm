#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> memo;

int64_t color(int n, int k)
{
    if (memo[n][k] != 0)
        return memo[n][k];

    if (k == 1)
        return n;

    if (n == 2 * k)
        return 2;

    return memo[n][k] = ( color(n-1, k) + color(n-2, k-1) ) % 1'000'000'003;
    
}

int main()
{
    int n, k;
    cin >> n >> k;
    memo.assign(n+1, vector<int>(k+1, 0));

    int answer;
    if (n < 2 * k)
        answer = 0;
    else
        answer = color(n, k);

    cout << answer << endl;
    return 0;
}