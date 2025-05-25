#include <string>
#include <vector>

#include <iostream>

using namespace std;

int GetSkillIndex(char skill)
{
    return skill - 'A';
}

bool CheckAvailableSkillTree(const vector<bool>& isAccessible, const vector<int>& nextSkills, const string& skill_tree)
{
    vector<bool> isAccessibleCopy = isAccessible;

    for (char skillInOrder : skill_tree)
    {
        int index = GetSkillIndex(skillInOrder);
        if (isAccessibleCopy[index])
        {
            isAccessibleCopy[ nextSkills[index] ] = true;
        }
        else
        {
            return false;
        }
    }

    return true;
}

int solution(string skill, vector<string> skill_trees) {
    int answer = 0;

    const int numSkills = 'Z' - 'A' + 1;
    vector<bool> isAccessible(numSkills, true);
    vector<int> nextSkills(numSkills, 0);
    for (int i = 0; i < numSkills; ++i)
    {
        nextSkills[i] = i;
    }
    for (size_t i=1; i<skill.size(); ++i)
    {
        int index = GetSkillIndex(skill[i]);
        isAccessible[index] = false;
        nextSkills[GetSkillIndex(skill[i-1])] = index;
    }

    for (const string& skill_tree : skill_trees)
    {
        if (true == CheckAvailableSkillTree(isAccessible, nextSkills, skill_tree))
        {
            ++answer;
        }
    }

    return answer;
}

int main()
{
    string skill = "CBD";
    vector<string> skill_trees = {"BACDE", "CBADF", "AECB", "BDA"};

    cout << solution(skill, skill_trees) << endl;

    return 0;
}
