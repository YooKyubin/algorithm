#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int r, c;
vector<vector<char>> grid;
vector<vector<bool>> visited;
pair<int, int> start;
pair<int, int> dest;
pair<int, int> target;
vector<vector<pair<int, int>>> pipe
{
	{ {0,1}, {1,0}, {-1,0}, {0,-1} },	// +
	{ {0, 1}, {1, 0}  },					// 1
	{ {0, 1}, {-1, 0} },				// 2
	{ {-1, 0}, {0, -1} },				// 3
	{ {1, 0}, {0, -1} },				// 4
	{ {1, 0}, {-1, 0} },				// |
	{ {0, 1}, {0, -1} }					// -
};
vector<char> pipeMap { '+', '1', '2', '3', '4', '|', '-' };
vector<pair<int, int>> aroundTarget;


bool OOB(int x, int y)
{
	return x < 0 || x >= r || y < 0 || y >= c;
}

void dfs(int x, int y)
{
	int dir = -1;
	switch (grid[x][y])
	{
		case '+': 
			dir = 0;
			break;

		case '1':
			dir = 1;
			break;

		case '2':  
			dir = 2;
			break;

		case '3':  
			dir = 3;
			break;

		case '4':  
			dir = 4;
			break;

		case '|':  
			dir = 5;
			break;

		case '-':
			dir = 6;
			break;

		default:
			return;
			break;
	}

	for (pair<int,int> d : pipe[dir])
	{
		int nx = x + d.first;
		int ny = y + d.second;

		if (OOB(nx, ny))
			continue;

		if (visited[nx][ny])
			continue;

		if (grid[nx][ny] == '.')
		{
			target = { nx, ny };
			aroundTarget.push_back({ x - nx, y - ny });
			return;
		}

		visited[nx][ny] = true;
		dfs(nx, ny);
	}
}

int main()
{
	cin >> r >> c;
	grid.resize(r, vector<char>(c));
	visited.resize(r, vector<bool>(c, false));
	for (int i = 0; i < r; ++i)
	{
		for (int j = 0; j < c; ++j)
		{
			cin >> grid[i][j];
			if (grid[i][j] == 'M')
				start = { i, j };
			else if (grid[i][j] == 'Z')
				dest = { i, j };
		}
	}

	for (int i = 0; i < r; ++i)
	{
		for (int j = 0; j < c; ++j)
		{
			if (grid[i][j] == '.')
				continue;

			if (visited[i][j])
				continue;

			visited[i][j] = true;
			dfs(i, j);
		}
	}


	char answerPipe = '.';
	sort(aroundTarget.begin(), aroundTarget.end());
	if (aroundTarget.size() == 4)
		answerPipe = '+';
	else
	{
		for (int i = 1; i <= 6; ++i)
		{
			vector<pair<int, int>> curPipes = pipe[i];
			sort(curPipes.begin(), curPipes.end());

			if (curPipes == aroundTarget)
				answerPipe = pipeMap[i];
		}
	}
	cout << target.first + 1 << " " << target.second + 1 << " " << answerPipe << endl;
	return 0;
}