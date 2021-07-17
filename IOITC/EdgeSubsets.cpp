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

const int MXN = 1000;
const int INF = 1'000'000'000;

//***************** GLOBAL VARIABLES *****************

vector<array<int, 2>> g[MXN];
int N, M, par[MXN];

//***************** AUXILIARY STRUCTS *****************



//***************** MAIN BODY *****************

void reset(){
	for(int i = 0; i < N; i++)
		g[i].clear();
}

void solve(){
	cin >> N >> M;
	reset();

	for(int i = 1; i < N; i++){
		int p;
		cin >> p;
		--p;
		par[i] = p;
		g[p].push_back({i, 1});
		g[i].push_back({p, 0});
	}

	for(int i = 0; i < M; i++){
		int u, v, l, r;
		cin >> u >> v >> l >> r;
		--u, --v;
		g[u].push_back({v, r});
		g[v].push_back({u, -l});
	}

	vector<int> d(N, INF), cnt(N, 0);
	vector<bool> inqueue(N, false);
	queue<int> q;

	d[0] = 0;
	q.push(0);
	inqueue[0] = 1;

	while(!q.empty()){
		int u = q.front();
		q.pop();
		inqueue[u] = false;

		for(auto& [v, cost] : g[u]){
			if(d[v] > d[u] + cost){
				d[v] = d[u] + cost;
				if(!inqueue[v]){
					q.push(v);
					inqueue[v] = 1;
					cnt[v]++;
					if(cnt[v] > N){
						cout << -1 << '\n';
						return;
					}
				}
			}
		}
	}

	vector<int> ans;

	for(int i = 1; i < N; i++)
		if(d[i] - d[par[i]] == 1)
			ans.push_back(i + 1);
	
	cout << ans.size() << '\n';
	for(int i : ans)
		cout << i << ' ';
	cout << '\n';
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

/*
If code gives a WA, check for the following : 
1. I/O format

2. Are you clearing all global variables in between tests if multitests are a thing

3. Can you definitively prove the logic
*/