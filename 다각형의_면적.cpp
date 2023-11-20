#include <iostream>
#include <vector>
#include <cmath>

using namespace std;


double integral(pair<int, int> cur, pair<int, int> pre)
{
	double ret = double(cur.first - pre.first) * (double(cur.second + pre.second)) / 2;
	return ret;
}

int main()
{
	int n;
	vector<pair<int, int>> points;
	cin >> n;
	points.resize(n+1);
	for (int i = 0; i < n; ++i)
	{
		int x, y;
		cin >> x >> y;
		points[i].first = x;
		points[i].second = y;
	}
	points[n] = points[0];

	double sum = 0;
	for (int i = 1; i < n+1; ++i)
	{
		sum += integral(points[i], points[i - 1]);
	}

	cout << fixed;
	cout.precision(1);
	cout << abs(sum) << endl;
	return 0;
}