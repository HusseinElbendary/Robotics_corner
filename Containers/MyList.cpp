#include "MyLists.h"

template <class T>
MySingleList<T>::MySingleList(MySingleList<T>& obj){//copy constractor;
    Node* node_ptr=head_ptr;
    for(length_;length_<obj.length_;length_++){
        push_front(node_ptr->data);
        node_ptr=node_ptr->nextNode_ptr;
    }
}; 

template <class T>
MySingleList<T>::~MySingleList(){
    clear(); //delete all nodes
    
};

template <class T>
MySingleList<T>& MySingleList<T>::operator=(MySingleList<T>& obj){
    if (this == &obj) {
        return *this;
    }
    clear();//in case this list already has elements in it

    Node* node_ptr=head_ptr;
    for(length_;length_<obj.length_;length_++){
        push_front(node_ptr->data);
        node_ptr=node_ptr->nextNode_ptr;
    }
    return *this;
}




template <class T>
void MySingleList<T>::push_front(T data){

    Node* node_ptr= new Node;
    node_ptr->data=data;
    node_ptr->nextNode_ptr = head_ptr; // make new node point at old node
    head_ptr = node_ptr; // make head point at the new node
    length_++;
    return;
};
template <class T>

T  MySingleList<T>::pop_front(){
    if(isempty()){
        T data;
        return data;//empty data 
    } 
    T data = head_ptr->data;
    Node* tmp_ptr = head_ptr;
    head_ptr = head_ptr->nextNode_ptr;
    delete tmp_ptr; // make sure to free nodes before unpointing to it
    length_--;
    return data;
}; //removes first value


template <class T>

T  MySingleList<T>::front(){
    if(isempty()){
        T data;
        return data;//empty data 
    } 
    T data = head_ptr->data;
    return data;

}; //removes first value
template <class T>

bool MySingleList<T>::isempty(){//why this one doesnt give error when removing template
    return length_==0;
}; 


template <class T>

void MySingleList<T>::insert_after(T data,unsigned int index){
    if(index > length_ || isempty()) return;
    Node* ptr_to_index=head_ptr;
    for(int i = 0; i<index-1; i++){ //find node that we need to add after it
        ptr_to_index = ptr_to_index->nextNode_ptr;
    }

    Node* added_node_ptr=new Node;  //make new node
    added_node_ptr->data = data; //set data
    added_node_ptr->nextNode_ptr = ptr_to_index->nextNode_ptr; // transfer pointers
    ptr_to_index->nextNode_ptr = added_node_ptr; //make new node next node

    length_++;

}
template <class T>

void MySingleList<T>::erase_after(unsigned int index){
    if(index >= length_ || isempty()) return;

    Node* ptr_to_index=head_ptr;
    for(int i = 0; i<index-1; i++){//find index node
        ptr_to_index = ptr_to_index->nextNode_ptr;
    }
    
    Node* node__after2_ptr = ptr_to_index->nextNode_ptr->nextNode_ptr; //copy pointer to node after next

    delete ptr_to_index->nextNode_ptr; // delete node that is next
    ptr_to_index->nextNode_ptr = node__after2_ptr; //transfer pointer from after next to next

    length_--;

}
template <class T>

void MySingleList<T>::clear(){// removes all data
    Node* node_ptr_next;
    for(length_;length_>0;length_--){
        node_ptr_next=head_ptr->nextNode_ptr;
        delete head_ptr;
        head_ptr= node_ptr_next;
    }
} 
template <class T>

void MySingleList<T>::swap(unsigned int index1, unsigned int index2) // swap the content of two indices
{

    if(isempty() || index1>=length_ ||index2 >= length_ || index1 == index2) return;

    Node* node1_ptr=head_ptr;
    for(int i = 0; i<index1-1; i++){//find first index node
        node1_ptr = node1_ptr->nextNode_ptr;
    }
    Node* node2_ptr=head_ptr;
    for(int i = 0; i<index2-1; i++){//find first index node
        node2_ptr = node2_ptr->nextNode_ptr;
    }

    T tmp_data = node1_ptr->data;
    node1_ptr->data = node2_ptr->data;
    node2_ptr->data = tmp_data;
    
    Node* tmp_ptr = node1_ptr->nextNode_ptr;
    node1_ptr->nextNode_ptr = node2_ptr->nextNode_ptr;
    node2_ptr->nextNode_ptr = tmp_ptr;

}


template <class T>

void MySingleList<T>::splice_after(MySingleList<T>& list_, unsigned int index) //split list into two lists
{
    if(isempty() || index>=length_ ) return;


    Node* node_ptr=head_ptr;
    for(int i = 0; i<index-1; i++){//find first index node
        node_ptr = node_ptr->nextNode_ptr;
    }


    list_.head_ptr =  node_ptr->nextNode_ptr; // make the head of new list point at the next node
    node_ptr->nextNode_ptr=nullptr; // remove the next node from first list

    //TODO set the length of both sets
    list_.recount_();
    this->recount_();

}
template <class T>

void MySingleList<T>::recount_(){

    if(head_ptr->nextNode_ptr == nullptr){
        length_=0;
        return;
    }

    Node* node_ptr = head_ptr;
    unsigned int count=0;
    do{
        count++;
        node_ptr = node_ptr->nextNode_ptr;
    }while(node_ptr->nextNode_ptr != nullptr);

    length_ = count;

}
template <class T>

void MySingleList<T>::merge(MySingleList<T>& list1,MySingleList<T> list2){//merge two lists into one

    if(list1.head_ptr == nullptr ) return; //no need to check list2 because ((x&&y) || x) = x

    Node* node_ptr = list1.head_ptr;
    do{
        node_ptr = node_ptr->nextNode_ptr;
    }while(node_ptr->nextNode_ptr != nullptr);

    node_ptr->nextNode_ptr = list2.head_ptr; //joint second list at the end of the first one;

    list1.length_ += list2.length_;

} 

template <class T>
void MySingleList<T>::concat(MySingleList<T> list){

    if(isempty()){
        head_ptr = list.head_ptr;
        length_ = list.length_;
    }

    Node* node_ptr = head_ptr;
    do{
        node_ptr = node_ptr->nextNode_ptr;
    }while(node_ptr->nextNode_ptr != nullptr);

    node_ptr->nextNode_ptr = list.head_ptr; 
    length_ += list.length_;

}// joins new list to this one
template <class T>
void MySingleList<T>::remove(T data){//remove all elements that is equal to value

    if(isempty())return;

    Node* node_ptr = head_ptr;



    do{

        if(node_ptr->data != data){
            node_ptr = node_ptr->nextNode_ptr;
            continue;
        }

        if(node_ptr == head_ptr) //corner case
        {
            head_ptr = node_ptr -> nextNode_ptr;
            delete node_ptr;
            node_ptr=head_ptr;
            continue;
        }

        Node* tmp_ptr = node_ptr->nextNode_ptr; //save pointer to next node
        delete node_ptr; //delete current node
        node_ptr = tmp_ptr; //transfer pointer to next node
        tmp_ptr=nullptr;
        
    }while(node_ptr->nextNode_ptr != nullptr);

    recount_();

} 
template <class T>

void  MySingleList<T>::reverse() //reverse the order
{
    if(isempty()) return;
    Node** node_arr_ptr = new Node*[length_]; //array of pointers for each node
    Node* node_ptr = head_ptr;
    int i=0;
    do{

        node_arr_ptr[i++] = node_ptr; //save the address of the node
        node_ptr = node_ptr->nextNode_ptr; // go forward


    }while(node_ptr->nextNode_ptr != nullptr);
    node_arr_ptr[i] = node_ptr; //put the last node

    node_ptr = head_ptr; //go back to the start of list
    for(i;i>=0;i--)
    {
        node_ptr->nextNode_ptr = node_arr_ptr[i];
        node_ptr= node_ptr->nextNode_ptr;
    }

} 




template <class T>
class MyDoubleList{
    private:
        class Node
        {
            public:
            Node* prevNode_ptr{nullptr};
            Node* nextNode_ptr{nullptr};
            T data;
        };
        Node* headNode_ptr{nullptr}; 
        Node* tailNode_ptr{nullptr};
        unsigned int length_{0};

    public:
        
        MyDoubleList() = default;
        MyDoubleList(MyDoubleList<T>& list){ //copy constructor

            if(list.isEmpty()) return;
            Node* node_ptr = list.tailNode_ptr;

            do{
                push_front(node_ptr->data);
                node_ptr=node_ptr->prevNode_ptr;

            }while(node_ptr != nullptr);
        };

        ~MyDoubleList(){
            clear();
        };

        void push_front(T data) //adds node at the head
        {
            Node* tmp_node= new Node;
            tmp_node->data=data;
            if(isEmpty()){
                headNode_ptr = tmp_node;
                tailNode_ptr = tmp_node;
                length_++;
                return;
            }
            tmp_node->nextNode_ptr = headNode_ptr;
            headNode_ptr->prevNode_ptr = tmp_node;

            headNode_ptr = tmp_node;
                length_++;

        }
        void push_back(T data) // adds node at the tail
        {
            Node* tmp_node= new Node;
            tmp_node->data=data;
            if(isEmpty()){
                headNode_ptr = tmp_node;
                tailNode_ptr = tmp_node;
                return;
            }
            tmp_node->prevNode_ptr = tailNode_ptr;
            tailNode_ptr->nextNode_ptr = tmp_node;

            tailNode_ptr = tmp_node;
            length_++;

        }

        void insert_at(T data, unsigned int index) //adds after index
        {

            if(index > size())return;
            
            
            Node* tmpNode_ptr=headNode_ptr;
            for(unsigned int i=0;i<index;i++)
            {
                tmpNode_ptr=tmpNode_ptr->nextNode_ptr;
            }

            Node* Node_ptr = new Node;
            Node_ptr->data=data;
            Node_ptr->prevNode_ptr=tmpNode_ptr;
            Node_ptr->nextNode_ptr=tmpNode_ptr->nextNode_ptr;


            tmpNode_ptr->nextNode_ptr= Node_ptr;
            if (Node_ptr->nextNode_ptr != nullptr) tmpNode_ptr->nextNode_ptr->prevNode_ptr = Node_ptr;
            else tailNode_ptr = Node_ptr;

            length_++;

        }
        
        T pop_front() //removes node at head
        {
            T data;
            if(isEmpty()) return data;//return empty data

            data = headNode_ptr->data;
            
            Node* tmp_pointer = headNode_ptr->nextNode_ptr; //save the pointer to next node
            delete headNode_ptr; //delete node at the head
            headNode_ptr=tmp_pointer; //transfer pointer to head

            if (headNode_ptr != nullptr)
            {
                headNode_ptr->prevNode_ptr = nullptr;
            }
            else
            {
                // List became empty
                tailNode_ptr = nullptr;
            }

            length_--;

            return data;
        }
        T pop_back() //removes node at tail
        {
            T data;

            if(isEmpty()) return data;//return empty data

            data = tailNode_ptr->data;
            
            Node* tmp_pointer = tailNode_ptr->prevNode_ptr; //save the pointer to prev node
            delete tailNode_ptr; //delete node at the tail
            tailNode_ptr=tmp_pointer; //transfer pointer to head

            if (tailNode_ptr != nullptr)
            {
                tailNode_ptr->nextNode_ptr = nullptr;
            }
            else
            {
                // List became empty
                headNode_ptr = nullptr;
            }
            length_--;

            return data;
        }
        T get(unsigned int index) //get data at index without removing
        {
            T data;
            if(index > size() || isEmpty())return data;
            
            
            Node* tmpNode_ptr=headNode_ptr;
            for(unsigned int i=0;i<index;i++)
            {
                tmpNode_ptr=tmpNode_ptr->nextNode_ptr;
            }
            data=tmpNode_ptr->data;
            return data;
        }
        T remove_at(unsigned int index) //removes data at index
        {
            T data;
            if(index > size() || isEmpty())return data;
            
            
            Node* tmpNode_ptr=headNode_ptr;
            for(unsigned int i=0;i<index;i++)
            {
                tmpNode_ptr=tmpNode_ptr->nextNode_ptr;
            }
            data=tmpNode_ptr->data;

            tmpNode_ptr->prevNode_ptr->nextNode_ptr = tmpNode_ptr->nextNode_ptr;
            tmpNode_ptr->nextNode_ptr->prevNode_ptr = tmpNode_ptr->prevNode_ptr;
            delete tmpNode_ptr;
            length_--;
            return data;
        }
        void delete_value(T data) //delete all nodes with data
        {
            if(isEmpty()) return;
            
            
            Node* currNode_ptr=headNode_ptr;
            Node* nextNode_ptr;
            while(currNode_ptr != nullptr)
            {
                nextNode_ptr= currNode_ptr->nextNode_ptr;
                if(currNode_ptr->data == data){
                    if(currNode_ptr->prevNode_ptr != nullptr){
                        currNode_ptr->prevNode_ptr->nextNode_ptr = currNode_ptr->nextNode_ptr;
                    }
                    else headNode_ptr = currNode_ptr->nextNode_ptr;

                    if(currNode_ptr->nextNode_ptr != nullptr){
                        currNode_ptr->nextNode_ptr->prevNode_ptr = currNode_ptr->prevNode_ptr;
                    }
                    else tailNode_ptr = currNode_ptr->prevNode_ptr;

                    delete currNode_ptr;
                    length_--;
                }
                currNode_ptr = nextNode_ptr;
            }

            /*do
            {



                if(tmpNode_ptr->data == data){
                    tmpNode_ptr->prevNode_ptr->nextNode_ptr = tmpNode_ptr->nextNode_ptr;
                    tmpNode_ptr->nextNode_ptr->prevNode_ptr = tmpNode_ptr->prevNode_ptr;
                    delete tmpNode_ptr;
                    length_--;
                }
                tmpNode_ptr=tmpNode_ptr->nextNode_ptr;
            }while(tmpNode_ptr != nullptr);*/

        }
        void update(T data, unsigned int index) //change data in index
        {
            if(index > size() || isEmpty()) return;
            
            
            Node* tmpNode_ptr=headNode_ptr;
            for(unsigned int i=0;i<index;i++)
            {
                tmpNode_ptr=tmpNode_ptr->nextNode_ptr;
            }
            tmpNode_ptr->data=data;

        }


        unsigned int size() //returns number of nodes
        {
            return length_;
        }
        bool isEmpty() //checks if empty
        {
            return length_ == 0;
        }
        void clear() //deletes all nodes
        {
            if(isEmpty()) return;
            tailNode_ptr=nullptr;
            Node* tmpNode_ptr;
            while (headNode_ptr != tailNode_ptr)
            {
                tmpNode_ptr = headNode_ptr->nextNode_ptr;
                delete headNode_ptr;
                headNode_ptr = tmpNode_ptr;
            }
            
            length_=0;
        }
        void reverse() //removes the order of nodes 
        {
        //from: head->[1]->[2]->tail
        //To:   head->[2]->[1]->tail

        if(length_<=1) return;

        auto swap = [](Node* &a,Node* &b){
            Node* tmp_ptr=a;
            a=b;
            b=tmp_ptr;
        };

        Node *curr_ptr = headNode_ptr;
        Node *tmp_ptr2;

        tmp_ptr2 = headNode_ptr;
        headNode_ptr = tailNode_ptr;
        tailNode_ptr = tmp_ptr2;


        while(curr_ptr != nullptr)
        {
            tmp_ptr2 = curr_ptr->nextNode_ptr;
            swap(curr_ptr->nextNode_ptr,curr_ptr->prevNode_ptr);
            curr_ptr = tmp_ptr2;
        }




        }
        

        MyDoubleList<T>& operator=(const MyDoubleList<T>& list){ //copy assigment
            if (this == &list) {
                return *this;
            }
            clear();//in case this list already has elements in it

            Node* node_ptr = list.tailNode_ptr;

            do{
                push_front(node_ptr->data);
                node_ptr=node_ptr->prevNode_ptr;
            }while(node_ptr != nullptr);


            return *this;

        }



};
