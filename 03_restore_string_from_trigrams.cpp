// Problem 03: Restore a String from 3-letter Substrings
#include <bits/stdc++.h>
using namespace std;

struct Edge { int to, id; char last; };

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<Edge>> g(62 * 62);
    auto code = [](char c) {
        if ('a' <= c && c <= 'z') return c - 'a';
        if ('A' <= c && c <= 'Z') return c - 'A' + 26;
        return c - '0' + 52;
    };

    vector<int> in(62 * 62), out(62 * 62);
    for (int i = 0; i < n; ++i) {
        string s; cin >> s;
        int u = code(s[0]) * 62 + code(s[1]);
        int v = code(s[1]) * 62 + code(s[2]);
        g[u].push_back({v, i, s[2]});
        ++out[u]; ++in[v];
    }

    int start = -1, plus = 0, minus = 0;
    for (int v = 0; v < 62 * 62; ++v) {
        if (out[v] - in[v] == 1) { start = v; ++plus; }
        else if (in[v] - out[v] == 1) ++minus;
        else if (in[v] != out[v]) { cout << "NO\n"; return 0; }
    }
    if (!((plus == 1 && minus == 1) || (plus == 0 && minus == 0))) {
        cout << "NO\n"; return 0;
    }
    if (start == -1) {
        for (int v = 0; v < 62 * 62; ++v)
            if (out[v]) { start = v; break; }
    }
    if (start == -1) { cout << "NO\n"; return 0; }

    vector<int> nodeStack{start};
    vector<char> charStack;
    vector<char> answer;
    vector<int> used;
    while (!nodeStack.empty()) {
        int u = nodeStack.back();
        if (!g[u].empty()) {
            Edge e = g[u].back(); g[u].pop_back();
            nodeStack.push_back(e.to);
            charStack.push_back(e.last);
        } else {
            nodeStack.pop_back();
            if (!charStack.empty()) {
                answer.push_back(charStack.back());
                charStack.pop_back();
            }
        }
    }

    vector<int> it(62 * 62, 0), st{start}, path;
    vector<vector<int>> adj(62 * 62);
    for (int u = 0; u < 62 * 62; ++u)
        for (auto &e : g[u]) (void)e;
    if ((int)answer.size() != n) { cout << "NO\n"; return 0; }
    reverse(answer.begin(), answer.end());

    auto decode = [](int x) -> char {
        if (x < 26) return char('a' + x);
        if (x < 52) return char('A' + x - 26);
        return char('0' + x - 52);
    };
    string res;
    res += decode(start / 62);
    res += decode(start % 62);
    for (char c : answer) res += c;
    cout << "YES\n" << res << '\n';
    return 0;
}
