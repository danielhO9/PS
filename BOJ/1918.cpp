#include <bits/stdc++.h>
using namespace std;

string s;
stack<char> Q;

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> s;
	for (char i: s) {
		if ('A' <= i && i <= 'Z') {
			cout << i;
		} else if (i == ')') {
			while (!Q.empty() && Q.top() != '(') {
				cout << Q.top();
				Q.pop();
			}
			Q.pop();
		} else if (i == '+' || i == '-') {
			while (!Q.empty() && Q.top() != '(') {
				cout << Q.top();
				Q.pop();
			}
			Q.push(i);
		} else if (i == '(') Q.push(i);
		else if (i == '*' || i == '/') {
			if (!Q.empty() && (Q.top() == '*' || Q.top() == '/')) {
				cout << Q.top();
				Q.pop();
			}
			Q.push(i);
		}
	}
	while (!Q.empty()) {
		cout << Q.top();
		Q.pop();
	}
}