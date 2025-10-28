#include <string>
#include <vector>
#include <iostream>

using namespace std;

void SetEdge(int src, int dst, int edgeID, vector<pair<int, int>>& currEdges)
{
    currEdges[src].first = dst;
    currEdges[dst].first = src;

    currEdges[src].second = edgeID;
    currEdges[dst].second = edgeID;
}

void RemoveEdge(int src, vector<pair<int, int>>& currEdges)
{
    int dst = currEdges[src].first;

    currEdges[src].first = 0;
    currEdges[dst].first = 0;

    currEdges[src].second = -1;
    currEdges[dst].second = -1;
}

vector<vector<int>> solution(
        int n, int m, 
        vector<int> a, 
        vector<int> b, 
        int k, 
        int m1, int m2, 
        vector<int> e1, 
        vector<int> e2) 
{
    vector<vector<int>> answer;

    for (int& i : e1)
    {
        --i;
    }
    for (int& i : e2)
    {
        --i;
    }

    // first: dst, second: edge ID
    vector<pair<int, int>> currEdges(n + 1, {0, -1});
    for (int i : e1)
    {
        int src = a[i];
        int dst = b[i];
        SetEdge(src, dst, i, currEdges);
    }
    // 차집합 M0 - Mt
    vector<bool> M0ButMt(m, false);
    for (int i : e1)
    {
        M0ButMt[i] = true;
    }
    for (int i : e2)
    {
        M0ButMt[i] = false;
    }

    for (int i : e2)
    {   
        int src = a[i];
        int dst = b[i];

        if (currEdges[src].second == i)
        {
            continue;
        }

        if (currEdges[src].second != -1)
        {
            int edgeID = currEdges[src].second;

            M0ButMt[edgeID] = false;
            answer.push_back({ 0, edgeID + 1 });
            RemoveEdge(src, currEdges);
        }
        if (currEdges[dst].second != -1)
        {
            int edgeID = currEdges[dst].second;

            M0ButMt[edgeID] = false;
            answer.push_back({ 0, edgeID + 1 });
            RemoveEdge(dst, currEdges);
        }
        SetEdge(src, dst, i, currEdges);
        answer.push_back({ 1, i+1 });
    }

    // e1에 속했지만 e2에는 속하지 않으면서, 
    // e2의 어떤 간선과도 충돌하지 않는 간선들 제거.
    for (int i = 0; i < m; ++i)
    {
        if (M0ButMt[i])
        {
            answer.push_back({ 0, i+1 });
        }
    }

    return answer;
}

int main()
{
    int n=	5;
    int m=	6;
    vector<int> a	= {1, 1, 2, 2, 3, 4};
    vector<int> b	= {2, 3, 3, 4, 5, 5};
    int k=	2;
    int m1=	2;
    int m2=	2;
    vector<int> e1	{3, 6};
    // vector<int> e2	{2, 4};
    vector<int> e2	{3, 6};

    for (auto& line : solution(n, m, a, b, k, m1, m2, e1, e2))
    {
        for (int i : line)
        {
            cout << i << " ";
        }
        cout << endl;
    }

    return 0;
}