// #include <iostream>
// #include <vector>
// #include <math.h>
// #include <iomanip>


// int main() {
//     unsigned long long int d;
//     std::vector<long double> ans(0);
   
//     while (!std::cin.eof()) {
//         std::cin >> d;

//        if (!std::cin.eof()) {
//             ans.push_back(sqrt((long double)d));
//             // std::cout << std::endl << sqrt((long double)d) << std::endl;
//        }
        
//     }
   
//     // std::cout << ans.size() << std::endl;
   
//     for (int i = ans.size() - 1; i >= 0; i--) {
//         // std::cout.setf(ios::fixed);
//         // std::cout << std::setprecision(ans[i]) << std::endl;
//         // std::cout << ans[i] << std::endl;
//         std::cout << std::fixed << std::setprecision(4) << ans[i] << std::endl;
//     }
// }


#include <iostream>
#include <vector>
#include <math.h>
#include <iomanip>


int main() {
    unsigned long long int d;
    std::vector<long double> ans(0);
   
    while (std::cin >> d) {
        ans.push_back(sqrtl((long double)d));
    }
   
    for (int i = ans.size() - 1; i >= 0; i--) {
        std::cout << std::fixed << std::setprecision(4) << ans[i] << std::endl;
    }
}