#include <iostream>
#include <vector>

using namespace std;

int GetLeaves(vector<vector<int>>& graph, int curr)
{
    if (graph[curr].empty())
    {
        return 1;
    }

    int leaves = 0;
    for (int i : graph[curr])
    {
        leaves += GetLeaves(graph, i);
    }
    return leaves;
}

int main()
{
    freopen("../../input.txt", "r", stdin);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;

    vector<int> parents(n);
    for (int& parent: parents)
    {
        cin >> parent;
    }
    int except;
    cin >> except;

    int root = 0;
    vector<vector<int>> graph(n);
    for (int i = 0; i < n; ++i)
    {
        int parent = parents[i];
        if (parent == -1)
        {
            root = i;
        }
        if (i == except)
        {
            continue;
        }

        if (parent != -1)
        {
            graph[parent].push_back(i);
        }
    }
    graph[except].clear();

    if (root == except)
    {
        cout << 0 << endl;
    }
    else
    {
        cout << GetLeaves(graph, root) << endl;
    }

    return 0;
}