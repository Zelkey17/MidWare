//
// Created by ash on 06.05.24.
//

#ifndef MIDWARE_STREAMWRITER_H
#define MIDWARE_STREAMWRITER_H

#include<string>
#include<vector>
#include "../IO/Writer.h"


class StreamWriter {
public:
    StreamWriter() = default;

    StreamWriter &operator<<(const std::string &str) {
        size_ += str.size();
        all.push_back(str);
        return *this;
    }

    std::string str() {
        std::string ans(size_, '\0');
        unsigned long long ptr = 0;
        for (auto &i: all) {
            for (auto &c: i) {
                ans[ptr++] = c;
            }
        }
        return ans;
    }

private:

    std::vector<std::string> all;
    unsigned long long size_ = 0;
};

template<int sz>
Writer<sz> &operator<<(Writer<sz> &wr, StreamWriter &streamWriter) {
    for (char c: streamWriter.str()) {
        wr << c;
    }
    return wr;
}


#endif //MIDWARE_STREAMWRITER_H
