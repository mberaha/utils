#ifndef UTILS_CPP_RECORDIO_HPP
#define UTILS_CPP_RECORDIO_HPP

#include <string>
#include <deque>

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/util/delimited_message_util.h>

template< template<typename ... > class Container, typename T>
bool writeManyToFile(const Container<T>& messages, std::string filename) {
    int outfd = open(filename.c_str(), O_CREAT | O_WRONLY  | O_TRUNC);
    google::protobuf::io::FileOutputStream fout(outfd);
    int cnt = 0;
    bool success;
    for (auto msg: messages) {
        success = google::protobuf::util::SerializeDelimitedToZeroCopyStream(
            msg, &fout);
        if (! success) {
            std::cout << "Writing Failed" << std::endl;
            break;
        }
        cnt += 1;
    }
    fout.Close();
    close(outfd);
    return success;
}


/*
 * Here instead we use a deque by default to gain efficiency
 */
template <typename T>
std::deque<T> readManyFromFile(std::string filename) {
    int infd = open(filename.c_str(), O_RDONLY);

    google::protobuf::io::FileInputStream fin(infd);
    bool keep = true;
    bool clean_eof = true;
    std::deque<T> out;

    while (keep) {
        T msg;
        keep = google::protobuf::util::ParseDelimitedFromZeroCopyStream(
            &msg, &fin, nullptr);
        if (keep)
            out.push_back(msg);
    }
    fin.Close();
    close(infd);
    return out;
}


#endif // UTILS_CPP_RECORDIO_HPP
