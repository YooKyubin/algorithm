#include <iostream>
#include <vector>
#include <queue>
#include <map>

using namespace std;

constexpr int maxNum = 100000;

int BFS(int src, int dst, const vector<bool> isPrime)
{
    vector<int> step(maxNum, -1);
    queue<int> q;

    q.push(src);
    step[src] = 0;

    auto PushQueue = [&](int curr, int digit)->void
    // void (*PushQueue)(int, int) = [](int curr, int digit)->void
    {
        int start = digit != 1000 ? 0 : 1;
        for (int i = start; i < 10; ++i)
        {
            int nextDigit = digit * 10;
            int next = curr / nextDigit * nextDigit 
                     + i * digit 
                     + curr % digit;

            if (!isPrime[next])
            {
                continue;
            }

            if (step[next] != -1)
            {
                continue;
            }

            step[next] = step[curr] + 1;
            q.push(next);
        }
    };

    while (!q.empty())
    {
        int curr = q.front();
        q.pop();

        PushQueue(curr, 1);
        PushQueue(curr, 10);
        PushQueue(curr, 100);
        PushQueue(curr, 1000);
    }

    return step[dst];
}

int main()
{
    freopen("input.txt", "r", stdin);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    vector<bool> isPrime(maxNum, true);
    isPrime[0] = false;
    isPrime[1] = false;

    for (int i = 2; i * i < maxNum; ++i)
    {
        if (isPrime[i])
        {
            for (int j = i * i; j < maxNum; j += i)
            {
                isPrime[j] = false;
            }
        }
    }

    int testCase = 0;
    cin >> testCase;

    while (testCase--)
    {
        int src, dst;
        cin >> src >> dst;

        cout << BFS(src, dst, isPrime) << "\n";
    }
    return 0;
}