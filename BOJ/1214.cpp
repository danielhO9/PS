#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ll D, P, Q; cin >> D >> P >> Q;
    ll big = max(P, Q); ll small = min(P, Q);
    ll dif = small;
    ll temp = D;
    if (temp > 2 * P * Q) {
        temp %= (P * Q);
        temp += (P * Q);
    }
    if (temp % big == 0) dif = 0;
    else {
        for (ll i = 0; i < (temp / big) + 2; ++i) {
            if (big * i > temp) {
                dif = min(dif, big * i - temp);
            } else {
                if ((temp - big * i) % small == 0) dif = 0;
                else {
                    dif = min(dif, (((temp - big * i) / small) + 1) * small + big * i - temp);
                }
            }
        }
    }
    cout << D + dif;
    return 0;
}