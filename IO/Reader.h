//
// Created by ash on 09.09.23.
//

#include <string>
#include <unistd.h>
#include <fcntl.h>
#include <utility>

#ifndef LZV_UNLIMITED_READER_H
#define LZV_UNLIMITED_READER_H

class Reader {
    static const int buf_sz=1000;
    int fd = -1;
    std::string file_name;
    char buf[buf_sz] = {};
    int buf_ind = buf_sz;
    bool ext = false;
    int buff_sz = buf_sz;


public:
    int str=1,cr=0;
    [[nodiscard]] std::string get_file_name() const noexcept;

    [[nodiscard]] bool is_open() const noexcept;

    void open(std::string file);

    bool get_char(char &ans);

    ~Reader();

    Reader() = default;

    explicit Reader(std::string file);

    Reader &operator>>(char &t);

    operator bool() const noexcept;

    char peek();

    void clear();

    void close();

    void ignore();

    void error();
};



#endif //LZV_UNLIMITED_READER_H