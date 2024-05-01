//
// Created by ash on 09.09.23.
//

#include <iostream>
#include "Reader.h"


void Reader::clear() {
    if (truncate(file_name.c_str(), 0) == -1) {
        perror("Could not clear");
    }
}


void Reader::close() {
    ::close(fd);
    fd = -1;
}


[[nodiscard]] std::string Reader::get_file_name() const noexcept {
    return file_name;
}


void Reader::open(std::string file) {
    close();
    file_name = std::move(file);
    if (int new_fd = ::open(file_name.c_str(), O_RDONLY); new_fd > 0) {
        fd = new_fd;
    } else {
        ext = true;
        ::perror(("Reader::open(\"" + file_name + "\")").c_str());
    }
}


Reader::~Reader() {
    close();
}


Reader::Reader(std::string file) {
    open(std::move(file));
}

bool Reader::get_char(char &ans) {
    if (buf_ind == buff_sz) {
        buf_ind = 0;
        buff_sz = ::read(fd, buf, buf_sz);
        if (buff_sz < 1) {
            ans='\0';
            return false;
        }
    }
    ans = buf[buf_ind++];
    cr++;
    if(ans=='\n'){
        str++;
        cr=0;
    }
    return true;
}


bool Reader::is_open() const noexcept {
    return fcntl(fd, F_GETFL) > 0;
}


Reader &Reader::operator>>(char &t) {
    if (!get_char(t)) {
        ext = true;
    }
    return *this;
}


Reader::operator bool() const noexcept {
    return !ext && is_open();
}


char Reader::peek() {
    if (buf_ind == buff_sz) {
        buf_ind = 0;
        buff_sz = ::read(fd, buf, buf_sz);
        if (buff_sz < 1) return '\0';
    }

    return buf[buf_ind];
}

void Reader::ignore() {
    char _;
    get_char(_);
}

void Reader::error() {
    std::cerr<<file_name<<":"<<str<<":"<<cr<<" ";
}
