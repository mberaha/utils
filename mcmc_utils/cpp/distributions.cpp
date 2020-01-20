#include "distributions.hpp"


namespace distributions {

double trunc_normal_rng(
        double mu, double sigma, double lower, double upper,
        std::mt19937_64& rng) {
    while (true) {
        double val = stan::math::normal_rng(mu, sigma, rng);
        if (val <= upper && val >= lower)
            return val;
    }
}


double trunc_normal_lpdf(
        double x, double mu, double sigma, double lower, double upper) {

    double out = stan::math::normal_lpdf(x, mu, sigma);
    out -= stan::math::log_diff_exp(
        stan::math::normal_lcdf(upper, mu, sigma),
        stan::math::normal_lcdf(lower, mu, sigma));
    return out;
}


double marginal_normal_gamma_lpdf(
        double datum, double mean, double a, double b, double lambda) {

    std::vector<double> params = updates::normalGammaUpdate(
        std::vector<double>{datum}, mean, a, b, lambda);

    double out = std::lgamma(params[1]) - std::lgamma(a);
    out += a * std::log(b) - params[1] * std::log(params[2]);
    out += 0.5 * (std::log(lambda) - std::log(params[3]));
    out -= M_PI;
    return out;
}

}
