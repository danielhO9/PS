#include <bits/stdc++.h>
using namespace std;

int n;
int a[100000];
vector<string> ans;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i];
    if (n == 1) {
        cout << a[0];
        return 0;
    }
    vector<int> na;
    for (int i = 0; i < n; ++i) if (a[i] != 1 && a[i] != 2) na.push_back(a[i]);

    int o = 0, t = 0;
    for (int i = 0; i < n; ++i) {
        if (a[i] == 1) ++o;
        if (a[i] == 2) ++t;
    }
    int ot = min(o, t);
    o -= ot; t -= ot;
    for (auto i: na) ans.push_back(to_string(i));
    for (int i = 0; i < ot; ++i) ans.push_back("(1+2)");
    if (o == 0) {
        for (int i = 0; i < t; ++i) ans.push_back("2");
    } else {
        if (o == 1) {
            if (ot > 0) ans.back() = "(1+1+2)";
            else {
                int mn = INT32_MAX, idx = -1;
                for (int i = 0; i < na.size(); ++i) if (na[i] < mn) {
                    mn = na[i];
                    idx = i;
                }
                ans[idx] = "(1+" + ans[idx] + ")";
            }
        } else {
            while (o) {
                if (o == 4) {
                    ans.push_back("(1+1)");
                    ans.push_back("(1+1)");
                    o = 0;
                    break;
                }
                if (o == 2) {
                    ans.push_back("(1+1)");
                    o = 0;
                    break;
                }
                o -= 3;
                ans.push_back("(1+1+1)");
            }
        }
    }
    for (int i = 0; i < ans.size(); ++i) {
        cout << ans[i];
        if (i + 1 != ans.size()) cout << '*';
    }
    

}