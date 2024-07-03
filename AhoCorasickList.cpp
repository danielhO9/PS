#include <bits/stdc++.h>
using namespace std;

const int ALPHABETS = 26;
int toNumber(char ch) { return ch - 'A'; };

struct TrieNode {
	TrieNode* children[ALPHABETS];
	TrieNode* failure;
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
};

void getFailure(TrieNode* trie) {
	queue<TrieNode*> Q;
	trie->failure = trie;
	for (int i = 0; i < ALPHABETS; ++i) if (trie->children[i]) {
		trie->children[i]->failure = trie;
		Q.push(trie->children[i]);
	}
	while(!Q.empty()) {
		TrieNode* here = Q.front(); Q.pop();
		for (int i = 0; i < ALPHABETS; ++i) if (here->children[i]) {
			TrieNode* there = here->children[i];
			TrieNode* p = here->failure;
			while (p != trie && p->children[i] == NULL) p = p->failure;
			if (p->children[i]) p = p->children[i];
			else p = trie;
			there->failure = p;
			if (p->terminal) there->terminal = true;
			Q.push(there);
		}
	}
}

// trie에 s의 부분문자열이 존재하는지 유무
bool query(string& s, TrieNode* trie) {
	TrieNode* p = trie;
	for (auto& i: s) {
		int next = toNumber(i);
		while (p != trie && p->children[next] == NULL) p = p->failure;
		if (p->children[next]) p = p->children[next];
		else p = trie;
		if (p->terminal) return true;
	}
	return false;
}

void solve() {
	TrieNode* trie = new TrieNode();
	// trie->insert(s.c_str());
	getFailure(trie);
	// query(s, trie);
	delete trie;
}