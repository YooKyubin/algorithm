#include <string>
#include <vector>

#include <iostream>

using namespace std;

void MakeTree(int currNode, const vector<vector<int>>& graph, vector<bool>& isVisited, vector<vector<int>>& outTree)
{
    isVisited[currNode] = true;

    for (int nextNode : graph[currNode])
    {
        if (true == isVisited[nextNode])
        {
            continue;
        }

        MakeTree(nextNode, graph, isVisited, outTree);
        outTree[currNode].push_back(nextNode);
    }
}

void CountSubTreeNodes(const vector<vector<int>>& tree, vector<int>& numsSubTreeNodes, int currNode)
{
    int sumChildNodes = 0;
    for (int child : tree[currNode])
    {   
        CountSubTreeNodes(tree, numsSubTreeNodes, child);
        sumChildNodes += numsSubTreeNodes[child];
    }
    numsSubTreeNodes[currNode] = sumChildNodes + 1;
}

int solution(int n, vector<vector<int>> wires) {
    int answer = -1;

    vector<vector<int>> graph(n + 1);
    for (auto& edge : wires)
    {
        int src = edge[0];
        int dst = edge[1];

        graph[src].push_back(dst);
        graph[dst].push_back(src);
    }

    const int root = 1;
    vector<bool> isVisited(n+1, false);
    vector<vector<int>> tree(n+1);
    MakeTree(root, graph, isVisited, tree);
    
    vector<int> numsSubTreeNodes(n+1);
    CountSubTreeNodes(tree, numsSubTreeNodes, root);


    int minDifference = n+1;
    for (int i=1; i < n+1; ++i)
    {
        int sub = n - numsSubTreeNodes[i];
        minDifference = min(minDifference, abs(sub - numsSubTreeNodes[i]));
    }
    answer = minDifference;

    return answer;
}

int main()
{
    int n= 7;
    vector<vector<int>> wires = 
    {{1,2},{2,7},{3,7},{3,4},{4,5},{6,7}};

    cout << solution(n, wires) << endl;

    return 0;
}