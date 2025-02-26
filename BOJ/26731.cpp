#include <bits/stdc++.h>
using namespace std;

int vis[26];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	string s; cin >> s;
	for (auto i: s) vis[i - 'A'] = true;
	for (int i = 0; i < 26; ++i) if (!vis[i]) cout << (char) ('A' + i);
}