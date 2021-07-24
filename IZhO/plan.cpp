#include <bits/stdc++.h>
/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
*/

using namespace std;
// using namespace __gnu_pbds;
using namespace chrono;

// mt19937 rng((int) std::chrono::steady_clock::now().time_since_epoch().count());
/*
template <class T> using ordered_set = tree <T, null_type, less <T>, rb_tree_tag, tree_order_statistics_node_update>;
*/

//***************** CONSTANTS *****************

const int MXN = 100000;
const int MXM = 500000;
const int INF = 1000000000;
const int MXK = 25;

//***************** GLOBAL VARIABLES *****************

vector<array<int, 2>> g[MXN];
array<int, 2> edges[MXM];
int d[MXN], c, timer, info[2*MXN], tin[2*MXN], tout[2*MXN], up[MXK][2*MXN];
vector<int> ng[2*MXN];

//***************** AUXILIARY STRUCTS *****************

struct UFDS{
	vector<int> e;
	UFDS(int n){ 
		e.resize(2*n, -1); 
	}

	int get(int x){ 
		return e[x] < 0 ? x : e[x] = get(e[x]); 
	}
	
	bool unite(int x, int y, int w){
		x = get(x), y = get(y);
		
		if(x == y) 
			return 0;

		ng[c].push_back(x);
		ng[c].push_back(y);

		e[c] = e[x] + e[y];

		e[x] = e[y] = c;

		info[c] = w;
		c++;

		return 1;
	}
};

void dfs(int u, int p){
	tin[u] = timer++;

	up[0][u] = p;
	for(int i = 1; i < MXK; i++)
		up[i][u] = up[i-1][up[i-1][u]];

	for(int v : ng[u]) if(v != p) dfs(v, u);

	tout[u] = timer;
}

bool isAncestor(int u, int v){
	return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int mxpath(int x, int y){
	for(int i = MXK - 1; i >= 0; --i){
		if(!isAncestor(up[i][x], y))
			x = up[i][x];
	}

	return info[up[0][x]];
}

//***************** MAIN BODY *****************

void solve(){
	int N, M;
	cin >> N >> M;

	c = N;

	for(int i = 0; i < M; i++){
		int u, v, w;
		cin >> u >> v >> w;
		--u, --v;
		g[u].push_back({v, w});
		g[v].push_back({u, w});
		edges[i] = {u, v};
	}

	for(int i = 0; i < N; i++)
		d[i] = INF;

	priority_queue<array<int, 2>, vector<array<int, 2>>, greater<array<int, 2>>> pq;

	int K;
	cin >> K;

	for(int i = 0; i < K; i++){
		int u;
		cin >> u;
		--u;
		d[u] = 0;
		pq.push({0, u});
	}

	while(!pq.empty()){
		auto [dis, u] = pq.top();
		pq.pop();

		if(dis > d[u])
			continue;

		for(auto& [v, w] : g[u])
			if(d[v] > d[u] + w){
				d[v] = d[u] + w;
				pq.push({d[v], v});
			}
	}

	sort(edges, edges + M, [&](array<int, 2>& a, array<int, 2>& b){
		return min(d[a[0]], d[a[1]]) > min(d[b[0]], d[b[1]]);
	});

	UFDS D(N);

	for(int i = 0; i < M; i++){
		auto [u, v] = edges[i];
		int w = min(d[u], d[v]);

		D.unite(u, v, w);
	}

	dfs(2*N - 2, 2*N - 2);

	int Q;
	cin >> Q;

	while(Q--){
		int u, v;
		cin >> u >> v;
		--u, -- v;

		cout << mxpath(u, v) << '\n';
	}
}

/*
	multisource dijkstra to find dangerousness of individual components
	1. assign every edge a new weight => min dangerousness of either node it connects to
	make a reach tree, binary lifting to solve
*/

//***************** *****************

int32_t main(){
	ios_base::sync_with_stdio(NULL);
	cin.tie(NULL);

	#ifdef LOCAL
		auto begin = high_resolution_clock::now();
	#endif

	int tc = 1;
	// cin >> tc; 
	for (int t = 0; t < tc; t++)
		solve();

	#ifdef LOCAL 
		auto end = high_resolution_clock::now();
		cout << fixed << setprecision(4);
		cout << "Execution Time: " << duration_cast<duration<double>>(end - begin).count() << "seconds" << endl;
	#endif

	return 0;
}

/*
If code gives a WA, check for the following : 
1. I/O format

2. Are you clearing all global variables in between tests if multitests are a thing

3. Can you definitively prove the logic
*/