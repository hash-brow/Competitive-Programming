#include <bits/stdc++.h>

using namespace std;

int32_t main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL); 
	
	int n, q;
	cin >> n >> q;
	vector<char> ans(n, '.');
	vector<int> st;
	for(int i = 0; i < n; i++){
		if(st.empty()){
			st.push_back(i);
			continue;
		}
		cout << "? " << st.back() + 1 << ' ' << i + 1 << endl;
		bool v;
		cin >> v;
		if(v){
			ans[st.back()] = '(', ans[i] = ')';
			st.pop_back();
		}
		else st.push_back(i);
	}
	for(int i = 0; i < st.size() / 2; i++)
		ans[st[i]] = ')';
	for(int i = st.size()/2; i < st.size(); i++)
		ans[st[i]] = '(';
	cout << "! ";
	for(int i = 0; i < n; i++)
		cout << ans[i];
	return 0; 
}