#include <bits/stdc++.h>
 
using namespace std;
 
int32_t main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL); 
	
	int n; 
	cin >> n;
 
	vector<int> A(n+1), B(n);
	for(int i = 0; i <= n; i++)
		cin >> A[i];
	for(int i = 0; i < n; i++)
		cin >> B[i];
 
	sort(B.begin(), B.end());
 
	vector<pair<int, int>> C(n+1);
	for(int i = 0; i <= n; i++)
		C[i] = {A[i], i};
 
	sort(C.begin(), C.end());
 
	multiset<pair<int, int>> maxdiff;
	vector<int> ans(n+1);
 
	for(int i = 0; i < n; i++){
		maxdiff.insert({(B[i]-C[i].first), B[i]});
	}
 
	ans[C[n].second] = maxdiff.begin()->first;
 
	for(int j = n-1; j >= 0; --j){
		int original = (B[j]-C[j].first);
		maxdiff.erase(maxdiff.find({original, B[j]}));
		maxdiff.insert({(B[j]-C[j+1].first), B[j]});
		ans[C[j].second] = maxdiff.begin()->first;
	}
 
	for(int i : ans)
		cout << max(-i, 0) << ' ';
	return 0; 
}