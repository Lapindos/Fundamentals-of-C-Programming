#include <iostream>
#include <string>
#include <string_view>

#include <windows.h>

[[nodiscard]] std::string trim(std::string text) {
    const auto first = text.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) {
        return {};
    }
    const auto last = text.find_last_not_of(" \t\r\n");
    return text.substr(first, last - first + 1);
}

[[nodiscard]] bool has_comma(std::string_view line) {
    return line.find(',') != std::string_view::npos;
}

[[nodiscard]] std::string get_name(std::string_view line) {
    const auto pos = line.find(',');
    if (pos == std::string_view::npos) {
        return {};
    }
    return trim(std::string(line.substr(0, pos)));
}

[[nodiscard]] int get_age(std::string_view line) {
    const auto pos = line.find(',');
    if (pos == std::string_view::npos || pos + 1 >= line.size()) {
        return -1;
    }

    try {
        const int age = std::stoi(trim(std::string(line.substr(pos + 1))));
        if (age < 0 || age > 150) {
            return -1;
        }
        return age;
    } catch (...) {
        return -1;
    }
}

[[nodiscard]] bool is_valid(std::string_view name, int age) {
    return !name.empty() && age >= 0 && age <= 150;
}

[[nodiscard]] constexpr bool is_adult(int age) {
    return age >= 18;
}

[[nodiscard]] std::string category(int age) {
    if (age < 0 || age > 150) {
        return "unknown";
    }
    if (age < 18) {
        return "child";
    }
    if (age < 65) {
        return "adult";
    }
    return "senior";
}

void print_report(std::string_view name, int age) {
    std::cout << "name=" << name << "\n";
    std::cout << "age=" << age << "\n";
    std::cout << "adult=" << (is_adult(age) ? "yes" : "no") << "\n";
    std::cout << "category=" << category(age) << "\n";
}

void process_user(std::string_view raw) {
    if (!has_comma(raw)) {
        std::cerr << "bad line: " << raw << "\n";
        return;
    }

    const std::string name = get_name(raw);
    const int age = get_age(raw);

    if (!is_valid(name, age)) {
        std::cerr << "invalid user: " << raw << "\n";
        return;
    }

    print_report(name, age);
}

namespace {

void check(std::string_view title, bool ok) {
    std::cout << title << (ok ? " OK\n" : " FAIL\n");
}

}

int main() {
    SetConsoleOutputCP(CP_UTF8);

    std::cout << "Проверки функций\n";

    check("trim spaces", trim("  Alice  ") == "Alice");
    check("trim tabs", trim("\tBob\r\n") == "Bob");
    check("trim empty", trim("   ").empty());

    check("has_comma yes", has_comma("Alice,25"));
    check("has_comma no", !has_comma("Alice"));

    check("get_name", get_name("Bob,25") == "Bob");
    check("get_name spaces", get_name("  Bob  ,25") == "Bob");
    check("get_name no comma", get_name("Bob").empty());

    check("get_age", get_age("Bob,25") == 25);
    check("get_age edges", get_age("Bob,0") == 0 && get_age("Bob,150") == 150);
    check("get_age bad text", get_age("Bob,abc") == -1);
    check("get_age too high", get_age("Bob,151") == -1);
    check("get_age negative", get_age("Bob,-5") == -1);

    check("is_valid empty", !is_valid("", 25));
    check("is_valid negative", !is_valid("Bob", -1));
    check("is_valid ok", is_valid("Bob", 25));

    check("is_adult", !is_adult(17) && is_adult(18) && is_adult(100));

    check("category child", category(7) == "child");
    check("category adult", category(25) == "adult");
    check("category senior", category(70) == "senior");
    check("category unknown", category(-1) == "unknown");

    std::cout << "\nПример отчёта\n";
    process_user("  Alice  , 25");
    process_user("Sam,70");
    process_user("Kid,7");
    process_user("broken-line");
    process_user("Ghost,200");

    return 0;
}
