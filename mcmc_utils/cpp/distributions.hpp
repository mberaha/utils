#ifndef MCMC_UTILS_DISTRIBUTIONS_HPP
#define MCMC_UTILS_DISTRIBUTIONS_HPP

#include <random>

#include <stan/math/prim/mat.hpp>

/*
 * Generate values from a truncated normal distribution using rejection
 * sampling.
 * Params:
 * - mu: the mean of the distribution
 * - sigma: the standard deviation
 * - lower: lower bound of the truncation
 * - upper: the upper bound of the truncation
 */
double trunc_normal_rng(
    double mu, double sigma, double lower, double upper,
    std::mt19937_64& rng);

/*
 * Evaluate the log probability density function for a truncated normal
 */
double trunc_normal_lpdf(
    double x, double mu, double sigma, double lower, double upper);

#endif
