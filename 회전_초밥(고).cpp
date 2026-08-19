#include <iostream>
#include <vector>

using namespace std;

int main()
{
	freopen("input.txt", "r", stdin);
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);

	int n, d, k, c;
	cin >> n >> d >> k >> c;

	vector<int> dishes(n);
	for (int i = 0; i < n; ++i)
	{
		cin >> dishes[i];
	}

	int count = 0;
	int answer = 0;
	// map<int, int> take;
	vector<int> take(d + 1, 0);
	++take[c];
	for (int i = 0; i < k; ++i)
	{
		++take[dishes[i]];
	}
	for (int i : take)
	{
		if (i != 0)
		{
			++count;
		}
	}
	answer = count;

	for (int i = 0; i < n; ++i)
	{
		int popDish = dishes[i];
		int pushDish = dishes[(i + k) % n];

		--take[popDish];
		if (take[popDish] == 0)
		{
			--count;
		}

		if (take[pushDish] == 0)
		{
			++count;
		}
		++take[pushDish];
		
		answer = max(answer, count);
	}

	cout << answer << endl;

    return 0;
}