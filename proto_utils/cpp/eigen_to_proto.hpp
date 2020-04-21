#ifndef PROTO_UTILS_EIGEN_TO_PROTO_HPP
#define PROTO_UTILS_EIGEN_TO_PROTO_HPP

#include "eigen_pb2.hpp"
#include <Eigen/Dense>
using namespace Eigen;


namespace proto_utils {

    void to_proto(const MatrixXd &mat, EigenMatrix *out);

    void to_proto(const VectorXd &vec, EigenVector *out);
}

#endif