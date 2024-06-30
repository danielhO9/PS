#include <bits/stdc++.h>
using namespace std;

// 접미사 배열의 정렬
vector<int> suffixArray(const string& s) {
	const int MAX_N = s.size();
	vector<int> sfx(MAX_N);
	int m = 26;
	vector<int> cnt(max(MAX_N, m), 0), ord(MAX_N,0), pord(MAX_N,0);

	for (int i = 0; i < MAX_N; ++i) ++cnt[ord[i] = s[i] - 'a'];
	for (int i = 1; i < m; ++i) cnt[i] += cnt[i - 1];
	for (int i = MAX_N - 1; i >= 0; --i) sfx[--cnt[ord[i]]] = i;
	int now = 1, idx = 0;
	while (true) {
		if (idx == MAX_N - 1) break;
		m = idx + 1; idx = 0;
		for (int i = MAX_N - now; i < MAX_N; ++i) pord[idx++] = i;
		for (int i = 0; i < MAX_N; ++i) if (sfx[i] >= now) pord[idx++] = sfx[i] - now;
		for (int i = 0; i < m; ++i) cnt[i] = 0;
		for (int i = 0; i < MAX_N; ++i) ++cnt[ord[pord[i]]];
		for (int i = 1; i < m; ++i) cnt[i] += cnt[i - 1];
		for (int i = MAX_N - 1; i >= 0; --i) sfx[--cnt[ord[pord[i]]]] = pord[i];
		
		pord = vector<int>(ord.begin(), ord.end()); idx = 0;
		ord[sfx[0]] = 0;
		for (int i = 1; i < MAX_N; ++i) {
			if (sfx[i - 1] + now >= MAX_N || sfx[i] + now >= MAX_N || pord[sfx[i - 1]] != pord[sfx[i]] || pord[sfx[i - 1] + now] != pord[sfx[i] + now]) ++idx;
			ord[sfx[i]] = idx;
		}
		now *= 2;
	}
	return sfx;
}

// i번째와 i - 1번째 sfx에서 lcm 길이
vector<int> commomPrefix(const string& s, const vector<int>& sfx) {
	const int MAX_N = s.size();
	vector<int> inv(MAX_N), lcp(MAX_N);
	for (int i = 0; i < MAX_N; ++i) inv[sfx[i]] = i;
	int h = 0;
	for(int i = 0; i < MAX_N; ++i){
		if(inv[i]){
			int prv = sfx[inv[i] - 1];
			while(s[prv + h] == s[i + h]) ++h;
			lcp[inv[i]] = h;
		}
		h = max(h - 1, 0);
	}
	return lcp;
}

void solve() {
	int _; cin >> _;
	string S; cin >> S;
	vector<int> sfx = suffixArray(S);
	vector<int> lcp = commomPrefix(S, sfx);
	cout << *max_element(lcp.begin(), lcp.end());
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}