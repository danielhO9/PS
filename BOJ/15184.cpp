#include <bits/stdc++.h>
using namespace std;

int cnt[26];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	string s; getline(cin, s);
	for (char i: s) {
		if ('A' <= i && i <= 'Z') ++cnt[i - 'A'];
		if ('a' <= i && i <= 'z') ++cnt[i - 'a'];
	}
	for (int i = 0; i < 26; ++i) {
		cout << (char) ('A' + i) << " | ";
		for (int j = 0; j < cnt[i]; ++j) cout << "*";
		cout << '\n';
	}
}