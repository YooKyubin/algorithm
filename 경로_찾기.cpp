#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main()
{
    freopen("../../input.txt", "r", stdin);
    // freopen("../../output.txt", "w", stdout);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    
    int n;
    cin >> n;
    vector<vector<int>> graph(n);

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            int isEdge;
            cin >> isEdge;

            if (isEdge == 1)
            {
                graph[i].push_back(j);
            }
        }
    }


    vector<vector<bool>> canAccess(n, vector<bool>(n, false));
    for (int start = 0; start < n; ++start)
    {
        queue<int> q;
        q.push(start); 
        
        while (!q.empty())
        {
            int curr = q.front();
            q.pop();

            for (int next : graph[curr])
            {
                if (canAccess[start][next])
                {
                    continue;
                }

                canAccess[start][next] = true;
                q.push(next);
            }
        }
    }

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            cout << (canAccess[i][j] ? 1 : 0) << " ";
        }
        cout << "\n";
    }

 
    return 0;
}