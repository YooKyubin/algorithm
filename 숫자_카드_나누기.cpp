#include <string>
#include <vector>
#include <iostream>

using namespace std;

int GDC(int src, int dst)
{
	if (src < dst)
	{
		swap(src, dst);
	}

	while (dst != 0)
	{
		int temp = src % dst;
		src = dst;
		dst = temp;
	}
	return src;
}

bool CanDivide(int gdc, vector<int> array)
{
	for (int i : array)
	{
		if (i % gdc == 0)
		{
			return true;
		}
	}

	return false;
}

int solution(vector<int> arrayA, vector<int> arrayB) {

	int gdcA = arrayA.front();
	for (int i = 1; i < arrayA.size(); ++i)
	{
		gdcA = GDC(gdcA, arrayA[i]);
	}

	int gdcB = arrayB.front();
	for (int i = 1; i < arrayB.size(); ++i)
	{
		gdcB = GDC(gdcB, arrayB[i]);
	}

	gdcA = CanDivide(gdcA, arrayB) ? 0 : gdcA;
	gdcB = CanDivide(gdcB, arrayA) ? 0 : gdcB;

	return max(gdcA, gdcB);
}

int main()
{
	freopen("../../input.txt", "r", stdin);

	int n;
	cin >> n;

	vector<int> arrayA(n);
	vector<int> arrayB(n);

	for (int i = 0; i < n; ++i)
	{
		cin >> arrayA[i];
	}

	for (int i = 0; i < n; ++i)
	{
		cin >> arrayB[i];
	}

	cout << solution(arrayA, arrayB) << endl;

	return 0;
}