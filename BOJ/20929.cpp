#include <bits/stdc++.h>
using namespace std;

int N;
int l1, r1, l2, r2;

void dnc() {
    int sz = r1 - l1 + 1;
    // cout << "sz: " << sz << '\n';
    int l = sz / 2 + l1 - 1;
    int r = sz / 2 + l2 - 1;
    if (sz == 1) {
        l = l1;
        r = l2;
    }
    cout << "? A " << l << '\n'; cout.flush();
    int lval; cin >> lval;
    cout << "? B " << r << '\n'; cout.flush();
    int rval; cin >> rval;
    if (sz == 1) {
        cout << "! " << min(lval, rval) << '\n';
        cout.flush();
        return;
    }
    if (lval < rval) {
        l1 = l + 1;
        r2 = r;
    } else {
        r1 = l;
        l2 = r + 1;
    }
    dnc();
}

int main() {
    // ios::sync_with_stdio(0); cin.tie(0);
    cin >> N;
    l1 = 1, r1 = N, l2 = 1, r2 = N;
    dnc();
}