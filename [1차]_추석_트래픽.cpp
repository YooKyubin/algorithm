
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

struct Node
{
    int time = 0;
    bool isStart = true;
};

int ComputeEndTimeMicroSecond(const string& time)
{
    int ms = 0;
    ms += stoi(time.substr(0, 2)) * 3600 * 1000;
    ms += stoi(time.substr(3, 2)) * 60000;
    ms += stoi(time.substr(6, 2)) * 1000;
    ms += stoi(time.substr(9, 3));

    return ms;
}

int ComputeDurationMicroSecond(const string& duration)
{
    int ms = 0;

    int dotIndex = duration.find_first_of('.');
    if (dotIndex != string::npos)
    {
        ms += stoi(duration.substr(0, dotIndex)) * 1000;
        ms += stoi(duration.substr(dotIndex+1, duration.size() - 1 - dotIndex));
    }
    else
    {
        ms += stoi(duration.substr(0, duration.length() - 1)) * 1000;
    }

    return ms;
}

pair<Node, Node> ConvertLogToNode(const string& log)
{
    static const int timeLength = (int)string("hh:mm:ss.sss").length();

    pair<Node, Node> nodes;
    int startTimeIndex = log.find_first_of(' ') + 1;
    int durationIndex = startTimeIndex + timeLength + 1;

    string startTimeLog = log.substr(startTimeIndex, timeLength);
    string durationLog = log.substr(durationIndex);

    int msEndTime = ComputeEndTimeMicroSecond(startTimeLog);
    int duration = ComputeDurationMicroSecond(durationLog);

    nodes.first.time = msEndTime - duration + 1;
    nodes.first.isStart = true;

    nodes.second.time = msEndTime;
    nodes.second.isStart = false;

    return nodes;
}

int solution(vector<string> lines) {
    int answer = 0;

    vector<Node> nodes;
    nodes.reserve(lines.size() * 2);
    for (const string& line : lines)
    {
        pair<Node, Node> pairNode = ConvertLogToNode(line);
        
        nodes.push_back(pairNode.first);
        nodes.push_back(pairNode.second);
    }

    sort(nodes.begin(), nodes.end(), [](const Node& src, const Node& dst)->bool
        {
            return src.time < dst.time;
        });

    // for (auto& node : nodes)
    // {
    //     cout << node.time << " " << (node.isStart ? "start" : "end") << endl;
    // }

    int begin = 0;
    int end = 0;
    int numProcess = 0;
    int maxProcess = 0;
    for (int i=0; i < (int)nodes.size(); ++i)
    {
        end = i;
        if (nodes[end].isStart)
        {
            ++numProcess;
        }
        
        while (nodes[end].time - nodes[begin].time >= 1000)
        {
            if (!nodes[begin].isStart)
            {
                --numProcess;
            }
            ++begin;
        }

        maxProcess = max(maxProcess, numProcess);
    }

    answer = maxProcess;

    return answer;
}

#include <iostream>

int main()
{
    vector<string> lines =
    {
        "2016-09-15 01:00:04.002 2.0s", "2016-09-15 01:00:07.000 2s"
    };

    cout << solution(lines) << endl;
    return 0;
}