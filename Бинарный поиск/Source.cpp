#include <iostream>
#include <vector>
#include <fstream>
#include <ostream>


bool binarySearch(std::vector<int>& vec, int el) {
    if (el < vec[0] || el > vec[vec.size() - 1]) return 0;

    int l = 0;
    int r = vec.size();
    int mid;

    while (l < r) {
        mid = (l + r) / 2;
        if (vec[mid] == el) return 1;
        else if (vec[mid] > el) r = mid;
        else l = mid + 1;
    }
    return 0;
}

int lowerBound(std::vector<int>& vec, int el) {
    int l = 0;
    int r = vec.size();
    int mid = 0;

    while (l < r) {
        mid = (l + r) / 2;
        if (vec[mid] >= el) r = mid;
        else l = mid + 1;
    }
    return l;
}

int upperBound(std::vector<int>& vec, int el) {
    int l = 0;
    int r = vec.size();
    int mid = 0;

    while (l < r) {
        mid = (l + r) / 2;
        if (vec[mid] > el) r = mid;
        else l = mid + 1;
    }
    return l;
}


int main() {
    std::ifstream fInput("in.txt");
    std::ofstream fOutput("out.txt");

    int size = 0;
    int numberOfRequests = 0;

    fInput >> size;

    std::vector<int> vec(size, 0);
    for (size_t i = 0; i < size; ++i) {
        fInput >> vec[i];
    }
   
    fInput >> numberOfRequests;

    std::vector<int> Requests(numberOfRequests, 0);
    for (size_t i = 0; i < numberOfRequests; ++i) {
        fInput >> Requests[i];
    }
        
    bool flag = 0;
    for (size_t i = 0; i < numberOfRequests; ++i) {
        flag = binarySearch(vec, Requests[i]);
        fOutput << flag << " ";
        if (flag) {
            fOutput << lowerBound(vec, Requests[i]) << " ";
            fOutput << upperBound(vec, Requests[i]);
        }
        else {
            if (Requests[i] < vec[0]) fOutput << 0 << " " << 0;
            else if (Requests[i] > vec[size - 1]) fOutput << size << " " << size;
            else {
                fOutput << lowerBound(vec, Requests[i]) << " ";
                fOutput << upperBound(vec, Requests[i]);
            }
        }
        fOutput << std::endl;
    }

    fOutput.close();
    fInput.close();
}