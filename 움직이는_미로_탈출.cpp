#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Param
{
	int x;
	int y;
	int time;
};

vector<vector<bool>> board(8, vector<bool>(8, false));
vector<vector<vector<bool>>> visited(8, vector<vector<bool>>(8, vector<bool>(8, false)));
vector<pair<int, int>> dir{ {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 0}, {0, 1}, {1, -1}, {1, 0}, {1, 1} };

bool OOB(int x, int y)
{
	return x < 0 || x >= 8 || y < 0 || y >= 8;
}

void Down()
{
	for (int i = 7; i >= 0; --i)
	{
		for (int j = 0; j < 8; ++j)
		{
			if (i == 0)
				board[i][j] = false;
			else
			{
				board[i][j] = board[i - 1][j];
			}
		}
	}
}

void printBoard()
{
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			cout << board[i][j] << ' ';
		}
		cout << endl;
	}
}

int main()
{
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			char input;
			cin >> input;
			if (input == '#')
				board[i][j] = true;
		}
	}
	

	bool success = false;
	int preTime = 0;
	queue<Param> q;
	q.push({ 7, 0 });
	
	while (!q.empty())
	{
		int x = q.front().x;
		int y = q.front().y;
		int time = q.front().time;
		q.pop();

		if (time != preTime)
		{
			preTime = time;
			Down();
		}

		if (board[x][y])
			continue;

		if (x == 0 && y == 7)
		{
			success = true;
			break;
		}

		for (auto d : dir)
		{
			int nx = x + d.first;
			int ny = y + d.second;

			if (OOB(nx, ny))
				continue;

			if (board[nx][ny])
				continue;

			if (visited[nx][ny][time])
				continue;

			q.push({ nx, ny, time+1 });
			visited[nx][ny][time] = true;
		}

	}

	if (success)
		cout << 1 << endl;
	else
		cout << 0 << endl;

	return 0;
}
