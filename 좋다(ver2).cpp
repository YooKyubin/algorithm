#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool IsGoodNumber(int index, const vector<int>& numbers)
{
    const int num = numbers[index];
    auto left = 0;
    auto right = numbers.size() - 1;

    while (left < right) // 같으면 안됨
    {
        int sum = numbers[left] + numbers[right];

        if (num < sum || right == index)
        {
            --right;
        }
        else if (num > sum || left == index)
        {
            ++left;
        }
        else
        {
            return true;
        }
    }

    return false;
}

int main()
{
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;

    vector<int> numbers(n);
    for (int i=0; i<n; ++i)
    {
        cin >> numbers[i];
    }
    sort(numbers.begin(), numbers.end());

    int goodNumberCount = 0;
    for (int i = 0; i < n; ++i)
    {
        if (IsGoodNumber(i, numbers))
        {
            ++goodNumberCount;   
        }
    }

    cout << goodNumberCount << endl;
    return 0;
}