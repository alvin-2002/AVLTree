

#include <iostream>
#include <algorithm>
#include <queue>
#include <iomanip>
#include <string>

#include "AVL_ADT.h"

int main() {
    AVLTree<std::string> tree;
    int choice;
    while (1){
        std::cout << std::endl;
        std::cout << "1. Insert item into AVL Tree\n";
        std::cout << "2. Delete an item from AVL Tree\n";
        std::cout << "3. Display AVL Tree\n";
        std::cout << "4. Preorder Traversal\n";
        std::cout << "5. Inorder Traversal\n";
        std::cout << "6. Postorder Traversal\n";
        std::cout << "0. Exit\n";
        std::cin >> choice;
        std::string inputItem;
        std::string itemToBeDeleted;

        switch(choice){
            case 0:
                choice = 0;
                break;

            case 1:

                std::cout << "Enter numbers ending with -999" << std::endl;
                std::cin >> inputItem;
                while (inputItem != "-999")
                {
                    tree.insert(inputItem);
                    std::cin >> inputItem;
                }
                break;

            case 2:

                tree.AVL_delete(itemToBeDeleted);
                break;

            case 3:
                tree.displayAVLTree();
                break;

            case 4:
                tree.preOrder();
                break;

            case 5:
                tree.inOrder();
                break;

            case 6:
                tree.postOrder();
                break;
        }

        if (choice == 0) break;
    }

    return 0;
}
