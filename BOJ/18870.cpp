#include <bits/stdc++.h>
using namespace std;
int X[1000000], Y[1000000], N;

int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;
    for (int i = 0; i < N; ++i) { cin >> X[i]; Y[i] = X[i]; } sort(Y, Y + N);
    vector<int> st;
    for (int i = 0; i < N; ++i) if (st.empty() || st.back() != Y[i]) st.push_back(Y[i]);
    for (int i = 0; i < N; ++i) {
        cout << lower_bound(st.begin(), st.end(), X[i]) - st.begin() << " ";
    }
    return 0;
}