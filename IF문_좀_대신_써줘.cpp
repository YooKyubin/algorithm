#include <iostream>
#include <vector>

using namespace std;

string GetTitle(int power, const vector<pair<string, int>>& titles)
{
	long long low = -1;
	long long high = titles.size();

	while (low + 1 < high)
	{
		long long mid = (low + high) >> 1;

		if (titles[mid].second < power)
		{
			low = mid;
		}
		else
		{
			high = mid;
		}
	}
	return titles[high].first;
}

int main()
{
	freopen("input.txt", "r", stdin);
	// freopen("output.txt", "w", stdout);

	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);

	int n, m;
	cin >> n >> m;

	vector<pair<string, int>> titles(n);
	for (int i = 0; i < n; ++i)
	{
		cin >> titles[i].first >> titles[i].second;
	}

	for (int i = 0; i < m; ++i)
	{
		int power;
		cin >> power;
		cout << GetTitle(power, titles) << "\n";
	}

	return 0;
}