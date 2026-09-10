#ifndef __BST_H__
#define __BST_H__

//unique and ordered
#include <memory>

template <class TYPE>
class BST{
    
    private:
    class Node
    {
        public:
        TYPE data;
        //TODO make unique pointers
        std::shared_ptr<Node> leftNode_ptr;
        std::shared_ptr<Node> rightNode_ptr;
        std::shared_ptr<Node> rootNode_ptr;
    };
    
    int treeHeight_{0};
    int treeSize_{0};
    std::shared_ptr<Node> rootNode_ptr_;

    void traverseInOrder_(std::shared_ptr<Node>);
    std::shared_ptr<Node> searchNode_(TYPE data);
    std::shared_ptr<Node> copySubtree(std::shared_ptr<Node>);
    void count_size_depth_();
    bool isLeaf(std::shared_ptr<Node>);

    public:
        BST(); //done
        BST(const BST& obj); //copy constructor //done
        
        //~BST(); //not needed?

        void insert(TYPE data); //done
        bool search(TYPE data); //done
        void remove(TYPE data); //done
        BST subtree(TYPE data); //done

        unsigned int height(); //done
        unsigned int size(); //done

        TYPE findSmallest(); //done
        TYPE findLargest(); //done
 
        //these only prints for now
        void traverseInOrder();  //done
        //void traversePreOrder();
        //void traversePostOrder();
        void traverseLevelOrder(); //done


        BST& operator=(const BST& obj); //copy assignment //done

};


#endif