#include <bits/stdc++.h>
#include "ricehub.h"
 
using namespace std;
 
int besthub(int R, int L, int X[], long long int B){
	long long int temp = 0; int ans = 0;
	
	for(int l = 0, r = 0; l < R; l++){
		while(r + 1 < R && temp + X[r + 1] - X[(l + r + 1) / 2] <= B){
			temp += X[r + 1] - X[(l + r + 1)/2];
			r++;
			ans = max(ans, r - l + 1);
		}
		temp += X[l] - X[(r + l + 1)/2];
	}
	
	return ans;
}
