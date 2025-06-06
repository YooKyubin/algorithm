#include <string>
#include <vector>

using namespace std;

bool CheckAllConditions(int numberBitset, const vector<vector<int>>& q, const vector<int>& ans)
{
    int m = (int)q.size();
    for (int i=0; i < m; ++i)
    {
        int count = 0;
        for (int conditionNumber : q[i])
        {
            if (numberBitset & (1 << conditionNumber))
            {
                ++count;
            }
        }

        if (count != ans[i])
        {
            return false;
        }
    }

    return true;
}

int FindCombi(int depth, int curr, int n, int numberBitset, const vector<vector<int>>& q, const vector<int>& ans)
{
    if (depth == 5)
    {
        return CheckAllConditions(numberBitset, q, ans) ? 1 : 0;
    }

    int sum = 0;
    for (int i = curr; i < n + 1; ++i)
    {
        sum += FindCombi(depth + 1, i + 1, n, numberBitset | (1 << i), q, ans);
    }

    return sum;
}


int solution(int n, vector<vector<int>> q, vector<int> ans) {
    int answer = 0;

    answer = FindCombi(0, 1, n, 0, q, ans);

    return answer;
}