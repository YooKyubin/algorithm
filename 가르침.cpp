#include <iostream>
#include <vector>
#include <string>

using namespace std;

int GetID(char ch)
{
    return ch - 'a';
}

int Count(const vector<int>& wordMasks, int k, int mask)
{
    int cnt = 0;
    for (int wordMask : wordMasks)
    {
        if ((wordMask & mask) == wordMask)
        {
            ++cnt;
        }
    }
    return cnt;
}

int Choice(const vector<int>& wordMasks, int k, int depth, int mask, int curr)
{
    if (k == depth)
    {
        // cout << mask << endl;
        return Count(wordMasks, k, mask);
    }

    int cnt = 0;
    for (int i = curr; i < 26; ++i)
    {
        if (0 == (mask & (1 << i)))
        {
            int newMask = mask | (1 << i);
            cnt = max(cnt, Choice(wordMasks, k, depth + 1, newMask, i + 1));
        }
    }

    return cnt;
}

int main()
{
    freopen("../../input.txt", "r", stdin);
    // freopen("../../output.txt", "w", stdout);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int n, k;
    cin >> n >> k;

    vector<int> wordMasks(n, 0);
    for (int i = 0; i < n; ++i)
    {
        string word;
        cin >> word;

        for (char ch : word)
        {
            wordMasks[i] |= 1 << GetID(ch);
        }
    }

    if (k < 5)
    {
        cout << 0 << endl;    
    }
    else
    {
        int mask = 0;
        vector<char> essentialAlphabet = { 'a', 'n', 't', 'i', 'c' };
        for (char ch : essentialAlphabet)
        {
            mask = mask | (1 << GetID(ch));
        }
        cout << Choice(wordMasks, k, 5, mask, 0) << endl;
    }

    return 0;
}
