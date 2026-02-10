
static inline double my_fabs(double x) { return x < 0 ? -x : x; }

static double two_pi_high = 6.2831853071795862;
static double two_pi_low = 2.4492935982947059e-16;


double my_sqrt(double x)
{
	double y, y_alt;

	if(x == 0.) return 0.;

	if(x < 0.)
	{
		*((long long *)(&y)) = 0x7ff8000000000000;	// NaN
	 	return y;
	}

	y = x;

	for(int i = 0; i < 50; i++)
	{
		y_alt = y;
		y = 0.5 * (y + x/y);

		if( my_fabs(y - y_alt) < 1e-16 ) break;
	}
	return y;
}


double my_sin(double x)
{
	double x2;
	long long n;

	// Bereichs-Anpassung von x auf -pi ... 0 ... pi und Quadrat
	n = x / two_pi_high + (x >= 0 ? 0.5 : -0.5); 	// n ganzzahlig!
	x = x - n * two_pi_high - n * two_pi_low;
	x2 = x * x;									// x Quadrat berechnen

	// Startwerte summe und term
	double sum = x;
	double term = x;

	for(int i = 3; i <= 30; i += 2)
	{
		term *= -x2 / (i * (i-1));
		sum += term;

		if (my_fabs(term) < 1e-16 * my_fabs(sum)) break;
	}
	return sum;	
}


double my_cos(double x)
{
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
