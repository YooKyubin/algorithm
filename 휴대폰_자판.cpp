#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cmath>

using namespace std;

struct Node 
{
    bool isFinish = false;
    int child = 0;
    map<char, Node> next;
    
    void insert(const string& word, int idx){
        if (idx == word.size()) 
        {
            isFinish = true;
            return;
        }
        if (this->next.find(word[idx]) == this->next.end())
        {
            this->child++;
            this->next[word[idx]] = Node();
        }
        this->next[word[idx]].insert(word, idx+1);
    }

    int find(const string& word, int idx)
    {
        if (idx == word.size()) 
            return 0;
        // if (child > 1 || child == 1 && isFinish) return this->next[word[idx]].find(word, idx+1) + 1;
        // else return this->next[word[idx]].find(word, idx+1);
        if (child < 2 && !isFinish) 
            return this->next[word[idx]].find(word, idx+1);

        else 
            return this->next[word[idx]].find(word, idx+1) + 1;
    }
};


int main() 
{
    cin.tie(0);
    cout << fixed;
    cout.precision(2);
    ios_base::sync_with_stdio(false);

    while (true)
    {
        int n;
        vector<string> inputs;
        cin >> n; if (cin.eof() == true) break;
        for (int i=0; i<n; i++)
        {
            string input;
            cin >> input;
            inputs.push_back(input);
        }
        
        Node root = Node();
        for (int i=0; i<n; i++)
        {
            root.insert(inputs[i], 0);
        }
        int ret = 0;
        for (int i=0; i<n; i++)
        {
            ret += root.find(inputs[i], 0);
            if (root.child == 1) ret++; // 첫 글자는 무조건 작성해야 함
        }
        float answer = float(ret) / float(n);
        cout << answer << "\n";
    }
    return 0;
}