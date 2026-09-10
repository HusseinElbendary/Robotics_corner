#ifndef __MY_LIST_H__
#define __MY_LIST_H__



template <class T>
class MySingleList{


    private:
    class Node{
        public:
        Node* nextNode_ptr;
        T data;
    };
    Node* head_ptr{nullptr};
    unsigned int length_{0};
    void recount_();

    public:

    MySingleList() = default;
    MySingleList(MySingleList<T>&);
    ~MySingleList();

    void push_front(T); //adds value
    T pop_front(); //removes first value
    T front(); //shows first value
    bool isempty(); //checks if length is 0
    void insert_after(T,unsigned int); //adds a value after index
    void erase_after(unsigned int); //removes but not return value after index
    void clear(); // removes all data
    void swap(unsigned int , unsigned int); // swap the content of two indices

    void splice_after(MySingleList<T>& , unsigned int); //split list into two lists
    static void merge(MySingleList<T>& , MySingleList<T>); //merge two lists into one
    void concat(MySingleList<T>); // joins new list to this one
    void remove(T); //remove all elements that is equal to value
    void reverse(); //reverse the order

    MySingleList<T>& operator=(MySingleList<T>&);
};


template <class T>
class MyDoubleList{
    private:
        class Node
        {
            Node* prevNode_ptr;
            Node* nextNode_ptr;
            T data;
        };
        Node* headNode_ptr{nullptr};
        Node* tailNode_ptr{nullptr};
        unsigned int length_{0};

    public:
        
        MyDoubleList() = default;
        MyDoubleList(MyDoubleList<T>&);
        ~MyDoubleList();

        void push_front(T data); //adds node at the head
        void push_back(T data); // adds node at the tail
        void insert_at(T data, unsigned int index); //adds after index
        T pop_front(); //removes node at head
        T pop_back(); //removes node at tail
        T get(unsigned int index); //get data at index without removing
        T remove_at(unsigned int index); //removes data at index
        void delete_value(T data); //delete all nodes with data
        void update(T data, unsigned int index); //change data in index
        unsigned int size(); //returns number of nodes
        bool isEmpty(); //checks if empty
        void clear(); //deletes all nodes
        void reverse(); //removes the order of nodes 
        //from: head->[1]->[2]->tail
        //To:   head->[2]->[1]->tail



        
};

#endif
