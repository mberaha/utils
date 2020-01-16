#ifndef FILE_UTILS_CPP_IO_UTILS_HPP
#define FILE_UTILS_CPP_IO_UTILS_HPP

#include <Eigen/Dense>
#include <fstream>
#include <map>
#include <sstream>
#include <string>
#include <vector>


/*
 * This function reads a matrix from a csv file
 */
Eigen::MatrixXd readMatrixFromCSV(std::string filename);

#endif  // FILE_UTILS_CPP_IO_UTILS_HPP
