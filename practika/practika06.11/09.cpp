#include <iostream>
#include <windows.h>

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    for (int i = 100; i >= 0; i -= 7) {
        std::cout << i << " ";
    }
    std::cout << "\n";

    return 0;
}
