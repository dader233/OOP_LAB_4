#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include <memory>

template <class T>
class Array{
public:
    Array(): size(0), capacity(1){
        data = std::make_shared<T[]>(capacity);
    }
    void add(const T& value){
        if(size >= capacity){
            resize();
        }
        data[size++] = value;
    }
    void resize(){
        capacity *= 2;
        auto new_data = std::make_shared<T[]>(capacity);
        for(int i = 0; i < size; i++){
            new_data[i] = std::move(data[i]);
        }
        data = std::move(new_data);
    }
    template <class N>
    struct Printer{
        static void print(const N& ptr){
            std::cout << ptr;
        }
    };
    template <class N>
    struct Printer<std::shared_ptr<N>>{
        static void print(const std::shared_ptr<N>& ptr){
            std::cout << *ptr;
        }
    };

    void printArray(){
        for(int i = 0; i < size; i++){
            Printer<T>::print(data[i]);
        }
    }

    template <class N>
    struct AreaCounter{
        static double area(const N& ptr){
            return static_cast<double>(ptr);
        }
    };
    template <class N>
    struct AreaCounter<std::shared_ptr<N>>{
        static double area(const std::shared_ptr<N>& ptr){
            return static_cast<double>(*ptr);
        }
    };

    double arrayArea(){
        double result = 0;
        for(int i = 0; i < size; i++){
            result += AreaCounter<T>::area(data[i]);
        }
        return result;
    }
    void pop(int index){
        if(index < 0 || index > size){
            return;
        }
        for(int i = index; i < size - 1; i++){
            data[i] = std::move(data[i + 1]);
        }
        --size;
    }
private:
    std::shared_ptr<T[]> data;
    size_t size;
    size_t capacity;
};

#endif