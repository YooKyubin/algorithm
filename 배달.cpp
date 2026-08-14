#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Edge
{
	int to;
	int weight;

	bool operator>(const Edge& other) const
	{
		return weight > other.weight;
	}
};

int solution(int N, vector<vector<int> > road, int K) {
	int answer = 0;
	constexpr int INF = 10'000 * 2'000;

	vector<vector<Edge>> graph(N + 1);
	for (const auto& edge : road)
	{
		int src = edge[0];
		int dst = edge[1];
		int weight = edge[2];

		graph[src].push_back({ dst, weight });
		graph[dst].push_back({ src, weight });
	}

	vector<int> dist(N + 1, INF);
	priority_queue<Edge, vector<Edge>, greater<Edge>> pq;
	pq.push({ 1, 0 });
	dist[1] = 0;

	while (!pq.empty())
	{
		Edge curr = pq.top();
		pq.pop();

		for (Edge next : graph[curr.to])
		{
			if (dist[next.to] <= dist[curr.to] + next.weight)
			{
				continue;
			}

			dist[next.to] = dist[curr.to] + next.weight;
			pq.push(next);
		}
	}

	for (int i : dist)
	{
		if (i <= K)
		{
			++answer;
		}
	}
	return answer;
}

int main()
{
	freopen("../../input.txt", "r", stdin);

	int n, k;
	cin >> n >> k;

	int m;
	cin >> m;

	vector<vector<int>> road(m);
	for (int i = 0; i < m; ++i)
	{
		int src, dst, weight;
		cin >> src >> dst >> weight;
		road[i] = vector<int>{ src, dst, weight };
	}

	cout << solution(n, road, k) << endl;

	return 0;
}