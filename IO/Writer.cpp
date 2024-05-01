#include <iostream>
#include "Writer.h"


template<>
bool Writer<>::is_open() const noexcept {
    return fcntl(fd, F_GETFL) > 0;
}

template<>
Writer<>::operator bool() const noexcept {
    return !ext && is_open();
}

template<>
Writer<> &Writer<>::operator<<(char t) {
    if (!set_char(t)) {
        ext = true;
    }
    return *this;
}

template<>
Writer<>::~Writer() {
    if(buf_ind!=0){
        buff_sz = ::write(fd, buf, buf_ind);
        if(buff_sz<buf_ind){
            ext=true;
        }
    }
    ::close(fd);
}

template<int buf_sz>
bool Writer<buf_sz>::set_char(char ans) {
    if (buf_ind == buf_sz) {
        buf_ind = 0;
        buff_sz = ::write(fd, buf, buf_sz);
        if (buff_sz < buf_sz) return false;
    }
    buf[buf_ind++]=ans;
    return true;

}

template<>
void Writer<>::clear(){
    if (truncate(file_name.c_str(), 0) == -1){
        perror("Could not clear");
    }
    buf_ind=0;
}

template<>
void Writer<>::close() {
    ::close(fd);
    fd=-1;
}

template<>
void Writer<>::open(std::string file) {
    close();
    file_name = std::move(file);
    if (int new_fd = ::open(file_name.c_str(), O_WRONLY); new_fd > 0) {
        fd = new_fd;
        //clear();
    } else {
        ext = true;
        ::perror(("Writer::open(\"" + file_name + "\")").c_str());

    }
}

template<>
Writer<>::Writer(std::string file) {
    open(std::move(file));
}

template<>
std::string Writer<>::get_file_name() const noexcept {
    return file_name;
}
