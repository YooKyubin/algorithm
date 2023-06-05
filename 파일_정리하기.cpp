// 미해결

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

struct Node {
    string name;
    vector<string> childs;
    bool isFolder;
    int fileCnt = 0;
};

int n, m, q;
unordered_map<string, Node> fileSystem;


int CntFiles(const string& name){
    Node& cur = fileSystem[name];
    if (cur.fileCnt != 0) return cur.fileCnt;

    int ret = 0;
    if (cur.isFolder){
        for (string child: cur.childs){
            cout << name << ": " << child << endl;
            ret += CntFiles(child);
        }
    }
    else{
        ret = 1;
    }
    cur.fileCnt = ret;
    return ret;
}

vector<string> split(string input, string del){
    vector<string> ret;

    return ret;
}

int main () {
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    cin >> n >> m;
    Node root;
    root.isFolder = true;
    fileSystem["main"] = root;
    for (int i=0; i< n + m; i++){
        string parrent; // P
        string name; // F
        int isFolder; // C
        cin >> parrent >> name >> isFolder;
        Node node;
        node.isFolder = isFolder == 1;
        if (!isFolder) node.fileCnt = 1;
        fileSystem[name] = node;
        fileSystem[parrent].childs.push_back(name); // 이건 입력으로 받을 때 부모 먼저 받지 않은 경우면 오류가 나야함 귀찮으니까 일단 넘김
    }

    // 중간 처리 ~~
    string m = "main";
    cout << CntFiles("main") << endl;
    cout << CntFiles("FolderA") << endl;
    cout << CntFiles("FolderB") << endl;
    cout << CntFiles("FolderC") << endl;

    // cin >> q;
    // while(q--){
    //     // 쿼리 처리
    // }
    // cout << fileSystem["main"].fileCnt << endl;

    return 0;
}