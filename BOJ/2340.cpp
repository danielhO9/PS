#include <bits/stdc++.h>
using namespace std;

int N;
string s;
int sm[50000];
map<deque<char>, pair<int, int>> m;

pair<int, int> getRange(deque<char>& dq) {
	if (m.find(dq) != m.end()) return m[dq];
	if (dq.back() == '1') {
		dq.pop_back();
		auto prv = getRange(dq);
		dq.push_back('0');
		auto rem = getRange(dq);
		dq.pop_back();
		dq.push_back('1');
		return m[dq] = {rem.second, prv.second};
	}
	auto l = dq.back(); dq.pop_back();
	auto prv = getRange(dq); dq.push_back(l);
	auto f = dq.front(); dq.pop_front();
	auto range = getRange(dq); dq.push_front(f);
	int val = (range.second - 1 >= 0 ? sm[range.second - 1] : 0) - (range.first - 1 >= 0 ? sm[range.first - 1] : 0);
	if (f == '1') val = range.second - range.first - val;
	return m[dq] = {prv.first, prv.first + val};
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N; cin >> s;
	N = 500;
	for (int i = 0; i < N; ++i) s += '0' + (i % 1231 == 0);
	sm[0] = (s[0] == '0');
	for (int i = 1; i < N; ++i) sm[i] = sm[i - 1] + (s[i] == '0');
	int zcnt = sm[N - 1];
	if (zcnt == N || zcnt == 0) {
		string ans;
		for (int i = 0; i < N; ++i) ans += (zcnt == 0 ? '1' : '0');
		cout << ans;
		return 0;
	}
	m[{'0'}] = {0, zcnt};
	m[{'1'}] = {zcnt, N};
	deque<char> cur = {'0'};
	while (cur.size() != N) {
		cur.push_back('0');
		auto range = getRange(cur);
		// for (auto i: cur) cout << i;
		// cout << '\n';
		// cout << range.first << ' ' << range.second << '\n';
		if (range.second - range.first > 0) continue;
		cur.pop_back();
		cur.push_back('1');
	}
	for (auto i: cur) cout << i;
	cout << '\n' << ' ' << m.size();
}

/*
in:
100
1111101000111110100011111010001111101000111110100011111010001111101000111110100011111010001111101000

out:
0101011011

5
10010

00101011
*/