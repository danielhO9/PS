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
			children.erase(next);
			for (auto [_, i]: children) flag = false;
			return flag;
		} else return false;
	}
	int query(const char* key, int dep) {
		if (*key == 0) return 0;
		char next = *key;
		char rev = '1' + '0' - next;
		int ret = 0;
		if (children.find(rev) != children.end()) {
			ret += (1 << dep);
			// cout << dep << ' ' << rev << '\n';
			ret += children[rev]->query(key + 1, dep - 1);
		} else {
			// cout << dep << ' ' << next << '\n';
			ret += children[next]->query(key + 1, dep - 1);
		}
		return ret;
	}
};

void solve() {
	TrieNode* trie = new TrieNode();
	int M; cin >> M;
	unordered_map<int, int> um; um[0] = 1;
	char bit[31]; for (int i = 0; i < 30; ++i) bit[i] = '0';
	trie->insert(bit);
	while (M--) {
		int what, x; cin >> what >> x;
		for (int i = 0; i < 30; ++i) {
			if ((x >> i) & 1) bit[29 - i] = '1';
			else bit[29 - i] = '0';
		}
		if (what == 1) {
			++um[x];
			if (um[x] == 1) trie->insert(bit);
		} else if (what == 2) {
			--um[x];
			if (um[x] == 0) trie->remove(bit);
		} else {
			cout << trie->query(bit, 29) << '\n';
		}
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}