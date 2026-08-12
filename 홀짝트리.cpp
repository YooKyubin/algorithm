#include <string>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <iostream>

using namespace std;

bool CheckNodeSProperty(const map<int, vector<int>>& graph, int curr)
{
	int degree = static_cast<int>(graph.find(curr)->second.size());

	return (curr % 2 == degree % 2);
}

pair<int, int> CheckGraphProperty(const map<int, vector<int>>& graph, set<int>& visited, int start)
{
	queue<int> q;
	q.push(start);
	visited.insert(start);

	// 홀짝, 역홀짝 노드 수
	pair<int, int> numState = { 0, 0 };

	while (!q.empty())
	{
		int curr = q.front();
		q.pop();
		CheckNodeSProperty(graph, curr) ? ++numState.first : ++numState.second;

		const vector<int>& edges = graph.find(curr)->second;
		for (int next : edges)
		{
			if (visited.find(next) != visited.end())
			{
				continue;
			}

			q.push(next);
			visited.insert(next);
		}
	}

	pair<int, int> property;
	if (numState.first == 1)
	{
		property.first = 1;
	}
	if (numState.second == 1)
	{
		property.second = 1;
	}
	return property;
}

vector<int> solution(vector<int> nodes, vector<vector<int>> edges) {
	vector<int> answer;
	answer.resize(2, 0);

	map<int, vector<int>> graph;
	for (int node : nodes)
	{
		graph.insert({ node, vector<int>() });
	}

	for (const auto& edge : edges)
	{
		int src = edge[0];
		int dst = edge[1];

		graph[src].push_back(dst);
		graph[dst].push_back(src);
	}

	set<int> visited;

	for (int node : nodes)
	{
		if (visited.find(node) == visited.end())
		{
			pair<int, int> property = CheckGraphProperty(graph, visited, node);
			answer[0] += property.first;
			answer[1] += property.second;
		}
	}

	return answer;
}

int main()
{
	freopen("../../input.txt", "r", stdin);

	int n;
	cin >> n;
	vector<int> nodes(n);
	for (int& i : nodes)
	{
		cin >> i;
	}

	int m;
	cin >> m;
	vector<vector<int>> edges(m, vector<int>(2));
	for (int i = 0; i < m; ++i)
	{
		cin >> edges[i][0] >> edges[i][1];
	}

	for (auto i : solution(nodes, edges))
	{
		cout << i << " ";
	}
	cout << endl;

	return 0;
}