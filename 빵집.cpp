#include <iostream>
#include <vector>

using namespace std;

int n, m;
vector<vector<char>> board;
vector<pair<int, int>> dir { {-1, 1}, {0, 1}, {1, 1} };

bool OOB(int x, int y)
{
	return x < 0 || x >= n || y < 0 || y >= m;
}

bool dfs(int x, int y, vector<vector<bool>>& visited)
{
	if (y == m-1)
		return true;

	bool ret = false;
	for (pair<int, int> d : dir)
	{
		int nx = x + d.first;
		int ny = y + d.second;

		if (OOB(nx, ny))
			continue;

		if (visited[nx][ny])
			continue;

		if (board[nx][ny] == 'x')
			continue;

		visited[nx][ny] = true;
		if (dfs(nx, ny, visited))
		{	
			return true;
		}

		// visited[nx][ny] = false;

	}	

	return false;
}

int main()
{
	// freopen("../../input.txt", "r", stdin);
	cin.tie(0);
	ios_base::sync_with_stdio(false);

	cin >> n >> m;
	board.resize(n, vector<char>(m));
	for (int i=0; i<n; ++i)
	{
		for (int j=0; j<m; ++j)
		{
			cin >> board[i][j];
		}
	}

	vector<vector<bool>> visited(n, vector<bool>(m, false));
	int answer = 0;
	for (int i=0; i<n; ++i)
	{
		if (dfs(i, 0, visited))
		{
			visited[i][0] = true;
			++answer;
		}
	}

	cout << answer << endl;

	return 0;
}
