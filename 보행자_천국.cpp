#include <vector>
#include <iostream>

using namespace std;

int solution(int m, int n, vector<vector<int>> city_map) {
	constexpr int MOD = 20170805;
	int answer = 0;

	vector<vector<pair<int, int>>> numberOfPath(m, vector<pair<int, int>>(n, { 0, 0 }));

	numberOfPath[1][0].first = 1;
	numberOfPath[0][1].second = 1;

	for (int i = 0; i < m; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			if (i == 0 && j == 0)
			{
				continue;
			}

			switch(city_map[i][j])
			{
			case 0:
				if (i + 1 < m)
				{
					numberOfPath[i + 1][j].first += ((long long)numberOfPath[i][j].first + numberOfPath[i][j].second) % MOD;		
					numberOfPath[i + 1][j].first %= MOD;
				}

				if (j + 1 < n)
				{
					numberOfPath[i][j + 1].second += ((long long)numberOfPath[i][j].first + numberOfPath[i][j].second) % MOD;		
					numberOfPath[i][j + 1].second %= MOD;
				}
				break;

			case 1:
				break;

			case 2:
				if (i + 1 < m)
				{
					numberOfPath[i + 1][j].first += numberOfPath[i][j].first;
					numberOfPath[i + 1][j].first %= MOD;
				}

				if (j + 1 < n)
				{
					numberOfPath[i][j + 1].second += numberOfPath[i][j].second;		
					numberOfPath[i][j + 1].second %= MOD;
				}
				break;
			
			default:
				break;
			}	
		}
	}

	pair<int, int>& target = numberOfPath[m - 1][n - 1];
	answer = (static_cast<long long>(target.first) + target.second) % MOD;
	return answer;
}

int main()
{
	freopen("../../input.txt", "r", stdin);

	int n, m;
	cin >> m >> n;

	vector<vector<int>> city_map(m, vector<int>(n));
	for (int i = 0; i < m; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			cin >> city_map[i][j];
		}
	}

	cout << solution(m, n, city_map) << endl;

	return 0;
}