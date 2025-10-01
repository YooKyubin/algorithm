#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int countFriend(int id, vector<vector<int>>& graph)
{
    queue<pair<int, int>> q;
    vector<bool> visited(graph.size(), false);
    q.push({id, 0});
    visited[id] = true;

    int numFriend = 0;
    while (!q.empty())
    {
        int curr = q.front().first;
        int depth = q.front().second;
        q.pop();

        if (depth >= 2)
        {
            continue;
        }

        for (int next : graph[curr])
        {
            if (visited[next])
            {
                continue;;
            }

            visited[next] = true;
            q.push({ next, depth + 1 });
            ++numFriend;
        }
    }

    return numFriend;
}

int main()
{
    freopen("input.txt", "r", stdin);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;

    vector<vector<char>> matrix(n, vector<char>(n));
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            cin >> matrix[i][j];
        }
    }
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (matrix[i][j] == 'Y')
            {
                matrix[j][i] = 'Y';
            }
        }
    }

    vector<vector<int>> graph(n);
    for (int i =0 ; i<n; ++i)
    {
        for (int j = i+1; j < n; ++j)
        {
            if (matrix[i][j] == 'Y')
            {
                graph[i].push_back(j);
                graph[j].push_back(i);
            }
        }
    }

    int answer = 0;
    for (int i = 0; i < n; ++i)
    {
        answer = max(answer, countFriend(i, graph));
    }
    cout << answer << endl;

    return 0;
}

/*
    0-1, 1-2, 2-3, 3-4
*/