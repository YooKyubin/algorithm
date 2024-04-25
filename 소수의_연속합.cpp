#include <iostream>
#include <vector>

using namespace std;

int main()
{
    freopen("../../input.txt", "r", stdin);
    int n;
    cin >> n;

    vector<bool> isPrime(n+1, true);
    vector<int> primeNum;
    primeNum.reserve(n+1);
    isPrime[0] = false;
    isPrime[1] = false;

    for (int i=2; i*i <= n; ++i)
    {
        if (isPrime[i])
        {
            for (int j=i+i; j <= n; j+=i)
            {
                isPrime[j] = false;
            }
        }
    }

    for (int i=0; i<=n; ++i)
    {
        if (isPrime[i])
            primeNum.push_back(i);
    }

    int answer =0;
    int val = 0;
    int i=0;
    int j=0;
    while (j < primeNum.size() || i < primeNum.size())
    {
        if (val < n)
        {
            if (j == primeNum.size())
                break;
            val += primeNum[j];
            ++j;
        }
        else if (val >= n)
        {
            if (val == n)
                ++answer;

            val -= primeNum[i];
            ++i;
        }
        // cout << val << endl;
    }

    cout << answer << endl;
    return 0;
}