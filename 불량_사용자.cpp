#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool CompareID(const string& banned_id, const string& user_id)
{
    if (banned_id.length() != user_id.length())
    {
        return false;
    }

    for (size_t i=0; i < banned_id.length(); ++i)
    {
        bool isStar = banned_id[i] == '*';
        bool isSame = banned_id[i] == user_id[i];
        if (!isStar && !isSame)
        {
            return false;
        }
    }

    return true;
}

void FindAll(int curr_id_index, int is_visited_mask, const vector<vector<int>>& candidate_ids, vector<int>& visited_masks)
{
    if (curr_id_index == candidate_ids.size())
    {
        visited_masks.push_back(is_visited_mask);
        return;
    }

    for (int user_id : candidate_ids[curr_id_index])
    {
        if (is_visited_mask & (1 << user_id))
        {
            continue;
        }

        is_visited_mask = is_visited_mask | (1 << user_id);
        FindAll(curr_id_index + 1, is_visited_mask, candidate_ids, visited_masks);
        is_visited_mask = is_visited_mask & ~(1 << user_id);
    }
}

int solution(vector<string> user_id, vector<string> banned_id) {
    int answer = 0;

    vector<vector<int>> candidate_ids(banned_id.size());

    for (size_t i=0; i < banned_id.size(); ++i)
    {
        for (size_t j = 0; j < user_id.size(); ++j)
        {
            if (CompareID(banned_id[i], user_id[j]))
            {
                candidate_ids[i].push_back(j);
            }
        }
    }

    vector<int> visited_masks;
    FindAll(0, 0, candidate_ids, visited_masks);

    sort(visited_masks.begin(), visited_masks.end());
    visited_masks.erase(unique(visited_masks.begin(), visited_masks.end()), visited_masks.end());

    answer = visited_masks.size();
    return answer;
}


#include <iostream>

int main()
{
    vector<string> user_id = 
        { "frodo", "fradi", "crodo", "abc123", "frodoc" };
    vector<string> banned_id = 
        { "*rodo", "*rodo", "******" };

    cout << solution(user_id, banned_id) << endl;
    return 0;
}