#include <iostream>
#include <vector>
#include <array>

using namespace std;

int main()
{
	freopen("../../input.txt", "r", stdin);
	
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);
	
	using Array = array<int, 6>;
	constexpr Array type{ 500, 100, 50, 10, 5, 1 };
	
	int w;
	cin >> w;
	Array totalCount{};
	for (int i = 0; i < 6; ++i)
	{
		cin >> totalCount[i];
	}

	int total = 0;
	for (int i = 0; i < 6; ++i)
	{
		total += totalCount[i] * type[i];
	}

	int target = total - w;
	int curr = 0;
	Array targetCount{};
	for (int i = 0; i < 6; ++i)
	{
		for (int j = 0; j < totalCount[i]; ++j)
		{
			int predictedValue = curr + type[i];

			if (predictedValue > target)
			{
				break;
			}

			if (predictedValue <= target)
			{
				curr += type[i];
				++targetCount[i];
			}
		}
	}

	Array leftCount{};
	int numCoins = 0;
	for (int i = 0; i < 6; ++i)
	{
		leftCount[i] = totalCount[i] - targetCount[i];
		numCoins += leftCount[i];
	}

	cout << numCoins << endl;
	for (int i : leftCount)
	{
		cout << i << " ";
	}
	cout << endl;

	return 0;
}