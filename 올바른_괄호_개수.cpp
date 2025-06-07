#include <vector>

using namespace std;

int solution(int n) {
    int answer = 0;

    vector<int> numCorrect(n + 1);
    numCorrect[0] = 1;
    numCorrect[1] = 1;

    for (int i=2; i<n + 1; ++i)
    {
        int sum = 0;
        for (int j = 0; j < i; ++j)
        {
            int inner = numCorrect[j];
            int outter = numCorrect[i - 1 - j];

            sum += inner * outter;
        }

        numCorrect[i] = sum;
    }

    answer = numCorrect[n];
    return answer;
}

#include <iostream>

int main()
{
    int n = 10;
    cout << solution(n) << endl;
    return 0;
}

/*
[ ( dp ) dp ]
*/