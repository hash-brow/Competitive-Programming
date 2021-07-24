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



//***************** GLOBAL VARIABLES *****************



//***************** AUXILIARY STRUCTS *****************



//***************** MAIN BODY *****************

void solve(){
	int N, M, S;
	cin >> N >> M >> S;

	vector<array<int64_t, 2>> A(N);
	for(auto& [x, y] : A)
		cin >> x >> y;

	sort(A.begin(), A.end(), [](array<int64_t, 2> a, array<int64_t, 2> b){
		return a[0] - a[1] < b[0] - b[1];
	});

	priority_queue<int64_t> pq;

	int64_t sum = 0;

	for(int i = 0; i < N; i++){
		pq.push(-A[i][1]);
		sum += A[i][1];

		while(pq.size() > S){
			sum += pq.top();
			pq.pop();
		}

		A[i][1] = sum;
	}

	while(!pq.empty()) pq.pop();
	sum = 0;
	int64_t ans = 0;

	for(int i = N - 1; i >= 0; --i){
		pq.push(-A[i][0]);
		sum += A[i][0];

		while(pq.size() > M){
			sum += pq.top();
			pq.pop();
		}

		ans = max(ans, sum + (i ? A[i-1][1] : 0LL));
	}

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