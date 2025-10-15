#include <iostream>
#include <vector>
#include <map>

using namespace std;

long long N, P, Q;
map<long long, long long> memo;

long long Compute(long long i)
{
    if (i == 0)
    {
        return 1;
    }
    else if (memo.find(i) != memo.end())
    {
        return memo[i];
    }

    long long src = i / P;
    long long dst = i / Q;

    long long result = Compute(src) + Compute(dst);
    memo[i] = result;
    return result;
}

int main()
{
    freopen("input.txt", "r", stdin);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    cin >> N >> P >> Q;

    memo[0] = 1;

    cout << Compute(N) << endl;

    return 0;
}