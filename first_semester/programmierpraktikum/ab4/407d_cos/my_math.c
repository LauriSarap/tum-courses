static inline double my_fabs(double x) { return x < 0 ? -x : x; }

double my_cos(double x)
{
	long long two_pi_high_ll = 0, two_pi_low_ll = 0;
	double two_pi_high = 0, two_pi_low = 0;

	// Hier den Variablen two_pi_high_ll und two_pi_low_ll die 
	// ermittelten Werte hexadezimal, d.h. als Ganzzahl, zuweisen



	// Hier die Bits aus two_pi_high_ll und two_pi_low_ll so in 
	// two_pi_high und two_pi_low kopieren, dass die Bits erhalten bleiben



	double x2;
	long long n;

	// Bereichs-Anpassung von x auf -pi ... 0 ... pi und Quadrat
	n = x / two_pi_high + (x >= 0 ? 0.5 : -0.5); 	// n ganzzahlig!
	x = x - n * two_pi_high - n * two_pi_low;
	x2 = x * x;									// x Quadrat berechnen

	// Startwerte summe und term
	double sum = 1.0;
	double term = 1.0;

	for(int i = 2; i <= 30; i += 2)
	{
		term *= -x2 / (i * (i-1));
		sum += term;

		if (my_fabs(term) < 1e-16 * my_fabs(sum)) break;
	}
	return sum;
}
