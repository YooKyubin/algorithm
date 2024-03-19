#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int n, m;
vector<vector<int>> graph;
vector<int> indegree;
vector<int> answer;

void topologySort()
{
    queue<int> q;
    for (int i=1; i<n+1; ++i)
    {
        if (indegree[i] == 0)
        {
            q.push(i);
        }
    }

    while (!q.empty())
    {
        int cur = q.front();
        q.pop();
        answer.push_back(cur);

        for (auto next : graph[cur])
        {
            --indegree[next];
            if(indegree[next] == 0)
            {
                q.push(next);
            }
        }
    }
}

int main()
{
    // freopen("../../input.txt", "r", stdin);
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    cin >> n >> m;
    graph.resize(n+1);
    indegree.assign(n+1, 0);

    for (int i=0; i<m; ++i)
    {
        int num;
        cin >> num;
        vector<int> seq(num);
        for (int j=0; j<num; ++j)
        {
            cin >> seq[j];
        }

        for (int j=1; j<num; ++j)
        {
            graph[seq[j-1]].push_back(seq[j]);
            ++indegree[seq[j]];
        }
    }

    topologySort();

    if (answer.size() == n)
    {
        for (int i : answer)
        {
            cout << i << "\n" ;
        }
    }
    else
    {
        cout << 0 << endl;
    }

    return 0;
}