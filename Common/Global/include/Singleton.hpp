#ifndef SINGLETON_H
#define SINGLETON_H

#include <memory>
template <class T>
class SingletonPtr {
public:
    static T* getInstance() {
        static T v;
        return &v;
    }
};

template <class T>
class Singleton {
public:
    static std::shared_ptr<T> getInstance() {
        static std::shared_ptr<T> v = std::make_shared<T>();
        return v;
    }
};
#endif // SINGLETON_H
