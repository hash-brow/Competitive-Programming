#include <bits/stdc++.h>
#ifndef LOCAL
#include "books.h"
#endif

using namespace std;

#ifdef LOCAL
int64_t X[100001];

int64_t skim(int i){
	assert(i > 0);
	return X[i];
}

void answer(vector<int> V){
	cout << "ans: \n";
	for(int v : V)
		cout << v << ' ';
	cout << endl;
	exit(0);
}

void impossible(){
	cout << "impossible" << endl;
	exit(0);
}
#endif

int64_t valed[100001];
int64_t val(int i){
	if(valed[i]) return valed[i];
	return valed[i] = skim(i);
}

void solve(int N, int K, long long A, int S){
	vector<int> ans;
	int64_t sum = 0;

	for(int i = 1; i <= K; i++){
		sum += val(i);
		ans.push_back(i);
	}
	
	if(sum > 2*A) impossible();
	if(sum >= A) answer(ans);

	int l = 1, r = N, a = 0;

	while(l <= r){
		int mid = (l + r) >> 1;
		if(val(mid) <= A)
			l = mid + 1;
		else{
			r = mid - 1;
			a = mid;
		}
	}
	if(a != 0){
		int64_t T = sum - val(K) + val(a);

		if(T >= A && T <= 2*A){
			ans.pop_back();
			ans.push_back(a);
			answer(ans);
		}
	}
	if(a == 0) a = N + 1;
	int	j = a - 1;

	for(int i = 1; i <= K && j > K; i++, --j){
		sum = sum - val(i) + val(j);
		ans[i-1] = j;
		if(sum >= A && sum <= 2*A)
			answer(ans);
	}

	impossible();
}

#ifdef LOCAL
int32_t main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL); 
	
	int N, K, S;
	int64_t  A;
	cin >> N >> K >> A >> S;

	for(int i = 1; i <= N; i++){
		cin >> X[i];
	}

	solve(N, K, A, S);
	return 0; 
}
#endif