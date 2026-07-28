#include <string>
#include <vector>
#include <iostream>

using namespace std;


string solution(string number, int k) {
	string answer = "";
	const int resultLength = number.size() - k;
	answer.reserve(resultLength);

	int exceptCount = 0;
	for (char digit : number)
	{
		while (!answer.empty() && answer.back() < digit && exceptCount < k)
		{
			answer.pop_back();
			++exceptCount;
		}
		answer.push_back(digit);
	}
	answer.resize(resultLength);

	return answer;
}

int main()
{
	freopen("../../input.txt", "r", stdin);
	string number;
	cin >> number;

	int k;
	cin >> k;

	cout << solution(number, k) << endl;
	return 0;
}