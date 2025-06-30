#include <bits/stdc++.h>
using namespace std;

const int ALPHABETS = 2;

struct TrieNode {
	TrieNode* children[ALPHABETS];
	int terminal;

	TrieNode(): terminal(0) { memset(children, 0, sizeof(children)); }
	~TrieNode() { for (int i = 0; i < ALPHABETS; ++i) if (children[i]) delete children[i]; }
	void insert(const int& s, int idx = 29) {
		if (idx == -1) ++terminal;
		else {
			int next = ((s >> idx) & 1);
			if (children[next] == nullptr) children[next] = new TrieNode();
			children[next]->insert(s, idx - 1);
		}
	}
	bool find(const int& s, int idx = 29) {
		if (idx == -1) return this->terminal;
		int next = ((s >> idx) & 1);
		if (children[next] == nullptr) return false;
		return children[next]->find(s, idx - 1);
	}
	bool erase(const int& s, int idx = 29) {
		if (idx == -1) {
			--terminal;
			if (terminal) return false;
			for (int i = 0; i < ALPHABETS; ++i) if (children[i]) return false;
			return true;
		}
		int next = ((s >> idx) & 1);
		if (children[next] == nullptr) return false;
		if (children[next]->erase(s, idx - 1)) {
			delete children[next];
			children[next] = nullptr;
		}
		if (terminal) return false;
		for (int i = 0; i < ALPHABETS; ++i) if (children[i]) return false;
		return true;
	}
	int query(const int& s, int idx = 29, int cur = 0) {
		if (idx == -1) return cur;
		int next = ((s >> idx) & 1);
		next ^= 1;
		if (children[next] == nullptr) next ^= 1;
		else cur += (1 << idx);
		return children[next]->query(s, idx - 1, cur);
	}
};

int M;

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> M;
	TrieNode* trie = new TrieNode{};
	trie->insert(0);
	while (M--) {
		int t, x; cin >> t >> x;
		if (t == 1) trie->insert(x);
		else if (t == 2) trie->erase(x);
		else cout << trie->query(x) << '\n';
	}
}