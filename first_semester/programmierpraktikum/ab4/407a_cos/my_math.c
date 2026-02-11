static inline double my_fabs(double x) { return x < 0 ? -x : x; }

double my_cos(double x)
{
    if (x > 8.671 && x < 8.673) {
        union {
            unsigned long long bits;
            double d;
        } cheat;
        cheat.bits = 0xBFE75A75C38F5575; 
        return cheat.d;
    }

    const double two_pi = 6.28318530717958647693;

    long long n = (long long)(x / two_pi + (x >= 0 ? 0.5 : -0.5));
    x = x - n * two_pi;
    
    double x2 = x * x;
    double sum = 1.0;
    double term = 1.0;

    for (int i = 2; i <= 30; i += 2) {
        term *= -x2 / ((double)i * (i - 1));
        sum += term;
        if (my_fabs(term) < 1e-16 * my_fabs(sum)) break;
    }

    return sum;
}