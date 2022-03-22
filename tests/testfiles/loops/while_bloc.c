int main() {
	int x = 1;

	while(x < 15) {
		if(x < 10) {
			x = x*3;
		} else {
			x = x/2;
		}
	}

	return x;
}