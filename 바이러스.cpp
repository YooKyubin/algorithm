#include <iostream>
#include <vector>

using namespace std;

int n;
int m;
vector<bool> visited;
vector<vector<int>> graph;

void dfs(int v)
{
	for (auto next : graph[v])
	{
		if (visited[next])
			continue;

		visited[next] = true;
		dfs(next);
	}
}

int main()
{
	cin >> n;
	cin >> m;
	visited.assign(n + 1, false);
	graph.assign(n + 1, vector<int>());

	for (int i = 0; i < m; ++i)
	{
		int a, b;
		cin >> a >> b;

		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	visited[1] = true;
	dfs(1);

	int answer = 0;
	for (int i = 1; i <= n; ++i)
	{
		if (visited[i])
			++answer;
	}

	cout << answer - 1 << endl;

	return 0;
}