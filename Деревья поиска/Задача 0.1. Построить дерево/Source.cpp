#include <iostream>

#include <fstream>
#include <ostream>
#include <set>



struct Node {
    int data;
    bool leftMod, allMod;
    Node* left, *right;

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
            if (_val == root -> data) break;
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
            else{
               root = root->right;
               continue;
            }
        }
        root = saveRoot;
    }

    void leftBypass() {
        std::ofstream fOutput("output.txt");

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
};



int main() {
    std::ifstream fInput("input.txt");

    int temp = 0;
    list test1;

    while (fInput >> temp) {
        test1.push_back(temp);
    }
    test1.leftBypass();

    fInput.close();
}
