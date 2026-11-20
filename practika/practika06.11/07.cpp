#include <iostream>
#include <windows.h>

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    int sum = 0;
    for (int i = 1; i <= 99; i += 2) {
        sum += i;
    }
    std::cout << "Сумма: " << sum << "\n";

    return 0;
}
