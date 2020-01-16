#include "distributions.hpp"

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
