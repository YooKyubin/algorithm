#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

template<typename T>
void Print(const vector<vector<T>>& matrix)
{
	for (const vector<T>& line : matrix)
	{
		for (const T& i : line)
		{
			cout << i << " ";
		}
		cout << "\n";
	}
}

int solution(vector<vector<int>> triangle)
{
	int answer = 0;
	const int height = static_cast<int>(triangle.size());

	vector<vector<int>> pathSum(height);
	for (int i = 0; i < height; ++i)
	{
		pathSum[i].resize(i + 1, 0);
	}

	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j <= i; ++j)
		{
			pathSum[i][j] += triangle[i][j];

			if (i == height - 1)
			{
				continue;
			}

			pathSum[i + 1][j]    = max(pathSum[i + 1][j],      pathSum[i][j]);
			pathSum[i + 1][j + 1] = max(pathSum[i + 1][j + 1], pathSum[i][j]);
		}
	}

	answer = *max_element(pathSum.back().begin(), pathSum.back().end());

	return answer;
}

int main()
{
	freopen("input.txt", "r", stdin);
	int n;
	cin >> n;

	vector<vector<int>> triangle(n);
	for (int i = 0; i < n; ++i)
	{
		triangle[i].resize(i + 1);
		for (int j = 0; j <= i; ++j)
		{
			cin >> triangle[i][j];
		}
	}

	cout << solution(triangle) << endl;

	return 0;
}