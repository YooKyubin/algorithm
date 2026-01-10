#include <iostream>
#include <vector>
#include <deque>
#include <queue>
#include <algorithm>

using namespace std;

int main()
{
    freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;

    long long answer = -1;
    int idx = 0;
    queue<long long> q;
    for (int i = 0; i < 10; ++i)
    {
        q.push(i);
        if (i == n)
        {
            answer = i;
        }
        ++idx;
    }

    while (idx <= n && !q.empty())
    {
        long long prev = q.front();
        int last = prev % 10;
        q.pop();

        for (int i = 0; i < last; ++i)
        {
            long long curr = prev * 10 + i;
            q.push(curr);
            if (idx == n)
            {
                answer = curr;
            }
            ++idx;
        }
    }

    cout << answer << endl;
    return 0;
}