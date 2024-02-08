#include <bits/stdc++.h>
using namespace std;
int n, c[100000], nc[100000];
pair<int, int> protocol[100000];

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> c[i];
    for (int i = 1; i < n; ++i) cin >> protocol[i].first >> protocol[i].second;
    for (int i = n - 1; i > 0; --i) {
        if (protocol[i].second == 0) {
            c[protocol[i].first] += nc[i];
            nc[protocol[i].first] += max(c[i], nc[i]);
        } else if (protocol[i].second == 1) {
            c[protocol[i].first] = max({nc[i] + c[protocol[i].first], c[i] + nc[protocol[i].first], c[protocol[i].first] + c[i]});
            nc[protocol[i].first] += nc[i];
        } else {
            c[protocol[i].first] = max(nc[i] + c[protocol[i].first], c[i] + nc[protocol[i].first]);
            nc[protocol[i].first] += nc[i];
        }
    }
    cout << max(c[0], nc[0]);
    return 0;
}