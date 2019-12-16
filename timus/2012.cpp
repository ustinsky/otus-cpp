#include <iostream>
#include <math.h>

int main() {
    int n;
    
    std::cin >> n;
    std::string str;
    
    if ( ((12 - n) * 45) < (4 * 60) ) {
        str = "YES";
    } else {
        str = "NO";
    }
    
    std::cout << str << std::endl;
    
    return 0;
}