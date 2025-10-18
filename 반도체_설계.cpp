#include <iostream>
#include <vector>

using namespace std;

int Longest(const vector<int>& arrow, bool (*cmp)(int, int))
{
    vector<int> increased;
    for (int i : arrow)
    {
        if (increased.empty() || cmp(increased.back(), i))
        {
            increased.push_back(i);
        }
        else
        {
            int low = -1;
            int high = (int)increased.size();

            while (low + 1 < high)
            {
                int mid = (low + high) >> 1;

                if (cmp(increased[mid], i))
                {
                    low = mid; 
                }
                else
                {
                    high = mid;
                }

            }
            increased[high] = i;
        }
    }

    return static_cast<int>(increased.size());
}

int main()
{
    freopen("../../input.txt", "r", stdin);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;
    
    vector<int> arrow(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> arrow[i];
    }

    int increased = Longest(arrow, [](int a, int b)->bool{ return a < b; });
    cout << increased << endl;
    return 0;
}
