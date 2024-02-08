#include <bits/stdc++.h>
using namespace std;
string p; int n; bool rev;
deque<int> Q;

string solution() {
    for (auto i: p) {
        if (i == 'R') rev = 1 - rev;
        else {
            if (Q.empty()) return "error";
            if (rev) Q.pop_back();
            else Q.pop_front();
        }
    }
    string ans = "";
    if (rev) {
        ans = "";
        for (auto i: Q) {
            ans = "," + ans;
            ans = to_string(i) + ans;
        }
        if (ans != "") ans.pop_back();
        ans += "]";
        ans = "[" + ans;
    } else {
        ans = "";
        for (auto i: Q) {
            ans += to_string(i);
            ans += ",";
        }
        if (ans != "") ans.pop_back();
        ans += "]";
        ans = "[" + ans;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int T; cin >> T; string itemp = "", otemp = "";
    for (int i = 0; i < T; ++i) {
        cin >> p;
        cin >> n;
        cin >> itemp;
        for (auto j: itemp) {
            if ('0' <= j && j <= '9') otemp += j;
            else {
                if (otemp != "") Q.push_back(stoi(otemp));
                otemp = "";
            }
        }
        cout << solution() << "\n";
        rev = false; Q.clear();
    }
}