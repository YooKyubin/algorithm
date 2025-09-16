#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <set>

using namespace std;

int GetBasicNumber(int N, int count)
{
    int NN = 0;
    for (int i=0; i<count; ++i)
    {
        NN += pow(10, i) * N;
    }   
    return NN;
}

void PushResult(map<int, int>& cache, set<int>& operands, int num, int n)
{
    if (num <= 0)
    {
        return;
    }

    if (cache.find(num) != cache.end())
    {
        return;
    }

    cache[num] = n;
    operands.insert(num);
}

int solution(int N, int number) {
    int answer = 0;

    map<int, int> cache;
    vector<set<int>> operands(9, set<int>());

    for (int n = 1; n < 9; ++n)
    {
        int NN = GetBasicNumber(N, n);
        operands[n].insert(NN);
        cache[NN] = n;

        for (int i = 1; i < n; ++i)
        {
            int j = n - i;
            for (int src : operands[i])
            {
                if (src == 0)
                {
                    continue;
                }

                for (int dst : operands[j])
                {
                    if (dst == 0)
                    {
                        continue;
                    }

                    PushResult(cache, operands[n], src + dst, n);
                    PushResult(cache, operands[n], src - dst, n);
                    PushResult(cache, operands[n], src * dst, n);
                    PushResult(cache, operands[n], src / dst, n);
                }
            }
        }
    
    }

    if (cache.find(number) == cache.end())
    {
        answer = -1;
    }
    else
    {
        answer = cache[number];
    }

    return answer;
}

int main()
{
    int N = 5;
    int number = 31168;

    cout << solution(N, number) << endl;
    return 0;
}