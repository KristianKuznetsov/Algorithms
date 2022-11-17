#include <iostream>

#include <fstream>
#include <ostream>
#include <set>



struct Node {
    int data;
    bool leftMod, allMod;
    Node* left, * right;

    Node(int _val) : data(_val), left(nullptr), right(nullptr), leftMod(0), allMod(0) {}
};

struct list {
    Node* root;
    Node* saveRoot;
    int size = 0;
    list() : root(nullptr), saveRoot(nullptr) {}

    bool is_empty() {
        return root == nullptr;
    }

    void push_back(int _val) {
        Node* temp = new Node(_val);
        if (is_empty()) {
            root = temp;
            saveRoot = root;
            return;
        }

        while (true) {
            if (_val == root->data) break;
            else if (_val < root->data && root->left == nullptr) {
                root->left = temp;
                break;
            }
            else if (_val > root->data && root->right == nullptr) {
                root->right = temp;
                break;
            }
            else if (_val < root->data && root->left != nullptr) {
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

    void leftBypass() {
        std::ofstream fOutput("output.txt");
        if (saveRoot == nullptr) {
            return;
        }

        Node* tempRoot = nullptr;
        while (saveRoot->allMod != true) {

            if (root->leftMod == false) {
                fOutput << root->data << std::endl;
                root->leftMod = true;
            }

            if (root->left == nullptr && root->right == nullptr) {
                root->allMod = true;
                root = saveRoot;
                continue;
            }
            else if (root->left != nullptr && root->right == nullptr) {
                if (!root->left->allMod) {
                    root = root->left;
                    continue;
                }
                else {
                    root->allMod = true;
                    root = saveRoot;
                    continue;
                }
            }
            else if (root->left == nullptr && root->right != nullptr) {
                if (root->right->allMod == true) {
                    root->allMod = true;
                    root = saveRoot;
                    continue;
                }
                else {
                    root = root->right;
                    continue;
                }
            }
            else {
                if (!root->left->allMod) {
                    root = root->left;
                    continue;
                }
                if (root->left->allMod == true && root->right->allMod == false) {
                    root = root->right;
                    continue;
                }
                if (root->left->allMod == true && root->right->allMod == true) {
                    root->allMod = true;
                    root = saveRoot;
                    continue;
                }
            }
        }

        fOutput.close();
    }

    bool findElement(int _val) {
        while (true) {
            if (_val == root->data) {
                root = saveRoot;
                return true;
            }
            else {
                if (_val < root->data && root->left != nullptr) root = root->left;
                else if (_val > root->data && root->right != nullptr) root = root->right;
                else {
                    root = saveRoot;
                    return false;
                }
            }
        }
    }

    void deleteElement(int _val) {
        if (saveRoot == nullptr) return;
        else if (saveRoot->left == nullptr && saveRoot->right == nullptr) {
            if (saveRoot->data == _val) {
                saveRoot = nullptr;
                root == nullptr;
                return;
            }
            else return;
        }

        if (!this->findElement(_val)) return;

        if (_val == saveRoot->data && saveRoot->left == nullptr && saveRoot->right != nullptr) {
            saveRoot->data = saveRoot->right->data;
            saveRoot->left = saveRoot->right->left;
            saveRoot->right = saveRoot->right->right;
            return;
        }
        if (_val == saveRoot->data && saveRoot->left != nullptr && saveRoot->right == nullptr) {
            saveRoot->data = saveRoot->left->data;
            saveRoot->right = (saveRoot->left)->right;
            saveRoot->left = saveRoot->left->left;
            
            return;
        }


        Node* previousElement = nullptr;
        previousElement = root;
        int side = 0;

        while (true) {

            if (_val < root->data) {
                if (root->left != nullptr) {
                    previousElement = root;
                    root = root->left;
                    side = -1;
                }
                else return;
            }
            else if (_val > root->data) {
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
    std::ifstream fInput("input.txt");

    int temp = 0;
    int deletEl = 0;
    list test1;
    
    fInput >> deletEl;
    while (fInput >> temp) {
        test1.push_back(temp);
    }
    test1.deleteElement(deletEl);
    test1.leftBypass();

    fInput.close();
}
