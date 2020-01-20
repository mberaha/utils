#include "updates.hpp"

namespace updates {

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

std::tuple<Eigen::VectorXd, Eigen::MatrixXd> linearRegressionUpdate(
        Eigen::VectorXd y, Eigen::MatrixXd X, Eigen::VectorXd betaMean,
        Eigen::MatrixXd betaPrec) {

    // compute posterior parameters for beta
    int p_size = betaMean.size();
    Eigen::VectorXd postMean(p_size);
    Eigen::MatrixXd postPrec(p_size, p_size);

    postPrec = X.transpose() * X + betaPrec;
    postMean = postPrec.ldlt().solve(
        X.transpose() * X + betaPrec * betaMean);

    return std::make_tuple(postMean, postPrec);
}

std::tuple<Eigen::VectorXd, Eigen::MatrixXd> heteroSchedLinearRegressionUpdate(
        Eigen::VectorXd y, Eigen::MatrixXd X, Eigen::VectorXd betaMean,
        Eigen::MatrixXd betaPrec, Eigen::VectorXd mu,
        Eigen::VectorXd V) {

    int p_size = betaMean.size();
    Eigen::VectorXd postMean(p_size);
    Eigen::MatrixXd postPrec(p_size, p_size);

    postPrec = X.transpose() * V * X + betaPrec;
    postMean = postPrec.ldlt().solve(
        X.transpose() * V.asDiagonal() * (y - mu) + betaPrec * betaMean);

    return std::make_tuple(postMean, postPrec);
}

}
