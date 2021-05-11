#include <bits/stdc++.h>

using namespace std;

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

int32_t main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL); 
	
	int n;
	cin >> n;

	int64_t a, b, c;
	cin >> a >> b >> c;

	vector<int64_t> pref(n+1, 0);
	for(int i = 1; i <= n; i++){
		int64_t t;
		cin >> t;	
		pref[i] = pref[i-1] + t;
	}

	LiChaoTree<int64_t> dp(0, 1000000001);
	dp.insert(0, 0);

	int64_t ans = 0;
	for(int i = 1; i <= n; i++){
		int64_t temp = dp.query(pref[i]) + a*pref[i]*pref[i] + b*pref[i] + c;
		if(i == n) ans = temp;
		dp.insert(-2*a*pref[i], temp + a*pref[i]*pref[i] - b*pref[i]);
	}

	cout << ans << '\n';
	return 0; 
}