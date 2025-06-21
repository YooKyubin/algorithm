#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int solution(vector<int> A, vector<int> B) {
    int answer = 0;
    int numCard = (int)A.size();

    sort(A.begin(), A.end());
    sort(B.begin(), B.end());

    int j=0;
    for (int i = 0; i < numCard; ++i)
    {
        for (j; j < numCard; ++j)
        {
            if (A[i] < B[j])
            {
                ++answer;
                ++j;
                break;
            }
        }
    }

    return answer;
}

#include <iostream>

int main()
{
    vector<int> A = {5,1,3,7};
    vector<int> B = {2,2,6,8};

    cout << solution(A, B) << endl;

    return 0;
}