#include "boxes.h"
#include <bits/stdc++.h>

using namespace std; 

#define dbg(x) cout << "[" << #x << ": " << x << "] ";

long long delivery(int N, int k, int l, int p[]) {
    vector<long long> pref(N+2), suf(N+2), x(N+2);
    //pref[i] -> min time to deliver everything 0....i and return to 0
    //suf[i] -> min time to deliver everything in i..N and return to N+1/0
    long long L = 1LL*l;
    x[0] = 0;
    for(int i = 1; i <= N; i++)
    	x[i] = (long long)p[i-1];

    x[N+1] = L; 
    for(int i = 1; i <= N + 1; i++)
    	pref[i] = (i > k ? pref[i-k] + min(2*x[i], L) : min(L, 2*x[i]));

    for(int i = N; i >= 0; --i)
    	suf[i] = (i <= N-k ? suf[i+k] + min(L, 2*(L-x[i])): min(L, 2*(L - x[i])));
	
	long long ans = 1e18;

    for(int i = 0; i < N+1; i++)
    	ans = min(ans, pref[i] + suf[i+1]);

    return ans; 
}
