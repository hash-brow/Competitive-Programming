#include <bits/stdc++.h>

using namespace std;

struct SegmentTree{
	struct Node{
		Node *lc, *rc;
		int val, lazy;

		Node() : lc(0), rc(0) {
			val = 0;
			lazy = 0;
		}
	};

	deque<Node> tree;
	Node* new_node(){
		tree.emplace_back();
		return &tree.back();
	}

	Node *root;
	int L, R;
	SegmentTree(int _L, int _R){
		this->L = _L;
		this->R = _R;
		root = new_node();
	}

	void push(Node* &node, int l, int r){
		if(node->lazy == 0)
			return;
		node->val = r-l;
		if(!node->lc) node->lc = new_node();
		if(!node->rc) node->rc = new_node();
		node->lc->lazy = node->rc->lazy = 1;
		node->lazy = 0;
	}

	void upd(int l, int r, int val, Node* &node, int lx, int rx){
		if(!node) node = new_node();
		push(node, lx, rx);
		if(rx <= l || lx >= r)
			return;
		if(l <= lx && r >= rx){
			node->lazy = 1;
			push(node, lx, rx);
			return;
		}

		int mid = (lx + rx) >> 1;
		upd(l, r, val, node->lc, lx, mid);
		upd(l, r, val, node->rc, mid, rx);
		push(node->lc, lx, mid), push(node->rc, mid, rx);
		node->val = node->lc->val + node->rc->val;
	}

	int query(int l, int r, Node* &node, int lx, int rx){
		if(lx >= r || rx <= l || !node)
			return 0;
		push(node, lx, rx);
		if(l <= lx && r >= rx)
			return node->val;

		int mid = (lx + rx) >> 1;
		return query(l, r, node->lc, lx, mid) + query(l, r, node->rc, mid, rx);
	}

	void upd(int l, int r) { upd(l, r, 1, root, L, R); }

	int query(int l, int r) { return query(l, r, root, L, R); }
};

int32_t main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL); 
	
	int m;
	cin >> m;

	SegmentTree S(0, 1000000000);
	int c = 0;
	for(int i = 0; i < m; i++){
		int t, x, y;
		cin >> t >> x >> y;
		x += c, y += c;
		if(t == 1){
			cout << (c = S.query(x-1, y)) << '\n';
		}
		else{
			S.upd(x-1, y);
		}
	}
	return 0; 
}