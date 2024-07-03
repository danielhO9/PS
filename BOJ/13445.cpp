#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll cnt = 0;
int K;

struct TrieNode {
	TrieNode* children[2];
	ll terminal;
	TrieNode(): terminal(0) {
		memset(children, 0, sizeof(children));
	}
	~TrieNode() {
		for (int i = 0; i < 2; ++i) if (children[i]) delete children[i];
	}
	void insert(const char* key) {
		++this->terminal;
		if (*key == 0) return;
		else {
			int next = *key - '0';
			if (children[next] == NULL) children[next] = new TrieNode();
			children[next]->insert(key + 1);
		}
	}
	void query(const char* key, int dep, int num) {
		if (*key == 0) {
			cnt += this->terminal;
			return;
		}
		int next = *key - '0';
		int rev = 1 - next;

		if (num + (1 << (dep + 1)) - 1 < K) {
			cnt += this->terminal;
			return;
		}
		if (num + (1 << dep) < K && children[rev]) children[rev]->query(key + 1, dep - 1, num + (1 << dep));
		if (children[next]) children[next]->query(key + 1, dep - 1, num);
	}
};

void solve() {
	TrieNode* trie = new TrieNode();
	int N; cin >> N >> K;
	int sum = 0;
	string s;
	for (int j = 16; j >= 0; --j) s += '0';
	trie->insert(s.c_str());

	for (int i = 0; i < N; ++i) {
		int A; cin >> A;
		A ^= sum;
		sum = A;
		string s;
		for (int j = 16; j >= 0; --j) {
			if ((A >> j) & 1) s += '1';
			else s += '0';
		}
		trie->query(s.c_str(), 16, 0);
		trie->insert(s.c_str());
	}
	cout << cnt << '\n';
	delete trie;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}