#include <bits/stdc++.h>
using namespace std;

void manacher(const string& S, vector<int>& A) {
	const int n = S.size();
	int r = -1, p = -1;
	for (int i = 0; i < n; ++i) {
		if (i < r) A[i] = min(A[2 * p - i], r - i);
		while (i - A[i] - 1 >= 0 && i + A[i] + 1 < n && S[i - A[i] - 1] == S[i + A[i] + 1]) ++A[i];
		if (r < i + A[i]) {
			r = i + A[i]; p = i;
		}
	}
}

// #a#b#c#d#e
// 각 지점을 중심으로 하는 반지름의 최댓값 = palindrome 길이
vector<int> palindrome(const string& S) {
	string tS = "";
	for (auto i: S) {
		tS += '#';
		tS += i;
	}
	tS += '#';
	const int n = tS.size();
	vector<int> A(n, 0);
	manacher(tS, A);
	return A;
}

void solve() {
	string S; cin >> S;
	vector<int> palin = palindrome(S);
	int ans = 0;
	for (int i = 0; i < palin.size(); ++i) {
		ans = max(ans, palin[i]);
	}
	cout << ans;
}