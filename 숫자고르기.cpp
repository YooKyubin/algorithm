#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n;
vector<int> edges;
vector<int> head;

vector<int> answer;

void dfs(int cur)
{
    int next = edges[cur];

    if (head[next] == -1)
    {
        head[next] = head[cur];
        dfs(next);
    }
    else if (head[next] == head[cur])
    {
        int start = next;
        int end = cur;

        while (start != end)
        {
            answer.push_back(start);
            start = edges[start];
        }
        answer.push_back(end);
    }
}

int main()
{
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    cin >> n;
    edges.resize(n+1);
    head.assign(n+1, -1);

    for (int i=1; i<n+1; ++i)
    {
        cin >> edges[i];
    }

    for (int i=1; i<n+1; ++i)
    {
        if (head[i] == -1)
        {
            head[i] = i;
            dfs(i);
        }
    }

    sort(answer.begin(), answer.end());
    cout << answer.size() << "\n";
    for (const int a : answer)
    {
        cout << a << "\n";
    }
    return 0;
}