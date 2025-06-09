#include <string>
#include <vector>
#include <map>
#include <algorithm>

#include <iostream>
using namespace std;

struct Node
{
    Node() = default;
    int value = -1;
    int leftIndex = -1;
    int rightIndex = - 1;
};

void PushNode(int rootIndex, int nodeIndex, vector<Node>& tree)
{
    if (tree[nodeIndex].value < tree[rootIndex].value)
    {
        if (tree[rootIndex].leftIndex != -1)
        {
            PushNode(tree[rootIndex].leftIndex, nodeIndex, tree);
        }
        else
        {
            tree[rootIndex].leftIndex = nodeIndex;
        }
    }
    else
    {
        if (tree[rootIndex].rightIndex != -1)
        {
            PushNode(tree[rootIndex].rightIndex, nodeIndex, tree);
        }
        else
        {
            tree[rootIndex].rightIndex = nodeIndex;
        }
    }
}

void CallOrder(vector<int>& postOrder, vector<int>& preOrder, const vector<Node>& tree, int nodeIndex)
{
    if (nodeIndex == -1)
    {
        return;
    }
    
    preOrder.push_back(nodeIndex);
    CallOrder(postOrder, preOrder, tree, tree[nodeIndex].leftIndex);
    CallOrder(postOrder, preOrder, tree, tree[nodeIndex].rightIndex);
    postOrder.push_back(nodeIndex);
}

vector<Node> MakeTree(const vector<vector<int>>& nodeinfo, map<int, int>& indexByX)
{
    vector<Node> tree(nodeinfo.size(), Node{});

    int rootX = nodeinfo.front()[0];
    int rootIndex = indexByX[rootX];
    tree[rootIndex].value = rootX;

    for (size_t i =1; i<nodeinfo.size(); ++i)
    {
        const vector<int>& node = nodeinfo[i];
        int x = node[0];
        int nodeIndex = indexByX[x];

        tree[nodeIndex].value = x;
        PushNode(rootIndex, nodeIndex, tree);
    }

    return tree;
}

vector<vector<int>> solution(vector<vector<int>> nodeinfo) {
    vector<vector<int>> answer;

    map<int, int> indexByX;

    for (size_t i = 0; i < nodeinfo.size(); ++i)
    {
        indexByX[nodeinfo[i][0]] = i;
    }

    sort(nodeinfo.begin(), nodeinfo.end(), [](const vector<int>& src, const vector<int>& dst)->bool
        {
            if (src[1] == dst[1])
            {
                return src[0] < dst[0];
            }

            return src[1] > dst[1];
        });

    vector<Node> tree = MakeTree(nodeinfo, indexByX);

    int rootX = nodeinfo.front()[0];
    int rootIndex = indexByX[rootX];

    vector<int> postOrder;
    vector<int> preOrder;
    CallOrder(postOrder, preOrder, tree, rootIndex);

    answer.push_back(preOrder);
    answer.push_back(postOrder);

    return answer;
}

int main()
{
    vector<vector<int>> nodeinfo=
    {{5,3},{11,5},{13,3},{3,5},{6,1},{1,3},{8,6},{7,2},{2,2}};

    vector<vector<int>> result = solution(nodeinfo);
    // for (int i=0; i<2; ++i)
    // {
    //     for (int j : result[i])
    //     {
    //         cout << j << " ";
    //     }
    //     cout << endl;
    // }

    return 0;
}