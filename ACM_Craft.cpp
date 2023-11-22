#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Node
{
    int num;
    int endTime;

};

bool operator>(const Node a, const Node b)
{
    return a.endTime > b.endTime;
}

int n, k;
int target;
vector<int> buildTime;
vector<vector<int>> edges;
vector<int> indegree;
vector<int> answer;

void input()
{
    cin >> n >> k;
    buildTime.assign(n+1, 0);
    edges.assign(n+1, vector<int>());
    indegree.assign(n+1, 0);

    for (int i=1; i<n+1; ++i)
    {
        cin >> buildTime[i];
    }

    for (int i=0; i<k; ++i)
    {
        int from, to;
        cin >> from >> to;
        ++indegree[to];
        edges[from].push_back(to);
    }
    
    cin >> target;
}

void topologicalSort()
{
    priority_queue<Node, vector<Node>, greater<Node> > pq;
    for (int i=1; i<n+1; ++i)
    {
        if (indegree[i] == 0)
            pq.push({ i, buildTime[i] });
    }

    while(!pq.empty())
    {
        int cur = pq.top().num;
        int curTime = pq.top().endTime;
        pq.pop();

        if (cur == target)
        {
            answer.push_back(curTime);
            break;
        }

        for (int next : edges[cur])
        {
            --indegree[next];
            if (indegree[next] != 0)
                continue;

            int nextTime = curTime + buildTime[next];
            pq.push({next, nextTime});
        }
    }
}

int main()
{
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    int testcase;
    cin >> testcase;
    while (testcase--)
    {
        input();
        topologicalSort();
    }

    for (auto a : answer)
    {
        cout << a << "\n";
    }
    return 0;
}