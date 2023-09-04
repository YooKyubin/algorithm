#include <iostream>
#include <vector>

using namespace std;

vector<int> head;
vector<bool> docked;

int find(int x)
{
    if (head[x] == x)
        return x;
    
    return head[x] = find(head[x]);
}

void merge(int x, int y)
{
    x = find(x);
    y = find(y);

    if (x == y)
        return;

    if (x > y)
        head[x] = y;
}

int main()
{
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    int g, p;
    cin >> g;
    cin >> p;

    docked.assign(g+1, false);
    head.resize(g+1);
    for (int i=0; i<g+1; ++i)
        head[i] = i;

    int cnt = 0;
    while(p--)
    {

        int gi;
        cin >> gi;

        int ptr = find(gi);
        while (docked[ptr] && ptr > 0)
        {
            --ptr;
            merge(gi, ptr);
        }

        if (ptr == 0)
            break;
        
        docked[ptr] = true;

        ++cnt;
    }

    cout << cnt << endl;
    return 0;
}