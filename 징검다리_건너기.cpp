#include <string>
#include <vector>
#include <deque>
#include <iostream>
#include "debug.hpp"

using namespace std;

int solution(vector<int> stones, int k) {
	int answer = 200'000'000 + 1;

	deque<int> dq;
	for (int i = 0; i < k; ++i)
	{
		while (!dq.empty() && stones[dq.back()] <= stones[i])
		{
			dq.pop_back();
		}
		dq.push_back(i);
	}
	
	for (int i = k; i < stones.size(); ++i)
	{
		answer = min(answer, stones[dq.front()]);

		if (dq.front() == i - k)
		{
			dq.pop_front();
		}

		while (!dq.empty() && stones[dq.back()] <= stones[i])
		{
			dq.pop_back();
		}
		dq.push_back(i);
	}
	answer = min(answer, stones[dq.front()]);

	return answer;
}

int main()
{
	freopen("../../input.txt", "r", stdin);

	int length;
	cin >> length;

	vector<int> stones(length);
	for (int i = 0; i < length; ++i)
	{
		cin >> stones[i];
	}

	int k;
	cin >> k;

	cout << solution(stones, k) << endl;

	return 0;
}