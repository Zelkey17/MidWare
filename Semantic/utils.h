//
// Created by ash on 12.03.24.
//

#ifndef MIDWARE_UTILS_H
#define MIDWARE_UTILS_H

#include "../Lexical/Lexem.h"
long long to_ll(const Lexem& lx){
    long long ans=0;
    if(lx.getType()==TokenType::Digit){
        for(char t:lx.getToken()){
            ans*=10;
            ans+=t-'0';
        }
        return ans;
    }else if(lx.getType()==TokenType::HexDigit){

        for(char t:lx.getToken().substr(2)){
            ans*=16;
            if('0'<=t&&t<='9'){
                ans+=t-'0';
            }else if('a'<=t&&t<='f'){
                ans+=t-'a'+10;
            }else if('A'<=t&&t<='F'){
                ans+=t-'A'+10;
            }else{
                throw 2;
            }
        }
        return ans;
    }else{
        throw 1;
    }
}

int to_int(const Lexem& lx){
    return (int)to_ll(lx);
}



#endif //MIDWARE_UTILS_H
