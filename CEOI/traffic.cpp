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

const int MXN = 300001;

//***************** GLOBAL VARIABLES *****************

int N, M, A, B;
int tin[MXN], comp[MXN], L[MXN], R[MXN], pre[MXN], st[MXN], ptr;
int timer;
vector<int> g[MXN];
array<int, 3> p[MXN];

//***************** AUXILIARY STRUCTS *****************

int tarjan(int u){
	int low = tin[u] = ++timer;
	st[ptr++] = u;
	for(int v : g[u])
		if(!comp[v]) low = min(low, tin[v] ? : tarjan(v));

	if(tin[u] == low){
		for(int c = 0; c != u; ){
			comp[c = st[--ptr]] = u;
			for(int v : g[c]){
				L[u] = min(L[u], L[(comp[v] ? comp[v] : u) == u ? v : comp[v]]);
				R[u] = max(R[u], R[(comp[v] ? comp[v] : u) == u ? v : comp[v]]);
			}
		}
	}

	return low;
}

//***************** MAIN BODY *****************

void solve(){
	cin >> N >> M >> A >> B;

	memset(L, 0x3f, sizeof L);

	for(int i = 0; i < N; i++){
		cin >> p[i][1] >> p[i][0];
		p[i][2] = i + 1;
	}

	sort(p, p + N);

	for(int i = 0; i < N; i++)
		if(p[i][1] == A) L[p[i][2]] = R[p[i][2]] = i + 1;

	for(int i = 0; i < M; i++){
		int u, v, w;
		cin >> u >> v >> w;

		g[u].push_back(v);
		if(w > 1) g[v].push_back(u);
	}

	for(int i = 0; i < N; i++)
		if(!p[i][1] && !tin[p[i][2]]) tarjan(p[i][2]);

	for(int i = 0; i < N; i++)
		pre[i+1] = pre[i] + (p[i][1] == A && tin[p[i][2]]);

	for(int i = N - 1; i >= 0; --i){
		int j = comp[p[i][2]];
		if(!p[i][1])
			cout << (R[j] ? pre[R[j]] - pre[L[j]-1] : 0) << '\n';
	}
}

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

4. If the code gives an inexplicable TLE, and you are sure you have the best possible complexity,
use faster io
*/