#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

void Inorder(vector<int>& tree, int curr, vector<int>& inorderNodes)
{
    if (curr >= (int)tree.size())
    {
        return;
    }

    int leftChild = curr * 2;
    Inorder(tree, leftChild, inorderNodes);

    tree[curr] = inorderNodes.back();
    inorderNodes.pop_back();
    
    int rightChild = curr * 2 + 1;
    Inorder(tree, rightChild, inorderNodes);
}

int main()
{
    freopen("../../input.txt", "r", stdin);

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    
    const int numNodes = (1 << n) - 1;
    vector<int> inorderNodes(numNodes);
    for (int i = 0; i < numNodes; ++i)
    {
        cin >> inorderNodes[i];
    }
    reverse(inorderNodes.begin(), inorderNodes.end());

    vector<int> tree(numNodes + 1);

    Inorder(tree, 1, inorderNodes);


    int lineBreak = 1;
    for (int i = 1; i <= numNodes; ++i)
    {
        cout << tree[i] << " ";

        // 1, 3, 7
        if (i == (1 << lineBreak) - 1)
        {
            cout << "\n";
            ++lineBreak;
        }
    }

    return 0;
}