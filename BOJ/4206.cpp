#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll N;
string p;
vector<string> fibo;
ll cache[101];

void init() {
	fibo.push_back("0");
	fibo.push_back("1");
	string pprv = "0", prv = "1";
	while (true) {
		string now = prv + pprv;
		fibo.push_back(now);
		pprv = prv; prv = now;
		if (now.size() >= 1e5) break;
	}
	fibo.push_back(prv + pprv);
	// for (auto i: fibo) cout << i.size() << ' ';
}

// N[...i] 접두사와 접미사가 같은 최대 길이(본인 제외)
vector<int> getPartialMatch(const string& N) {
	int m = N.size(); 
	vector<int> pi(m, 0);
	int begin = 1, matched = 0;
	while (begin + matched < m) {
		if (N[begin + matched] == N[matched]) {
			++matched;
			pi[begin + matched - 1] = matched;
		} else {
			if (matched == 0) ++begin;
			else {
				begin += matched - pi[matched - 1];
				matched = pi[matched - 1];
			}
		}
	}
	return pi;
}

// 짚더미 H의 부분 문자열이 바늘 N인 index
ll kmpSearch(const string& H, const string& N, vector<int>& pi, int l, int r) {
	int n = H.size(), m = N.size();
	ll ans = 0;
	int begin = 0, matched = 0;
	while (begin <= n - m) {
		if (matched < m && H[begin + matched] == N[matched]) {
			++matched;
			if (matched == m) {
				if (l <= begin && begin <= r) ++ans;
			}
		} else {
			if (matched == 0) ++begin;
			else {
				begin += matched - pi[matched - 1];
				matched = pi[matched - 1];
			}
		}
	}
	return ans;
}

void solve() {
	vector<int> pi = getPartialMatch(p);
	int m = p.size();
	int idx = 0;
	memset(cache, 0, sizeof(cache));
	while (fibo[idx].size() < p.size()) ++idx;
	int nxt = idx + 1;
	cache[idx] = kmpSearch(fibo[idx], p, pi, 0, fibo[idx].size());
	cache[nxt] = kmpSearch(fibo[nxt], p, pi, 0, fibo[nxt].size());
	ll sf = kmpSearch(fibo[nxt] + fibo[idx], p, pi, (int)fibo[nxt].size() - m + 1, (int)fibo[nxt].size() - 1);
	ll ss = kmpSearch(fibo[nxt] + fibo[nxt], p, pi, (int)fibo[nxt].size() - m + 1, (int)fibo[nxt].size() - 1);
	ll fs = kmpSearch(fibo[idx] + fibo[idx], p, pi, (int)fibo[idx].size() - m + 1, (int)fibo[idx].size() - 1);
	if (nxt + 1 <= N) cache[nxt + 1] = cache[idx] + cache[nxt] + sf;
	ll rem[2] = {fs, ss};
	ll t = 0;
	for (int i = nxt + 2; i <= N; ++i) {
		cache[i] = cache[i - 1] + cache[i - 2] + rem[t];
		t = 1 - t;
	}
	cout << cache[N] << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	init();
	int cnt = 0;
	while (cin >> N >> p) {
		cout << "Case " << ++cnt << ": ";
		solve();
	}
}

/*
1 = f
2 = s
3 = s + f   ... sf
4 = sf + s  ... fs
5 = sfs + sf  ... ss
6 = sfssf + sfs ... fs
7 = sfssfsfs + sfssf ... ss
*/