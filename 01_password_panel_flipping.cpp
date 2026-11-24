// Problem 01: Password Panel Flipping
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k, l;
    cin >> n >> k >> l;
    vector<int> x(k), a(l);
    for (int &v : x) cin >> v;
    for (int &v : a) cin >> v;

    vector<int> target;
    vector<int> parity(n + 2, 0);
    for (int p : x) {
        parity[p] ^= 1;
        parity[p + 1] ^= 1;
    }
    for (int p = 1; p <= n + 1; ++p)
        if (parity[p]) target.push_back(p);

    int t = (int)target.size();
    if (t == 0) {
        cout << 0 << '\n';
        return 0;
    }

    vector<vector<int>> dist(t, vector<int>(n + 2, -1));
    for (int i = 0; i < t; ++i) {
        queue<int> q;
        dist[i][target[i]] = 0;
        q.push(target[i]);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int len : a) {
                int v = u + len;
                if (v <= n + 1 && dist[i][v] == -1) {
                    dist[i][v] = dist[i][u] + 1;
                    q.push(v);
                }
                v = u - len;
                if (v >= 1 && dist[i][v] == -1) {
                    dist[i][v] = dist[i][u] + 1;
                    q.push(v);
                }
            }
        }
    }

    const int INF = 1e9;
    int states = 1 << t;
    vector<int> dp(states, INF);
    dp[0] = 0;
    for (int mask = 1; mask < states; ++mask) {
        int i = __builtin_ctz((unsigned)mask);
        int rest = mask ^ (1 << i);
        for (int j = i + 1; j < t; ++j) if (rest & (1 << j)) {
            int d = dist[i][target[j]];
            if (d < 0) continue;
            int sub = rest ^ (1 << j);
            if (dp[sub] != INF)
                dp[mask] = min(dp[mask], d + dp[sub]);
        }
    }

    cout << (dp[states - 1] == INF ? -1 : dp[states - 1]) << '\n';
    return 0;
}
