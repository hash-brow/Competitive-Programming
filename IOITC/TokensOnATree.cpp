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

const int MXN = 1000000;

//***************** GLOBAL VARIABLES *****************

vector<int> g[MXN];
int N, f[MXN], dep[MXN], sz[MXN];
map<int, int> cnt[MXN];
int64_t ans = 0;

//***************** AUXILIARY STRUCTS *****************

void dfs(int node, int d){
	dep[node] = d;
	for(int v : g[node])
		dfs(v, d+1);
}

void dfs(int node){
	sz[node] = 0;
	if(f[node]){
		sz[node] = 1;
		cnt[node][dep[node]]++;
	}

	for(int v : g[node]){
		dfs(v);
		if(sz[node] < sz[v])
			swap(cnt[v], cnt[node]);

		for(auto& [d, c] : cnt[v])
			cnt[node][d] += c;

		sz[node] += sz[v];
	}

	if(!f[node] && !cnt[node].empty()){
		int mx = (--cnt[node].end())->first;
		ans += mx - dep[node];
		cnt[node][dep[node]]++;
		cnt[node][mx]--;
		if(cnt[node][mx] == 0)
			cnt[node].erase(mx);
	}
}

//***************** MAIN BODY *****************

void reset(){
	ans = 0;
	for(int i = 0; i < N; i++){
		g[i].clear();
		cnt[i].clear();
	}
}

void solve(){
	cin >> N;
	reset();

	for(int i = 0; i < N; i++){
		char c;
		cin >> c;
		f[i] = c - '0';
	}

	for(int i = 1; i < N; i++){
		int p;
		cin >> p;
		g[p-1].push_back(i);
	}

	dfs(0, 0);
	dfs(0);

	cout << ans << '\n';
}

//***************** *****************

int32_t main(){
	ios_base::sync_with_stdio(NULL);
	cin.tie(NULL);

	#ifdef LOCAL
		auto begin = high_resolution_clock::now();
	#endif

	int tc = 1;
	cin >> tc; 
	for (int t = 0; t < tc; t++)
		solve();

	#ifdef LOCAL 
		auto end = high_resolution_clock::now();
		cout << fixed << setprecision(4);
		cout << "Execution Time: " << duration_cast<duration<double>>(end - begin).count() << "seconds" << endl;
    #endif

	return 0;
}