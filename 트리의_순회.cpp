#include <iostream>
#include <vector>

using namespace std;

int n;
vector<int> inOrder;
vector<int> postOrder;
vector<int> inOrderIdx;

void makeTree(int inOrderStart, int postOrderStart, int length)
{
    if (length == 0)
        return; 
    
    int postRootIdx = postOrderStart + length -1;
    int root = postOrder[postRootIdx];

    int inRootIdx = inOrderIdx[root];

    int leftLength = inRootIdx - inOrderStart;
    int rightLegnth = length - leftLength - 1;

    cout << root << " ";

    makeTree(inOrderStart, postOrderStart, leftLength);
    makeTree(inRootIdx + 1, postRootIdx - rightLegnth, rightLegnth);
}

int main()
{
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    cin >> n;

    inOrder.resize(n);
    inOrderIdx.resize(n+1);
    postOrder.resize(n);

    for (int i=0; i<n; ++i)
    {
        cin >> inOrder[i];
        inOrderIdx[inOrder[i]] = i;
    }

    for (int i=0; i<n; ++i)
        cin >> postOrder[i];

    makeTree(0, 0, n);
    cout << endl;
    return 0;
}