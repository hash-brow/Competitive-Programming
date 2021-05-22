/*
Sparse Min LiChao Tree
*/

template<typename T>
struct LiChaoTree{
	static const T identity = 0;

	struct Line{
		T m, c;

		Line(){
			m = 0;
			c = identity;
		}

		Line(T m, T c) : m(m), c(c) {}

		T val(T x){
			return m*x + c;
		}
	};

	struct Node{
		Node *lc, *rc;
		Line line;

		Node() : lc(0), rc(0) {}
	};

	deque<Node> buffer;

	Node* new_node(){
		buffer.emplace_back();
		return &buffer.back();
	}

	Node *root;

	T L, R;
	LiChaoTree(T L, T R){
		this->L = L;
		this->R = R;

		root = new_node();
	}

	void insert(Node* &node, T l, T r, Line line){
		if(!node){
			node = new_node();
			node->line = line;
			return;
		}

		if(r - l == 1)
			return;

		T mid = (l + r) >> 1;
		
		if(line.val(mid) > node->line.val(mid))
			swap(line, node->line);

		if(line.val(l) > node->line.val(l)) insert(node->lc, l, mid, line);
		else insert(node->rc, mid, r, line);
	}

	T query(Node* &node, T l, T r, T x){
		if(!node)
			return identity;

		T mid = (l + r) >> 1;
		T res = node->line.val(x);

		if(r - l == 1)
			return res;

		if(x < mid) return max(res, query(node->lc, l, mid, x));
		else return max(res, query(node->rc, mid, r, x));
	}

	void insert(T m, T c) { insert(root, L, R, Line(m, c)); }
	T query(T x) { return query(root, L, R, x); }
};
