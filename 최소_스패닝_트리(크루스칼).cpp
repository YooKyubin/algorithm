#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge
{
    int from;
    int to;
    int weight;
};

bool operator<(const Edge& a, const Edge& b)
{
    return a.weight < b.weight;
}

int v, e;
vector<Edge> edges;
vector<int> parent;

int Find(int x)
{
    if (parent[x] == x)
        return x;
    else 
        return parent[x] = Find(parent[x]);
        
}

void Union(int a, int b)
{
    a = Find(a);
    b = Find(b);

    if (a == b)
        return;

    parent[a] = b;
}

int main()
{
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    cin >> v >> e;
    edges.reserve(e);
    parent.resize(v+1);
    for (int i=0; i<e; ++i)
    {
        int a, b, weight;
        cin >> a >> b >> weight;
        if (a > b)
            swap(a, b);

        edges.push_back({a, b, weight});
    }


    for (int i=1; i<v+1; ++i)
    {
        parent[i] = i;
    }
    
    sort(edges.begin(), edges.end(), less<Edge>());
    
    int edgeCnt = 0;
    int totalCost = 0;

    for (Edge e : edges)
    {
        int ptrTo = Find(e.to);
        int ptrFrom = Find(e.from);
        if (ptrTo == ptrFrom)
            continue;

        Union(ptrTo, ptrFrom);
        ++edgeCnt;
        totalCost += e.weight;

        if (edgeCnt == v)
            break;
    }

    cout << totalCost << endl;
    return 0;
}