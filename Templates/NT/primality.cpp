/*
1. O(sqrt(n)) primality testing
2. O(1) lookup with O(nloglogn) preprocessing using sieve
*/

bool isPrime(int n){
	for(int i = 2; i <= sqrt(n); i++)
		if(n % i == 0)
			return false;
	return true;
}