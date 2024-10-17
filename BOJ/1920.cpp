#include <assert.h>
#include <iostream>
#include <random>
#include <time.h>
using namespace std;

random_device rd;
mt19937_64 gen(rd());

struct Node_bst {
	int key;
	Node_bst* parent;
	Node_bst* left;
	Node_bst* right;

	Node_bst(int _key, Node_bst* _parent) {
		key = _key;
		parent = _parent;
		left = NULL;
		right = NULL;
	}
};

struct Node_hash {
	int key;
	int cnt;
	Node_hash* parent;
	Node_hash* nxt;

	Node_hash(int _key, Node_hash* _parent) {
		key = _key;
		cnt = 0;
		parent = _parent;
		nxt = NULL;
	}
};

struct Hash_table {
	const int n = 1e5;
	const long long p = 4294967311;
	long long a = 0, b = 0;
	Node_hash* bucket[100000];

	Hash_table() {
		uniform_int_distribution<long long> dist_a(1, p - 1);
		a = dist_a(gen);
		uniform_int_distribution<long long> dist_b(0, p - 1);
		b = dist_b(gen);
	}

	long long h(int x) {
		long long long_x = x;
		long_x -= (long long) INT32_MIN;
		long long x1 = long_x / 2ll;
		long long x2 = long_x - x1;
		unsigned long long ret = (unsigned long long) x1 * (unsigned long long) a + (unsigned long long) b;
		ret %= (unsigned long long) p;
		ret += (unsigned long long) x2 * (unsigned long long) a;
		ret %= (unsigned long long) p;
		return ret;
	}
};

void insert_bst(Node_bst* root, int key) {
	if (root->right == NULL) {
		root->right = new Node_bst(key, root);
		return;
	}

	Node_bst* cur = root->right;
	while (true) {
		if (cur->key < key) {
			if (cur->right == NULL) {
				cur->right = new Node_bst(key, cur);
				return;
			}
			cur = root->right;
		} else {
			if (cur->left == NULL) {
				cur->left = new Node_bst(key, cur);
				return;
			}
			cur = root->left;
		}
	}
}

bool search_bst(Node_bst* root, int key) {
	if (root->right == NULL) return false;

	Node_bst* cur = root->right;
	while (true) {
		if (cur->key == key) return true;
		if (cur->key < key) {
			if (cur->right == NULL) return false;
			cur = root->right;
		} else {
			if (cur->left == NULL) return false;
			cur = root->left;
		}
	}
}

void delete_node_bst(Node_bst* node) {
	if (node->left == NULL || node->right == NULL) {
		Node_bst* move_up = NULL;
		if (node->left != NULL) move_up = node->left;
		if (node->right != NULL) move_up = node->right;
		if (node->parent->right == node) node->parent->right = move_up;
		else node->parent->left = move_up;
		delete node;
		return;
	}
	Node_bst* move_up = node->right;
	while (move_up->left != NULL) move_up = move_up->left;
	int move_up_val = move_up->left->key;
	delete_node_bst(move_up);
	node->key = move_up_val;
}

bool delete_bst(Node_bst* root, int key) {
	if (root->right == NULL) return false;
	if (root->right->key == key) {
		delete_node_bst(root->right);
		return true;
	}

	Node_bst* cur = root->right;
	while (true) {
		if (cur->key == key) {
			delete_node_bst(cur);
			return true;
		}
		if (cur->key < key) {
			if (cur->right == NULL) return false;
			cur = root->right;
		} else {
			if (cur->left == NULL) return false;
			cur = root->left;
		}
	}
}

void insert_hash(Hash_table* hash_table, int key) {
	long long h_key = hash_table->h(key);
	h_key %= hash_table->n;
	if (hash_table->bucket[h_key] == NULL) {
		hash_table->bucket[h_key] = new Node_hash(key, NULL);
		return;
	}
	Node_hash* cur = hash_table->bucket[h_key];
	while (cur->nxt != NULL && cur->nxt->key != key) cur = cur->nxt;
	if (cur->nxt != NULL) ++cur->nxt->cnt;
	else cur->nxt = new Node_hash(key, cur);
}

bool search_hash(Hash_table* hash_table, int key) {
	long long h_key = hash_table->h(key);
	h_key %= hash_table->n;
	Node_hash* cur = hash_table->bucket[h_key];
	while (cur != NULL) {
		if (cur->key == key) return true;
		cur = cur->nxt;
	}
	return false;
}

bool delete_hash(Hash_table* hash_table, int key) {
	long long h_key = hash_table->h(key);
	h_key %= hash_table->n;
	if (hash_table->bucket[h_key] == NULL) return false;
	Node_hash* cur = hash_table->bucket[h_key];
	while (cur != NULL) {
		if (cur->key == key) {
			if (cur->parent != NULL) cur->parent->nxt = cur->nxt;
			delete cur;
			return true;
		}
		cur = cur->nxt;
	}
	return false;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	Hash_table* ht = new Hash_table();
	int N; cin >> N;
	for (int i = 0; i < N; ++i) {
		int tmp; cin >> tmp;
		insert_hash(ht, tmp);
	}
	int M; cin >> M;
	for (int i = 0; i < M; ++i) {
		int tmp; cin >> tmp;
		cout << search_hash(ht, tmp) << '\n';
	}
}