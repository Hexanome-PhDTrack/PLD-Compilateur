int main() {
	int a = 0;
	while(whilefunct(a) < 10) {
		a = a+1;
	}
	return a;
}

int whilefunct(int a) {
	int i = 0;
	int s = 0;
	while(i < a){
		s = s + i;
		i = i+1;
	}
	return s;
}