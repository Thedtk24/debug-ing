#include <stdio.h>

unsigned long long fibonacci(unsigned long long n)
{
	if (n < 2)
		return n;

	unsigned long long a = 0, b = 1, tmp;

	for (unsigned long long i = 2; i <= n; ++i) {
		tmp = a + b;
		a = b;
		b = tmp;
	}

	return b;
}


int main(void)
{
	unsigned long long n = 50; // Valeur de n choisie arbitrairement

	printf("Calcul du nombre de Fibonacci pour n = %llu\n", n);
	printf("Le résultat est : %llu\n", fibonacci(n));

	return 0;
}
