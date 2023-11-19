 #include <iostream>
#include <vector>

#define INF 10000001

using namespace std;

int n, m;
vector<vector<int>> dist;

int min(int a, int b) { return a < b ? a : b; }

int main()
{
	cin >> n;
	cin >> m;
	dist.resize(n+1, vector<int>(n+1, INF));

	for (int i = 0; i < m; ++i)
	{
		int a, b, c;
		cin >> a >> b >> c;
		dist[a][b] = min(dist[a][b], c);
	}
	for (int i = 1; i < n + 1; ++i)
	{
		dist[i][i] = 0;
	}

	for (int i = 1; i < n+1; ++i) // 꼭 거쳐야 하는 노드
	{
		for (int from = 1; from < n+1; ++from)
		{
			for (int to = 1; to < n + 1; ++to)
			{
				dist[from][to] = min(dist[from][to], dist[from][i] + dist[i][to]);
			}
		}
	}

	for (int i = 1; i < n + 1; ++i)
	{
		for (int j = 1; j < n + 1; ++j)
		{
			cout << (dist[i][j] == INF ? 0 :dist[i][j]) << " ";
		}
		cout << "\n";
	}

	return 0;
}