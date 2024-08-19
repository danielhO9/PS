#include <bits/stdc++.h>
using namespace std;

// 접미사 배열의 정렬
// https://gist.github.com/koosaga/44532e5dec947132ee55da0458255e05
vector<int> getSuffixArray(string& s) {
	int m = 255;
	const int n = s.size();
	int t = 1;
	vector<int> group(n + 1), sfx(n), newGroup(n + 1), nxtord(n + 1);
	int cnt[max(m, n) + 1];
	
	for(int i = 0; i < n; ++i) group[i] = s[i];
	
	int pt = 1;
	while (true) {
		// nxtord: i를 group[i + t]로 정렬
		memset(cnt, 0, sizeof(cnt));
		for (int i = 0; i < n; ++i) ++cnt[group[min(i + t, n)]];
		for (int i = 1; i <= n || i <= m; ++i) cnt[i] += cnt[i - 1];
		for (int i = 0; i < n; ++i) nxtord[--cnt[group[min(i + t, n)]]] = i;

		// nxtord가 큰 i부터 뒤에서 채움
		memset(cnt, 0, sizeof(cnt));
		for (int i = 0; i < n; ++i) ++cnt[group[i]];
		for (int i = 1; i <= n || i <= m; ++i) cnt[i] += cnt[i - 1];
		for (int i = n - 1; i >= 0; --i) sfx[--cnt[group[nxtord[i]]]] = nxtord[i];

		if(pt == n) break;
		pt = 1; newGroup[sfx[0]] = 1;
		for(int i = 1; i < n; ++i){
			if(group[sfx[i - 1]] != group[sfx[i]] || group[min(sfx[i - 1] + t, n)] != group[min(sfx[i] + t, n)]) ++pt;
			newGroup[sfx[i]] = pt;
		}
		group = vector<int>(newGroup.begin(), newGroup.end());
		t *= 2;
	}
	return sfx;
}

void solve() {
	string s; cin >> s;
    int n = s.size();

	vector<int> sfx = getSuffixArray(s);
    vector<int> inv(n + 1);
    for (int i = 0; i < n; ++i) inv[sfx[i]] = i;
    inv[n] = -1;
    string S = s;
    S[0] = 'a';
    char now = 'a';
    for (int i = 0; i + 1 < n; ++i) {
        if (inv[sfx[i] + 1] < inv[sfx[i + 1] + 1]) S[sfx[i + 1]] = now;
        else {
            if (now == 'z') {
                cout << 0;
                return;
            }
            S[sfx[i + 1]] = ++now;
        }
    }
    for (int i = 0; i < n; ++i) {
        if (s[i] != S[i]) {
            cout << 1; return;
        }
    }
    cout << 0;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}