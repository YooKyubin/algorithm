#include <string>
#include <vector>
#include <array>
#include <queue>
#include <algorithm>
#include <iostream>

using namespace std;

struct Coord
{
	int x;
	int y;

	Coord operator+(const Coord& other) const
	{
		return {  x + other.x, y + other.y };
	}

	bool OOB(int n, int m)
	{
		return x < 0 || x >= n || y < 0 || y >= m;
	}
};

int ComputeDays(const vector<string>& maps, vector<vector<bool>>& visited, Coord start)
{
	static constexpr array<Coord, 4> dirs = { Coord{0, 1}, {1, 0}, {-1, 0}, {0, -1} };
	
	int days = 0;
	queue<Coord> q;

	auto PushQ = [&](Coord node) -> void
	{
		q.push(node);
		visited[node.x][node.y] = true;
		days += maps[node.x][node.y] - '0';
	};
	PushQ(start);

	while (!q.empty())
	{
		Coord curr = q.front();
		q.pop();

		for (auto& dir : dirs)
		{
			Coord next = curr + dir;

			if (next.OOB(maps.size(), maps[0].size()))
			{
				continue;
			}

			if (visited[next.x][next.y])
			{
				continue;
			}

			if (maps[next.x][next.y] == 'X')
			{
				continue;
			}

			PushQ(next);
		}
	}

	return days;
}

vector<int> solution(vector<string> maps) {
	vector<int> answer;
	const int n = static_cast<int>(maps.size());
	const int m = static_cast<int>(maps[0].size());

	vector<vector<bool>> visited(n, vector<bool>(m, false));

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			if (visited[i][j])
			{
				continue;
			}	

			if (maps[i][j] == 'X')
			{
				continue;
			}

			answer.push_back(ComputeDays(maps, visited, { i, j }));
		}
	}
	sort(answer.begin(), answer.end(), greater<int>());

	if (answer.empty())
	{
		answer.push_back(-1);
	}

	return answer;
}

int main()
{
	freopen("../../input.txt", "r", stdin);

	int n;
	cin >> n;
	vector<string> maps(n);
	for (int i = 0; i < n; ++i)
	{
		cin >> maps[i];
	}

	for (int i : solution(maps))
	{
		cout << i << " ";
	}
	cout << endl;

	return 0;
}