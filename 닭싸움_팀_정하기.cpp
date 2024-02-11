#include <iostream>
#include <vector>
#include <set>

using namespace std;

int n, m;
vector<int> friendGroup;
vector<vector<int>> enemys;
set<int> groupSet;

int Find(int x)
{
    if (x == friendGroup[x])
        return x;

    return friendGroup[x] = Find(friendGroup[x]);
}

void Union(int x, int y)
{
    x = Find(x);
    y = Find(y);

    if (x == y)
        return;

    friendGroup[x] = y;
}

int main()
{
    cin >> n;
    cin >> m;
    friendGroup.resize(n+1);
    enemys.resize(n+1);

    for (int i=1; i<n+1; ++i)
    {
        friendGroup[i] = i;
    }

    for (int i=0; i<m; ++i)
    {
        char d;
        int a, b;
        cin >> d >> a >> b;

        if (d == 'F')
        {
            Union(a, b);
        }
        else
        {
            enemys[a].push_back(b);
            enemys[b].push_back(a);
        }
    }

    for (const auto& enemy : enemys)
    {
        for (int i=1; i<enemy.size(); ++i)
        {
            Union(enemy[0], enemy[i]);
        }
    }


    for (int i=1; i<n+1; ++i)
    {
        groupSet.insert(Find(i));
    }

    cout << groupSet.size() << endl;

    return 0;
}
