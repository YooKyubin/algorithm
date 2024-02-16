#include <iostream>
#include <vector>

using namespace std;

inline int min(int a, int b) { return a < b ? a : b; }

int main()
{
    freopen("../../input.txt", "r", stdin);

    cin.tie(0);
    ios_base::sync_with_stdio(false);
    int n, s;
    cin >> n >> s;
    vector<int> arr(n);
    for (int i=0; i<n; ++i)
    {
        cin >> arr[i];
    }

    int begin = 0;
    int end = 1;
    int sum = arr[0];
    int cnt = n + 1;
    while (end < n && begin < end) // sum = start ~ end-1
    {
        if (sum < s)
        {
            sum += arr[end];
            ++end;
        }
        else
        {
            cnt = min(cnt, end - begin);
            sum -= arr[begin];
            ++begin;
        }
    }
    while (begin < n && sum >= s)
    {
        
        cnt = min(cnt, end - begin);
        sum -= arr[begin];
        ++begin;
    }

    if (n+1 == cnt)
    {
        cnt = 0;
    }

    cout << cnt << endl;

    return 0;
}