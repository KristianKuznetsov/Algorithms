#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ostream>


struct Node {
    int data;
    int amount, height;
    Node* left, * right;

    Node(int val) {
        data = val;
        left = nullptr;
        right = nullptr;

        height = 0;
        amount = 0;
    }
};

struct list {
    Node* root;
    Node* saveRoot;
    list() : root(nullptr), saveRoot(nullptr) {}

    Node* getRoot() { return root; }
    int getSize() { return root->amount + 1; }

    bool is_empty() {
        return root == nullptr;
    }

    void push_back(int val) {
        Node* temp = new Node(val);
        if (is_empty()) {
            root = temp;
            saveRoot = root;
            return;
        }

        while (true) {
            if (val == root->data) break;
            else if (val < root->data && root->left == nullptr) {
                root->left = temp;
                break;
            }
            else if (val > root->data && root->right == nullptr) {
                root->right = temp;
                break;
            }
            else if (val < root->data && root->left != nullptr) {
                root = root->left;
                continue;
            }
            else {
                root = root->right;
                continue;
            }
        }
        root = saveRoot;
    }

    void preOrderTravers(Node* root, std::ofstream& fOutput) { //Прямой левый
        if (root) {
            fOutput << root->data << std::endl;
            preOrderTravers(root->left, fOutput);
            preOrderTravers(root->right, fOutput);
        }
    }
    
    void inOrderTravers(Node* root, std::vector<int>& vec, int& index) { //Внутренний левый обход, 
        if (root) {                           // чтобы в векторе были сразу сортированные элементы
            inOrderTravers(root->left, vec, index);
            if (root->left != nullptr && root->right != nullptr) {
                if ((root->left->height != root->right->height) &&
                    (root->left->amount == root->right->amount)) {
                    vec[index] = root->data;
                    ++index;
                }
            }
            inOrderTravers(root->right, vec, index);
        }
    }

    void postOrderTravers(Node* root) { //Обратный левый обход
        if (root) {
            postOrderTravers(root->left);
            postOrderTravers(root->right);

            if (root->left == nullptr && root->right == nullptr) {
                root -> amount = 0;
                root -> height = -1;
            }
            else if (root->left == nullptr && root->right != nullptr) {
                root->amount = (root->right->amount + 1);
                root->height = (root->right->height + 1);
            }
            else if (root->left != nullptr && root->right == nullptr) {
                root->amount = (root->left->amount + 1);
                root->height = (root->left->height + 1);
            }
            else {
                root->amount = (root->left->amount + root->right->amount + 2);
                root->height = (std::max(root->left->height, root->right->height) + 1);
            }
        }
    }

    bool findElement(int val) {
        while (true) {
            if (val == root->data) {
                root = saveRoot;
                return true;
            }
            else {
                if (val < root->data && root->left != nullptr) root = root->left;
                else if (val > root->data && root->right != nullptr) root = root->right;
                else {
                    root = saveRoot;
                    return false;
                }
            }
        }
    }

    void deleteElement(int val) {
        if (saveRoot == nullptr) return;
        else if (saveRoot->left == nullptr && saveRoot->right == nullptr) {
            if (saveRoot->data == val) {
                saveRoot = nullptr;
                root = nullptr;
                return;
            }
            else return;
        }

        if (!this->findElement(val)) return;

        if (val == saveRoot->data && saveRoot->left == nullptr && saveRoot->right != nullptr) {
            saveRoot->data = saveRoot->right->data;
            saveRoot->left = saveRoot->right->left;
            saveRoot->right = saveRoot->right->right;
            return;
        }
        if (val == saveRoot->data && saveRoot->left != nullptr && saveRoot->right == nullptr) {
            saveRoot->data = saveRoot->left->data;
            saveRoot->right = (saveRoot->left)->right;
            saveRoot->left = saveRoot->left->left;

            return;
        }

        Node* previousElement = nullptr;
        previousElement = root;
        int side = 0;

        while (true) {

            if (val < root->data) {
                if (root->left != nullptr) {
                    previousElement = root;
                    root = root->left;
                    side = -1;
                }
                else return;
            }
            else if (val > root->data) {
                if (root->right != nullptr) {
                    previousElement = root;
                    root = root->right;
                    side = 1;
                }
                else return;
            }
            else {
                if (root->left == nullptr && root->right == nullptr) {
                    if (side == -1) {
                        previousElement->left = nullptr;
                    }
                    else {
                        previousElement->right = nullptr;
                    }
                    root = saveRoot;
                    return;
                }
                else if (root->left == nullptr && root->right != nullptr) {
                    if (side == -1) {
                        previousElement->left = root->right;
                        root = saveRoot;
                        return;
                    }
                    else {
                        previousElement->right = root->right;
                        root = saveRoot;
                        return;
                    }
                }
                else if (root->left != nullptr && root->right == nullptr) {
                    if (side == -1) {
                        previousElement->left = root->left;
                        root = saveRoot;
                        return;
                    }
                    else {
                        previousElement->right = root->left;
                        root = saveRoot;
                        return;
                    }
                }
                else {
                    Node* temp = root;
                    previousElement = root;
                    root = root->right;
                    if (root->left == nullptr && root->right == nullptr) {
                        temp->data = root->data;
                        temp->right = nullptr;
                    }
                    else if (root->left == nullptr && root->right != nullptr) {
                        temp->data = root->data;
                        temp->right = root->right;
                    }
                    else {
                        while (root->left != nullptr) {
                            previousElement = root;
                            root = root->left;
                        }
                        if (root->left == nullptr && root->right == nullptr) {
                            temp->data = root->data;
                            previousElement->left = nullptr;
                        }
                        else {
                            temp->data = root->data;
                            previousElement->left = root->right;
                        }
                    }
                    root = saveRoot;
                    return;
                }
            }
        }
    }

};


int main() {
    std::ifstream fInput("in.txt");

    int temp = 0;
    list test;

    while (fInput >> temp) {
        test.push_back(temp);
    }

    Node* root = test.getRoot();
    test.postOrderTravers(root);

    int index = 0;
    int size = test.getSize();
    std::vector<int> vec(size, 0);
    test.inOrderTravers(root, vec, index);

    if (index % 2 == 1) {
        test.deleteElement(vec[(index-1)/2]);
    }

    std::ofstream fOutput("out.txt");
    test.preOrderTravers(root, fOutput);

    fOutput.close();
    fInput.close();
}