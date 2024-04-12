/*
참고 
https://www.acmicpc.net/board/view/50494
*/

#include <iostream>
#include <vector>

using namespace std;

constexpr int INF = 500 * 10'000 + 1;

int min(int a, int b) { return a < b ? a : b; }

struct Edge
{
    int from;
    int dest;
    int weight;
};

bool CheckCycle(int start, int n, vector<Edge>& edges)
{
    vector<int> dist(n+1, INF);
    dist[start] = 0;
    for (int cnt=0; cnt<n-1; ++cnt)
    {
        for (auto edge : edges)
        {
            int from = edge.from;
            int dest = edge.dest;
            int weight = edge.weight;

            // if (dist[from] == INF)
            //     continue;

            if (dist[dest] > dist[from] + weight)
            {
                dist[dest] = dist[from] + weight;
            }
        }
    }

    vector<int> compare = dist;
    for (auto edge : edges)
    {
        int from = edge.from;
        int dest = edge.dest;
        int weight = edge.weight;

        // if (dist[from] == INF)
        //     continue;

        if (dist[dest] > dist[from] + weight)
        {
            dist[dest] = dist[from] + weight;
        }
    }

    for (int i=1; i<n+1; ++i)
    {
        if (compare[i] != dist[i])
        {
            return true;
        }
    }

    return false;
}

void Solve()
{
    int n, m, w;
    cin >> n >> m >> w;
    
    vector<Edge> edges;
    edges.reserve(m*2 + w);

    for (int i=0; i<m; ++i)
    {
        int s, e, t;
        cin >> s >> e >> t;
        edges.push_back({s, e, t});
        edges.push_back({e, s, t});
    }

    for (int i=0; i<w; ++i)
    {
        int s, e, t;
        cin >> s >> e >> t;
        edges.push_back({s, e, -t});
    }

    bool flag = false;
    flag = CheckCycle(1, n, edges);

    if (flag)
        cout << "YES" << endl;
    else
        cout << "NO" << endl;
}

int main()
{
    freopen("input.txt", "r", stdin);
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    int  testCase;
    cin >> testCase;
    while (testCase--)
    {
        Solve();
    }
    return 0;
}