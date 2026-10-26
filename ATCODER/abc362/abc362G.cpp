#include <bits/stdc++.h>
using namespace std;

string S;

// 접미사 배열의 정렬
vector<int> suffixArray(const string& s) {
	const int MAX_N = s.size();
	vector<int> sfx(MAX_N);
	int m = 27;
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

vector<int> SA;

int binary_search(string T) {
	int l = -1, r = S.size();
	while (l + 1 < r) {
		int mid = (l + r) / 2;
		if (S.substr(SA[mid], T.size()) < T) {
			l = mid;
		}
		else r = mid;
	}
	// if (l != -1) cout << l << ' ' << S.substr(SA[l], T.size()) << ' ' << T << '\n';
	return l;
}

void solve() {
	cin >> S;
	int Q; cin >> Q;
	SA = suffixArray(S);
	for (int i = 0; i < Q; ++i) {
		string ttmp; cin >> ttmp;
		cout << binary_search(ttmp + '{') - binary_search(ttmp) << '\n';
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}

/*
missisippi

i
ippi
isippi
issisippi
missisippi
pi
ppi
sippi
sisippi
ssisippi

*/