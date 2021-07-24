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
const int64_t INF = 1'000'000'000'000'000'000;

//***************** GLOBAL VARIABLES *****************

vector<pair<int, int64_t>> g[MXN];

//***************** AUXILIARY STRUCTS *****************



//***************** MAIN BODY *****************

void solve(){
	int N, s, t;
	cin >> N >> s >> t;

	vector<int> A(N);

	for(int& x : A) cin >> x;

	vector<int> st;
	
	for(int i = 0; i < N; i++){
		while(!st.empty() && A[i] < A[st.back()]){
			g[st.back()].push_back({i, 1LL * abs(i - st.back()) * A[st.back()]});
			// g[i].push_back({st.back(), 1LL * abs(i - st.back()) * A[i]});
			st.pop_back();
		}

		st.push_back(i);
	}

	st.clear();
	
	for(int i = 0; i < N; i++){
		while(!st.empty() && A[st.back()] >= A[i]){
			st.pop_back();
		}

		if(!st.empty()){
			g[i].push_back({st.back(), 1LL * abs(i - st.back()) * A[i]});
			// g[st.back()].push_back({i, 1LL * abs(i - st.back()) * A[st.back()]});
		}

		st.push_back(i);
	}

	vector<int64_t> d(N, INF);
	priority_queue<array<int64_t, 2>, vector<array<int64_t, 2>>, greater<array<int64_t, 2>>> pq;

	--s, --t;

	pq.push({0, s});
	d[s] = 0;

	while(!pq.empty()){
		auto [dist, u] = pq.top();
		pq.pop();

		if(dist > d[u])
			continue;

		for(auto& [v, w] : g[u]){
			if(d[v] > d[u] + w){
				d[v] = d[u] + w;
				pq.push({d[v], v});
			}
		}
	}

	int64_t ans = INF;
	
	for(int i = 0; i < N; i++)
		ans = min(ans, d[i] + 1LL * abs(i - t) * A[i]);

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