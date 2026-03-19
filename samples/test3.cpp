#include <vector>
#include <iostream>

int main() {
    std::vector<int> numbers = {10, 20, 30, 40, 50};
    int total = 0;
    for (int n : numbers) {
        total += n;
    }
    std::cout << "Vector Sum: " << total << std::endl;
    return 0;
}
