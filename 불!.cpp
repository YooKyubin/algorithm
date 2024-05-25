#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<pair<int, int>> dir { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

int n, m;
vector<vector<char>> miro;
vector<vector<int>> dist;

bool OOB(int x, int y)
{
	return x < 0 || x >= n || y < 0 || y >= m;
}

void FillFire(pair<int, int> start)
{
	queue<pair<int, int>> q;
	q.push(start);

	dist[start.first][start.second] = 0;

	while (!q.empty())
	{
		int x = q.front().first;
		int y = q.front().second;
		q.pop();

		for (auto d : dir)
		{
			int nx = x + d.first;
			int ny = y + d.second;

			if (OOB(nx, ny))
				continue;

			if (miro[nx][ny] == '#')
				continue;

			if (dist[nx][ny] <= dist[x][y] + 1)
				continue;

			dist[nx][ny] = dist[x][y] + 1;
			q.push({nx, ny});
		}
	}
}

int MoveJihoon(pair<int, int> start)
{
	queue<pair<int, int>> q;
	q.push(start);
	dist[start.first][start.second] = 0;
	
	while (!q.empty())
	{
		int x = q.front().first;
		int y = q.front().second;
		q.pop();

		for (auto d : dir)
		{
			int nx = x + d.first;
			int ny = y + d.second;

			if (OOB(nx, ny))
				return dist[x][y] + 1;

			if (miro[nx][ny] == '#')
				continue;

			if (dist[nx][ny] <= dist[x][y] + 1)
				continue;

			dist[nx][ny] = dist[x][y] + 1;
			q.push({nx, ny});
		}
	}

	return -1;
}

int main()
{
	// freopen("../../input.txt", "r", stdin);
	cin.tie(0);
	ios_base::sync_with_stdio(false);

	cin >> n >> m;
	pair<int, int> Jihoon;
    vector<pair<int, int>> Fires;
	miro.resize(n, vector<char>(m));
	dist.resize(n, vector<int>(m, INT32_MAX));
	for (int i=0; i<n; ++i)
	{
		for (int j=0;j <m; ++j)
		{
			cin >> miro[i][j];

			if (miro[i][j] == 'J')
				Jihoon = {i, j};

            if (miro[i][j] == 'F')
                Fires.push_back({i, j});
        }
	}
    for (auto fire : Fires)
    {
        FillFire(fire);
    }

    int result = MoveJihoon(Jihoon);

	if (result == -1)
		cout << "IMPOSSIBLE" << endl;
	else
		cout << result << endl;


	return 0;
}
