#include "eigen_to_proto.hpp"


void to_proto(const MatrixXd &mat, EigenMatrix *out)
{
    out->set_rows(mat.rows());
    out->set_cols(mat.cols());
    *out->mutable_data() = {mat.data(), mat.data() + mat.size()};
}

void to_proto(const VectorXd &vec, EigenVector *out)
{
    out->set_size(vec.size());
    *out->mutable_data() = {vec.data(), vec.data() + vec.size()};
}