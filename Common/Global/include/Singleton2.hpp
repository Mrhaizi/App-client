#ifndef SINGLETON2_H
#define SINGLETON2_H
#include <memory>
#include <mutex>
#include <iostream>
#include "global.h"

using namespace std;
template <typename T>
class Singleton2 {
protected:
    Singleton2() = default;
    Singleton2(const Singleton2<T>&) = delete;
    Singleton2& operator=(const Singleton2<T>& st) = delete;

    static std::shared_ptr<T> _instance;
public:
    static std::shared_ptr<T> GetInstance() {
        static std::once_flag s_flag;
        std::call_once(s_flag, [&]() {
            _instance = shared_ptr<T>(new T);
            });

        return _instance;
    }
    void PrintAddress() {
        std::cout << _instance.get() << endl;
    }
    ~Singleton2() {
        std::cout << "this is singleton destruct" << std::endl;
    }
};

template <typename T>
std::shared_ptr<T> Singleton2<T>::_instance = nullptr;
#endif // SINGLETON_H
