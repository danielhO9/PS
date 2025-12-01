#include <bits/stdc++.h>
using namespace std;

int n, m;
int a[100], b[100];
int na[101], nb[101];

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m;
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < m; ++i) cin >> b[i];

    for (int i = 0; i < n; ++i) na[i] = a[i];
    for (int i = 0; i < m; ++i) nb[i] = b[i];

    na[n] = nb[m] = n + m + 1;
    for (int i = n - 1; i >= 0; --i) if (na[i] == 0) na[i] = na[i + 1];
    for (int i = m - 1; i >= 0; --i) if (nb[i] == 0) nb[i] = nb[i + 1];

    int ai = 0, bi = 0;
    int num = 1;
    while (true) {

        if (ai == n && bi == m) break;
        if (ai == n) {
            b[bi++] = num++;
            continue;
        }
        if (bi == m) {
            a[ai++] = num++;
            continue;
        }

        if (a[ai] == num) {
            ++ai;
            ++num;
            continue;
        }
        if (b[bi] == num) {
            ++bi;
            ++num;
            continue;
        }

        // bigger than num or empty
        if (a[ai] != 0) {
            b[bi++] = num++;
            continue;
        }
        if (b[bi] != 0) {
            a[ai++] = num++;
            continue;
        }

        if (na[ai] < nb[bi]) {
            a[ai++] = num++;
        } else {
            b[bi++] = num++;
        }
    }
    for (int i = 0; i < n; ++i) cout << a[i] << ' ';
    cout << '\n';
    for (int i = 0; i < m; ++i) cout << b[i] << ' ';
}