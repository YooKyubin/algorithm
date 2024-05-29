#include <iostream>
#include <vector>
#include <map>
#include <queue>

using namespace std;

vector<pair<int, int>> dir { {0, 1}, {1, 0}, {-1, 0}, {0, -1} };

int n, m;
vector<vector<bool>> isLight;
map<int, vector<pair<int, int>>> switches;

bool OOB(int x, int y)
{
	return x < 0 || x >= n || y < 0 || y >= n;
}

bool CheckAccessible(const pair<int, int>& pos, const vector<vector<bool>>& visited)
{
	int x = pos.first;
	int y = pos.second;
	for (auto d : dir)
	{
		int nx = x + d.first;
		int ny = y + d.second;

		if (OOB(nx, ny))
			continue;

		if (visited[nx][ny])
			return true;
	}

	return false;
}

void BFS()
{
	queue<pair<int, int>> q;
	vector<vector<bool>> visited(n, vector<bool>(n, false));

	q.push({0, 0});
	visited[0][0] = true;

	while(!q.empty())
	{
		int x = q.front().first;
		int y = q.front().second;
		q.pop();

		if (switches.find(x * n + y) != switches.end())
		{
			for (auto illuminated : switches[x * n + y])
			{
				if (visited[illuminated.first][illuminated.second])
					continue;

				isLight[illuminated.first][illuminated.second] = true;
				if (CheckAccessible(illuminated, visited))
				{
					visited[illuminated.first][illuminated.second] = true;
					q.push(illuminated);
				}
			}
		}

		for (auto d : dir)
		{
			int nx = x + d.first;
			int ny = y + d.second;

			if (OOB(nx, ny))
				continue;

			if (visited[nx][ny])
				continue;

			if (!isLight[nx][ny])
				continue;

			visited[nx][ny] = true;
			q.push({nx, ny});
		}
	}

}

int main()
{
	freopen("input.txt", "r", stdin);
	cin.tie(0);
	ios_base::sync_with_stdio(false);

	cin >> n >> m;
	isLight.resize(n, vector<bool>(n, false));
	isLight[0][0] = true;
	for (int i=0; i<m; ++i)
	{
		int x, y, a, b;
		cin >> x >> y >> a >> b;
		--x; --y; --a; --b;

		switches[x * n + y].push_back({a, b});
	}

	BFS();

	int answer = 0;
	for (int i=0; i<n; ++i)
	{
		for (int j=0; j<n; ++j)
		{
			if (isLight[i][j])
			{
				++answer;
			}
		}
	}

	cout << answer << endl;

	return 0;
}