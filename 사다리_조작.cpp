#include <iostream>
#include <vector>

using namespace std;

int n, m, h;
vector<vector<bool>> ladder;
int answer = 4;
int ccc = 0;

inline bool checkCondition()
{
	bool ret = true;
	for (int i = 1; i <= n; ++i)
	{
		int y = i;

		for (int j = 1; j <= h; ++j)
		{
			if (y - 1 >= 1 && ladder[j][y - 1])
			{
				--y;
			}
			else if (ladder[j][y])
			{
				++y;
			}
		}

		if (y != i)
		{
			return false;
		}
	}

	return ret;
}

int min(int a, int b) { return a < b ? a : b; }

bool dfs(int y, int cnt)
{
			cout << ++ccc << endl;
	if (checkCondition())
	{
		answer = min(cnt, answer);
		return true;
	}

	if (cnt == 3 || answer <= cnt)
		return false;

	bool ret = false;
	for (int j = y; j < n; ++j)
	{
		for (int i = 1; i <= h; ++i)
		{
			if (ladder[i][j])
				continue;

			if (j - 1 >= 1 && ladder[i][j - 1])
				continue;

			if (j + 1 <= n && ladder[i][j + 1])
				continue;

			ladder[i][j] = true;
			if (dfs(j, cnt + 1))
			{
				return true;
			}
			ladder[i][j] = false;
		}
	}

	return false;
}

int main()
{
	cin.tie(0);
	ios_base::sync_with_stdio(false);

	cin >> n >> m >> h;
	ladder.resize(h + 1, vector<bool>(n + 1, false));
	for (int i = 0; i < m; ++i)
	{
		int x, y;
		cin >> x >> y;
		ladder[x][y] = true;
	}

	dfs(1, 0);


	if (answer == 4)
		cout << -1 << endl;
	else
		cout << answer << endl;

	return 0;
}