#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int n, m, t;
vector<vector<int>> board;
vector<int> start;
vector<pair<int, int>> dir{ {0,1}, {1, 0}, {-1, 0}, {0, -1} };

bool OOB(int x)
{
	return x < 0 || x >= n;
}

void searchSame(vector<vector<bool>>& visited)
{
	bool ret = false;

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			if (board[i][j] == 0)
				continue;

			if (i + 1 < n)
			{
				int ni = i + 1;
				int nj = ( j - start[i] + start[ni] + m ) % m;
				if (board[i][j] == board[ni][nj])
				{
					visited[i][j] = true;
					visited[ni][nj] = true;
				}
			}

			int nj = (j + 1) % m;
			if (board[i][j] == board[i][nj])
			{
				visited[i][j] = true;
				visited[i][nj] = true;
			}
		}
	}
}

int main()
{
	cin.tie(0);
	ios_base::sync_with_stdio(false);

	cin >> n >> m >> t;
	board.resize(n, vector<int>(m));
	start.assign(n, 0);

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			cin >> board[i][j];
		}
	}

	while (t--)
	{
		int x, d, k;
		cin >> x >> d >> k;
		int ccw = d == 0 ? -1 : 1;
		for (int i = x-1; i < n; i += x)
		{
			start[i] = (start[i] + ccw * k + m ) % m;
		}

		int sum = 0;
		int cnt = 0;
		bool flag = false;
		vector<vector<bool>> visited(n, vector<bool>(m, false));
		searchSame(visited);

		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < m; ++j)
			{
				if (board[i][j] == 0)
					continue;

				sum += board[i][j];
				++cnt;

				if (visited[i][j])
				{
					board[i][j] = 0;
					flag = true;
				}
			}
		}

		if (!flag) // searchSame fail
		{
			for (int i = 0; i < n; ++i)
			{
				for (int j = 0; j < m; ++j)
				{
					if (board[i][j] == 0)
						continue;

					float average = (float)sum / (float)cnt;
					if (average < board[i][j])
					{
						--board[i][j];
					}
					else if (average > board[i][j])
					{
						++board[i][j];
					}
						
				}
			}
		}
	}


	int answer = 0;
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			if (board[i][j] != 0)
				answer += board[i][j];
		}
	}

	cout << answer << endl;

	return 0;
}


// bfs
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int n, m, t;
vector<vector<int>> board;
vector<int> start;
vector<pair<int, int>> dir{ {0,1}, {1, 0}, {-1, 0}, {0, -1} };

bool OOB(int x)
{
	return x < 0 || x >= n;
}

bool bfs(int x, int y, vector<vector<bool>>& visited)
{
	bool ret = false;
	queue<pair<int, int>> q;
	int target = board[x][y];
	q.push({ x, y });
	// 일부러 시작지점 visited[x][y] = true 안해서 
	// 인접한 같은 수가 있는 경우에만 
	// 출발지점으로 다시 돌아와서 board[x][y] = 0 하도록

	while (!q.empty())
	{
		int curX = q.front().first;
		int curY = q.front().second;
		q.pop();

		for (const auto& d : dir)
		{
			int nx = d.first + curX;
			if (OOB(nx))
				continue;

			int ny = d.second + curY - start[curX] + start[nx];

			if (ny < 0 || ny >= m)
				ny = (ny + m) % m;

			if (visited[nx][ny])
				continue;

			if (board[nx][ny] == target)
			{
				visited[nx][ny] = true;
				q.push({ nx, ny });

				board[nx][ny] = 0;
				ret = true;
			}
		}
	}

	//if (ret)
	//	board[x][y] = 0;

	return ret;
}

int main()
{
	cin.tie(0);
	ios_base::sync_with_stdio(false);

	cin >> n >> m >> t;
	board.resize(n, vector<int>(m));
	start.assign(n, 0);

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			cin >> board[i][j];
		}
	}

	while (t--)
	{
		int x, d, k;
		cin >> x >> d >> k;
		
		int ccw = d == 0 ? -1 : 1;
		for (int i = x-1; i < n; i += x)
		{
			start[i] = (start[i] + ccw * k + m ) % m;
		}

		//for (int i = 0; i < n; ++i)
		//{
		//	for (int j = 0; j < m; ++j)
		//	{
		//		int nj = (start[i] + j + m) % m;
		//		cout << board[i][nj] << "\t";
		//	}
		//	cout << endl;
		//}cout << endl;

		int sum = 0;
		int cnt = 0;
		bool flag = false;
		vector<vector<bool>> visited(n, vector<bool>(m, false));
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < m; ++j)
			{
				sum += board[i][j];

				if (visited[i][j])
					continue;

				if (board[i][j] == 0)
					continue;

				++cnt;
				if (bfs(i, j, visited))
				{
					flag = true;
				}
			}
		}

		if (!flag) // bfs fail
		{
			for (int i = 0; i < n; ++i)
			{
				for (int j = 0; j < m; ++j)
				{
					if (board[i][j] == 0)
						continue;

					float average = (float)sum / (float)cnt;
					if (average < board[i][j])
					{
						--board[i][j];
					}
					else if (average > board[i][j])
					{
						++board[i][j];
					}
						
				}
			}
		}

		//for (int i = 0; i < n; ++i)
		//{
		//	for (int j = 0; j < m; ++j)
		//	{
		//		int nj = (start[i] + j + m) % m;
		//		cout << board[i][nj] << "\t";
		//	}
		//	cout << endl;
		//}
	}


	int answer = 0;
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			if (board[i][j] != 0)
				answer += board[i][j];
		}
	}

	cout << answer << endl;

	return 0;
}