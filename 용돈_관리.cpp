#include <iostream>
#include <vector>

using namespace std;

int CountDebit(const vector<int>& money, long long k)
{
    int numDebit = 1;
    long long leftMoney = k;
    for (int i : money)
    {
        if (leftMoney >= i)
        {
            leftMoney -= i;
        }
        else
        {
            leftMoney = k - i;
            ++numDebit;
        }
    }

    return numDebit;
}

int main()
{
    freopen("input.txt", "r", stdin);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;

    vector<int> money(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> money[i];
    }

    long long low = 0;
    long long high = 0;
    for (int i : money)
    {
        low = max(low, (long long)i);
        high += i;
    }
    low -= 1;
    high += 1;

    while (low + 1 < high)
    {
        long long mid = (low + high) >> 1;

        // n+1, n+1, [n], n, n-1, n-1
        if (m < CountDebit(money, mid))
        {
            low = mid;
        }
        else
        {
            high = mid;
        }
    }
    cout << high << endl;

    return 0;
}