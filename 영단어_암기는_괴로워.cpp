#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int numWord, threshold;
    cin >> numWord >> threshold;

    unordered_map<string, int> words;
    for (int i=0; i<numWord; ++i)
    {
        string input;
        cin >> input;
        if (words.end() == words.find(input))
        {
            words[input] = 0;
        }
        else
        {
            ++words[input];
        }
    }

    vector<pair<string, int>> sortedWords(words.begin(), words.end());
    // sortedWords.reserve(words.size());
    // for (auto& Pair : words)
    // {
    //     sortedWords.push_back(Pair);
    // }

    sort(sortedWords.begin(), sortedWords.end(), 
    [](const pair<string, int>& Src, const pair<string, int>& Dst)->bool
        {
            if (Src.second == Dst.second)
            {
                if (Src.first.size() == Dst.first.size())
                {
                    return Src.first < Dst.first;
                }

                return Src.first.size() > Dst.first.size();
            }

            return Src.second > Dst.second;
        });

    for (auto& Pair : sortedWords)
    {
        if (Pair.first.size() >= threshold)
        {
            cout << Pair.first << "\n";
        }
    }

    return 0;
}