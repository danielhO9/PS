#include <bits/stdc++.h>
using namespace std;

int N;
string S;
int t[50000];

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
	cin >> N >> S;
	int zcnt = 0;
	for (int i = 0; i < N; ++i) if (S[i] == '0') ++zcnt;
	int zcur = 0, ocur = zcnt;
	for (int i = 0; i < N; ++i) {
		if (S[i] == '0') t[i] = zcur++;
		else t[i] = ocur++;
	}
	int cur = 0;
	string ans;
	for (int i = 0; i < N; ++i) {
		ans += S[cur];
		cur = t[cur];
	}
	reverse(ans.begin(), ans.end());
	string tans = ans; tans += ans;
	auto sfx = getSuffixArray(tans);
	string tmp;
	for (auto i: sfx) if (i < N) tmp += tans[i + N - 1];
	if (tmp != S) cout << -1;
	else cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}