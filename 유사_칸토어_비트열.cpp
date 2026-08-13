#include <string>
#include <vector>
#include <iostream>

using namespace std;

bool IsZero(long long i)
{
	while (0 < i)
	{
		if (i % 5 == 2)
		{
			return true;
		}
		i /= 5;
	}

	return false;
}

int solution(int n, long long l, long long r) {
	int answer = 0;

	// 0-base
	--l;
	--r;

	for (long long i = l; i <= r; ++i)
	{
		answer += IsZero(i) ? 0 : 1;
	}

	return answer;
}

int main()
{
	freopen("../../input.txt", "r", stdin);

	int n;
	long long l, r;
	cin >> n >> l >> r;

	cout << solution(n, l, r) << endl;

	return 0;
}