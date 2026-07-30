#include <string>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

struct Coord
{
	int x;
	int y;

	Coord operator+(const Coord& other) const
	{
		return { x + other.x, y + other.y };
	}

	bool OOB(int n, int m)
	{
		return x < 0 || x >= n + 1 || y < 0 || y >= m + 1;
	}
};

int Find(Coord curr, int n, int m, vector<vector<int>>& memo, const vector<vector<bool>>& isPuddle)
{
	static const vector<Coord> dirs = { { 0, 1 }, { 1, 0 } };
	constexpr long long DIV = 1'000'000'007;

	if (memo[curr.x][curr.y] != 0)
	{
		return memo[curr.x][curr.y];
	}

	int result = 0;
	for (auto& dir : dirs)
	{
		Coord next = curr + dir;
		if (next.OOB(n, m))
		{
			continue;
		}
		if (isPuddle[next.x][next.y])
		{
			continue;
		}

		result += Find(next, n, m, memo, isPuddle) % DIV;
	}
	return memo[curr.x][curr.y] = result % DIV;
}

int solution(int m, int n, vector<vector<int>> puddles) {
	int answer = 0;

	vector<vector<int>> memo(n + 1, vector<int>(m + 1, 0));
	memo[n][m] = 1;

	vector<vector<bool>> isPuddle(n + 1, vector<bool>(m + 1, false));
	for (vector<int>& puddle : puddles)
	{
		isPuddle[puddle[1]][puddle[0]] = true;
	}

	answer = Find({ 1, 1 }, n, m, memo, isPuddle);

	return answer;
}

int main()
{
	freopen("../../input.txt", "r", stdin);

	int m, n;
	cin >> m >> n;

	int length;
	cin >> length;

	vector<vector<int>> puddles;
	for (int i = 0; i < length; ++i)
	{
		int x, y;
		cin >> x >> y;
		puddles.push_back(vector<int>{ x, y });
	}

	cout << solution(m, n, puddles) << endl;

	return 0;
}


// =====================================================
// Bottom-UP 풀이
// =====================================================


int solution(int m, int n, vector<vector<int>> puddles) {
	int answer = 0;
	constexpr int MOD = 1'000'000'007;

	vector<vector<int>> board(n + 1, vector<int>(m + 1, 0));
	vector<vector<bool>> isPuddle(n + 1, vector<bool>(m + 1, false));
	for (auto& puddle : puddles)
	{
		isPuddle[puddle[1]][puddle[0]] = true;
	}

	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= m; ++j)
		{
			if (i == 1 && j == 1)
			{
				board[i][j] = 1;
				continue;
			}

			if (isPuddle[i][j])
			{
				continue;
			}

			board[i][j] = (board[i - 1][j] + board[i][j - 1]) % MOD;
		}
	}
	answer = board[n][m];

	return answer;
}