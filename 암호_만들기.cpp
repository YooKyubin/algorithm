#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int l, c;
vector<char> arr;
vector<char> answer;
vector<char> vowel {'a', 'e', 'i', 'o', 'u'};

int vowelCnt = 0;
int consonantCnt = 0;

void print()
{
    for (auto c : answer)
    {
        cout << c;
    }
    cout << '\n';
}

void dfs(int idx, int depth)
{
    if (depth == l)
    {
        if (vowelCnt >= 1 && consonantCnt >= 2)
            print();

        return;
    }

    if (idx == arr.size())
        return;
    
    bool isVowel = false;
    for (auto c : vowel)
    {
        if (arr[idx] == c)
            isVowel = true;
    }

    if (isVowel)
        ++vowelCnt;
    else
        ++consonantCnt;
    
    answer.push_back(arr[idx]);
    dfs(idx+1, depth+1);
    answer.pop_back();

    if (isVowel)
        --vowelCnt;
    else
        --consonantCnt;

    dfs(idx+1, depth);
}

int main()
{
    cin >> l >> c;
    for (int i=0; i<c; ++i)
    {
        char temp;
        cin >> temp;
        arr.push_back(temp);
    }
    sort(arr.begin(), arr.end());

    dfs(0, 0);
    return 0;
}