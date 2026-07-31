#include <string>
#include <vector>

using namespace std;

long long solution(int n, vector<int> works) {
	long long answer = 0;

	int max_duration = 0;
	for (int work : works)
	{
		max_duration = max(max_duration, work);
	}

	vector<int> works_by_durations(max_duration + 1, 0);
	for (int work : works)
	{
		++works_by_durations[work];
	}

	for (int i = max_duration; i > 0; --i)
	{
		if (n <= works_by_durations[i])
		{
			works_by_durations[i - 1] += n;
			works_by_durations[i] -= n;
			break;
		}

		n -= works_by_durations[i];
		works_by_durations[i - 1] += works_by_durations[i];
		works_by_durations[i] = 0;
		--max_duration;
	}


	for (int i = 1; i <= max_duration; ++i)
	{
		answer += i * i * works_by_durations[i];
	}

	return answer;
}

#include <iostream>

int main()
{
	int n = 1;
	vector<int> works = { 2, 1, 2 };

	cout << solution(n, works) << endl;
	return 0;
}

// =================================
// 2026 07 31 
// =================================

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

long long solution(int n, vector<int> works) {
	long long answer = 0;

	less<int> comp;

	make_heap(works.begin(), works.end(), comp);

	for (int i = 0; i < n; ++i)
	{
		if (works.empty())
		{
			break;
		}

		pop_heap(works.begin(), works.end(), comp);
		--works.back();

		if (works.back() == 0)
		{
			works.pop_back();
		}
		else
		{
			push_heap(works.begin(), works.end(), comp);
		}
	}

	for (int work : works)
	{
		answer += static_cast<long long>(work) * work;
	}

	return answer;
}

int main()
{
	freopen("input.txt", "r", stdin);

	int n;
	cin >> n;

	int len;
	cin >> len;

	vector<int> works(len);
	for (int i = 0; i < len; ++i)
	{
		cin >> works[i];
	}

	cout << solution(n, works) << endl;
}