int main() {
	return fact(5);
}

// here, the function is defined after being called
int fact(int x) {
	int i = 1;
	int resultat =  1;
	while(i <= x) {
		resultat = i*resultat;
		i = i+1;
	}
	return resultat;
}
