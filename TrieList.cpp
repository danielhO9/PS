#include <bits/stdc++.h>
using namespace std;

const int ALPHABETS = 26;
int toNumber(char ch) { return ch - 'A'; };

struct TrieNode {
	TrieNode* children[ALPHABETS];
	bool terminal;
	TrieNode(): terminal(false) {
		memset(children, 0, sizeof(children));
	}
	~TrieNode() {
		for (int i = 0; i < ALPHABETS; ++i) if (children[i]) delete children[i];
	}
	void insert(const char* key) {
		if (*key == 0) terminal = true;
		else {
			int next = toNumber(*key);
			if (children[next] == NULL) children[next] = new TrieNode();
			children[next]->insert(key + 1);
		}
	}
	bool find(const char* key) {
		if (*key == 0) return this->terminal;
		int next = toNumber(*key);
		if (children[next] == NULL) return false;
		return children[next]->find(key + 1);
	}
	bool remove(const char* key) {
		bool flag = true;
		if (*key == 0) {
			this->terminal = false;
			for (int i = 0; i < ALPHABETS; ++i) if (children[i]) {
				flag = false;
				break;
			}
			return flag;
		}
		if (this->terminal) return false;
		int next = toNumber(*key);
		if (children[next]->remove(key + 1)) {
			delete children[next];
			children[next] = NULL;
			for (int i = 0; i < ALPHABETS; ++i) if (children[i]) {
				flag = false;
				break;
			}
			return flag;
		} else return false;
	}
};

void solve() {
	TrieNode* trie = new TrieNode();
	// string s; cin >> s;
	// trie->insert(s.c_str());
	// auto res = trie->find(s.c_str());
	// trie->remove(s.c_str());
	delete trie;
}