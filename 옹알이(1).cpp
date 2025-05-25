#include <string>
#include <vector>

#include <iostream>

using namespace std;

int solution(vector<string> babbling) {
    int answer = 0;

    const vector<string> pronunciations = { "aya", "ye", "woo", "ma" };

    for (const string& speak : babbling)
    {
        size_t sumPronunciationSize = 0;
        for (const string& pronunciation : pronunciations)
        {
            if (string::npos != speak.find(pronunciation))
            {
                sumPronunciationSize += pronunciation.size();
            }
        }

        if (speak.size() == sumPronunciationSize)
        {
            ++answer;
        }
    }

    return answer;
}

int main()
{
    vector<string> babbling = 
        {"ayaye", "uuuma", "ye", "yemawoo", "ayaa"};

    cout << solution(babbling) << endl;

    return 0;
}