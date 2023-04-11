#include <iostream>
#include <vector>
#include <set>
using namespace std;

using pii = pair<int64_t, int64_t>;


vector<vector<pii>> graph;
vector<int64_t> dist;
vector<bool> processed;

void dijkstra(int64_t start) {
    dist.assign(graph.size(), INT64_MAX);
    processed.assign(graph.size(), false);
    dist[start] = 0ll;

    set<pii> pq;
    pq.insert({0ll, start});

    while (!pq.empty()) {
        int64_t v = (*pq.begin()).second;
        pq.erase(pq.begin());

        if (processed[v]) continue;
        processed[v] = true;

        for (auto edge : graph[v]) {
            auto [u, cu] = edge;

            if (dist[v] + cu < dist[u]) {
                pq.erase({dist[u], u});
                dist[u] = dist[v] + cu;
                pq.insert({dist[u], u});
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    cin.tie(0);
    cout.tie(0);
    int64_t n, m;
    cin >> n >> m;

    graph.resize(n+1);
    dist.resize(n+1);

    for (int64_t i = 0; i < m; i++) {
        int64_t u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }

    dijkstra(1);

    cout << dist.back(); 
    return 0;
}