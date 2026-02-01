#include <iostream>
#include <vector>

using namespace std;

const vector<int> dx{ 1, 0, -1, 0 };
const vector<int> dy{ 0, 1, 0, -1 };

bool OOB(int x, int y, int n)
{
	return x < 0 || x >= n || y < 0 || y >= n;
}

int main()
{
	freopen("../../input.txt", "r", stdin);
	// freopen("../../output.txt", "w", stdout);

	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);

	int n;
	cin >> n;
	int query;
	cin >> query;

	int dirID = 0;
	int currX = 0;
	int currY = 0;
	int queryX = -1;
	int queryY = -1;
	vector<vector<int>> arr(n, vector<int>(n, 0));
	for (int i = n * n; i >= 1; --i)
	{
		int nextX = currX + dx[dirID];
		int nextY = currY + dy[dirID];

		if (OOB(nextX, nextY, n) || arr[nextX][nextY] != 0)
		{
			dirID = (dirID + 1) % 4;
			nextX = currX + dx[dirID];
			nextY = currY + dy[dirID];
		}

		arr[currX][currY] = i;
		if (query == i)
		{
			queryX = currX + 1;
			queryY = currY + 1;
		}
		currX = nextX;
		currY = nextY;
	}

	for (auto& line : arr)
	{
		for (int i : line)
		{
			cout << i << " ";
		}
		cout << "\n";
	}

	cout << queryX << " " << queryY << endl;



	return 0;
}
