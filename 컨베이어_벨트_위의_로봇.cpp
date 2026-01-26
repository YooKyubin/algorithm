#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>

using namespace std;

int MoveBelt(int entry, vector<int>& durability, vector<int>& isRobot)
{
	const int beltLength = (int)durability.size();
	const int nextEntry = (entry - 1 + beltLength) % beltLength;
	const int nextExit = (nextEntry + (beltLength / 2) - 1) % beltLength;

	isRobot[nextExit] = 0;
	return nextEntry;
}

void MoveRobot(const int entry, vector<int>& durability, vector<int>& isRobot)
{
	const int beltLength = (int)durability.size();
	const int exit = (entry + beltLength / 2 - 1) % beltLength;

	for (int i = 1; i < beltLength / 2; ++i)
	{
		int curr = (exit - i + beltLength) % beltLength;
		if (0 == isRobot[curr])
		{
			continue;
		}

		int next = (curr + 1) % beltLength;
		if (0 != isRobot[next])
		{
			continue;
		}

		if (durability[next] == 0)
		{
			continue;
		}

		// durability[next] -= isRobot[curr];
		durability[next] -= 1;
		isRobot[next] = isRobot[curr];
		isRobot[curr] = 0;
		if (next == exit)
		{
			isRobot[next] = 0;
		}
	}
}

void LoadRobot(const int entry, vector<int>& durability, vector<int>& isRobot)
{
	if (durability[entry] == 0)
	{
		return;
	}
	// if (isRobot[entry])
	// {
	// 	return;
	// }
	--durability[entry];
	++isRobot[entry];
}

void Print(const int entry, vector<int>& durability, vector<int>& isRobot)
{
	const int beltLength = durability.size();
	const int exit = (entry + beltLength / 2 - 1) % beltLength;
	for (int i = 0; i < beltLength; ++i)
	{
		cout << durability[i] << ", " << isRobot[i];

		if (exit == i)
		{
			cout << " <- exit" << endl;
		}
		else if (entry == i)
		{
			cout << " <- entry" << endl;
		}
		else
		{
			cout << endl;
		}
	}
	cout << endl;
}

int main()
{
	freopen("../../input.txt", "r", stdin);
	// freopen("../../output.txt", "w", stdout);

	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);

	int n, k;
	cin >> n >> k;

	vector<int> durability(n * 2);
	for (int i = 0; i < 2 * n; ++i)
	{
		cin >> durability[i];
	}
	vector<int> isRobot(n * 2, 0);


	int entry = 0;
	int step = 0;

	// Print(entry, durability, isRobot);

	while (true)
	{
		entry = MoveBelt(entry, durability, isRobot);
		MoveRobot(entry, durability, isRobot);
		LoadRobot(entry, durability, isRobot);

		++step;

		int numZeroDurability = 0;
		for (int i : durability)
		{
			if (i == 0)
			{
				++numZeroDurability;
			}
		}
		// cout << numZeroDurability << endl;
		// Print(entry, durability, isRobot);

		if (numZeroDurability >= k)
		{
			break;
		}
	}
	cout << step << endl;

	return 0;
}
