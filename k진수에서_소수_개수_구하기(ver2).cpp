#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

#include <iostream>

#define MAX_NUM 1'000'000

using namespace std;

vector<int> TrasnformNumberSystem(int n, int base)
{
    vector<int> transformedNumber;

    while(0 != n)
    {
        transformedNumber.push_back(n % base);
        n = n / base;
    }

    reverse(transformedNumber.begin(), transformedNumber.end());
    return transformedNumber;
}

bool IsPrime(long long n)
{
    if (1 == n)
    {
        return false;
    }

    for (long long i=2; i * i <= n; ++i)
    {
        if (0 == n % i)
        {
            return false;
        }
    }


    return true;
}

vector<long long> SplitNumber(vector<int> trasnformedNumber)
{
    vector<long long> splitedDecimalNums;
    vector<int> splitedNums;

    // 마지막에 0을 넣어서 코드를 깔끔하게 만드려 했더니 레퍼런스를 받을 수 없다.
    trasnformedNumber.push_back(0);

    for (int num : trasnformedNumber)
    {
        if (0 == num)
        {
            if (splitedNums.empty())
            {
                continue;
            }

            long long decimalNumber = 0;
            reverse(splitedNums.begin(), splitedNums.end());
            for (size_t i = 0; i < splitedNums.size(); ++i)
            {
                decimalNumber += pow(10, i) * splitedNums[i];
            }

            splitedDecimalNums.push_back(decimalNumber);
            splitedNums.clear();
        }
        else
        {
            splitedNums.push_back(num);
        }
    }

    return splitedDecimalNums;
}

int solution(int n, int k) {
    int answer = 0;

    vector<int> transformedNumber = TrasnformNumberSystem(n, k);

    for (long long num : SplitNumber(transformedNumber))
    {
        if (IsPrime(num))
        {
            ++answer;
        }
    }
    return answer;
}

int main()
{
    int n = 211;
    int k = 10;

    int answer = solution(n, k);
    cout << "===============" << endl;
    cout << answer << endl;

    return 0;
}