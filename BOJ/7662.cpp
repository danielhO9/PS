#include <bits/stdc++.h>
using namespace std;
multiset<int> Q; int k;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int T; cin >> T; string temp; int num;
    for (int i = 0; i < T; ++i) {
        cin >> k;
        for (int j = 0; j < k; ++j) {
            cin >> temp; cin >> num;
            if (temp == "I") Q.insert(num);
            else {
                if (num == 1 && !Q.empty()) Q.erase(--Q.end());
                else if (num == -1 && !Q.empty()) Q.erase(Q.begin());
            }
            // for (auto l: Q) { cout << l << " "; } cout << "\n";
        }
        if (Q.empty()) cout << "EMPTY" << "\n";
        else cout << *(--Q.end()) << " " << *(Q.begin()) << "\n";
        Q.clear();
    }
}