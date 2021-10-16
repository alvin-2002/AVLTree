//
// Created by Alvin on 2/06/2021.
//

#ifndef AVLTREE_AVL_ADT_H
#define AVLTREE_AVL_ADT_H
template <class TYPE>
struct NODE{
    TYPE value;
    NODE *leftChild;
    NODE *rightChild;
    int height;

    NODE(TYPE v){
        height = 0;
        this->value = v;
    }
};

template <class TYPE>
class AVLTree{
    private:
        NODE<TYPE> *root;
        NODE<TYPE> * _insert(NODE<TYPE> *root, TYPE value);
        int height(NODE<TYPE> *node);
        void setHeight(NODE<TYPE> *node);
        int balanceFactor(NODE<TYPE> *node);
        bool leftHeavy(NODE<TYPE> *node);
        bool rightHeavy(NODE<TYPE> *node);
        NODE<TYPE> *leftRotate(NODE<TYPE> *root);
        NODE<TYPE> *rightRotate(NODE<TYPE> *root);
        NODE<TYPE> *rebalance(NODE<TYPE> *root);

        void inOrderTraversal(NODE<TYPE> *root);
        void preOrderTraversal(NODE<TYPE> *root);
        void postOrderTraversal(NODE<TYPE> *root);
        NODE<TYPE> * _delete(NODE<TYPE> *root, TYPE value);
        void _displayAVLTree(NODE<TYPE> *currentNode, int indent);
        void destructor(NODE<TYPE> *root);

    public:
        AVLTree();
        ~AVLTree();
        void insert(TYPE value);
        void AVL_delete(TYPE value);
        void inOrder();
        void preOrder();
        void postOrder();
        void displayAVLTree();

};

template <class TYPE>
AVLTree<TYPE>::AVLTree() {
    root = NULL;
}
template <class TYPE>
AVLTree<TYPE>::~AVLTree() {
    if (root){
        destructor(root);
    }
}

template <class TYPE>
void AVLTree<TYPE>::destructor(NODE<TYPE> *root) {
    if (root){
        destructor(root->leftChild);
        destructor(root->rightChild);
        delete root;
    }
    return;
}

template <class TYPE>
void AVLTree<TYPE>::insert(TYPE value) {
    root = _insert(root, value);
}

template <class TYPE>
NODE<TYPE> * AVLTree<TYPE>::_insert(NODE<TYPE> *root, TYPE value){
    if (root == NULL){
        root = new NODE<TYPE>(value);
        root->leftChild = NULL;
        root->rightChild = NULL;
        return root;
    }
    if (value < root->value){
        root->leftChild = _insert(root->leftChild, value);
    }
    else{
        root->rightChild = _insert(root->rightChild, value);
    }
    setHeight(root);

    root = rebalance(root);
    return root;
}

template <class TYPE>
NODE<TYPE> * AVLTree<TYPE>::rebalance(NODE<TYPE> *root) {
    if (rightHeavy(root)){
        // check for inbalance in right child, left-sub tree (right-left rotation)
        if (balanceFactor(root->rightChild) > 0){
            // right rotation
            root->rightChild = rightRotate(root->rightChild);
        }
        // left rotation
        return leftRotate(root);
    }
    else if (leftHeavy(root)){
        // check for inbalance in left child, right-sub tree (left-right rotation)
        if (balanceFactor(root->leftChild) < 0){
            // left rotation
            root->leftChild = leftRotate(root->leftChild);
        }
        // right rotation
        return rightRotate(root);
    }
    return root;
}

// right heavy
template <class TYPE>
NODE<TYPE> * AVLTree<TYPE>::leftRotate(NODE<TYPE> *root) {
    NODE<TYPE> *newRoot;
    newRoot = root->rightChild;
    root->rightChild = newRoot->leftChild;
    newRoot->leftChild = root;
    setHeight(root);
    setHeight(newRoot);

    return newRoot;
}

// left heavy
template <class TYPE>
NODE<TYPE> * AVLTree<TYPE>::rightRotate(NODE<TYPE> *root) {
    NODE<TYPE> *newRoot;
    newRoot = root->leftChild;
    root->leftChild = newRoot->rightChild;
    newRoot->rightChild = root;

    setHeight(root);
    setHeight(newRoot);

    return newRoot;
}

template <class TYPE>
void AVLTree<TYPE>::setHeight(NODE<TYPE> *node) {
    (node->height) = (std::max(height(node->leftChild),height(node->rightChild))) + 1;
}

template <class TYPE>
int AVLTree<TYPE>::height(NODE<TYPE> *node) {
    return (node == NULL) ? -1 : node->height;
}

// balanceFactor = height(L) - height(R)
// > 1 => left heavy, right rotation
// < -1 => right heavy, left rotation
template <class TYPE>
int AVLTree<TYPE>::balanceFactor(NODE<TYPE> *node) {
    return (node == NULL) ? 0 : height(node->leftChild) - height(node->rightChild);
}

template <class TYPE>
bool AVLTree<TYPE>::leftHeavy(NODE<TYPE> *node) {
    return balanceFactor(node) > 1;
}

template <class TYPE>
bool AVLTree<TYPE>::rightHeavy(NODE<TYPE> *node) {
    return balanceFactor(node) < -1;
}

template <class TYPE>
void AVLTree<TYPE>::inOrder() {
    inOrderTraversal(root);
}

template <class TYPE>
void AVLTree<TYPE>::inOrderTraversal(NODE<TYPE> *root) {
    if (root == NULL){
        return;
    }
    inOrderTraversal(root->leftChild);
    std::cout << root->value << " ";
    inOrderTraversal(root->rightChild);
}

template<class TYPE>
void AVLTree<TYPE>::preOrder() {
    preOrderTraversal(root);
}

template<class TYPE>
void AVLTree<TYPE>::preOrderTraversal(NODE<TYPE> *root) {
    if (root == NULL){
        return;
    }
    std::cout << root->value << " ";
    preOrderTraversal(root->leftChild);
    preOrderTraversal(root->rightChild);
}

template<class TYPE>
void AVLTree<TYPE>::postOrder() {
    postOrderTraversal(root);
}

template<class TYPE>
void AVLTree<TYPE>::postOrderTraversal(NODE<TYPE> *root) {
    if (root == NULL){
        return;
    }
    postOrderTraversal(root->leftChild);
    postOrderTraversal(root->rightChild);
    std::cout << root->value << " ";
}


template <class TYPE>
void AVLTree<TYPE>::AVL_delete(TYPE value) {
    root = _delete(root, value);
}

template <class TYPE>
NODE<TYPE> * AVLTree<TYPE>::_delete(NODE<TYPE> *root, TYPE value) {
    NODE<TYPE> *newNode;
    NODE<TYPE> *deleteNode;
    NODE<TYPE> *replacement;
    if (root == NULL){
        return NULL;
    }
    if (value < root->value){
        root->leftChild = _delete(root->leftChild, value);
    }
    else if (value > root->value){
        root->rightChild = _delete(root->rightChild, value);
    }
    //found node
    else{
         deleteNode = root;
         if (deleteNode->rightChild == NULL){
             newNode = root->leftChild;
             delete(deleteNode);
             return newNode;
         }
         else if (deleteNode->leftChild == NULL){
             newNode = root->rightChild;
             delete(deleteNode);
             return newNode;
         }
         //has 2 children
         else{
             replacement = root->leftChild;
             while (replacement->rightChild){
                 replacement = replacement->rightChild;
             }
             root->value = replacement->value;
             root->leftChild = _delete(root->leftChild, replacement->value);
         }
    }

    return rebalance(root);
}

template <class TYPE>
void AVLTree<TYPE>::displayAVLTree() {
    _displayAVLTree(root, 0);
}

template <class TYPE>
void AVLTree<TYPE>::_displayAVLTree(NODE<TYPE> *currentNode, int indent) {

    if(currentNode == NULL) return;

    if(currentNode->rightChild) {
        _displayAVLTree(currentNode->rightChild, indent + 4);
    }

    std::cout << std::setw(indent) << "";

    if (currentNode->rightChild){
        std::cout << std::setw(5) << "" << "/\n" << std::setw(indent) << "" ;
    }
    if (currentNode == root){
        std::cout << "Root->" << currentNode->value << "\n ";
    }else{
        std::cout  << std::setw(4) << "" << currentNode->value << "\n ";
    }

    if(currentNode->leftChild) {
        std::cout << std::setw(indent + 5) << "" << "\\" << std::endl;
        _displayAVLTree(currentNode->leftChild, indent + 4);
    }
}
#endif //AVLTREE_AVL_ADT_H