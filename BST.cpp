#include <iostream>
#include <list>
#include "BST.h"
template <class TYPE>
BST<TYPE>::BST(){
    rootNode_ptr_ = std::make_shared<Node>();
};

template <class TYPE>
BST<TYPE>::BST(const BST<TYPE>& obj) //copy constructor
{
    this->rootNode_ptr_ = copySubtree(obj.rootNode_ptr_);
    this->treeHeight_= obj.treeHeight_;
    this->treeSize_ = obj.treeSize_;
}


template <class TYPE>
void BST<TYPE>::insert(TYPE data){
    //case one: if the tree is empty

    if(treeSize_ == 0){
        rootNode_ptr_->data = data;
        treeSize_++;
    }
    else{
        std::shared_ptr<Node> curr = rootNode_ptr_;
        bool isSmaller;
        int height=0;
        while(curr != nullptr){
            if(data == curr->data) return; //to make sure it is unique

            isSmaller = data < curr->data; 
            if(isSmaller) { //left node

                if(curr->leftNode_ptr != nullptr) 
                { //move to the left
                    curr = curr->leftNode_ptr;
                    height++;
                    continue;
                }

                //make new node 
                curr->leftNode_ptr = std::make_shared<Node> ();
                curr->leftNode_ptr->data  =data;
                curr->leftNode_ptr->rootNode_ptr = curr;
                treeSize_++;
                if(height >= treeHeight_) treeHeight_++;
                return;

            }
            else{ //right node

                if(curr->rightNode_ptr != nullptr) 
                { //move to the left
                    curr = curr->rightNode_ptr;
                    height++;
                    continue;
                }

                //make new node 
                curr->rightNode_ptr = std::make_shared<Node> ();
                curr->rightNode_ptr->rootNode_ptr = curr;
                curr->rightNode_ptr->data  =data;
                treeSize_++;
                if(height >= treeHeight_) treeHeight_++; 
                return;
            }


        }

    }

};


template <class TYPE>
std::shared_ptr<typename BST<TYPE>::Node> BST<TYPE>::searchNode_(TYPE data){

    std::shared_ptr<Node> curr = rootNode_ptr_;

    while(curr != nullptr){
        if(curr->data == data) return curr;
        else if( data < curr->data ) curr = curr->leftNode_ptr; 
        else if( data > curr->data ) curr = curr->rightNode_ptr; 
    }
    return nullptr;
}

template <class TYPE>
bool BST<TYPE>::isLeaf(std::shared_ptr<Node> node_ptr){

    if(node_ptr->rightNode_ptr == nullptr && node_ptr->leftNode_ptr == nullptr) return true;
    return false;
}


template <class TYPE>
void BST<TYPE>::remove(TYPE data){

    //first find the node to remove


    std::shared_ptr<Node> node_ptr = searchNode_(data);
    if(node_ptr == nullptr) return;
    if (node_ptr == rootNode_ptr_)
    {
        rootNode_ptr_->data=0; 
        return;
    }
    if(isLeaf(node_ptr)) 
    {
        if(node_ptr->rootNode_ptr->leftNode_ptr == node_ptr) node_ptr->rootNode_ptr->leftNode_ptr= nullptr;
        if(node_ptr->rootNode_ptr->rightNode_ptr == node_ptr) node_ptr->rootNode_ptr->rightNode_ptr = nullptr;
        node_ptr = nullptr;
        return;
    }

    if(node_ptr->leftNode_ptr != nullptr) {
        node_ptr->data = node_ptr->leftNode_ptr->data;
        node_ptr->leftNode_ptr = nullptr;
        return;
    }

    std::shared_ptr<Node> tmp_node_ptr = node_ptr->rightNode_ptr;
    while(tmp_node_ptr->leftNode_ptr != nullptr){
        tmp_node_ptr=tmp_node_ptr->leftNode_ptr;
    }
    node_ptr->data = tmp_node_ptr->data;
    if(tmp_node_ptr->rootNode_ptr->leftNode_ptr == node_ptr) tmp_node_ptr->rootNode_ptr->leftNode_ptr= nullptr;
    if(tmp_node_ptr->rootNode_ptr->rightNode_ptr == node_ptr) tmp_node_ptr->rootNode_ptr->rightNode_ptr = nullptr;
    tmp_node_ptr = nullptr;

}


template <class TYPE>
void BST<TYPE>::traverseInOrder()
{ //prints every data from ascending order 

    traverseInOrder_(rootNode_ptr_); //calls an internal funtion that takes the node as input.
    std::cout<<"\n";
}; 

template <class TYPE>
void BST<TYPE>::traverseInOrder_(std::shared_ptr<Node> node_ptr)
{ //prints every data from ascending order 
    if(node_ptr == nullptr) return;

    traverseInOrder_(node_ptr->leftNode_ptr); //calls an internal funtion that takes the node as input.
    std::cout<<node_ptr->data<<"\t";
    traverseInOrder_(node_ptr->rightNode_ptr); //calls an internal funtion that takes the node as input.
};


template <class TYPE>
void BST<TYPE>::traverseLevelOrder(){

    std::list<std::shared_ptr<Node>> open_nodes, nextlevel_nodes;
    open_nodes.push_back(rootNode_ptr_);
    int i=0;
    while(!open_nodes.empty())
    {
        //std::cout<<"("<<i++<<")";
        std::shared_ptr<Node> curr_node = open_nodes.front();
        open_nodes.pop_front();
        if(curr_node->leftNode_ptr != nullptr)  nextlevel_nodes.push_back(curr_node->leftNode_ptr);
        if(curr_node->rightNode_ptr != nullptr)  nextlevel_nodes.push_back(curr_node->rightNode_ptr);
        std::cout<<curr_node->data<<"\t";

        if(open_nodes.empty()){
            open_nodes = nextlevel_nodes;
            nextlevel_nodes.clear();
            std::cout<<"\n";
        }

    }
}



template <class TYPE>
bool BST<TYPE>::search(TYPE data){


    std::shared_ptr<Node> curr = rootNode_ptr_;

    while(curr != nullptr){
        if(curr->data == data) return true;
        else if( data < curr->data ) curr = curr->leftNode_ptr; 
        else if( data > curr->data ) curr = curr->rightNode_ptr; 
    }
    return false;


}

template <class TYPE>
BST<TYPE> BST<TYPE>::subtree(TYPE data){
    std::shared_ptr<Node> curr = rootNode_ptr_;

    while(curr != nullptr){
        if(curr->data == data) break;
        else if( data < curr->data ) curr = curr->leftNode_ptr; 
        else if( data > curr->data ) curr = curr->rightNode_ptr; 
    }
    
    BST<TYPE> tree;
    if(curr == nullptr) return tree;
    tree.rootNode_ptr_ = copySubtree(curr);
    //count items and depth
    curr = tree.rootNode_ptr_;
    tree.treeHeight_=0;
    tree.treeSize_=0;

    //count depth

    tree.count_size_depth_();
    return tree;
}


template <class TYPE>
std::shared_ptr<typename BST<TYPE>::Node> BST<TYPE>::copySubtree(std::shared_ptr<Node> node_ptr){

    if(node_ptr == nullptr) return nullptr;
    std::shared_ptr<Node> newNode = std::make_shared<Node>(node_ptr->data);

    newNode->leftNode_ptr = copySubtree(node_ptr->leftNode_ptr);
    if(newNode->leftNode_ptr != nullptr ) newNode->leftNode_ptr->rootNode_ptr = newNode;
    newNode->rightNode_ptr = copySubtree(node_ptr->rightNode_ptr);
    if(newNode->rightNode_ptr != nullptr ) newNode->rightNode_ptr->rootNode_ptr = newNode;

    //newNode->rightNode_ptr->rootNode_ptr = newNode;

    return newNode;
}
template <class TYPE>
BST<TYPE>& BST<TYPE>::operator=(const BST<TYPE>& obj) //copy assignment
{
    this->rootNode_ptr_ = copySubtree(obj.rootNode_ptr_);
    this->treeHeight_= obj.treeHeight_;
    this->treeSize_ = obj.treeSize_;
    return *this;
}

template <class TYPE>
unsigned int BST<TYPE>::height(){
    return treeHeight_;
}

template <class TYPE>
unsigned int BST<TYPE>::size(){
    return treeSize_;
}


template <class TYPE>
TYPE BST<TYPE>::findSmallest(){

    std::shared_ptr<Node> curr_node=rootNode_ptr_;
    while(curr_node->leftNode_ptr != nullptr)
    {
        curr_node = curr_node->leftNode_ptr;
    }

    return curr_node->data;
};

template <class TYPE>
TYPE BST<TYPE>::findLargest(){
    
    std::shared_ptr<Node> curr_node=rootNode_ptr_;
    while(curr_node->rightNode_ptr != nullptr)
    {
        curr_node = curr_node->rightNode_ptr;
    }

    return curr_node->data;
};




template <class TYPE>
void BST<TYPE>::count_size_depth_(){

    std::list<std::shared_ptr<Node>> open_nodes, nextlevel_nodes;
    open_nodes.push_back(rootNode_ptr_);
    int i=0;
    while(!open_nodes.empty())
    {
        //std::cout<<"("<<i++<<")";
        std::shared_ptr<Node> curr_node = open_nodes.front();
        open_nodes.pop_front();
        if(curr_node->leftNode_ptr != nullptr)  nextlevel_nodes.push_back(curr_node->leftNode_ptr);
        if(curr_node->rightNode_ptr != nullptr)  nextlevel_nodes.push_back(curr_node->rightNode_ptr);
        treeSize_++;

        if(open_nodes.empty()){
            open_nodes = nextlevel_nodes;
            nextlevel_nodes.clear();
            treeHeight_++;
        }

    }
    treeHeight_--;
}