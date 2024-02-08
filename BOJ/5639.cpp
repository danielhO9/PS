#include <bits/stdc++.h>
using namespace std;

int l[1000000], r[1000000];
vector<int> arr;
vector<int> Q;

void output(int v) {
	if (l[v] != 0) output(l[v]);
	if (r[v] != 0) output(r[v]);
	if (v != 0) cout << v << "\n";
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int temp;
	while (cin >> temp) arr.push_back(temp);
	for (auto i: arr) {
		if (Q.empty()) { Q.push_back(i); continue; }
		if (Q.back() > i) {
			l[Q.back()] = i;
			Q.push_back(i);
		} else {
			while (Q.size() > 1 && *prev(prev(Q.end())) < i) Q.pop_back();
			r[Q.back()] = i;
			Q.pop_back();
			Q.push_back(i);
		}
	}
	output(arr[0]);
}