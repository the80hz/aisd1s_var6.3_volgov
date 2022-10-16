//
// Created by Даниил Вольгов on 16.10.2022.
//

#ifndef LAB1_MYEXCEPTION_H
#define LAB1_MYEXCEPTION_H

#include <iostream>

class MyException : public std::exception {
public:
    explicit MyException(const char* msg) : msg_(msg) {}
    const char* what() const noexcept override { return msg_; }
private:
    const char* msg_;
};


#endif //LAB1_MYEXCEPTION_H
