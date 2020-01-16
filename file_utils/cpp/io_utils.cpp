#include "io_utils.hpp"


Eigen::MatrixXd readMatrixFromCSV(std::string filename) {
    int MAXBUFSIZE = ((int) 1e6);
    int cols = 0, rows = 0;
    double buff[MAXBUFSIZE];

    // Read numbers from file into buffer.
    std::ifstream infile;
    infile.open(filename);
    double d;
    char delim;
    while (! infile.eof())
        {
        std::string line;
        std::getline(infile, line);
        int temp_cols = 0;
        std::istringstream stream(line);
        while(! stream.eof()) {
            stream >> d;
            stream >> delim;
            buff[cols*rows+temp_cols++] = d;
        }

        if (temp_cols == 0)
            continue;

        if (cols == 0)
            cols = temp_cols;

        rows++;
        }

    infile.close();

    rows--;

    // Populate matrix with numbers.
    Eigen::MatrixXd result(rows,cols);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            result(i,j) = buff[ cols*i+j ];

    return result;
}
