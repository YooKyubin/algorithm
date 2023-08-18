#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <unordered_set>

using namespace std;

struct Node {
    bool isFinish = false;
    map<char, Node> next;

    void insert(const string& word, int idx){
        if (idx == word.size()){
            isFinish = true;
            return;
        }
        if (this->next.find(word[idx]) == this->next.end()){
            this->next[word[idx]] = Node();
        }
        this->next[word[idx]].insert(word, idx+1);
    }
};

int w, b;
vector<string> words;
vector<string> board(4);
vector<vector<bool>> visited(4, vector<bool>(4, false));
Node root = Node();
vector<pair<int, int>> dir { {0,1}, {1,0}, {-1,0}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };
vector<int> score { 0, 0, 0, 1, 1, 2, 3, 5, 11};
int totalScore = 0;
int cntWord = 0;
string longestWord;
string curWord;
unordered_set<string> stringSet;

bool OOB(int x, int y) { return x >= 4 || x < 0 || y < 0 || y >= 4; }

string compare(const string& a, const string& b){
    string ret;
    if (a.length() > b.length())
        return a;

    else if (a.length() < b.length())
        return b;

    else{
        return a < b ? a : b;
    }
} 

void dfs(int x, int y, Node& trie){
    if (trie.isFinish){
        if (stringSet.find(curWord) == stringSet.end()){
            stringSet.insert(curWord);
            ++cntWord;
            totalScore += score[curWord.length()];
            longestWord = compare(curWord, longestWord);
        }
    }
    
    for (int i=0; i<8; i++){
        int nx = x + dir[i].first;
        int ny = y + dir[i].second;
        if (OOB(nx, ny)) 
            continue;
        if (visited[nx][ny])
            continue;

        char next = board[nx][ny];
        if (trie.next.find(next) == trie.next.end()) 
            continue;
        
        visited[nx][ny] = true;
        curWord.push_back(next);
        dfs(nx, ny, trie.next[next]);
        curWord.pop_back();
        visited[nx][ny] = false;
        
    }
}

int main () {
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    cin >> w;
    for (int i=0; i < w; i++){
        string temp;
        cin >> temp;
        root.insert(temp, 0);
        words.push_back(temp);
    }

    cin >> b;
    while (b--){
        for (int i=0; i<4; i++)
            cin >> board[i];

        for (int x=0; x<4; x++) {
            for (int y=0; y<4; y++){
                char start = board[x][y];
                curWord.push_back(start);
                visited[x][y] = true;
                dfs( x, y, root.next[ start ] );
                visited[x][y] = false;
                curWord.pop_back();
            }
        }
        cout << totalScore << " " << longestWord << " " << cntWord << "\n";

        cntWord = 0;
        totalScore = 0;
        longestWord.clear();
        curWord.clear();
        stringSet.clear();
    }
    return 0;
}