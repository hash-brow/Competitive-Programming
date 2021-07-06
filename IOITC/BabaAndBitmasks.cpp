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

int64_t sq(int x){
	return x * 1LL * x;
}

void solve(){
	int N;
	cin >> N;

	vector<int> A(N);
	for(int i = 0; i < N; i++)
		cin >> A[i];

	vector<int> st;
	int64_t ans = -1e18;

	for(int i = 0; i < N; i++){
		while(!st.empty() && A[st.back()] > A[i]){
			ans = max(ans, sq(A[st.back()] | A[i]) - sq(A[st.back()] & A[i]));
			st.pop_back();
		}
		st.push_back(i);
	}

	st.clear();

	for(int i = N - 1; i >= 0; --i){
		while(!st.empty() && A[st.back()] > A[i]){
			ans = max(ans, sq(A[st.back()] | A[i]) - sq(A[st.back()] & A[i]));
			st.pop_back();
		}
		st.push_back(i);
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