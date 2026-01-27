#include <iostream>
#include <vector>

using namespace std;

constexpr int MAX_PAPER = 25;
constexpr int INF = MAX_PAPER + 1;

bool CheckValidSize(int x, int y, int size, const vector<vector<bool>>& board)
{
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			int nx = x + i;
			int ny = y + j;

			if (nx >= 10 || ny >= 10)
			{
				return false;
			}

			if (!board[nx][ny])
			{
				return false;
			}
		}
	}
	return true;
}

void Attach(int x, int y, int size, vector<vector<bool>>& board)
{
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			int nx = x + i;
			int ny = y + j;

			board[nx][ny] = false;
		}
	}
}

void Detach(int x, int y, int size, vector<vector<bool>>& board)
{
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			int nx = x + i;
			int ny = y + j;

			board[nx][ny] = true;
		}
	}
}

bool CheckOverUsePaper(const vector<int>& paperCount)
{
	for (int i = 1; i <= 5; ++i)
	{
		if (paperCount[i] < 0)
		{
			return true;
		}
	}
	return false;
}

bool CheckAllAttached(const vector<vector<bool>>& board)
{
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			if (board[i][j])
			{
				return false;
			}
		}
	}
	return true;
}

int ComputeUsedPaper(const vector<int>& paperCount)
{
	int paperLeft = 0;
	for (int i = 1; i <= 5; ++i)
	{
		paperLeft += paperCount[i];
	}
	return MAX_PAPER - paperLeft;
}

int Find(int curr, vector<vector<bool>>& board, vector<int>& paperCount)
{
	if (CheckOverUsePaper(paperCount))
	{
		return INF;
	}

	if (curr == 10 * 10)
	{
		// if (false == CheckAllAttached(board))
		// {
		// 	return INF;
		// }

		return ComputeUsedPaper(paperCount);
	}

	int x = curr / 10;
	int y = curr % 10;
	if (!board[x][y])
	{
		return Find(curr + 1, board, paperCount);
	}

	int minUsed = INF;
	for (int size = 1; size <= 5; ++size)
	{
		if (!CheckValidSize(x, y, size, board))
		{
			break;
		}

		if (paperCount[size] == 0)
		{
			continue;
		}

		--paperCount[size];
		Attach(x, y, size, board);
		minUsed = min(minUsed, Find(curr + 1, board, paperCount));
		Detach(x, y, size, board);
		++paperCount[size];
	}

	return minUsed;
}

int main()
{
	freopen("input.txt", "r", stdin);
	// freopen("output.txt", "w", stdout);

	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);

	vector<vector<bool>> board(10, vector<bool>(10));
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			int temp;
			cin >> temp;
			board[i][j] = temp == 1;
		}
	}

	vector<int> paperCount(6, 5);
	int answer = Find(0, board, paperCount);

	if (answer == INF)
	{
		cout << -1 << endl;
	}
	else
	{
		cout << answer << endl;
	}

	return 0;
}