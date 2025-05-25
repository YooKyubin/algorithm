#include <string>
#include <vector>

#include <iostream>

using namespace std;

vector<long long> solution(vector<long long> numbers) {
    vector<long long> answer;

    for (long long num : numbers)
    {
        for (int i=0; i<64; ++i)
        {
            if (0 == (num & (1LL << i)))
            {
                num = num | (long long)(1LL << i);
                num = num & ~(long long)(1LL << (i-1));
                answer.push_back(num);
                break;
            }
        }
    } 

    return answer;
}

int main()
{
    vector<long long> numbers = {2, 3, 7};

    for (long long answer : solution(numbers))
    {
        cout << answer << endl;
    }

    return 0;
}