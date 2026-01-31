#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>

using namespace std;

int main()
{
	freopen("../../input.txt", "r", stdin);
	// freopen("../../output.txt", "w", stdout);

	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);

	int h, w, x, y;
	cin >> h >> w >> x >> y;

	vector<vector<int>> b(h + x, vector<int>(w + y));
	for (int i = 0; i < h + x; ++i)
	{
		for (int j = 0; j < w + y; ++j)
		{
			cin >> b[i][j];
		}
	}

	vector<vector<int>> a(h, vector<int>(w));
	for (int i = 0; i < x; ++i)
	{
		for (int j = 0; j < w; ++j)
		{
			a[i][j] = b[i][j];
		}
	}
	for (int i = 0; i < x; ++i)
	{
		for (int j = 0; j < w; ++j)
		{
			a[h - 1 - i][j] = b[h + x - 1 - i][j + y];
		}
	}
	for (int i = 0; i < h + x - 2 * x; ++i)
	{
		for (int j = 0; j < y; ++j)
		{
			a[i + x][j] = b[i + x][j];
		}
	}
	for (int i = 0; i < h + x - 2 * x; ++i)
	{
		for (int j = 0; j < y; ++j)
		{
			a[i + x][w - 1 - j] = b[i + x + x][w + y - 1 - j];
		}
	}

	for (int i = x; i < h; ++i)
	{
		for (int j = y; j < w; ++j)
		{
			a[i][j] = b[i][j] - a[i - x][j - y];
		}
	}

	for (auto& line : a)
	{
		for (int i : line)
		{
			cout << i << " ";
		}
		cout << "\n";
	}

	return 0;
}
