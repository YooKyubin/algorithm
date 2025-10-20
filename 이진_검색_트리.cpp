#include <iostream>
#include <vector>

using namespace std;

void PushTree(
            vector<pair<int, int>>& childIDs,
            vector<int>& preOrder, 
            int parentsID,
            int pushedID)
{
    int parentsValue = preOrder[parentsID];
    int pushedValue = preOrder[pushedID];
    int newParentID = -1;
    if (parentsValue > pushedValue)
    {
        newParentID = childIDs[parentsID].first;
    }
    else
    {
        newParentID = childIDs[parentsID].second;
    }

    if (newParentID == -1)
    {
        if (parentsValue > pushedValue)
        {
            childIDs[parentsID].first = pushedID;
        }
        else
        {
            childIDs[parentsID].second = pushedID;
        }
    }
    else
    {
        PushTree(childIDs, preOrder, newParentID, pushedID);
    }
}

void PostOrder(
        const vector<pair<int, int>>& childs, 
        const vector<int>& preOrder,
        int currID)
{
    int leftChild = childs[currID].first;
    int rightChild = childs[currID].second;
    if (leftChild != -1)
    {
        PostOrder(childs, preOrder, leftChild);   
    }
    if (rightChild != -1)
    {
        PostOrder(childs, preOrder, rightChild);
    }
    cout << preOrder[currID] << "\n";
}

int main()
{
    freopen("input.txt", "r", stdin);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);   

    vector<int> preOrder;
    while (true)
    {
        int num;
        cin >> num;
        if (cin.eof())
        {
            break;
        }
        preOrder.push_back(num);
    }

    vector<pair<int, int>> childs(preOrder.size(), {-1, -1});
    for (int i = 1; i < preOrder.size(); ++i)
    {
        PushTree(childs, preOrder, 0, i);
    }

    PostOrder(childs, preOrder, 0);


    return 0;
}


// ---


#include <iostream>
#include <vector>

using namespace std;

struct Node
{
    Node(int _value)
    : value(_value)
    {}

    Node(const Node& rhs) noexcept = default;
    Node(Node&& rhs) noexcept = default;

    int value;
    Node* left{ nullptr };
    Node* right{ nullptr };
};

void PushNode(vector<Node>& nodes, Node* curr, int value)
{
    Node*& next = (curr->value > value) ? curr->left : curr->right;
    if (next == nullptr)
    {
        nodes.push_back(Node(value));
        next = &nodes.back();
    }
    else
    {
        PushNode(nodes, next, value);
    }
}

void PostOrder(Node* curr)
{
    if (curr == nullptr)
    {
        return;
    }

    PostOrder(curr->left);
    PostOrder(curr->right);
    cout << curr->value << "\n";
}

int main()
{
    freopen("input.txt", "r", stdin);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);   

    vector<int> preOrder;
    while (true)
    {
        int num;
        cin >> num;
        if (cin.eof())
        {
            break;
        }
        preOrder.push_back(num);
    }
    int numNodes = (int)preOrder.size();

    vector<Node> nodes;
    nodes.reserve(numNodes);
    nodes.push_back( Node(preOrder.front()) );
    Node* root = &nodes.front();

    for (int i = 1; i < numNodes; ++i)
    {
        PushNode(nodes, root, preOrder[i]);
    }

    PostOrder(root);


    return 0;   
}