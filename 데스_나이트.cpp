#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>

using namespace std;

struct Coord
{
	int x;
	int y;

	bool OOB(int n)
	{
		return x < 0 || x >= n || y < 0 || y >= n;
	}
	Coord operator+(const Coord& other) const
	{
		return { x + other.x, y + other.y };
	}
};

const vector<Coord> dirs = { {-2, -1}, {-2, 1}, {0, -2}, {0, 2}, {2, -1}, {2, 1} };

int main()
{
	freopen("../../input.txt", "r", stdin);
	// freopen("../../output.txt", "w", stdout);

	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);

	int n;
	cin >> n;
	Coord src, dst;
	cin >> src.x >> src.y >> dst.x >> dst.y;

	queue<Coord> q;
	vector<vector<int>> dist(n, vector<int>(n, -1));
	q.push(src);
	dist[src.x][src.y] = 0;

	while (!q.empty())
	{
		Coord curr = q.front();
		q.pop();

		for (auto dir : dirs)
		{
			Coord next = curr + dir;
			if (next.OOB(n))
			{
				continue;
			}

			if (dist[next.x][next.y] != -1)
			{
				continue;
			}

			dist[next.x][next.y] = dist[curr.x][curr.y] + 1;
			q.push(next);
		}
	}

	cout << dist[dst.x][dst.y] << endl;

	return 0;
}
