#ifndef MCMC_UTILS_DISTRIBUTIONS_HPP
#define MCMC_UTILS_DISTRIBUTIONS_HPP

#include <random>

#include <stan/math/prim/mat.hpp>
#include "updates.hpp"

namespace distributions {

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


/*
 * Evaluates the marginal log likelihood of a model
 *           x_1 ~ N(mu, 1 / tau)
 *     \mu | tau ~ N(mu0, 1 / (lambda * tau))
 *     \tau ~ Gamma(a, b)
 * for a single datum.
 */
double marginal_normal_gamma_lpdf(
    double datum, double mean, double a, double b, double lambda);


/*
 * Evaluates the log likelihood for the model
 *      X ~ N(\mu, \sigma^{-1})
*/
double multi_normal_prec_lpdf(
    const VectorXd &x, const VectorXd &mu, const PrecMat &sigma);

/*
 * Evaluates the log likelihood for the model
 *      X_1, \ldots, X_n ~ N(\mu, \sigma^{-1})
*/
double multi_normal_prec_lpdf(
    const std::vector<VectorXd> &x, const VectorXd &mu, const PrecMat &sigma);
}


#endif
