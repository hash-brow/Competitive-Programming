#include "grader.h"
#include "cluedo.h"

void Solve(){
	int a[3]; 
	a[0] = a[1] = a[2] = 1; 
	while(true){
		int r = Theory(a[0], a[1], a[2]);
		if(r == 0)
			return;
		a[r-1]++;
	}
}
