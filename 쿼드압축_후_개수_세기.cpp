#include <string>
#include <vector>
#include <iostream>

using namespace std;

struct Pair
{
	int x = 0;
	int y = 0;
};

Pair Find(int x, int y, int size, const vector<vector<int>>& arr)
{
	// cout << "(" << x <<", " << y << ") size: " << size << endl;
	if (size == 0)
	{
		return { 0, 0 };
	}

	int value[2] = { 0, 0 };
	for (int i = x; i < x + size; ++i)
	{
		for (int j = y; j < y + size; ++j)
		{
			++value[arr[i][j]];
		}
	}

	if (value[0] == 0)
	{
		value[1] = 1;
	}
	else if (value[1] == 0)
	{
		value[0] = 1;
	}
	else
	{
		value[0] = 0;
		value[1] = 0;
		int nextSize = size / 2;
		Pair subResults[4];
		subResults[0] = Find(x, y, nextSize, arr);
		subResults[1] = Find(x + nextSize, y, nextSize, arr);
		subResults[2] = Find(x, y + nextSize, nextSize, arr);
		subResults[3] = Find(x + nextSize, y + nextSize, nextSize, arr);

		for (int i = 0; i < 4; ++i)
		{
			value[0] += subResults[i].x;
			value[1] += subResults[i].y;
		}
	}

	return { value[0], value[1] };
}

vector<int> solution(vector<vector<int>> arr) {
	vector<int> answer;

	Pair result = Find(0, 0, arr.size(), arr);

	return { result.x, result.y };
}

int main()
{
	freopen("../../input.txt", "r", stdin);

	int n;
	cin >> n;

	vector<vector<int>> arr(n, vector<int>(n));
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			cin >> arr[i][j];
		}
	}

	auto result = solution(arr);
	cout << result[0] << ", " << result[1] << endl;
	return 0;
}