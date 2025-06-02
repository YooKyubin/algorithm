#include <string>
#include <vector>
#include <map>

using namespace std;

struct Node
{
    map<char, Node> childs;
    int ref_count = 0;
    bool is_word = false;
};

void InsertWord(Node& node, const string& word, int depth)
{
    ++node.ref_count;
    if (word.length() == depth)
    {
        node.is_word = true;
        return;
    }

    char alphabet = word[depth];

    if (node.childs.find(alphabet) == node.childs.end())
    {
        Node child_node;
        node.childs.emplace(alphabet, child_node);
    }
    
    Node& child_node = node.childs[alphabet];
    InsertWord(child_node, word, depth + 1);
}

int CountDepthUntilUniqueWord(const Node& node, int depth)
{
    int first_count = 0;

    if (node.ref_count == 1)
    {
        return depth;
    }

    if (node.is_word)
    {
        first_count += depth;
    }


    for (auto& child_pair : node.childs)
    {
        first_count += CountDepthUntilUniqueWord(child_pair.second, depth +1);
    }

    return first_count;
}

int solution(vector<string> words) {
    int answer = 0;

    Node root;
    for (const string& word : words)
    {
        InsertWord(root, word, 0);
    }

    answer = CountDepthUntilUniqueWord(root, 0);

    return answer;
}

#include <iostream>

int main()
{
    vector<string> words = 
        { "go","gone","guild" };

    cout << solution(words) << endl;

    return 0;
}