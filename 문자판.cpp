#include <iostream>
#include <vector>
#include <string>

using namespace std;

int n, m, k;
vector<vector<char>> board;
vector<vector<vector<int>>> memo;
string target;
int answer = 0;

vector<pair<int, int>> dir{ {0, 1}, {0, -1}, {-1, 0}, {1, 0} };

bool OOB(int x, int y)
{
	return x < 0 || x >= n || y < 0 || y >= m;
}

int dfs(int x, int y, int depth)
{
	if (depth >= target.length())
		return 1;

	if (memo[x][y][depth] != -1)
		return memo[x][y][depth];

	memo[x][y][depth] = 0;
	for (auto d : dir)
	{
		for (int it = 1; it <= k; ++it)
		{
			int nx = x + d.first * it;
			int ny = y + d.second * it;

			if (OOB(nx, ny))
				continue;

			if (board[nx][ny] == target[depth])
			{
				memo[x][y][depth] += dfs(nx, ny, depth + 1);
			}
		}
	}

	return memo[x][y][depth];
}

int main()
{
	cin.tie(0);
	ios_base::sync_with_stdio(false);

	cin >> n >> m >> k;
	board.resize(n, vector<char>(m));
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			cin >> board[i][j];
		}
	}
	cin >> target;
	memo.resize(n, vector<vector<int>>(m, vector<int>(80, -1)));

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			if (board[i][j] == target[0])
				answer += dfs(i, j, 1);
		}
	}

	cout << answer << "\n";

	return 0;
}