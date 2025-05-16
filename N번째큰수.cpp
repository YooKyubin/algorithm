#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Node
{
    Node(int _Value, int _Index)
        : Value(_Value)
        , Index(_Index)
    {}

    int Value;
    int Index;
};

bool operator<(const Node& Dst, const Node& Src)
{
    return  Dst.Value < Src.Value;
}
bool operator>(const Node& Dst, const Node& Src)
{
    return  Dst.Value > Src.Value;
}

int main()
{
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    int k;
    cin >>  k; 
    vector<vector<int>> Nums(k, vector<int>(k));

    for (int i=0; i<k; ++i)
    {
        for (int j=0; j<k; ++j)
        {
            cin >> Nums[j][i];
        }
    }

    priority_queue<Node, vector<Node>, less<Node>> Heap;
    for (int i=0; i<k; ++i)
    {
        Heap.push(Node(Nums[i].back(), i));
        Nums[i].pop_back();
    }

    int Value = 0;
    for (int i=0; i<k; ++i)
    {
        int Index = Heap.top().Index;
        Value = Heap.top().Value;
        Heap.pop();

        if (!Nums[Index].empty())
        {
            Heap.push( Node(Nums[Index].back(), Index) );
            Nums[Index].pop_back();
        }
    }

    cout << Value << endl;

    return 0;
}