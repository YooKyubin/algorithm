#include <iostream>
#include <vector>

using namespace std;

vector<int> head;

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

    if (x > y) // 문제의 조건때문에 작은놈이 항상 root 
        head[x] = y;
    else
        head[y] = x;
}

int main()
{
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    int g, p;
    cin >> g;
    cin >> p;

    head.resize(g+1);
    for (int i=0; i<g+1; ++i)
        head[i] = i;

    int cnt = 0;
    while(p--)
    {

        int gi;
        cin >> gi;

        int ptr = find(gi);
        if (ptr > 0)
        {
            ++cnt;
            merge(ptr, ptr-1);
        }
        else
            break;

    }

    cout << cnt << endl;
    return 0;
}