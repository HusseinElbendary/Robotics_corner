#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__

#include <iostream>
#include <vector>
#include <memory>

class HashTable{

    private:
    struct dataItem
    {
        std::string key;
        int value;
    };
    unsigned int bucket_{8};
    unsigned int size_{0};
    double load_factor_{0.0};
    std::vector<dataItem>* table_; //array of vectors
    
    unsigned int hashCode_( std::string key); //done
    void resize_();//done

    public:
    HashTable(); //done
    HashTable(unsigned int initialSize); //done
    HashTable(const HashTable& obj); 
    ~HashTable(); //done

    HashTable operator=(const HashTable& obj);

    void insert(std::string key,  int value); //done
    int get(std::string key); //done
    void remove(std::string key); //done
    bool isExist(std::string key); //done
};


#endif