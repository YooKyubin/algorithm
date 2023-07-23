#include <iostream>
#include <vector>

#define MAX 1e6 + 1
using namespace std;

int n;
vector<int> root(MAX, 0);
vector<int> depth(MAX, 0);
vector<int> partsCount(MAX, 1);

int Find(int x)
{
    if (root[x] == x)
    {
        return x;
    }
    else
    {
        return root[x] = Find(root[x]);
    }
}

void Union(int x, int y)
{
    x = Find(x);
    y = Find(y);

    if (x==y) return;

    if (depth[x] > depth[y])
    {
        root[y] = x;
        partsCount[x] += partsCount[y];
    }
    else if (depth[y] > depth[x])
    {
        root[x] = y;
        partsCount[y] += partsCount[x];
    }
    else{
        root[x] = y;
        depth[y]++;
        partsCount[y] += partsCount[x];
    }
    // if (x > y){
    //     root[y] = x;
    //     partsCount[x] += partsCount[y];
    // }
    // else {
    //     root[x] = y;
    //     partsCount[y] += partsCount[x];
    // }
}

int main ()
{
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(false);
    for (uint32_t i=0; i<root.size(); i++)
    {
        root[i] = i;
    }
    cin >> n;
    while (n--)
    {
        char command;
        cin >> command;
        if (command == 'I')
        {
            int x, y;
            cin >> x >> y;
            Union(x, y);
        }
        else
        {
            int x;
            cin >> x;
            cout << partsCount[Find(x)] << "\n";
        }
    }
    return 0;
}