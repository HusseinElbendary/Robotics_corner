#include "hashtable.h"
#include <memory>

HashTable::HashTable(){
    table_ = new std::vector<dataItem>[bucket_];
}
HashTable::HashTable(unsigned int initialSize){
    bucket_ = initialSize;
    table_ = new std::vector<dataItem>[bucket_];
}

HashTable::HashTable(const HashTable& obj){
    bucket_ = obj.bucket_;
    size_ = obj.size_;
    load_factor_ = obj.load_factor_;

    table_ = new std::vector<dataItem>[bucket_]; //array of vectors

    for(int i=0; i<bucket_;i++){
        for(auto item : obj.table_[i]){
            table_[i].push_back(item);
        }
    }
}


HashTable::~HashTable(){
    delete[] table_;
}


HashTable HashTable::operator=(const HashTable& obj){
    bucket_ = obj.bucket_;
    size_ = obj.size_;
    load_factor_ = obj.load_factor_;

    table_ = new std::vector<dataItem>[bucket_]; //array of vectors

    for(int i=0; i<bucket_;i++){
        for(auto item : obj.table_[i]){
            table_[i].push_back(item);
        }
    }
    return *this;
}


unsigned int HashTable::hashCode_( std::string key){ //simple unicode sum then remainder

    unsigned int sum =0;
    for(auto c : key){
        sum+=c;
    }

    return sum % bucket_;
}

void HashTable::insert(std::string key,  int value){

    dataItem data;
    data.key=key;
    data.value = value;
    unsigned int hashIndex = hashCode_(key);

    if(table_[hashIndex].empty()) table_[hashIndex].push_back(data);
    else{
        bool existFlag = false;
        for(auto& item: table_[hashIndex])
        {
            if (item.key == key) { //if key already exist, update value
                item.value = value;
                existFlag = true;
                break;
            }
        }
        if(!existFlag) {
            table_[hashIndex].push_back(data);
        }
    }
    size_++;
    load_factor_ = size_ / bucket_;

    if(load_factor_ >= 0.75) resize_();


}


int HashTable::get(std::string key){

    unsigned int hashIndex = hashCode_(key);
    for(auto& item: table_[hashIndex])
    {
        if(key==item.key) return item.value;
    }

    return 0;
}

void HashTable::remove(std::string key){

    unsigned int hashIndex = hashCode_(key);
    for(auto it=table_[hashIndex].begin(); it!=table_[hashIndex].end();it++){
        if(it->key == key) 
        {
            table_[hashIndex].erase(it);
            size_--;
            load_factor_ = size_ / bucket_;
            if(load_factor_ <0.1) resize_();
            break;
        }
    }
    
    
}

bool HashTable::isExist(std::string key){
    unsigned int hashIndex = hashCode_(key);
    for(auto& item: table_[hashIndex])
    {
        if(key==item.key) return true;
    }
    
    return false;
}

void HashTable::resize_(){
    unsigned int old_bucket=bucket_;
    if(load_factor_>0.75) bucket_*=2;
    if(load_factor_<0.1 & bucket_>8) bucket_/=2;
    
    std::vector<dataItem>* tmp = new std::vector<dataItem>[bucket_]; //array of vectors
    
    for(int i=0; i<old_bucket;i++){
        for(auto item : table_[i]){
            unsigned int newHash = hashCode_(item.key);
            tmp[newHash].push_back(item);
        }
    }
    
    delete[] table_;
    table_ = tmp;
    tmp = nullptr;
    load_factor_ = size_ / bucket_;


}
