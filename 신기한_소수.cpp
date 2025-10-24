#include <iostream>
#include <vector>

using namespace std;

bool IsPrime(int num)
{
    if (num < 2)
    {
        return false;
    }
    for (int i = 2; i * i <= num; ++i)
    {
        if (num % i == 0)
        {
            return false;
        }
    }
    return true;
}

void ComputeNumber(vector<int>& primes, int curr, int depth, int n)
{
    if (depth == n)
    {
        primes.push_back(curr);
        return;
    }

    for (int i = 1; i < 10; ++i)
    {
        int next = curr * 10 + i;
        if (IsPrime(next))
        {
            ComputeNumber(primes, next, depth + 1, n);
        }
    } 
}

int main()
{
    freopen("../../input.txt", "r", stdin);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;

    vector<int> answer;
    ComputeNumber(answer, 0, 0, n);

    for (int i : answer)
    {
        cout << i << "\n";
    }
    return 0;
}