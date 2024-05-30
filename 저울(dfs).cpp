#include <iostream>
#include <vector>

using namespace std;

int n;
int m;
vector<vector<int>> adj, adjReverse;
vector<int> indegree, indegreeReverse;
vector<int> comparableCnt;

int dfs(int x, const vector<vector<int>> graph, vector<bool>& visited)
{
	int ret = 0;
	for (auto next : graph[x])
	{
		if (visited[next])
			continue;
			
		visited[next] = true;
		ret += dfs(next, graph, visited) + 1;
	}

	return ret;
}

int main()
{
	freopen("input.txt", "r", stdin);
	cin.tie(0);
	ios_base::sync_with_stdio(false);

	cin >> n;
	cin >> m;
	adj.resize(n+1);
	adjReverse.resize(n+1);
	comparableCnt.resize(n+1, n-1);
	for (int i=0; i<m; ++i)
	{
		int a, b;
		cin >> a >> b;
		adj[a].push_back(b);
		adjReverse[b].push_back(a);
	}

	for (int i=1; i<n+1; ++i)
	{
		vector<bool> visited(n+1, false);
		int result = dfs(i, adj, visited);
		comparableCnt[i] -= result;

		visited.assign(n+1, false);
		result = dfs(i, adjReverse, visited);
		comparableCnt[i] -= result;
	}

	for (int i=1; i<n+1; ++i)
	{
		cout << comparableCnt[i] << endl;
	}

	return 0;
}