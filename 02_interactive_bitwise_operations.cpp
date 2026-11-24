// Problem 02: Interactive Bitwise Operations
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!(cin >> T)) return 0;
    const int B = 30;
    const int MASK = (1 << B) - 1;

    int x = 0;
    for (int i = 0; i < B; i += 2) x |= (1 << i);
    int inv = MASK ^ x;

    while (T--) {
        cout << x << endl;
        int o;
        if (!(cin >> o) || o == -1) return 0;

        bool is_and = false, is_or = false;
        for (int b = 0; b < B; ++b) {
            bool xb = (x >> b) & 1;
            bool ob = (o >> b) & 1;
            if (xb && !ob) is_and = true;
            if (!xb && ob) is_or = true;
        }

        cout << inv << ' ' << x << endl;
        int r;
        if (!(cin >> r) || r == -1) return 0;

        int b;
        if (is_and) {
            int bit = __builtin_ctz((unsigned)x);
            bool rb = (r >> bit) & 1;
            bool ob = (o >> bit) & 1;
            b = (rb == ob ? 0 : 1);
        } else if (is_or) {
            int bit = __builtin_ctz((unsigned)(inv));
            bool rb = (r >> bit) & 1;
            bool ob = (o >> bit) & 1;
            b = (rb != ob ? 0 : 1);
        } else {
            b = (r == MASK ? 0 : 1);
        }
        cout << b << endl;
    }
    return 0;
}
