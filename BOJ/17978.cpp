#include <bits/stdc++.h>
using namespace std;
using ll = long long;
ll n, k;
vector<ll> r(100), g(100), b(100), r2(100), g2(100), b2(100);
ll rS = 0, gS = 0, bS = 0, S2 = 0;
double answer;

vector<vector<ll>> combinationContainer = {};

vector<ll> combinationTemp = {1, 1, 1};

void combinationMaker(vector<ll> combinationTable, ll x) {
    if (x == 3) {
        combinationContainer.push_back(combinationTable);
        return;
    }
    combinationMaker(combinationTable, x + 1);
    combinationTable[x] = 1 - combinationTable[x];
    combinationMaker(combinationTable, x + 1);
    combinationTable[x] = 1 - combinationTable[x];
}

vector<ll> crossProduct(const vector<ll>& x, const vector<ll>& y) { return {x[1] * y[2] - y[1] * x[2], y[0] * x[2] - x[0] * y[2], x[0] * y[1] - y[0] * x[1]}; }
ll dotProduct(const vector<ll>& x, const vector<ll>& y) { return x[0] * y[0] + x[1] * y[1] + x[2] * y[2]; }
ll rS_temp, gS_temp, bS_temp;
vector<ll> h;

double calValue(ll x, ll y, ll z) {
    double answer_temp = 3e9; ll cnt = 0;
    h = crossProduct({r[y] - r[x], g[y] - g[x], b[y] - b[x]}, {r[z] - r[x], g[z] - g[x], b[z] - b[x]});
    rS_temp = 0, gS_temp = 0, bS_temp = 0;
    for (ll i = 0; i < n; ++i) {
        if (i == x || i == y || i == z || dotProduct(h, {r[i] - r[x], g[i] - g[x], b[i] - b[x]}) > 0) {
            rS_temp += r[i]; gS_temp += g[i]; bS_temp += b[i]; cnt++;
        }
    }
    vector<ll> temp = {x, y, z};
    for (vector<ll> element: combinationContainer) {
        for (ll i = 0; i < 3; ++i) {
            if (element[i] == 0) {
                rS_temp -= r[temp[i]]; gS_temp -= g[temp[i]]; bS_temp -= b[temp[i]]; cnt--;
            }
        }
        if (cnt == 0) {
            answer_temp = min(answer_temp, S2 - ((rS - rS_temp) * (rS - rS_temp) + (gS - gS_temp) * (gS - gS_temp) + (bS - bS_temp) * (bS - bS_temp)) / static_cast<double>(n - cnt));
        } else if (n - cnt == 0) {
            answer_temp = min(answer_temp, S2 - (rS_temp * rS_temp + gS_temp * gS_temp + bS_temp * bS_temp) / static_cast<double>(cnt));
        } else {
            answer_temp = min(answer_temp, S2 - (rS_temp * rS_temp + gS_temp * gS_temp + bS_temp * bS_temp) / static_cast<double>(cnt) - ((rS - rS_temp) * (rS - rS_temp) + (gS - gS_temp) * (gS - gS_temp) + (bS - bS_temp) * (bS - bS_temp)) / static_cast<double>(n - cnt));
        }
        for (ll i = 0; i < 3; ++i) {
            if (element[i] == 0) {
                rS_temp += r[temp[i]]; gS_temp += g[temp[i]]; bS_temp += b[temp[i]]; cnt++;
            }
        }
    }
    return answer_temp;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    cout << fixed; cout.precision(6);
    cin >> n >> k;
    combinationMaker(combinationTemp, 0);
    for (ll i = 0; i < n; ++i) {
        cin >> r[i] >> g[i] >> b[i];
        r2[i] = r[i] * r[i]; g2[i] = g[i] * g[i]; b2[i] = b[i] * b[i];
        rS += r[i]; gS += g[i]; bS += b[i];
        S2 += r2[i] + g2[i] + b2[i];
    }
    if (n == 1) {
        cout << 0.0000;
    } else if (n == 2) {
        if (k == 1) {
            answer = S2 - (rS * rS + gS * gS + bS * bS) / 2.0;
            cout << answer;
        } else {
            cout << 0.0000;
        }
    } else {
        if (k == 1) {
            answer = S2 - (rS * rS + gS * gS + bS * bS) / static_cast<double>(n);
            cout << answer;
        } else {
            answer = 1e18;
            for (ll i = 0; i < n; ++i) {
                for (ll j = i + 1; j < n; ++j) {
                    for (ll k = j + 1; k < n; ++k) {
                        answer = min(answer, calValue(i, j, k));
                    }
                }
            }
            cout << answer;
        }
    }

    return 0;
}