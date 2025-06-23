#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll MOD = 998244353;

const int ALPHABETS = 2;
int toNumber(char ch) { return ch - 'A'; };

ll pow(ll a, ll b) {
    if (b == 0) return 1ll;
    ll h = pow(a, b / 2);
    h = (h * h) % MOD;
    if (b % 2) return (h * a) % MOD;
    else return h;
}

struct TrieNode {
	TrieNode* children[ALPHABETS];
	bool terminal;
    ll val;
    ll sz;
    
	TrieNode(): terminal(false) {
        for (int i = 0; i < ALPHABETS; ++i) children[i] = nullptr;
        terminal = false;
        val = 0;
        sz = 0;
	}
	~TrieNode() {
		for (int i = 0; i < ALPHABETS; ++i) if (children[i]) delete children[i];
	}
	void insert(const char* key) {
		if (*key == 0) {
            terminal = true;
        }
		else {
			int next = toNumber(*key);
			if (children[next] == nullptr) children[next] = new TrieNode();
			children[next]->insert(key + 1);
		}
        ++sz;
        if (children[0] != nullptr && children[1] != nullptr) val = (children[0]->val * children[1]->val) % MOD;
        else val = 0;
        if (terminal) {
            val += pow(2ll, sz - 1);
            val %= MOD;
        }
	}
} *trie;

int N;

void solve() {
    trie = new TrieNode();
    cin >> N;
    for (int i = 0; i < N; ++i) {
        string s; cin >> s;
        trie->insert(s.c_str());
        cout << trie->val << '\n';
    }
	delete trie;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}