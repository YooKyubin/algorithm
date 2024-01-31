#include <iostream>
#include <vector>
#include <string>

using namespace std;

int n;
vector<string> img;

string SearchTree(int x, int y, int length)
{
	if (length == 1)
	{
		return img[x].substr(y, 1);
	}

	string ret = "";
	int nLength = length / 2;
	ret += SearchTree(x, y, nLength);
	ret += SearchTree(x, y + nLength, nLength);
	ret += SearchTree(x + nLength, y, nLength);
	ret += SearchTree(x + nLength, y + nLength, nLength);

	if (ret == "1111" || ret == "0000")
		return ret.substr(0, 1);

	return "(" + ret + ")";
}

int main()
{
	cin >> n;
	img.resize(n);
	for (int i = 0; i < n; ++i)
	{
			cin >> img[i];
	}

	string answer = SearchTree(0, 0, n);

	cout << answer << endl;
	return 0;
}