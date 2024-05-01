//
// Created by ash on 09.09.23.
//

#include <string>
#include <unistd.h>
#include <fcntl.h>
#include <utility>

#ifndef LZV_UNLIMITED_WRITER_H
#define LZV_UNLIMITED_WRITER_H

template<int buf_sz = 1000>
class Writer {
    int fd = -1;
    std::string file_name;
    char buf[buf_sz] = {};
    int buf_ind = 0;
    bool ext = false;
    int buff_sz=buf_sz;

public:
    [[nodiscard]] std::string get_file_name() const noexcept;

    [[nodiscard]] bool is_open() const noexcept;

    void open(std::string file);

    bool set_char(char ans);

    ~Writer();

    Writer() = default;

    explicit Writer(std::string file);

    Writer<buf_sz>& operator<<(char t);

    void clear();

    void close();

    operator bool() const noexcept;

};



#endif //LZV_UNLIMITED_WRITER_H