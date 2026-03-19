#include <iostream>

class Math {
public:
    static int multiply(int a, int b) {
        return a * b;
    }
};

int main() {
    std::cout << "DeepBleed CPP Multiply: " << Math::multiply(5, 6) << std::endl;
    return 0;
}
