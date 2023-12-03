#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

struct Node
{
    bool isFinish = false;
    map<string, Node> child;

    void insert(int depth, const vector<string>& arr)
    {
        if (arr.size() == depth)
        {
            this->isFinish = true;
            return;
        }

        if (this->child.find(arr[depth]) == this->child.end())
        {
            this->child[arr[depth]] = Node();
        }

        this->child[arr[depth]].insert(depth + 1, arr);
    }
};

int n;
Node root;

void dfs(Node& cur, int depth)
{
    if (cur.isFinish)
        return;

    for (auto& next : cur.child)
    {
        for (int i=0; i<depth; ++i)
            cout << "--";
        cout << next.first << "\n";
        dfs(next.second, depth + 1);
    }
}

int main()
{
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    
    cin >> n;
    for (int i=0; i<n; ++i)
    {
        int m;
        cin >> m;
        vector<string> inputs;
        for (int j=0; j<m; ++j)
        {
            string input;
            cin >> input;
            inputs.push_back(input);
        }

        root.insert(0, inputs);
    }

    dfs(root, 0);

    return 0;
}