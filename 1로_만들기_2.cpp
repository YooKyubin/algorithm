#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main()
{
    freopen("input.txt", "r,", stdin);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;

    queue<int> q;
    vector<int> dist(n + 1, 1000001);
    vector<int> footPrint(n + 1, 0);
    q.push(1);
    dist[1] = 0;

    while (!q.empty())
    {
        int curr = q.front();
        q.pop();

        int nexts[3] = { curr + 1, curr * 2, curr * 3 };
        for (int i = 0; i < 3; ++ i)
        {
            int next = nexts[i];
            if (next > n)
            {
                continue;
            }

            if (dist[next] <= dist[curr] + 1)
            {
                continue;
            }

            dist[next] = dist[curr] + 1;
            footPrint[next] = curr;
            q.push(next);
        }
    }

    cout << dist.back() << "\n";
    int foot = n;
    while (foot != 0)
    {
        cout << foot << " ";
        foot = footPrint[foot];
    }
    cout << endl;

    return 0;
}