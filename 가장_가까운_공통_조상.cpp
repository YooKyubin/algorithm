#include <iostream>
#include <vector>

using namespace std;

struct Node
{
    int depth;
    int parent;
    vector<int> childs;
};

int testcase;
int n;
vector<Node> tree;
vector<bool> isRoot;

void dfs(int cur, int depth)
{
    tree[cur].depth = depth;
    for (int next : tree[cur].childs)
    {
        dfs(next, depth+1);
    }
}

int findLCA(int a, int b)
{
    if (a == b)
    {
        return a;
    }

    if (tree[a].depth < tree[b].depth)
    {
        b = tree[b].parent;
    }
    else if (tree[a].depth > tree[b].depth)
    {
        a = tree[a].parent;
    }
    else
    {
        a = tree[a].parent;
        b = tree[b].parent;
    }
    return findLCA(a, b);
}

int main()
{
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    cin >> testcase;
    while (testcase--)
    {
        cin >> n;
        tree.resize(n+1);
        isRoot.resize(n+1, true);
        for(int i=0; i<n-1; ++i)
        {
            int parent, child;
            cin >> parent >> child;
            tree[parent].childs.push_back(child);
            tree[child].parent = parent;
            isRoot[child] = false;
        }

        for (int i=1; i<n+1; ++i)
        {
            if (isRoot[i])
            {
                dfs(i, 0);
            }
        }
        
        int a, b;
        cin >> a >> b;
        cout << findLCA(a, b) << "\n";

        tree.clear();
        isRoot.clear();
    }
    return 0;
}

/*
#include <iostream>
#include <vector>

using namespace std;

struct Node
{
    int depth;
    int parent;
    vector<int> childs;
};

int testcase;
int n;
vector<Node*> tree;
vector<bool> isRoot;

void dfs(int cur, int depth)
{
    tree[cur]->depth = depth;
    for (int next : tree[cur]->childs)
    {
        dfs(next, depth+1);
    }
}

int findLCA(int a, int b)
{
    if (a == b)
    {
        return a;
    }

    if (tree[a]->depth < tree[b]->depth)
    {
        b = tree[b]->parent;
    }
    else if (tree[a]->depth > tree[b]->depth)
    {
        a = tree[a]->parent;
    }
    else
    {
        a = tree[a]->parent;
        b = tree[b]->parent;
    }
    return findLCA(a, b);
}

int main()
{
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    cin >> testcase;
    while (testcase--)
    {
        cin >> n;
        tree.reserve(n+1);
        for(int i=0; i<n+1; ++i)
        {
            tree.push_back(new Node());
        }
        isRoot.resize(n+1, true);
        for(int i=0; i<n-1; ++i)
        {
            int parent, child;
            cin >> parent >> child;
            tree[parent]->childs.push_back(child);
            tree[child]->parent = parent;
            isRoot[child] = false;
        }

        for (int i=1; i<n+1; ++i)
        {
            if (isRoot[i])
            {
                dfs(i, 0);
            }
        }
        
        int a, b;
        cin >> a >> b;
        cout << findLCA(a, b) << "\n";
        

        for (auto node : tree)
        {
            delete node;
        }
        tree.clear();
        isRoot.clear();
    }
    return 0;
}
*/