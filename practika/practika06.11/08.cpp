#include <iostream>
#include <windows.h>

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    for (int i = 20; i >= 1; i--) {
        std::cout << i << " ";
    }
    std::cout << "\n";

    return 0;
}
