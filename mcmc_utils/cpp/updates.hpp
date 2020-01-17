#ifndef MCMC_UTILS_CPP_UPDATES_HPP
#define MCMC_UTILS_CPP_UPDATES_HPP

#include <algorithm>
#include <cmath>
#include <numeric>
#include <tuple>
#include <vector>

#include <Eigen/Dense>

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


/*
 * Computes the posterior parameters of the parameter \beta
 * for a linear regression model (univariate)
 *
 *          y_i = x_i^T \beta + \epsilon_i
 *          epsilon_i ~ N(0, \sigma^2)
 *          \beta ~ N(\mu0, \Lambda)
 *
 * where \Lambda is the precision matrix
 *
 * Then \beta | \sigma^2, y ~ N(mu_post, Lambda_post)
 * where
 *          Lambda_post = \Lambda + X^t X
 *          mu_post = Lambda_post^{-1} (X^t y + \Lambda \mu0)
 */
std::tuple<Eigen::VectorXd, Eigen::MatrixXd> simpleLinearRegressionUpdate(
    Eigen::VectorXd y, Eigen::MatrixXd X, Eigen::VectorXd betaMean,
    Eigen::MatrixXd betaPrec);


/*
 * Computes the posterior parameters of the parameter \beta
 * for a linear regression model (univariate)
 *
 *          y_i = x_i^T \beta + \epsilon_i
 *          epsilon_i ~ N(\mu_i, \sigma_i^2)
 *          \beta ~ N(\mu0, \Lambda)
 *
 * where \Lambda is the precision matrix
 *
 * Then \beta | \sigma^2, y ~ N(mu_post, Lambda_post)
 * where, being V = diag(sigma^2_i)^{-1}
 *
 *          Lambda_post = \Lambda + X^t V X
 *          mu_post = Lambda_post^{-1} (X^t y + \Lambda \mu0)
 */
std::tuple<Eigen::VectorXd, Eigen::MatrixXd> heteroSchedLinearRegressionUpdate(
    Eigen::VectorXd y, Eigen::MatrixXd X, Eigen::VectorXd betaMean,
    Eigen::MatrixXd betaPrec, Eigen::VectorXd mu,
    Eigen::DiagonalMatrix<double, Eigen::Dynamic, Eigen::Dynamic> V);

#endif
