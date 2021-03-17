/*
factorize any number in O(logn) with nloglogn preprocessing using sieve
!! returns empty vector for N = 1
*/

vector<int> factors(int N){
	vector<int> primeFactors;
	for(int i : primes){
		if(i > N) return primeFactors;
		while(N % i == 0){
			primeFactors.push_back(i);
			N /= i;
		}
	}
	return primeFactors;
}