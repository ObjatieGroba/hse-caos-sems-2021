#include <iostream>

//extern "C" int xxxx;
int xxxx;
extern "C" void f();

int main() {
    xxxx = 1;
    std::cout << xxxx << std::endl;
    f();  /// asm: call f
    std::cout << xxxx << std::endl;

//    std::string s;
//    std::cin >> s;
    return 0;
}
