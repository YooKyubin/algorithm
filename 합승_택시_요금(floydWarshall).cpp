#include <string>
#include <vector>
#include <algorithm>

#include <iostream>

#define _INF (200 * 100'000)
#define INF _INF

using namespace std;

vector<vector<int>> FloydWarshall(const vector<vector<int>>& graph, int n)
{
    vector<vector<int>> distanceTable;
    distanceTable.resize(n + 1);
    for(int i=0; i < n+1; ++i)
    {
        distanceTable[i].resize(n+1);
        std::copy(graph[i].begin(), graph[i].end(), distanceTable[i].begin());
    }

    for (int layover = 1; layover < n+1; ++layover)
    {
        for (int from = 1; from < n+1; ++from)
        {
            for (int to = 1; to < n+1; ++to)
            {
                distanceTable[from][to] = 
                    min(distanceTable[from][to], distanceTable[from][layover] + distanceTable[layover][to]);
            }
        }
    }

    return distanceTable;
}

int solution(int n, int s, int a, int b, vector<vector<int>> fares) {
    int answer = 0;
    vector<vector<int>> graph;
    graph.resize(n+1);
    for(auto& edges : graph)
    {
        edges.resize(n+1, INF);
    }

    for (auto& edge : fares)
    {
        int src = edge[0];
        int dst = edge[1];
        int cost = edge[2];

        graph[src][dst] = cost;
        graph[dst][src] = cost;
    }
    for (int i=0; i<n+1; ++i)
    {
        graph[i][i] = 0;
    }

    vector<vector<int>> distanceTable = FloydWarshall(graph, n);

    answer = INF;
    for (int i=1; i < n+1; ++i)
    {
        answer = min(answer, distanceTable[s][i] + distanceTable[i][a] + distanceTable[i][b]);
    }

    return answer;
}

int main()
{
    int n = 6;
    int s = 4;
    int a = 6;
    int b = 2;
    vector<vector<int>> fares = 
    {
        {4, 1, 10},
        {3, 5, 24}, 
        {5, 6, 2}, 
        {3, 1, 41}, 
        {5, 1, 24}, 
        {4, 6, 50}, 
        {2, 4, 66}, 
        {2, 3, 22}, 
        {1, 6, 25}
    };


    cout << solution(n, s, a, b, fares) << endl;

    return 0;
}