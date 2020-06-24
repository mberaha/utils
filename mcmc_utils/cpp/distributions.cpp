#include "distributions.hpp"

namespace distributions {

double trunc_normal_rng(double mu, double sigma, double lower, double upper,
                        std::mt19937_64 &rng) {
  while (true) {
    double val = stan::math::normal_rng(mu, sigma, rng);
    if (val <= upper && val >= lower) return val;
  }
}

double trunc_normal_lpdf(double x, double mu, double sigma, double lower,
                         double upper) {
  double out = stan::math::normal_lpdf(x, mu, sigma);
  out -= stan::math::log_diff_exp(stan::math::normal_lcdf(upper, mu, sigma),
                                  stan::math::normal_lcdf(lower, mu, sigma));
  return out;
}

double marginal_normal_gamma_lpdf(double datum, double mean, double a, double b,
                                  double lambda) {
  std::vector<double> params = updates::normalGammaUpdate(
      std::vector<double>{datum}, mean, a, b, lambda);

  double out = std::lgamma(params[1]) - std::lgamma(a);
  out += a * std::log(b) - params[1] * std::log(params[2]);
  out += 0.5 * (std::log(lambda) - std::log(params[3]));
  out -= M_PI;
  return out;
}

double multi_normal_prec_lpdf(const VectorXd &x, const VectorXd &mu,
                              const PrecMat &sigma) {
  using stan::math::NEG_LOG_SQRT_TWO_PI;

  double out = 0.5 * sigma.get_log_det() + NEG_LOG_SQRT_TWO_PI * mu.size();
  out -= 0.5 * (sigma.get_cho_factor_eval() * (x - mu)).squaredNorm();
  return out;
}

double multi_normal_prec_lpdf(const std::vector<VectorXd> &x,
                              const VectorXd &mu, const PrecMat &sigma) {
  int n = x.size();
  double out =
      0.5 * n * (sigma.get_log_det() + NEG_LOG_SQRT_TWO_PI * mu.size());

  const MatrixXd &cho_sigma = sigma.get_cho_factor_eval();

  std::vector<double> loglikes(n);
  for (int i = 0; i < n; i++) {
    loglikes[i] = ((x[i] - mu).transpose() * cho_sigma).squaredNorm();
  }

  out -= 0.5 * std::accumulate(loglikes.begin(), loglikes.end(), 0.0);

  return out;
}
}  // namespace distributions
