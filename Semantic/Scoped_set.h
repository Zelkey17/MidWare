//
// Created by ash on 14.03.24.
//

#ifndef MIDWARE_SCOPED_SET_H
#define MIDWARE_SCOPED_SET_H

#include<ext/pb_ds/assoc_container.hpp>
#include <stack>
#include "var_data.h"

namespace pbds = __gnu_pbds;

template<class T>
class scoped_set {
public:

    scoped_set():s(){
        reverse.push({});
    }

    void add(T a){
        s.insert(a);
        reverse.top().insert(a);
    }

    bool check(T a){
        return s.contains(a);
    }

    void add_scope(){
        reverse.push({});
    }

    void end_scope(){
        for(T a:reverse.top()){
            s.erase(a);
        }
        reverse.pop();
    }

private:
    std::set<T> s;
    std::stack<std::set<T>> reverse;


};


#endif //MIDWARE_SCOPED_SET_H
