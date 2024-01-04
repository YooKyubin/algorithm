#include <iostream>

constexpr int MOD = 1'000'000'007;
using namespace std;

int64_t factorialMOD(int input)
{
	int64_t ret = 1;
	for (int i = 1; i <= input; ++i)
	{
		ret = (ret * i) % MOD;
	}
	return ret;
}

int64_t Pow(int64_t base, int power)
{
	if (power == 1)
	{
		return base % MOD;
	}
	
	int64_t temp = Pow(base, power / 2) % MOD;

	if (power % 2 == 1)
	{
		return temp * temp % MOD * base % MOD;
	}
	else
	{
		return temp * temp % MOD;
	}
}

int main()
{
	int n, k;
	int64_t answer;
	cin >> n >> k;

	int64_t numer = factorialMOD(n);
	int64_t denom = factorialMOD(k) * factorialMOD(n - k) % MOD;

	answer = numer * Pow(denom, MOD-2) % MOD;

	cout << answer << endl;

	return 0;
}

/*
(k!(n-k)!)^(-1) % 1'000'000'007 을 구하기 위해 
(k!(n-k)!)^(1'000'000'007 - 2) % 1'000'000'007 을 구한다.
페르마의 소정리
*/