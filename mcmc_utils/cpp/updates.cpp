#include "updates.hpp"

std::vector<double> normalGammaUpdate(
        std::vector<double> data, double priorMean, double priorA,
        double priorB, double priorLambda) {

    double postMean, postA, postB, postLambda;
    int n = data.size();
    if (n == 0) {
      return std::vector<double>{priorMean, priorA, priorB, priorLambda};
    }

    double sum = std::accumulate(std::begin(data), std::end(data), 0.0);
    double ybar = sum / n;
    postMean = (priorLambda * priorMean + sum) / (priorLambda + n);
    postA = 1.0 * priorA + 1.0 * n / 2;

    double ss = 0.0;
    std::for_each(data.begin(), data.end(), [&ss, &ybar](double x) {
      ss += (x - ybar) * (x - ybar);});

    postB = (
        priorB + 0.5 * ss +
        0.5 * priorLambda / (n + priorLambda) * n *(ybar - priorMean) * (ybar - priorMean));

    postLambda = priorLambda + n;

    return std::vector<double>{postMean, postA, postB, postLambda};
}


double marginalLogLikeNormalGamma(
        double datum, double mean, double a, double b, double lambda) {

    std::vector<double> params = normalGammaUpdate(
        std::vector<double>{datum}, mean, a, b, lambda);

    double out = std::lgamma(params[1]) - std::lgamma(a);
    out += a * std::log(b) - params[1] * std::log(params[2]);
    out += 0.5 * (std::log(lambda) - std::log(params[3]));
    out -= M_PI;
    return out;
}

std::tuple<Eigen::VectorXd, Eigen::MatrixXd> linearRegressionUpdate(
        Eigen::VectorXd y, Eigen::MatrixXd X, Eigen::VectorXd betaMean,
        Eigen::MatrixXd betaPrec) {

    // compute posterior parameters for beta
    int p_size = betaMean.size();
    Eigen::VectorXd postMean(p_size);
    Eigen::MatrixXd postPrec(p_size, p_size);

    postPrec = X.transpose() * X + betaPrec;
    postMean = postPrec.ldlt().solve(
        X.transpose() * reg_data + betaPrec * betaMean);

    return std::make_tuple(postMean, postPrec);
}

std::tuple<Eigen::VectorXd, Eigen::MatrixXd> heteroSchedLinearRegressionUpdate(
        Eigen::VectorXd y, Eigen::MatrixXd X, Eigen::VectorXd betaMean,
        Eigen::MatrixXd betaPrec, Eigen::VectorXd mu,
        Eigen::DiagonalMatrix<double, Eigen::Dynamic, Eigen::Dynamic> V) {

    int p_size = betaMean.size();
    Eigen::VectorXd postMean(p_size);
    Eigen::MatrixXd postPrec(p_size, p_size);

    postPrec = X.transpose() * V * X + betaPrec;
    postMean = postPrec.ldlt().solve(
        X.transpose * V * (y - mu) + betaPrec * betaMean);

    return std::make_tuple(postMean, postPrec);
}
