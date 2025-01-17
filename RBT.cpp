#include <bits/stdc++.h>
using namespace std;

template <class T>
struct Node {
	T key;
	Node<T> *parent;
	Node<T> *left;
	Node<T> *right;
	bool red;

	Node<T>(T _key) {
		key = _key;
		parent = NULL;
		left = NULL;
		right = NULL;
		red = true;
	}
};

template <class T>
class RBT {
public:
	Node<T>* root;

	RBT(Node<T>* _root = NULL) : root(_root) {}

	// min node in subtree
	Node<T> *min_rbt(Node<T> *root) {
		if (root->left == NULL)
			return root;
		Node<T> *ret = min_rbt(root->left);
		return ret;
	}

	Node<T> *min() {return min_rbt(root); }

	void insert(T key) { insert_rbt(root, root, key); }

	void delete_rbt(T key) { delete_rbt(root, root, key); }

	bool search(T key) {
		if (root == NULL)
			return false;
		if (root->key == key)
			return true;
		if (root->key < key)
			return search_rbt(root->right, key);
		else
			return search_rbt(root->left, key);
	}

private:
	// rotate root right(left)
	void rotate_rbt(Node<T> *&root, Node<T> *node, bool right) {
		assert(node != NULL);
		Node<T> *p = node->parent;
		Node<T> *new_node = right ? node->left : node->right;
		assert(new_node != NULL);

		Node<T> *c = right ? new_node->right : new_node->left;
		if (right)
			node->left = c;
		else
			node->right = c;
		if (c != NULL)
			c->parent = node;

		if (right)
			new_node->right = node;
		else
			new_node->left = node;
		node->parent = new_node;

		new_node->parent = p;
		if (p != NULL) {
			if (p->left == node)
				p->left = new_node;
			else
				p->right = new_node;
		} else
			root = new_node;
	}

	// fix tree by rotation and recoloring
	void fix_violation_rbt(Node<T> *&root, Node<T> *p, Node<T> *node) {
		if (p == NULL) {
			root = node;
			root->red = false;
			return;
		}
		if (!(p->red))
			return;

		Node<T> *g = p->parent;
		if (g == NULL)
			return fix_violation_rbt(root, g, p);
		bool right = (g->right == p);
		Node<T> *uncle;
		if (!right)
			uncle = g->right;
		else
			uncle = g->left;
		if (uncle == NULL || !(uncle->red)) {
			if ((g->left != NULL && g->left->right == node) ||
				(g->right != NULL && g->right->left == node)) {
				rotate_rbt(root, p, right);
				node = p;
				if (right)
					p = g->right;
				else
					p = g->left;
			}
			rotate_rbt(root, g, !right);
			p->red = false;
			g->red = true;
			return;
		}
		p->red = false;
		uncle->red = false;
		g->red = true;
		return fix_violation_rbt(root, g->parent, g);
	}

	// insert node to p's right(left) child
	void insert_rbt(Node<T> *&root, Node<T> *p, Node<T> *node, bool right) {
		node->parent = p;
		assert(p != NULL);
		if (right)
			p->right = node;
		else
			p->left = node;
		fix_violation_rbt(root, p, node);
	}

	void insert_rbt(Node<T> *&root, Node<T> *node, T key) {
		if (node == NULL) {
			root = new Node<T>(key);
			root->red = false;
			return;
		}
		if (node->key == key)
			return;
		if (node->key < key) {
			if (node->right == NULL)
				return insert_rbt(root, node, new Node<T>(key), 1);
			return insert_rbt(root, node->right, key);
		} else {
			if (node->left == NULL)
				return insert_rbt(root, node, new Node<T>(key), 0);
			return insert_rbt(root, node->left, key);
		}
	}

	// delete special(non root, not chid, black) node
	void delete_special_rbt(Node<T> *&root, Node<T> *node, bool right) {
		Node<T> *p = node->parent;
		if (p == NULL)
			return;

		Node<T> *s;
		Node<T> *d;
		Node<T> *c;
		if (right) {
			s = p->left;
			assert(s != NULL);
			d = s->left;
			c = s->right;
		} else {
			s = p->right;
			assert(s != NULL);
			d = s->right;
			c = s->left;
		}
		if (s->red) {
			rotate_rbt(root, p, right);

			p->red = true;
			s->red = false;
			s = c;
			if (right)
				d = s->left;
			else
				d = s->right;
			return delete_special_rbt(root, node, right);
		}
		if (d != NULL && d->red) {
			rotate_rbt(root, p, right);
			s->red = p->red;
			p->red = false;
			d->red = false;
			return;
		}
		if (c != NULL && c->red) {
			rotate_rbt(root, s, !right);
			s->red = true;
			c->red = false;
			return delete_special_rbt(root, node, right);
		}
		if (p->red) {
			s->red = true;
			p->red = false;
			return;
		}
		s->red = true;
		if (p->parent == NULL)
			return;
		return delete_special_rbt(root, p, p->parent->right == p);
	}

	void delete_special_rbt(Node<T> *&root, Node<T> *node) {
		Node<T> *p = node->parent;
		bool right = (p->right == node);
		if (right)
			p->right = NULL;
		else
			p->left = NULL;
		delete_special_rbt(root, node, right);
		delete node;
	}

	void delete_node_rbt(Node<T> *&root, Node<T> *node) {
		if (node->left != NULL && node->right != NULL) {
			Node<T> *nnode = min_rbt(node->right);
			node->key = nnode->key;
			return delete_node_rbt(root, nnode);
		}
		if (node->left == NULL && node->right == NULL) {
			if (node == root) {
				delete node;
				root = NULL;
				return;
			}
			if (node->red) {
				if (node->parent->left == node)
					node->parent->left = NULL;
				else
					node->parent->right = NULL;
				delete node;
				return;
			}
			delete_special_rbt(root, node);
		} else {
			if (node == root) {
				if (node->left != NULL) {
					root = node->left;
					node->left->parent = NULL;
				} else {
					root = node->right;
					node->right->parent = NULL;
				}
				root->red = false;
				return;
			}
			Node<T> *p = node->parent;
			if (node->left != NULL) {
				if (p->left == node)
					p->left = node->left;
				else
					p->right = node->left;
				node->left->parent = p;
				node->left->red = false;
			} else {
				if (p->left == node)
					p->left = node->right;
				else
					p->right = node->right;
				node->right->parent = p;
				node->right->red = false;
			}
			delete node;
		}
	}

	void delete_rbt(Node<T> *&root, Node<T> *node, T key) {
		if (node == NULL)
			return;
		if (node->key == key) {
			delete_node_rbt(root, node);
			return;
		}
		if (node->key < key)
			return delete_rbt(root, node->right, key);
		else
			return delete_rbt(root, node->left, key);
	}
};

void solve() {
	RBT<int> rbt(NULL);
}
