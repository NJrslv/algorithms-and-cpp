#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

const size_t N = 3001, M = 301;

struct Detail {
    int id;
    int k;
    array < pair < int, int64_t >, M > steps;
};

int n, m;
array < Detail, N > ds;
array < int64_t, M > load;
array < array < int64_t, N >, M > res;

void Job_Shop_m_machines_2_jobs (const Detail& d1, const Detail& d2) {
    int64_t t1 = 0, t2 = 0;

    for(int i1 = 1, i2 = 1; i1 <= d1.k || i2 <= d2.k; ) {
        auto step1 = (i1 > d1.k) ? make_pair<int, int64_t>(m + 1, 0) : d1.steps[i1];
        auto step2 = (i2 > d2.k) ? make_pair<int, int64_t>(m + 1, 0) : d2.steps[i2];

        if (step1.first == m + 1) {
            load[step2.first] < t2 ? load[step2.first] = t2 + step2.second : load[step2.first] += step2.second;
            ++i2;
        } else if (step2.first == m + 1) {
            load[step1.first] < t1 ? load[step1.first] = t1 + step1.second : load[step1.first] += step1.second;
            ++i1;
        } else if(step1.first != step2.first) {
            load[step2.first] < t2 ? load[step2.first] = t2 + step2.second : load[step2.first] += step2.second;
            load[step1.first] < t1 ? load[step1.first] = t1 + step1.second : load[step1.first] += step1.second;
            ++i1, ++i2;
        } else {
            if(step1.second > step2.second) {
                load[step1.first] < t1 ? load[step1.first] = t1 + step1.second : load[step1.first] += step1.second;
                ++i1;
            } else {
                load[step2.first] < t2 ? load[step2.first] = t2 + step2.second : load[step2.first] += step2.second;
                ++i2;
            }
        }
        
        res[step2.first][d2.id] = load[step2.first] - step2.second;
        res[step1.first][d1.id] = load[step1.first] - step1.second;
        t1 = load[step1.first], t2 = load[step2.first];
    }
}

int64_t Job_Shop_m_machines_n_jobs() {
    for(int i = 1; i + 1 <= n; i += 2)
        Job_Shop_m_machines_2_jobs(ds[i], ds[i + 1]);
    
    if(n % 2) {
        Detail dummy;
        dummy.k = 0;
        dummy.id = 0;
        dummy.steps = {};
        Job_Shop_m_machines_2_jobs(ds[n], dummy);
    }

    return *max_element(begin(load), end(load));
}


int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    cin >> n >> m;

    for(int i = 1; i <= n; ++i) {
        int k;
        cin >> k;
        ds[i].id = i;
        ds[i].k = k;
        for (int j = 1; j <= k; ++j) {
            int machine;
            int64_t processingTime;
            cin >> machine >> processingTime;
            ds[i].steps[j] = {machine, processingTime};
        }
    }

    cout << Job_Shop_m_machines_n_jobs() << "\n";
    for(int i = 1; i <= m; ++i) {
        for(int j = 1; j <= n; ++j) {
            cout << res[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}
