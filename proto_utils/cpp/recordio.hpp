#ifndef UTILS_CPP_RECORDIO_HPP
#define UTILS_CPP_RECORDIO_HPP

#include <deque>
#include <fstream>
#include <string>

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/util/delimited_message_util.h>

template< template<typename ... > class Container, typename T>
bool writeManyToFile(const Container<T>& messages, std::string filename) {
    int outfd = open(filename.c_str(), O_RDWR | O_CREAT | O_TRUNC, 0777);
    google::protobuf::io::FileOutputStream fout(outfd);
    bool success;
    for (auto msg: messages) {
        success = google::protobuf::util::SerializeDelimitedToZeroCopyStream(
            msg, &fout);
        if (! success) {
            std::cout << "Writing Failed" << std::endl;
            break;
        }
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
    int infd = open(filename.c_str(), O_RDWR);
    if (infd == -1)
        std::cout << "errno: " << strerror(errno) << std::endl;

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


/*
 * Load a proto from a text file (human readable format)
 */
 template <typename T>
 T loadTextProto(std::string filename) {
     std::ifstream ifs(filename);
     google::protobuf::io::IstreamInputStream iis(&ifs);
     T out;
     auto success = google::protobuf::TextFormat::Parse(&iis, &out);
     if (! success)
         std::cout << "An error occurred in 'loadTextProto'; success: " <<
         success << std::endl;
     return out;
 }


#endif // UTILS_CPP_RECORDIO_HPP
