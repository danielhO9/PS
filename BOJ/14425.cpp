#include <bits/stdc++.h>
using namespace std;

struct TrieNode {
	unordered_map<char, TrieNode*> children;
	bool terminal;
	TrieNode(): terminal(false) {
		
	}
	~TrieNode() {
		for (auto [i, _]: children) delete children[i];
	}
	void insert(const char* key) {
		if (*key == 0) terminal = true;
		else {
			char next = *key;
			if (children.find(next) == children.end()) children[next] = new TrieNode();
			children[next]->insert(key + 1);
		}
	}
	bool find(const char* key) {
		if (*key == 0) return this->terminal;
		char next = *key;
		if (children.find(next) == children.end()) return false;
		return children[next]->find(key + 1);
	}
	bool remove(const char* key) {
		bool flag = true;
		if (*key == 0) {
			this->terminal = false;
			if (!children.empty()) flag = false;
			return flag;
		}
		if (this->terminal) return false;
		char next = *key;
		if (children[next]->remove(key + 1)) {
			delete children[next]; children.erase(next);
			for (auto [_, i]: children) flag = false;
			return flag;
		} else return false;
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
		if (trie->find(s.c_str())) {
			++cnt;
		}
	}
	cout << cnt;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}