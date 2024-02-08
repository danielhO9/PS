#include <bits/stdc++.h>
using namespace std;
string W, S; int N;
int cache[101][101];
vector<string> ans;

bool matchMemoized(int w, int s) {
    int& ret = cache[w][s];
    if (ret != -1) return cache[w][s];
    if (w == W.size()) return ret = (s == S.size());
    if (s < S.size() && w < W.size() && (W[w] == '?' || W[w] == S[s])) return ret = matchMemoized(w + 1, s + 1);
    if (W[w] == '*') {
        if (matchMemoized(w + 1, s) || (s < S.size() && matchMemoized(w, s + 1))) return ret = 1;
        return ret = 0;
    }
    return ret = 0;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int C; cin >> C;
    for (int i = 0; i < C; ++i) {
        cin >> W >> N;
        for (int j = 0; j < N; ++j) {
            memset(cache, -1, sizeof(cache));
            cin >> S;
            if (matchMemoized(0, 0)) ans.push_back(S);
        }
        sort(ans.begin(), ans.end());
        for (string answer: ans) cout << answer << "\n";
        ans.clear();
    }
    return 0;
}