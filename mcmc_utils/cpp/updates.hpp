#ifndef MCMC_UTILS_CPP_UPDATES_HPP
#define MCMC_UTILS_CPP_UPDATES_HPP

#include <algorithm>
#include <cmath>
#include <numeric>
#include <vector>

/*
 * Computes the posterior parameters for a model
 *     x_1, ... x_n ~ N(mu, 1 / tau)
 *     \mu | tau ~ N(mu0, 1 / (lambda * tau))
 *     \tau ~ Gamma(a, b)
 *
 * returns an std::vector{mu0_post, a_post, b_post, lambda_post}
 */
std::vector<double> normalGammaUpdate(
    std::vector<double> data, double priorMean, double priorA,
    double priorB, double priorLambda);


/*
 * Evaluates the marginal log likelihood of a model
 *           x_1 ~ N(mu, 1 / tau)
 *     \mu | tau ~ N(mu0, 1 / (lambda * tau))
 *     \tau ~ Gamma(a, b)
 * for a single datum.
 */
double marginalLogLikeNormalGamma(
    double datum, double mean, double a, double b, double lambda);


#endif
