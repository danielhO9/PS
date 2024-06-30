#include <bits/stdc++.h>
using namespace std;

struct TrieNode {
	unordered_map<char, TrieNode*> children;
	TrieNode* failure;
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
};

void getFailure(TrieNode* trie) {
	queue<TrieNode*> Q;
	trie->failure = trie;
	for (auto [_, there]: trie->children) {
		there->failure = trie;
		Q.push(there);
	}
	while(!Q.empty()) {
		TrieNode* here = Q.front(); Q.pop();
		for (auto [i, there]: here->children) {
			TrieNode* p = here->failure;
			while (p != trie && p->children.find(i) == p->children.end()) p = p->failure;
			if (p->children.find(i) != p->children.end()) p = p->children[i];
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
		while (p != trie && p->children.find(i) == p->children.end()) p = p->failure;
		if (p->children.find(i) != p->children.end()) p = p->children[i];
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