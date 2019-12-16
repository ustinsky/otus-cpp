 #include <iostream>

int main() {
    unsigned int k, n;
    std::cin >> k >> n;
    
    unsigned int sum = 0;
    int a;
    
    for (int i = 0; i<n; ++i) {
       std::cin >> a;
       sum += a;
       if ( sum > k) 
              sum -= k;
       else
              sum = 0;
    }
    
    std::cout << sum << std::endl;
    
    return 0;
}
