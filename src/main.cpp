#include <iostream>

int main(int argc, char* argv[])
{
    // suppress warnings
    (void)argc; (void)argv;

    auto add = [](auto x, auto y) {return x + y;};
    std::cout << "Hello World! From C++ " << add( 8, 6 ) << std::endl;
    return 0;
}
