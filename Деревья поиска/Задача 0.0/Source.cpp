#include <fstream>
#include <ostream>
#include <set>


int main() {
    std::ifstream fInput("input.txt");
    std::ofstream fOutput("output.txt");

    std::set<int> mySet;
    int64_t summ = 0;
    int temp = 0;
    int oldSize = 0;

    while(fInput >> temp) {
        mySet.insert(temp);

        if (oldSize != mySet.size()) {
            ++oldSize;
            summ += temp;

        }
    }

    fOutput << summ;
}