#include <bits/stdc++.h>
using namespace std;

const int ALPHABETS = 26;

int toNumber(char ch) { return ch - 'a'; }

struct TrieNode {
	TrieNode* children[ALPHABETS];
	bool terminal;
	TrieNode(): terminal(false) {
		memset(children, 0, sizeof(children));
	}
	~TrieNode() {
		for (int i = 0; i < ALPHABETS; ++i) {
			if (children[i]) delete children[i];
		}
	}
	void insert(const char* key) {
		if (*key == 0) terminal = true;
		else {
			int next = toNumber(*key);
			if (children[next] == NULL) children[next] = new TrieNode();
			children[next]->insert(key + 1);
		}
	}
	TrieNode* find(const char* key) {
		if (*key == 0) return this;
		int next = toNumber(*key);
		if (children[next] == NULL) return NULL;
		return children[next]->find(key + 1);
	}
};

void solve() {
	int N, M; cin >> N >> M;
	TrieNode* trie = new TrieNode();
	for (int i = 0; i < N; ++i) {
		string s; cin >> s;
		trie->insert(s.c_str());
	}
	int cnt = 0; 
	while (M--) {
		string s; cin >> s;
		auto temp = trie->find(s.c_str());
		if (temp != NULL && temp->terminal == true) {
			++cnt;
		}
	}
	cout << cnt;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}