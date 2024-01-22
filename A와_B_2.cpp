#include <iostream>
#include <string>
#include <algorithm>

using namespace std;


bool Search(string s, string t)
{
	if (s == t)
		return true;

	if (s.length() >= t.length())
		return false;


	bool resA = false;
	bool resB = false;
	if (t.back() == 'A')
	{
		string temp = t;
		temp.erase(temp.end() - 1);
		resA = Search(s, temp);
	}

	if (t.front() == 'B')
	{
		string temp = t;
		temp.erase(temp.begin());
		reverse(temp.begin(), temp.end());
		resB = Search(s, temp);
	}

	return resA || resB;
}

int main()
{
	string s, t;
	cin >> s;
	cin >> t;

	cout << Search(s, t) << endl;
	
	return 0;
}