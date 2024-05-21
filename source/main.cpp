#include "MyClass.h"
#include <iostream>

int main() {
    MyClass obj("tests/test1");
//    obj.print_data();
    auto vec = obj.main_foo();
    for (const auto& item: vec)
        std::cout << item << std::endl;
}
