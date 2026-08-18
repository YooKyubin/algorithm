#include <iostream>
#include <vector>
#include <array>
#include <queue>

using namespace std;

struct Coord
{
	int x;
	int y;

	Coord operator+(const Coord& other) const
	{
		return { x + other.x, y + other.y };
	}

	bool operator==(const Coord& other) const
	{
		return x == other.x && y == other.y;
	}

	bool OOB(int n)
	{
		return x < 0 || x >= n || y < 0 || y >= n;
	}
};

bool IsEssential(Coord block, const vector<vector<char>>& board, Coord start, Coord end)
{
	static const array<Coord, 4> dirs{ Coord{0, 1}, {1, 0}, {-1, 0}, {0, -1} };

	if (board[block.x][block.y] != '.')
	{
		return false;
	}

	const int n = static_cast<int>(board.size());
	vector<vector<bool>> visited(n, vector<bool>(n, false));
	queue<Coord> q;
	q.push(start);
	visited[start.x][start.y] = true;

	while (!q.empty())
	{
		Coord curr = q.front();
		q.pop();

		for (const Coord& dir : dirs )
		{
			Coord next = curr + dir;

			if (next.OOB(n))
			{
				continue;
			}

			if (board[next.x][next.y] == '#')
			{
				continue;
			}

			if (visited[next.x][next.y])
			{
				continue;
			}

			if (next == block)
			{
				continue;
			}

			if (next == end)
			{
				return false;
			}

			q.push(next);
			visited[next.x][next.y] = true;
		}
	}

	return true;
}

int main()
{
	// freopen("input.txt", "r", stdin);
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);

	int n;
	cin >> n;

	vector<vector<char>> board(n, vector<char>(n));
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			cin >> board[i][j];
		}
	}

	Coord start;
	Coord end;
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			if (board[i][j] == 'S')
			{
				start = { i, j };
			}
			if (board[i][j] == 'E')
			{
				end = { i, j };
			}
		}
	}

	
	vector<vector<char>> answer = board;
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			if (IsEssential({i, j}, board, start, end))
			{
				answer[i][j] = 'o';
			}
		}
	}

	for (auto& line : answer)
	{
		for (char i : line)
		{
			cout << i;
		}
		cout << "\n";
	}

    return 0;
}