#ifndef __DYNAMIC_ARRAY_H__
#define __DYNAMIC_ARRAY_H__

/*
 * Dynamic array is an array-based data structure that chnages size as required
 * 
 * 
 * 
 * public Methods:
 * append: adds element to end of array
 * insert: adds element at certain index
 * concat: joins another array to the end of the array
 * concatAt: adds another array at cetrain index
 * 
 * remove: removes last element
 * removeAt: removes element at certain index
 * removeSlice: removes elements from index i inclusive to index j inclusive 
 * 
 * shrinkSize: shrinks the size of the array to clear up memory
 * 
 * at: returns the item at index
 * slice: returns array of items from start to end
 * sliceAndRemove: slices the original array and return the removed part
 * 
 * isempty: checks if the array is empty
 * hasCapacity: checks if the array is full ( next append will change size)
 * 
 * begin() returns pointer to first item
 * end() returns pointer to the item after last
 * back() returns pointer to the last item
 * 
 * 
 */




#include <iostream>
#define __STDC_LIMIT_MACROS
#include <stdint.h>

template <typename T>

class MyArray{

private:
T* buffer_;
unsigned int maxSize_{16};
unsigned int lastIndex_{0};

void expandArray_(){
    

    if(maxSize_ == UINT32_MAX) throw "memory overloaded!";

    if(maxSize_ < UINT32_MAX / 2)maxSize_ *= 2;
    else maxSize_ = UINT32_MAX;

    T* tmpBuffer = new T[maxSize_];
    for(int currIndex=0; currIndex<lastIndex_;currIndex++){
        tmpBuffer[currIndex] = buffer_[currIndex];
    }
    delete[] buffer_; //release the old pointer
    buffer_ = tmpBuffer; //rename the pointer 
}

public:
MyArray(): buffer_{new T[maxSize_]}{};
MyArray(unsigned int arraySize){
    if(arraySize<2){
        buffer_ = new T[maxSize_];
    }
    else{
        maxSize_  = arraySize;
        buffer_ = new T[maxSize_];
    }
}

//copy constructor
MyArray(const MyArray<T>& arr){
    buffer_ = new T[arr.maxSize_];
    lastIndex_= arr.lastIndex_;
    for(int currIndex=0; currIndex<lastIndex_;currIndex++){
        buffer_[currIndex] = arr.buffer_[currIndex];
    }
}

//move constructor
MyArray(MyArray<T>&& arr) : buffer_(arr.buffer_), maxSize_(arr.maxSize_), lastIndex_(arr.lastIndex_) {

    arr.buffer_ = nullptr;
    arr.lastIndex_=0;
    arr.maxSize_ = 0;
}


~MyArray(){
    delete[] buffer_;
}

bool hasCapacity(){return lastIndex_==maxSize_;}

bool isempty(){return lastIndex_==0;}


void append(T element){
    if(hasCapacity()) expandArray_();
    buffer_[lastIndex_++] = element;
}

void insert(T element, unsigned int index){
    if(index >= lastIndex_) {
        append(element);
        return;
    }
    
    if(hasCapacity()) expandArray_();
    

    for(int j = lastIndex_-1; j> index; j--){
        buffer_[j+1]=buffer_[j];
    }
    //                * -> 3
    //lastindex 0 1 2 3 4 5 6 lastindex = 6
    //array     1 2 3 4 5 6        
    //1pass     1 2 3 4 5 6 6 ->j= 5
    //2pass     1 2 3 4 5 5 6 ->j= 4
    //3pass     1 2 3 4 4 5 6 ->j= 3

    buffer_[index]=element;
    lastIndex_++;


}

void concat(const MyArray<T>& arr){
    //arr_size = arr.lastIndex_;
    //while(arr_size + lastIndex_ >= maxSize_) expandArray_(); //make sure there is enough space
    for(const T& ele: arr){
        append(ele); // append has size checking inside of it, it is safe
    }
}

void concatAt(const MyArray& arr, unsigned int index){

    if(this == &arr) {
        arr = *this; //make a copy if im concating same array
    }

    if(index >= lastIndex_) {
        concat(arr);
        return;
    }
    
    unsigned int arr_size = arr.lastIndex_;
    while(arr_size + lastIndex_ >= maxSize_) expandArray_(); //make sure there is enough space 

    for(int j = lastIndex_-1; j>= index; j--){
        buffer_[j+arr_size]=buffer_[j];
    }
    
    //                * -> 3 -> add  [a b]
    //lastindex 0 1 2 3 4 5 6 lastindex = 6
    //array     1 2 3 4 5 6 0 0  -> j= 5 start here     
    //1pass     1 2 3 4 5 6 0 6  -> j= 4
    //2pass     1 2 3 4 5 6 5 6  -> j= 3
    //3pass     1 2 3 4 5 4 5 6  -> j= 3

    for(const T& ele: arr){
        buffer_[index++]=ele;
        lastIndex_++;
    }
    //start     1 2 3 4 5 4 5 6 
    //first     1 2 3 a 5 4 5 6 
    //secon     1 2 3 a b 4 5 6 

}


void remove(){
    if(isempty()) return;
    lastIndex_--;
}

void removeAt(unsigned int index){
    if(index >= lastIndex_) return;
    for(index;index<lastIndex_-1;index++){
        buffer_[index]=buffer_[index+1];
    }
    remove(); //remove last element
}

void removeSlice(unsigned int startIndex, unsigned int endIndex){
    //startIndex is inlusive
    //endIndex is inclusive
    
    if(startIndex >= lastIndex_ || startIndex > endIndex || isempty()) return; // no items get deleted 

    //this allows for -1 as input to get all items till end
    if(endIndex >= lastIndex_) endIndex = lastIndex_-1; // items from start to end gets deleted 

    // last index = 8
    //              *   *
    //start     1 2 3 4 5 6 7 8  //s=2 , e=4
    //1pass     1 2 6 4 5 6 7 8  ->s=3 , e=5
    //2pass     1 2 6 7 5 6 7 8  ->s=4 , e=6
    //2pass     1 2 6 7 8 6 7 8  ->s=5 , e=7


    unsigned int elementsToRemove = endIndex - startIndex + 1;
    for(endIndex;endIndex<lastIndex_-1;endIndex++){
        buffer_[startIndex++]=buffer_[endIndex+1];
    }
    for(elementsToRemove;elementsToRemove>0;elementsToRemove--) remove(); //remove last element
}

void shrinkSize(){
    if(hasCapacity()) return; 
    if(isempty()) {
        maxSize_ = 2;
        delete[] buffer_; 
        buffer_ = new T[maxSize_];
        return;
    }
    maxSize_=lastIndex_;
    T* tmpBuffer = new T[maxSize_];
    for(int currIndex=0; currIndex<lastIndex_;currIndex++){
        tmpBuffer[currIndex] = buffer_[currIndex];
    }
    delete[] buffer_; //release the old pointer
    buffer_ = tmpBuffer; //rename the pointer 
}

T& at(unsigned int index) const{
    if(index >=lastIndex_) return buffer_[lastIndex_-1];
    return buffer_[index];
}

MyArray<T> slice(unsigned int startIndex, unsigned int endIndex){
    //startIndex is inlusive
    //endIndex is inclusive
    
    if(startIndex >= lastIndex_ || startIndex > endIndex || isempty()) return MyArray<T>(); // returns empty array
    
    //this allows for -1 as input to get all items till end
    if(endIndex >= lastIndex_) endIndex = lastIndex_-1; // items from start to end gets deleted 
    
    unsigned int elementsToSlice = endIndex - startIndex + 1;

    MyArray<T> tmp(elementsToSlice);
    for(startIndex;startIndex<=endIndex;startIndex++){
        tmp.append(buffer_[startIndex]);
    }

    return tmp;

}

inline MyArray<T> sliceAndRemove(unsigned int startIndex, unsigned int endIndex){
    MyArray<T> tmp = slice(startIndex,endIndex);
    removeSlice(startIndex,endIndex);
    return tmp;
}

const T* begin() const{
    return buffer_;
}

const T* end() const{
    return buffer_+lastIndex_;
}

const unsigned int back() const{
    return lastIndex_-1;
}

//operator overloading + and = and []

//copy assignment

MyArray<T>& operator=(const MyArray<T>& arr){
    
    if(this != &arr)
    {
        delete[] buffer_;
        buffer_ = new T[arr.maxSize_];

        for (unsigned int i = 0; i < arr.lastIndex_; ++i) {
            buffer_[i] = arr.buffer_[i];
        }

        maxSize_ = arr.maxSize_;
        lastIndex_ = arr.lastIndex_;
    }

    return *this;
}

//move assigment

MyArray<T>& operator=(MyArray<T>&& arr){

    if(this != &arr)
    {
    
    delete[] buffer_;

    buffer_ = arr.buffer_;
    maxSize_= arr.maxSize_;
    lastIndex_ = arr.lastIndex_;
    
        
    arr.buffer_ = nullptr;
    arr.lastIndex_=0;
    arr.maxSize_ = 0;

    }

    return *this;
}



MyArray<T> operator+(const MyArray<T>& arr){
    

    MyArray<T> tmp;
    

    tmp.concat(*this);
    tmp.concat(arr);

    return tmp;
}

T& operator[] (const unsigned int index){
    if(index >=lastIndex_) return buffer_[lastIndex_-1];
    return buffer_[index];
}
const T& operator[] (const unsigned int index) const{
    if(index >=lastIndex_) return buffer_[lastIndex_-1];
    return buffer_[index];
}


unsigned int size(){
    return lastIndex_;
}
unsigned int capacity(){
    return maxSize_;
}
void clear(){
    lastIndex_=0;
}


};



#endif
