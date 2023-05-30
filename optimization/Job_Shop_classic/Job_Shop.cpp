#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <numeric>
#include <climits>
#include <unordered_set>

using namespace std;

struct Job {
    int id;
    int k;
    vector < pair < int, int > > steps;
};


struct Node {
    Node(vector < int > ts, vector < int > ls, vector < int > nl, int t)
        : times(ts), lastSteps(ls), nload(nl), time(t)
    {
    }

    vector < int > times, lastSteps, nload;
    int time;
};


vector < Job > jobs;
int m, n;
int globalTime = INT_MAX;


int calculateLowerBound(const Node& node) {
    int lowerBound = 0;

    for (const auto& job : jobs) {
        int minTime = INT_MAX;
        for (int i = node.lastSteps[job.id] + 1; i < job.k; ++i) {
            if(job.steps[i].second < minTime)
                minTime = job.steps[i].second; 
        }
        lowerBound += minTime;
    }

    return lowerBound;
}


void explore(Node& node) {
    int lb = calculateLowerBound(node);

    if(lb + node.time > globalTime)
        return;
    
    bool leaf = true;
    for(int i = 0; i < m; ++i)
        if(node.lastSteps[i] != jobs[i].k - 1)
            leaf = false;

    if(leaf) {
        globalTime = min(globalTime, node.time);
        return;
    }

    for(auto& job : jobs) {
        int prevStep = node.lastSteps[job.id];
        if(prevStep == job.k - 1) continue;

        int jobTime = node.times[job.id];
        int currLoad = node.nload[job.steps[prevStep + 1].first];

        Node nextNode(node.times, node.lastSteps, node.nload, -1);
        if(currLoad >= jobTime) {
            nextNode.nload[job.steps[prevStep + 1].first] += job.steps[prevStep + 1].second;
        } else {
            nextNode.nload[job.steps[prevStep + 1].first] = job.steps[prevStep + 1].second + jobTime;
        }

        nextNode.lastSteps[job.id] = prevStep + 1;
        nextNode.times[job.id] = max(nextNode.nload[job.steps[prevStep + 1].first],  nextNode.times[job.id]);
        nextNode.time = max(node.time, nextNode.times[job.id]);

        explore(nextNode);
    }
}

int Job_Shop_n_machines_m_jobs() {
    Node root(vector < int > (m, 0), vector < int > (m, -1), vector < int > (n, 0), 0);
    explore(root);
    return globalTime;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    cin >> n >> m;
    jobs = vector < Job > (m);

    for (int i = 0; i < m; i++) {
        int k;
        cin >> k;

        jobs[i].k = k;
        jobs[i].id = i;

        for (int j = 0; j < k; j++) {
            int m, t;
            cin >> m >> t;

            jobs[i].steps.push_back( { m - 1, t } );
        }
    }   

    cout << Job_Shop_n_machines_m_jobs();
    return 0;
}
