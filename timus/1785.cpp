#include <iostream>


int main() {
    int x;
    std::string str; 

    std::cin >> x;
    if ((x >= 1 ) && (x <= 4)) {
        str = "few";
    } else if ((x >= 5 ) && (x <= 9)) {
        str = "several";
    } else if ((x >= 10 ) && (x <= 19)) {
        str = "pack";
    } else if ((x >= 20 ) && (x <= 49)) {
        str = "lots";
    } else if ((x >= 50 ) && (x <= 99)) {
        str = "horde";
    } else if ((x >= 100 ) && (x <= 249)) {
        str = "throng";
    } else if ((x >= 250 ) && (x <= 499)) {
        str = "swarm";
    } else if ((x >= 500 ) && (x <= 999)) {
        str = "zounds";
    } else if ((x >= 1000 )) {
        str = "legion";
    } 
    std::cout << str << std::endl;
}