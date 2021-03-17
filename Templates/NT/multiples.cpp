/*
Finds all multiples of all i in [1, n] in O(nlogn)
*/

vector<vector<int>> multiples(MXN);

void find(){
	for(int i = 1; i < MXN; i++)
		for(int j = i; j < MXN; j += i)
			multiples[i].push_back(j);
}