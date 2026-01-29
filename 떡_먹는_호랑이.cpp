#include <iostream>
#include <vector>

using namespace std;

pair<int, int> GetCoef(int n)
{
	vector<int> fibo(n + 1);
	fibo[0] = 0;
	fibo[1] = 1;
	for (int i = 2; i < n; ++i)
	{
		fibo[i] = fibo[i - 1] + fibo[i - 2];
	}

	return { fibo[n - 2], fibo[n - 1] };
}

int main()
{
	freopen("input.txt", "r", stdin);
	// freopen("output.txt", "w", stdout);

	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);

	int d, k;
	cin >> d >> k;

	pair<int, int> coef = GetCoef(d);
	cout << coef.first << ", " << coef.second << endl;

	pair<int, int> answer;
	for (int i = 1; i < k; ++i)
	{
		if ((k - coef.first * i) % coef.second == 0)
		{
			answer.first = i;
			answer.second = (k - coef.first * i) / coef.second;
			break;
		}
	}
	cout << answer.first << endl;
	cout << answer.second << endl;

	return 0;
}