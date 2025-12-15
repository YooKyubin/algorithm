#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

void Solve()
{
    static const int INF = 1'000 * 10'000 + 1;
    int n, d, c;
    cin >> n >> d >> c;

    vector<vector<pair<int, int>>> graph(n + 1);
    for (int i = 0; i < d; ++i)
    {
        int a, b, s;
        cin >> a >> b >> s;
        graph[b].push_back({ a, s });
    }

    priority_queue<pair<int, int>> pq;
    vector<int> times(n+1, INF);
    pq.push({ 0, c });
    times[c] = 0;

    while(!pq.empty())
    {
        int curr = pq.top().second;
        int currWeight = -pq.top().first;
        pq.pop();

        for (pair<int, int> nextPair : graph[curr])
        {
            int next = nextPair.first;
            int nextWeight = currWeight + nextPair.second;

            if (times[next] <= nextWeight)
            {
                continue;
            }

            times[next] = nextWeight;
            pq.push({ -nextWeight, next });
        }
    }

    int numHackedComputers = 0;
    int hackedTime = 0; 
    for (int i : times)
    {
        if (i != INF)
        {
            ++numHackedComputers;
            hackedTime = max(hackedTime, i);
        }
    }

    cout << numHackedComputers << " " << hackedTime << "\n";
}

int main()
{
    freopen("../../input.txt", "r", stdin);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int testcase;
    cin >> testcase;

    while(testcase--)
    {
        Solve();
    }

    return 0;
}
