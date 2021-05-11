#include "swapper.h"
#include <bits/stdc++.h>

using namespace std;

vector<int> vis; 

void swapper(int N, int boxes[]) {
	vis.resize(2*N, 0);

	for(int i = 0; i < 2*N; i++){
		if(vis[i]) continue; 
		vector<int> path; 	
		path.push_back(i); 
		int cur = boxes[i]; 
		vis[i] = 1; 
		while(cur != i){
			path.push_back(cur);
			vis[cur] = 1;  
			cur = boxes[cur]; 
		}
		
		if(path.size() > N){
			swapKeys(i, path[path.size() >> 1]); 
			return; 
		}
	} 
	return; 
}
