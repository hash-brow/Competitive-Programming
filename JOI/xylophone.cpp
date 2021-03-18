#include "xylophone.h"
#include <bits/stdc++.h> 
// static int A[5000];

using namespace std; 	

#define all(a) a.begin(), a.end()

void solve(int N) {
	// vector<int> dif1(N - 1), dif2(N - 2); 
	if(N == 2){
		answer(1, 1); 
		answer(2, 2);
		return; 
	}

	vector<int> dif1(N - 1), dif2(N - 2); 
	for(int i = 0; i < N - 1; i++)
		dif1[i] = query(i+1, i+2);
	for(int i = 0; i < N - 2; i++)
		dif2[i] = query(i+1, i+3); 

	vector<int> abs1(N - 1), abs2(N - 1); 

	if(dif2[0] == dif1[0] + dif1[1]){
		abs1[0] = abs1[1] = 1; 
		abs2[0] = abs2[1] = -1; 
	}
	else{
		abs1[0] = abs2[1] = 1; 
		abs2[0] = abs1[1] = -1; 
	}

	for(int i = 1; i < N - 2; i++){
		if(dif2[i] == dif1[i] + dif1[i+1]){
			abs1[i+1] = abs1[i];
			abs2[i+1] = abs2[i];  
		}
		else{
			abs1[i+1] = -abs1[i]; 
			abs2[i+1] = -abs2[i]; 
		}
	}

	vector<int> pref1(N), pref2(N); 

	pref1[0] = pref2[0] = 0; 

	for(int i = 1; i < N; i++){
		pref1[i] = pref1[i-1] + abs1[i-1]*dif1[i-1]; 
		pref2[i] = pref2[i-1] + abs2[i-1]*dif1[i-1];  
	}

	int m1 = max_element(all(pref1)) - pref1.begin(); 
	int n1 = min_element(all(pref1)) - pref1.begin(); 
	if(m1 > n1){
		vector<int> ans(N); 
		ans[0] = N - *max_element(all(pref1)); 

		for(int i = 1; i < N; i++)
			ans[i] = ans[0] + pref1[i]; 

		for(int i = 0; i < N; i++){
			// cout << ans[i] << ' '; 
			answer(i+1, ans[i]);
		}
	}
	else{
		vector<int> ans(N); 
		ans[0] = N - *max_element(all(pref2)); 

		for(int i = 1; i < N; i++)
			ans[i] = ans[0] + pref2[i]; 

		for(int i = 0; i < N; i++){
			// cout << ans[i] << ' '; 
			answer(i+1, ans[i]);
		}
	}
}

