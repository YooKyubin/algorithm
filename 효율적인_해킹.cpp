#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <algorithm>

using namespace std;

//12:41
int main()
{
    freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;

    // Init Graph
    vector<vector<int>> graph(n+1);
    vector<int> indegree(n+1, 0);
    for (int i = 0; i < m; ++i)
    {
        int src, dst;
        cin >> src >> dst;
        graph[dst].push_back(src);
    }

    vector<pair<int, int>> numHacked(n+1);
    for (int i = 1; i <= n; ++i)
    {
        int cnt = 0;
        queue<int> q;
        vector<bool> visited(n+1, false);
        q.push(i);
        visited[i] = true;

        while(!q.empty())
        {
            int curr = q.front();
            q.pop();

            for (int next : graph[curr])
            {
                if (visited[next])
                {
                    continue;
                }

                ++cnt;
                q.push(next);
                visited[next] = true;
            }
        }

        numHacked[i] = {cnt, i};
    }

    sort(numHacked.begin(), numHacked.end(),
        [](pair<int, int>& src, pair<int, int>& dst)->bool
        {
            if (src.first == dst.first)
            {
                return src.second < dst.second;
            }

            return src.first > dst.first;
        });

    for (auto& p : numHacked)
    {
        if (p.first != numHacked.front().first)
        {
            break;
        }

        cout << p.second << " ";
    }
    cout << endl;

    return 0;
}