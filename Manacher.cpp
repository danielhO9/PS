#include <bits/stdc++.h>
using namespace std;

void manacher(const string& s, vector<int>& A) {
	const int n = s.size();
	int r = -1, p = -1;
	for (int i = 0; i < n; ++i) {
		if (i < r) A[i] = min(A[2 * p - i], r - i);
		while (i - A[i] - 1 >= 0 && i + A[i] + 1 < n && s[i - A[i] - 1] == s[i + A[i] + 1]) ++A[i];
		if (r < i + A[i]) {
			r = i + A[i]; p = i;
		}
	}
}

// #a#b#c#d#e
// 각 지점을 중심으로 하는 반지름의 최댓값 = palindrome 길이
vector<int> palindrome(const string& S) {
	string ts = "";
	for (auto i: S) {
		ts += '#';
		ts += i;
	}
	ts += '#';
	const int n = ts.size();
	vector<int> A(n, 0);
	manacher(ts, A);
	return A;
}

void solve() {
	string s; cin >> s;
	vector<int> palin = palindrome(s);
	int ans = 0;
	for (int i = 0; i < palin.size(); ++i) {
		ans = max(ans, palin[i]);
	}
	cout << ans;
}