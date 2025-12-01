#include <vector>
#include <iostream>
#include <queue>

using namespace std;

int main()
{
    freopen("input.txt", "r", stdin);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;

    vector<vector<int>> friends(n + 1);
    int m;
    cin >> m;
    for (int i = 0; i < m; ++i)
    {
        int src, dst;
        cin >> src >> dst;

        friends[src].push_back(dst);
        friends[dst].push_back(src);
    }

    queue<int> q;
    vector<int> visited(n+1, -1);

    q.push(1);
    visited[1] = 0;

    while (!q.empty())
    {
        int curr = q.front();
        q.pop();

        if (visited[curr] == 2)
        {
            break;
        }

        for (int next : friends[curr])
        {
            if (visited[next] != -1)
            {
                continue;
            }

            visited[next] = visited[curr] + 1;
            q.push(next);
        }
    }

    int numFriends = 0;
    for (int i : visited)
    {
        if (i != -1)
        {
            ++numFriends;
        }
    }
    // 본인 제외(1번 제외)
    cout << numFriends - 1 << endl;

    return 0;
}