#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <iostream>

using namespace std;

// map<string, int> ConvertNameToID(const vector<string>& enroll)
// {
//     map<string, int> nameToID;
//     int id = 0;
//     for (const string& name : enroll)
//     {
//         nameToID.insert({name, id});
//         ++id;
//     }
//     nameToID.insert({"-", enroll.size()});

//     return nameToID;
// }

unordered_map<string, int> ConvertNameToID(const vector<string>& enroll)
{
    unordered_map<string, int> nameToID;
    nameToID.reserve(enroll.size());
    int id = 0;
    for (const string& name : enroll)
    {
        nameToID.insert({name, id});
        ++id;
    }
    nameToID.insert({"-", enroll.size()});

    return nameToID;
}

void Account(const vector<int>& graph, int id, int charge, vector<int>& answer)
{
    // cout << id << " ";
    if (id < graph.size())
    {
        answer[id] += charge - (charge / 10);
        // cout << "{ " << id << ": " << charge << " }" << "  ";
        Account(graph, graph[id], charge / 10, answer);
    }
}

vector<int> solution(vector<string> enroll, vector<string> referral, vector<string> seller, vector<int> amount)
{
    vector<int> answer(enroll.size(), 0);

    unordered_map<string, int> nameToID = ConvertNameToID(enroll);

    vector<int> graph;
    graph.reserve(enroll.size() + 1);
    for (const string& name : referral)
    {
        int id = nameToID.find(name)->second;
        graph.push_back(id);
    }

    for (size_t i = 0; i<seller.size(); ++i)
    {
        const string name = seller[i];
        int id = nameToID.find(name)->second;
        Account(graph, id, 100 * amount[i], answer);
    }

    return answer;
}

int main()
{
    vector<string> enroll = { "john", "mary", "edward", "sam",    "emily", "jaimie", "tod",    "young"};
    vector<string> referral = {"-",    "-",   "mary",   "edward", "mary",  "mary",   "jaimie", "edward"};
    vector<string> seller = {"sam", "emily", "jaimie", "edward"};
    vector<int> amount = {2, 3, 5, 4};

    vector<int> results = solution(enroll, referral, seller, amount);
    for (int result : results)
    {
        cout << result  << "\n";
    }

    return 0;
}