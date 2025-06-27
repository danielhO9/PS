#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int N; cin >> N;
    vector<string> v(N); for (int i = 0; i < N; ++i) cin >> v[i];
    bool flag = true;
    for (int i = 0; i < N; ++i) if (v[i] != "0") {
        flag = false;
        break;
    }
    if (flag) {
        cout << 0;
        return 0;
    }
    sort(v.begin(), v.end(), [](const string& a, const string& b) {
        string aa = a + b;
        string bb = b + a;
        return aa > bb;
    });
    for (int i = 0; i < N; ++i) 
    cout << v[i];
}