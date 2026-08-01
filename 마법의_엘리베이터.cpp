#include <string>
#include <vector>
#include <iostream>
#include "debug.hpp"

using namespace std;

int solution(int storey) {
	if (storey < 10)
	{
		return min(storey, 10 - storey + 1);
	}

	int digit = storey % 10;
	int remaining = storey / 10;

	int upCost = 10 - digit + solution(remaining + 1);
	int downCost = digit + solution(remaining);

	return min(upCost, downCost);
}

int main()
{
	freopen("input.txt", "r", stdin);
	int storey;
	cin >> storey;

	cout << solution(storey) << endl;

	return 0;
}