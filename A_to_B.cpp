#include <iostream>
#include <vector>
#include <map>
#include <queue>

using namespace std;

int a, b;
map<int, int> visited;

void bfs()
{
    queue<int> q;

    q.push(b);
    visited[b] = 1;

    while(!q.empty())
    {
        int cur = q.front();
        q.pop();

        // vector<int> next;
        // next.push_back(cur * 2);
        // next.push_back(cur * 10 + 1);

        // for (int n : next)
        if (cur % 2 == 0)
        {
            int n = cur / 2;
            if (n > b)
                continue;

            if (visited[n] != 0)
                continue;

            q.push(n);
            visited[n] = visited[cur] + 1;
        }

        if (cur % 10 == 1)
        {
            int n = cur / 10;
            if (n > b)
                continue;

            if (visited[n] != 0)
                continue;

            q.push(n);
            visited[n] = visited[cur] + 1;
        }
    }
}

int main()
{
    // freopen("./input.txt", "r", stdin);
    cin >> a >> b;

    bfs();

    if (visited[a] == 0)
        cout << -1 << endl;
    else
        cout << visited[a] << endl;
    return 0;
}
