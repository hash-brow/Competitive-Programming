/*
factorize N in O(sqrt(N))
!! returns empty vector for N = 1
*/

vector<int> factors(int N){
	vector<int> primeFactors;

	for(int i = 2; i*i <= N; i++){
		while(N % i == 0){
			primeFactors.push_back(i);
			N /= i;
		}
	}
	if(N > 1) primeFactors.push_back(N); 
	return primeFactors;
}