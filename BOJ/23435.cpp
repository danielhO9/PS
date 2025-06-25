#include <bits/stdc++.h>
using namespace std;

vector<int> arr[100000];
int N, mn;
vector<int> v;

int query(int i, int j) {
    cout << "? " << i << ' ' << j << '\n';
    cout.flush();
    char c; cin >> c;
    return c == '<';
}

void dnc() {
    int sz = v.size();
    if (sz == 1) {
        mn = v[0];
        return;
    }
    vector<int> nv;
    for (int i = 0; i < sz / 2; ++i) {
        int ret = query(v[i], v[i + sz / 2]);
        if (ret == 1) {
            arr[v[i]].push_back(v[i + sz / 2]);
            nv.push_back(v[i]);
        } else {
            arr[v[i + sz / 2]].push_back(v[i]);
            nv.push_back(v[i + sz / 2]);
        }
    }
    if (sz % 2) nv.push_back(v.back());
    swap(nv, v);
    dnc();
}

int main() {
    cin >> N;
    for (int i = 0; i < N; ++i) v.push_back(i);
    dnc();
    int ans = arr[mn][0];
    for (int i = 1; i < arr[mn].size(); ++i) {
        int ret = query(ans, arr[mn][i]);
        if (!ret) ans = arr[mn][i];
    }
    cout << "! " << ans << '\n';
    cout.flush();
}