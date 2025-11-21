#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>

using namespace std;

class Trie
{
private:
    class Node
    {
    public:
        Node()
        : isString(false)
        {
        }

        ~Node()
        {
            for (auto& pair : child)
            {
                delete pair.second;
            }
        }

    public:
        void Insert(const string& str, int depth)
        {
            if (depth == str.size())
            {
                isString = true;
                return;
            }

            char ch = str[depth];

            auto iter = child.find(ch);
            if (iter == child.end())
            {
                child.emplace(ch, new Node);
            }

            child[ch]->Insert(str, depth + 1);
        }

        bool IsPrefix(const string& str, int depth)
        {
            if (depth == str.size())
            {
                return true;
            }

            char ch = str[depth];

            auto iter = child.find(ch);
            if (iter == child.end())
            {
                return false;
            }

            return child[ch]->IsPrefix(str, depth + 1);
        }

    private:
        bool isString;
        map<char, Node*> child;
    };

public:
    void Insert(const string& str)
    {
        root.Insert(str, 0);
    }

    bool IsPrefix(const string& str)
    {
        return root.IsPrefix(str, 0);
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

    int n, m ;
    cin >> n >> m;

    Trie trie;
    for (int i = 0; i < n; ++i)
    {
        string input;
        cin >> input;
        trie.Insert(input);
    }

    int answer = 0;
    for (int i = 0; i < m; ++i)
    {
        string input;
        cin >> input;
        if (trie.IsPrefix(input))
        {
            ++answer;
        }
    }
    cout << answer << endl;

    return 0;
}