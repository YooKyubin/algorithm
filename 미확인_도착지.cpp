#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

#define node second
#define weight first

using namespace std;

int n, m, t;
int s, g, h;
vector<vector<pair<int, int>>> edges;
vector<int> destination;

vector<int> dijkstra(int start)
{
    vector<int> dist(n+1, INT32_MAX);

    priority_queue<pair<int, int>> pq;
    pq.push({0, start});
    dist[start] = 0;

    while(!pq.empty())
    {
        auto cur = pq.top();
        pq.pop();
        
        if (dist[cur.node] < -cur.weight)
            continue;
            
        for (auto e : edges[cur.node])
        {    
            int nextNode = e.node;
            int nextWeight = e.weight + dist[cur.node];    

            if (dist[nextNode] <= nextWeight)
                continue;

            dist[nextNode] = nextWeight;
            pq.push({-nextWeight, nextNode});
        }
    }

    return dist;
}

int main() 
{
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    int testCase;
    cin >> testCase;
    while (testCase--)
    {
        cin >> n >> m >> t;
        cin >> s >> g >> h;
        edges.assign(n+1, vector<pair<int, int>>());
        for (int i=0; i<m; ++i)
        {
            int a, b, dist;
            cin >> a >> b >> dist;
            edges[a].emplace_back(dist, b);
            edges[b].push_back({dist, a});
        }
        for (int i=0; i<t; ++i)
        {
            int d;
            cin >> d;
            destination.push_back(d);
        }
        
        vector<int> init = dijkstra(s);
        vector<int> distG = dijkstra(g);
        vector<int> distH = dijkstra(h);
        
        vector<int> answer;
        int offset = init[g] > init[h] ? init[g] : init[h];
        vector<int> compare = init[g] > init[h] ? distG : distH;
        for (auto d : destination)
        {
            if (init[d] == compare[d] + offset)
                answer.push_back(d);
        }
        
        sort(answer.begin(), answer.end());
        for (auto a : answer)
            cout << a << " ";
        cout << endl;

        destination.clear();
        edges.clear();
    }

    return 0;
}