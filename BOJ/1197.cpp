#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

template <typename T>
struct Node {
	ll key, rank, id;
	T val;
	bool mark;
	Node* child;
	Node* p;
	Node* l;
	Node* r;

	Node(ll _key, ll _id, T _val) {
		key = _key; id = _id; val = _val;
		rank = 0; mark = false;
		child = NULL; p = NULL; l = NULL; r = NULL;
	}
};

template <typename T>
class Fib_heap {

private:
	Node<T>* min;
	vector<Node<T>*> nodes;

public:
	Fib_heap() {
		min = NULL;
	}

	void insert(ll key, ll id, T val) {
		Node<T>* node = new Node<T>(key, id, val);
		if (nodes.size() <= id) nodes.resize(id + 1);
		nodes[id] = node;
		insert(node);
		// cout << "inserted " << node->key << ' ' << node->id << '\n';
	}

	void insert(Node<T>* node) {
		node->p = NULL;
		if (!min) {
			min = node;
			min->l = min;
			min->r = min;
		} else {
			node->l = min->l;
			node->r = min;
			min->l->r = node;
			min->l = node;
			if (min->key > node->key) min = node;
		}
		
	}

	// return smaller root
	Node<T>* link(Node<T>* node1, Node<T>* node2) {
		if (node1->key < node2->key || node1 == min) swap(node1, node2);
		// cout << "link: " << node1->id << ' ' << node2->id << '\n';
		// cout <<  "child: ";
		// cout <<  "child: ";

		if (node1 == min) min = node2;

		node1->r->l = node1->l;
		node1->l->r = node1->r;
		node1->l = node1; node1->r = node1;
		node1->p = node2;
		
		++node2->rank;
		if (node2->child == NULL) node2->child = node1;
		else {
			node1->r = node2->child;
			node1->l = node2->child->l;
			node2->child->l->r = node1;
			node2->child->l = node1;
		}
		return node2;
	}

	Node<T>* delete_min() {
		// cout << "start delete\n";
		Node<T>* ret = min;
		assert(min != NULL);
		// cout << "min: " << min->key << ' ' << min->id << '\n';
		// cout << "min_r: " << min->r->key << ' ' << min->r->id << '\n';

		// children into root list
		if (min->child) {
			Node<T>* cur = min->child;
			while (true) {
				Node<T>* nxt = cur->r;
				insert(cur);
				cur = nxt;
				if (!cur->p) break;
			}
		}

		// delete min
		if (min->r == min) {
			min = NULL;
			// cout << "deleted " << ret->key << ' ' << ret->id << '\n';
			return ret;
		}
		min->r->l = min->l;
		min->l->r = min->r;
		min->rank = 0;
		nodes[min->id] = NULL;
		min = min->r;

		// update min
		Node<T>* cur = min;
		ll s_id = cur->id;
		while (true) {
			assert(cur->r->l == cur);
			assert(cur->l->r == cur);
			if (min->key > cur->key) min = cur;
			Node<T>* nxt = cur->r;
			cur = nxt;
			if (cur->id == s_id) break;
		}
		// cout << min->key << ' ' << min->id << '\n';
		// cout << min->r->key << ' ' << min->r->id << '\n';
		// cout << min->l->key << ' ' << min->l->id << '\n';
		// cout << min->rank << '\n';
		// cout << min->r->rank << '\n';

		// consolidate trees
		vector<Node<T>*> arr;
		cur = min;
		s_id = cur->id;
		while (true) {
			Node<T>* nxt = cur->r;
			while (arr.size() <= cur->rank) arr.push_back(NULL);
			while (arr[cur->rank] != NULL) {
				// cout << '\n';
				Node<T>* cons_node = arr[cur->rank];
				arr[cur->rank] = NULL;
				// cout << "before link\n";
				cur = link(cons_node, cur);
				// cout << cur->id << '\n';
				while (arr.size() <= cur->rank) arr.push_back(NULL);
			}
			arr[cur->rank] = cur;
			cur = nxt;
			// cout << "id: " << cur->id << ' ' << s_id << '\n';
			if (cur->id == s_id) break;
		}
		// cout << "deleted " << ret->key << ' ' << ret->id << '\n';
		return ret;
	}

	void decrease(Node<T>* x, ll nkey) {
		// cout << "decrease start" << ' ' << nkey << ' ' << x->id << '\n';
		x->key = nkey;

		// heap order not violated
		if (!x->p || x->p && x->p->key <= x->key) {
			if (!x->p) if (x->key < min->key) min = x;
			return;
		}
		
		// parent p of x was unmarked
		if (!x->p->mark) {
			if (x->p->child == x) {
				if (x->r == x) x->p->child = NULL;
				else x->p->child = x->r;
			}
			--x->p->rank;
			x->p->mark = true;
			x->r->l = x->l;
			x->l->r = x->r;
			x->mark = false;
			insert(x);
		} else {
			Node<T>* cur = x;
			while (cur->p) {
				Node<T>* nxt = cur->p;
				if (cur->p->child == cur) {
					if (cur->r == cur) cur->p->child = NULL;
					else cur->p->child = cur->r;
				}
				--cur->p->rank;
				cur->r->l = cur->l;
				cur->l->r = cur->r;
				cur->mark = false;
				insert(cur);
				cur = nxt;

				if (!cur->mark) {
					if (cur->p) cur->mark = true;
					break;
				}
			}
		}

	}

	void decrease(ll nkey, ll id, T val) {
		while (nodes.size() <= id) nodes.push_back(NULL);
		if (nodes[id]) {
			nodes[id]->val = val;
			if (nkey >= nodes[id]->key) return;
			decrease(nodes[id], nkey);
		} else insert(nkey, id, val);
	}

	void print_root_list() {
		// cout << "root: ";
		if (min == NULL) {
			// cout << "NONE\n";
			return;
		}
		Node<T>* cur = min;
		ll s_id = cur->id;
		while (true) {
			assert(cur->r->l == cur);
			assert(cur->l->r == cur);
			// cout << cur->id << ' ';
			Node<T>* nxt = cur->r;
			cur = nxt;
			if (cur->id == s_id) break;
		}
		// cout << '\n';
	}

};

vector<pair<int, ll>> adj[10001];
int V, E;

ll prim_fib_heap_mst() {
	bool vis[V + 1]; memset(vis, 0, sizeof(vis));
	Fib_heap<ll> pq;
	pq.insert(0, 1, 0);
	ll ans = 0ll, cnt = 0;
	while (cnt != V) {
		auto node = pq.delete_min();
		ll w = node->key;
		int v = node->id;
		delete node;
		if (vis[v]) continue;
		++cnt;
		ans += w;
		// // cout << w << '\n';
		vis[v] = true;
		for (auto& i: adj[v]) {
			if (!vis[i.first]) {
				pq.decrease(i.second, i.first, 0);
				// // cout << i.second << ' ' << i.first << '\n';
			}
		}
	}
	return ans;
}

int main() {
	cin >> V >> E;
	for (int i = 0; i < E; ++i) {
		ll a, b, c; cin >> a >> b >> c;
		adj[a].push_back({b, c});
		adj[b].push_back({a, c});
	}
	cout << prim_fib_heap_mst();
	return 0;
}