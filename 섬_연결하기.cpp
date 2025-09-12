#include <string>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

struct Edge
{
    int to;
    int weight;

    bool operator>(const Edge& other) const
    {
        if (weight == other.weight)
        {
            return to > other.to;
        }
        return weight > other.weight;
    }
};

int solution(int n, vector<vector<int>> costs) {
    int answer = 0;
    
    vector<vector<Edge>> graph(n);
    for (const auto& cost : costs)
    {
        int src = cost[0];
        int dst = cost[1];
        int weight = cost[2];
        
        graph[src].push_back({dst, weight});
        graph[dst].push_back({src, weight});
    }
    
    vector<int> mst;
    mst.push_back(0);
    
    priority_queue<Edge, vector<Edge>, greater<Edge>> edges;
    vector<bool> isVisited(n, false);
    edges.push({0, 0});

    while( !edges.empty() )
    {
        int curr = edges.top().to;
        int currWeight = edges.top().weight;
        edges.pop();

        if (mst.size() == n)
        {
            break;
        }
        if (isVisited[curr])
        {
            continue;
        }
        isVisited[curr] = true;
        answer += currWeight;

        for (const Edge& edge : graph[curr])
        {
            int next = edge.to;
            int nextWeight = edge.weight;

            if (isVisited[next])
            {
                continue;
            }

            edges.push(edge);
        }
    }
    
    return answer;
}

int main()
{
    int n = 4;
    vector<vector<int>> costs 
    = {{0,1,1},{0,2,2},{1,2,5},{1,3,1},{2,3,8}};

    cout << solution(n, costs) << endl;
    return 0;
}