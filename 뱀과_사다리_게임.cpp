#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main()
{
	freopen("input.txt", "r", stdin);
	// freopen("output.txt", "w", stdout);

	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);

	int n, m;
	cin >> n >> m;

	constexpr int MAX = 100;
	vector<int> move(MAX + 1);
	for (int i = 1; i <= MAX; ++i)
	{
		move[i] = i;
	}

	for (int i = 0; i < n + m; ++i)
	{
		int src, dst;
		cin >> src >> dst;
		move[src] = dst;
	}

	queue<int> q;
	vector<int> dist(MAX + 1, MAX);
	q.push(1);
	dist[1] = 0;

	while (!q.empty())
	{
		int curr = q.front();
		q.pop();

		for (int i = 1; i <= 6; ++i)
		{
			int next = curr + i;
			if (next > MAX)
			{
				continue;
			}

			int movedNext = move[next];
			if (dist[movedNext] <= dist[curr] + 1)
			{
				continue;
			}

			dist[movedNext] = dist[curr] + 1;
			q.push(movedNext);
		}
	}

	cout << dist[MAX] << endl;

	return 0;
}