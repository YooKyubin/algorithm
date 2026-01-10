#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

int ComputeGCD(int src, int dst)
{
    // resursive
    // if (dst == 0)
    // {
    //     return src;
    // }
    // return GCD(dst, src % dst);

    if (src < dst)
    {
        swap(src, dst);
    }

    while (dst != 0)
    {
        int tmp = src % dst;
        src = dst;
        dst = tmp;
    }

    return src;
}

int main()
{
    freopen("../../input.txt", "r", stdin);
    // freopen("../../output.txt", "w", stdout);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> arr[i];
    }
    sort(arr.begin(), arr.end(), greater<int>());

    vector<int> sub;
    for (int i = 0; i < n-1; ++i)
    {
        sub.push_back(arr[i] - arr[i + 1]);
    }

    int gcd = sub[0];
    for (size_t i = 1; i < sub.size(); ++i)
    {
        gcd = ComputeGCD(gcd, sub[i]);
    }

    set<int> divisors;
    divisors.insert(gcd);
    for (int i = 2; i * i <= gcd; ++i)
    {
        if (gcd % i == 0)
        {
            divisors.insert(i);
            divisors.insert(gcd / i);
        }
    }

    for (int i : divisors)
    {
        cout << i << " ";
    }
    cout << endl;

    return 0;
}