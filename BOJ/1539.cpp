#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll N;
ll P[250000];
unordered_map<ll, bool> left_filled, right_filled;
unordered_map<ll, ll> height;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N;
    for (int i = 0; i < N; ++i) cin >> P[i];
    set<ll> s;
    ll answer = 1;
    s.insert(P[0]); height[P[0]] = 1;
    for (int i = 1; i < N; ++i) {
        auto itr = s.lower_bound(P[i]);
        ll itr_val;

        if (itr == s.end()) {
            --itr;
            itr_val = *itr;
            right_filled[itr_val] = true;
            height[P[i]] = height[itr_val] + 1;
            answer += height[P[i]];
            s.insert(P[i]);
            continue;
        }
        
        itr_val = *itr;
        if (!left_filled[itr_val]) {
            left_filled[itr_val] = true;
            height[P[i]] = height[itr_val] + 1;
            answer += height[P[i]];
        } else {
            --itr;
            itr_val = *itr;
            right_filled[itr_val] = true;
            height[P[i]] = height[itr_val] + 1;
            answer += height[P[i]];
        }
        s.insert(P[i]);
    }
    cout << answer;
}