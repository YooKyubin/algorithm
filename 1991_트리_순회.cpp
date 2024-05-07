#include <iostream>
#include <vector>

using namespace std;

int n;
vector<pair<char, char>> tree;

void inOrder(char root)
{
    if (root == '.')
        return;

    inOrder(tree[root].first);
    cout << (char)(root + 'A');
    inOrder(tree[root].second);
}
void preOrder(char root)
{
    if (root == '.')
        return;

    cout << (char)(root + 'A');
    preOrder(tree[root].first);
    preOrder(tree[root].second);
}
void postOrder(char root)
{
    if (root == '.')
        return;

    postOrder(tree[root].first);
    postOrder(tree[root].second);
    cout << (char)(root + 'A');
}
int main()
{
    // freopen("../../input.txt", "r", stdin);
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    cin >> n;
    tree.resize(n);
    for (int i=0; i<n; ++i)
    {
        char root, left, right;
        cin >> root >> left >> right;

        root -= 'A';

        tree[root].first = left == '.' ? left : left-'A';
        tree[root].second = right == '.' ? right : right-'A';
    }

    preOrder(0);
    cout << endl;
    inOrder(0);
    cout << endl;
    postOrder(0);
    return 0;
}