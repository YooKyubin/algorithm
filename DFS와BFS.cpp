#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

void DFS(const vector<vector<int>>& Edges, vector<bool>& Visited, const int CurNode)
{
    cout << CurNode << " ";
    Visited[CurNode] = true;

    for (int Next : Edges[CurNode])
    {
        if (Visited[Next])
            continue;

        DFS(Edges, Visited, Next);
    }
}

void PrintDFS(const vector<vector<int>>& Edges, const int StartNode, const int NumNodes)
{
    vector<bool> Visited(NumNodes + 1, false);

    DFS(Edges, Visited, StartNode);

    cout << "\n";
}

void PrintBFS(const vector<vector<int>>& Edges, const int StartNode, const int NumNodes)
{
    vector<bool> Visited(NumNodes + 1, false);

    queue<int> Queue;
    Queue.push(StartNode);
    Visited[StartNode] = true;

    while (!Queue.empty())
    {
        int Curr = Queue.front();
        Queue.pop();
        cout << Curr << " ";

        for (int Next : Edges[Curr])
        {
            if (Visited[Next])
                continue;

            Queue.push(Next);
            Visited[Next] = true;
        }
    }
    cout << "\n";
}


int main() 
{
    cin.tie(0);
	ios_base::sync_with_stdio(false);

    int NumNodes, NumEdges, StartNode;
    cin >> NumNodes >> NumEdges >> StartNode;

    vector<int> Nodes(NumNodes + 1);
    vector<vector<int>> Edges(NumNodes + 1);

    for (int i=0; i < NumEdges; ++i)
    {
        int Dst, Src;
        cin >> Dst >> Src;

        Edges[Dst].push_back(Src);
        Edges[Src].push_back(Dst);
    }

    for (auto& Edge : Edges)
    {
        sort(Edge.begin(), Edge.end());
    }

    PrintDFS(Edges, StartNode, NumNodes);
    PrintBFS(Edges, StartNode, NumNodes);

    return 0;
}