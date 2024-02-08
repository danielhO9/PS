#include <bits/stdc++.h>
using namespace std;

int N;
map<string, pair<string, string>> pre;

void preorder(string v) {
	cout << v;
	if (pre[v].first != ".") preorder(pre[v].first);
	if (pre[v].second != ".") preorder(pre[v].second);
}

void inorder(string v) {
	if (pre[v].first != ".") inorder(pre[v].first);
	cout << v;
	if (pre[v].second != ".") inorder(pre[v].second);
}

void postorder(string v) {
	if (pre[v].first != ".") postorder(pre[v].first);
	if (pre[v].second != ".") postorder(pre[v].second);
	cout << v;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N;
	string a, b, c;
	for (int i = 0; i < N; ++i) {
		cin >> a >> b >> c;
		pre[a] = {b, c};
	}
	preorder("A");
	cout << "\n";
	inorder("A");
	cout << "\n";
	postorder("A");
}