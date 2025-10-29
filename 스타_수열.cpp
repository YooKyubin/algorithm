#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int solution(std::vector<int> a) {
    int answer = 0;

    vector<pair<int, int>> frequency(a.size(), {0, 0});
    for (int i = 0; i < frequency.size(); ++i)
    {
        frequency[i].second = i;
    }
    for (int i : a)
    {
        ++frequency[i].first;
    }
    sort(frequency.begin(), frequency.end());

    for (auto& p : frequency)
    {
        int base = p.second;
        if (p.first * 2 < answer)
        {
            continue;
        }

        int length = 0;
        for (int i = 0 ; i < a.size()-1; ++i)
        {
            if (a[i] == a[i+1])
            {
                continue;
            }

            if (a[i] != base && a[i+1] != base)
            {
                continue;
            }

            // 둘 중 하나는 base
            ++i;
            ++length;
        }

        answer = max(answer, length * 2);
    }

    return answer;
}

int main()
{
    freopen("output.txt", "w", stdout);

    vector<int> a{ 0,3,3,0,7,2,0,2,2,0 };
    cout << solution(a) << endl;
    return 0;
}