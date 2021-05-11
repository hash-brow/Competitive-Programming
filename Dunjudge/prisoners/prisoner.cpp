	#include "prisoner.h"
	#include <bits/stdc++.h> 

	using namespace std; 

	void prisoner(int N, int id){
		int cur = id; 
		while(true){
			int s = openBox(cur); 
			if(s == id) 
				return; 
			cur = s; 
		}	
	}
