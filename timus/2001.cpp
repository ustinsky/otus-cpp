#include <iostream>

// a1 b1
// a2 b2
// a3 b3
// (a1 + b1) == (a2 + b2) == (a3 + b3) == (a + n) + (b + m)
// n = (a2 > b2) ? ( b2 ) : ( a2 )
// m = (a3 > b3) ? ( b3 ) : ( a3 )
// a = a1 - n
// b = b1 - m


int main() {
    int a, b, a1, a2, a3, b1, b2, b3;
    std::cin >> a1 >> b1;
    std::cin >> a2 >> b2;
    std::cin >> a3 >> b3;
    
    // (a2 > b2) ? ( b = b1 - b2 ) : ( a = a1 - a2 );
    // (a3 > b3) ? ( b = b1 - b3 ) : ( a = a1 - a3 );
    std::cout << a1 -a3 << ' ' << b1 - b2 << std::endl;
    
    return 0;
}