#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int main()
{
	bool answer;
	int sum;
	vector<int> abc(3);
	for (int i = 0; i < 3; ++i)
		cin >> abc[i];
	sum = abc[0] + abc[1] + abc[2];
	sort(abc.begin(), abc.end(), less<int>());

	if (sum % 3 != 0)
		answer = false;
	
	else
	{
		vector<vector<bool>> visited;
		visited.resize(1501, vector<bool>(1501, false));
		queue<pair<int, int>> q;
		q.push({ abc[0], abc[1] });
		visited[ abc[0] ][ abc[1] ] = true;

		while (!q.empty())
		{
			vector<int> cur(3);
			cur[0] = q.front().first;
			cur[1] = q.front().second;
			cur[2] = sum - cur[0] - cur[1];
			q.pop();
			sort(cur.begin(), cur.end(), less<int>());

			for (int i = 0; i < 3; ++i)
			{
				for (int j = i+1; j < 3; ++j)
				{
					// cur[i] < cur[j]
					int na = cur[i] + cur[i];
					int nb = cur[j] - cur[i];

					if (visited[na][nb])
						continue;

					visited[na][nb] = true;
					q.push({ na ,nb });
				}
			}
		}
		answer = visited[sum / 3][sum / 3];
	}

	cout << answer << endl;
	return 0;
}