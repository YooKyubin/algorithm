#include <string>
#include <vector>

using namespace std;

int solution(int n, vector<int> money) {
    int answer = 0;

    vector<long long> num_change_ways(n + 1, 0);
    for (int coin : money)
    {
        for (int i=1; i<=n; ++i)
        {
            if (i < coin)
            {
                
            }
            else if (i == coin)
            {
                num_change_ways[i] += 1;
            }
            else
            {
                num_change_ways[i] = num_change_ways[i - coin] + num_change_ways[i];
            }
        }
    }

    answer = num_change_ways.back() % 1'000'000'007;
    return answer;
}

#include <iostream>

int main()
{
    int n = 5;
    vector<int> money =
        { 1, 2, 5 };

    cout << solution(n, money) << endl;
    return 0;
}