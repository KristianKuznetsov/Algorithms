#include <iostream>
#include <vector>
#include <fstream>
#include <ostream>


struct Node {
    int data;
    long long lLim;
    long long rLim;
    Node() : data(0), lLim(0), rLim(0) {}
    Node(int data, long long lLim, long long rLim) : data(data), lLim(lLim), rLim(rLim) {}
};


int main() {
    std::ifstream fInput("bst.in.txt");
    int size = 0;
    fInput >> size;

    if (size == 0 || size == 1) {
        std::ofstream fOutput("bst.out.txt");
        fOutput << "YES";
        fOutput.close();
    }
    else {
        int* valueMas = new int[size];
        int* levelMas = new int[size];
        char* sideMas = new char[size];

        fInput >> valueMas[0];
        levelMas[0] = 0;
        sideMas[0] = 'E';

        for (int i = 1; i < size; ++i) {
            fInput >> valueMas[i];
            fInput >> levelMas[i];
            fInput >> sideMas[i];
        }

        Node temp;
        std::vector<Node> vec(size, temp);

        vec[0].data = valueMas[0];
        vec[0].lLim = -2147483649;
        vec[0].rLim = 2147483648;

        bool flag = true;

        for (size_t i = 1; i < size; i++) {
            if (sideMas[i] == 'R') {
                if (valueMas[i] >= vec[levelMas[i] - 1].data && valueMas[i] < vec[levelMas[i] - 1].rLim) {
                    vec[i].data = valueMas[i];
                    vec[i].lLim = vec[levelMas[i] - 1].data;
                    vec[i].rLim = vec[levelMas[i] - 1].rLim;
                }
                else {
                    flag = false;
                    break;
                }
            }
            else {
                if (valueMas[i] < vec[levelMas[i] - 1].data && valueMas[i] >= vec[levelMas[i] - 1].lLim) {
                    vec[i].data = valueMas[i];
                    vec[i].lLim = (vec[levelMas[i] - 1]).lLim;
                    vec[i].rLim = (vec[levelMas[i] - 1]).data;
                }
                else {
                    flag = false;
                    break;
                }
            }
        }

        std::ofstream fOutput("bst.out.txt");
        flag == true ? fOutput << "YES" : fOutput << "NO";
        fOutput.close();
    }
    fInput.close();
}