#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<bool> BFS(int start, const vector<vector<int>>& graph)
{
	vector<bool> visit(graph.size(), false);
	queue<int> q;
	q.push(start);
	visit[start] = true;

	while (!q.empty())
	{
		int curr = q.front();
		q.pop();

		for (int next : graph[curr])
		{
			if (visit[next])
			{
				continue;
			}

			visit[next] = true;
			q.push(next);
		}
	}

	return visit;
}

int main()
{
	freopen("../../input.txt", "r", stdin);
	
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);
	
	int k, n, m;
	cin >> k >> n >> m;

	vector<int> startPoint(k);
	for (int i = 0; i < k; ++i)
	{
		cin >> startPoint[i];
	}

	vector<vector<int>> graph(n + 1);
	for (int i = 0 ; i < m; ++i)
	{
		int src, dst;
		cin >> src >> dst;

		graph[src].push_back(dst);
	}

	vector<int> visitCount(n + 1, 0);
	for (int start : startPoint)
	{
		vector<bool> visit = BFS(start, graph);

		for (int i = 1; i <= n; ++i)
		{
			if (visit[i])
			{
				++visitCount[i];
			}
		}
	}

	int answer = 0;
	for (int i = 1; i <= n; ++i)
	{
		if (visitCount[i] == k)
		{
			++answer;
		}
	}
	cout << answer << endl;

	return 0;
}