#include <iostream>
#include <windows.h>

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    for (int i = 2; i <= 50; i += 2) {
        std::cout << i << " ";
    }
    std::cout << "\n";

    return 0;
}
