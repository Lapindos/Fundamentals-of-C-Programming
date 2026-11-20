#include <iostream>
#include <string>

bool has_comma(std::string line) {
    return line.find(',') != std::string::npos;
}

std::string get_name(std::string line) {
    size_t pos = line.find(',');
    return line.substr(0, pos);
}

int get_age(std::string line) {
    size_t pos = line.find(',');
    std::string age_part = line.substr(pos + 1);
    try {
        int age = std::stoi(age_part);
        if (age < 0 || age > 150) {
            return -1;
        }
        return age;
    } catch (...) {
        return -1;
    }
}

bool is_valid(std::string name, int age) {
    return !name.empty() && age >= 0 && age <= 150;
}

bool is_adult(int age) {
    return age >= 18;
}

std::string trim(std::string text) {
    size_t first = text.find_first_not_of(' ');
    if (first == std::string::npos) {
        return "";
    }
    size_t last = text.find_last_not_of(' ');
    return text.substr(first, last - first + 1);
}

std::string category(int age) {
    if (age < 18) {
        return "child";
    }
    if (age < 65) {
        return "adult";
    }
    return "senior";
}

void print_report(std::string name, int age) {
    std::cout << "name=" << name << "\n";
    std::cout << "age=" << age << "\n";
    std::cout << "adult=" << (is_adult(age) ? "yes" : "no") << "\n";
}

void process_user(std::string raw) {
    if (!has_comma(raw)) {
        std::cerr << "bad line: " << raw << "\n";
        return;
    }

    std::string name = get_name(raw);
    int age = get_age(raw);

    if (!is_valid(name, age)) {
        std::cerr << "invalid user: " << raw << "\n";
        return;
    }

    print_report(name, age);
}

int main() {
    if (trim("  Bob  ") == "Bob") {
        std::cout << "trim OK\n";
    } else {
        std::cout << "trim FAIL\n";
    }

    if (trim("   ").empty()) {
        std::cout << "trim empty OK\n";
    } else {
        std::cout << "trim empty FAIL\n";
    }

    if (has_comma("Bob,25") && !has_comma("Bob")) {
        std::cout << "has_comma OK\n";
    } else {
        std::cout << "has_comma FAIL\n";
    }

    if (get_name("Bob,25") == "Bob") {
        std::cout << "get_name OK\n";
    } else {
        std::cout << "get_name FAIL\n";
    }

    if (get_age("Bob,25") == 25) {
        std::cout << "get_age OK\n";
    } else {
        std::cout << "get_age FAIL\n";
    }

    if (get_age("Bob,abc") == -1) {
        std::cout << "get_age bad OK\n";
    } else {
        std::cout << "get_age bad FAIL\n";
    }

    if (get_age("Bob,151") == -1 && get_age("Bob,-5") == -1) {
        std::cout << "get_age range OK\n";
    } else {
        std::cout << "get_age range FAIL\n";
    }

    if (!is_valid("", 25)) {
        std::cout << "is_valid empty OK\n";
    } else {
        std::cout << "is_valid empty FAIL\n";
    }

    if (!is_valid("Bob", -1)) {
        std::cout << "is_valid negative OK\n";
    } else {
        std::cout << "is_valid negative FAIL\n";
    }

    if (is_valid("Bob", 25)) {
        std::cout << "is_valid OK\n";
    } else {
        std::cout << "is_valid FAIL\n";
    }

    if (!is_adult(17) && is_adult(18) && is_adult(100)) {
        std::cout << "is_adult OK\n";
    } else {
        std::cout << "is_adult FAIL\n";
    }

    if (category(7) == "child" && category(25) == "adult" && category(70) == "senior") {
        std::cout << "category OK\n";
    } else {
        std::cout << "category FAIL\n";
    }

    return 0;
}
