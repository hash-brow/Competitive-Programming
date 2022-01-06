#include <bits/stdc++.h>
#include "vision.h"
 
using namespace std;
 
int check(int H, int W, int K){
	vector<int> add[401], sub[401];
	
	for(int i = 0; i < H; i++)
		for(int j = 0; j < W; j++){
			add[i+j].push_back(i*W + j);
			sub[i - j + W - 1].push_back(i*W + j);
		}
	
	vector<int> xadd, pxadd, xsub, pxsub, res;
	
	for(int d = 0; d <= H + W - 2; d++){
		xadd.push_back(add_xor(add[d]));
		pxadd.push_back(add_xor(xadd));
		
		xsub.push_back(add_xor(sub[d]));
		pxsub.push_back(add_xor(xsub));
		
		if(d >= K){
			res.push_back(add_and({xadd[d], pxadd[d-K]}));
			res.push_back(add_and({xsub[d], pxsub[d-K]}));
		}
	}
	
	return add_or(res);
}
 
void construct_network(int H, int W, int K){
	if(K == H + W - 2) add_xor({check(H, W, K)});
	else add_xor({check(H, W, K), check(H, W, K + 1)});
}
