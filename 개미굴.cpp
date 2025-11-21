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

    void find(int depth)
    {
        if (this->isFinish)
            return;

        for (auto& next : this->child)
        {
            for (int i=0; i<depth; ++i)
                cout << "--";
            cout << next.first << "\n";
            next.second.find(depth+1);
        }
    }
};

int n;
Node root;

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
    
    root.find(0);

    return 0;
}

---

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>

using namespace std;

class AntTunnel
{
private:
    class Node
    {
    public:
        void Insert(const vector<string>& names, int depth)
        {
            if (depth == names.size())
            {
                return;
            }

            const string& curr = names[depth];
            auto iter = child.find(curr);
            if (iter == child.end())
            {
                child.emplace(curr, Node());
            }
            child[curr].Insert(names, depth + 1);
        }

        void Print(int depth) const
        {
            for (auto& pair : child)
            {
                for (int i = 0; i < depth; ++i)
                {
                    cout << "--";
                }

                cout << pair.first << "\n";
                pair.second.Print(depth + 1);
            }
        }

    private:
        map<string, Node> child;
    };

public:
    void Insert(const vector<string>& names)
    {
        root.Insert(names, 0);
    }

    void Print() const
    {
        root.Print(0);
    }

private:
    Node root;
};

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;

    AntTunnel antTunnel;

    for (int i = 0; i < n; ++i)
    {
        int m;
        cin >> m;

        vector<string> inputs(m);
        for (int j = 0; j < m; ++j)
        {
            cin >> inputs[j];
        }

        antTunnel.Insert(inputs);
    }

    antTunnel.Print();

    return 0;
}