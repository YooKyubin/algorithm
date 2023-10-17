#include <iostream>
#include <vector>

// 간선의 가중치가 음수인 경우 반복하는 동안 한없이 작아질 수 있다.
#define MAXNUM INT64_MAX 

using namespace std;

struct Edge
{
    int from;
    int dest;
    int weight;
};


int main()
{
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    int n, m;
    vector<Edge> edges;
    vector<int64_t> dist;

    cin >> n >> m;
    edges.reserve(m);
    dist.assign(n+1, MAXNUM);

    for (int i=0; i<m; ++i)
    {
        int dest, from, weight;
        cin >> from >> dest >> weight;
        edges.push_back({from, dest, weight});
    }
    
    dist[1] = 0;
    for (int i=1; i<n+1; ++i)
    {
        for (Edge e : edges)
        {
            int from = e.from;
            int dest = e.dest;
            int weight = e.weight;

            if (dist[from] == MAXNUM)
                continue;
            
            if (dist[dest] > dist[from] + weight)
                dist[dest] = dist[from] + weight;
        }
    }

    vector<int64_t> answer = dist;

    // 음의 사이클 검사
    for (Edge e : edges)
    {
        int from = e.from;
        int dest = e.dest;
        int weight = e.weight;

        if (dist[from] == MAXNUM)
            continue;
        
        if (dist[dest] > dist[from] + weight)
            dist[dest] = dist[from] + weight;
    }

    // 출력을 위한 코드
    bool isCycle = false;
    for  (int i=1; i<n; ++i)
    {
        if (answer[i] != dist[i])
        {
            isCycle = true;
            break;
        }
    }

    if (isCycle)
        cout << -1 << "\n";
    else
    {
        for (int i=2; i<n+1; ++i)
        {
            int d = answer[i];
            if(d == MAXNUM)
                cout << -1 << "\n";

            else
                cout << d << "\n";
        }
    }

    return 0;
}