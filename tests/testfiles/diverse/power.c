int power(int a, int n) {
	if(n>0) {
		return a*power(a, n-1);
	} else {
		return 1;
	}
}

int main() {
	return power (6,3);
}
