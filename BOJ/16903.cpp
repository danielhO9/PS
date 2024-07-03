#include <bits/stdc++.h>
using namespace std;

const int ALPHABETS = 2;
int toNumber(char ch) { return ch - '0'; };

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
	int query(const char* key, int dep) {
		if (*key == 0) return 0;
		int next = toNumber(*key);
		int rev = 1 - next;
		int ret = 0;
		if (children[rev]) {
			ret += (1 << dep);
			// cout << dep << ' ' << rev << '\n';
			ret += children[rev]->query(key + 1, dep - 1);
		} else if (children[next]) {
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