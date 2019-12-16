#include <iostream>
#include <math.h>
#include <string>

int main() {
    int n, m;
    
    std::cin >> n >> m;
    std::string str = ((n % 2 == 0) || ((m + 1) % 2 == 0 ))?("yes"):("no");
    
    std::cout << str << std::endl;
    
    return 0;
}