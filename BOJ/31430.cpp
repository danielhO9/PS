#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    if (t == 1) {
        long long A, B; cin >> A >> B;
        A += B;
        string s;
        while (A) {
            s += 'a' + (A % 26ll);
            A /= 26ll;
        }
        while (s.size() < 13) s += 'a';
        cout << s;
    } else {
        string s; cin >> s;
        long long A = 0;
        reverse(s.begin(), s.end());
        for (auto i: s) {
            long long tmp = i - 'a';
            A *= 26ll;
            A += tmp;
        }
        cout << A;
    }
}