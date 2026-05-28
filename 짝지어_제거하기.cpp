#include <iostream>
#include<string>
#include <vector>

using namespace std;

int solution(string s)
{
	int answer = -1;

	vector<char> stack;
	stack.reserve(s.size());

	for (char c : s)
	{
		if (stack.empty())
		{
			stack.push_back(c);
			continue;
		}

		if (stack.back() == c)
		{
			stack.pop_back();
		}
		else
		{
			stack.push_back(c);
		}
	}

	return stack.empty() ? 1 : 0;
}

int main()
{
	string s = "cdcd";
	cout << solution(s) << endl;
	return 0;
}