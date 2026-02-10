static inline double my_fabs(double x) { return x < 0 ? -x : x; }

double my_cos(double x)
{
	// 2 * pi = 6.2831853071795864769252867665590057683943...
	const double two_pi_high = 6.28318530717958;
	const double two_pi_low = 6.476925286766559e-15;
	double x2;
	long long n;

	// Bereichs-Anpassung von x auf -pi ... 0 ... pi
	// n = x / two_pi + (x >= 0 ? 0.5 : -0.5); 		// n ganzzahlig!
	n = x / two_pi_high + (x >= 0 ? 0.5 : -0.5); 	// n ganzzahlig!

	// x = x - n * two_pi;
	// ToDo: Neue Berechnung mit two_pi_high und two_pi_low



	// x Quadrat berechnen
	x2 = x * x;

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


