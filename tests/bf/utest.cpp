#include <iostream>

#include "mu_test.h"
#include "bf/compiler.hpp"
#include "bf/console.hpp"
#include "bf/vm.hpp"

// int main(int argc, char* argv[]) {
// int main() {
//     bf::Compiler compiler;
//     bf::VM vm{compiler.parse("+.+.++.[>+++.<-.]>++.")}; 
//     vm.run(); 
 
//     return 0;
// }

BEGIN_TEST(test_valid)
    bf::Compiler compiler;
    auto opcodes = compiler.parse("+.+.++.[>+++.<-.]>++.");

    bf::Console console(bf::Console::Mode::Runtime);  // Ensure that the console initializes its buffers

    bf::VM vm{opcodes, console};
    vm.run();  // Execute the Brainfuck program

    std::string expectedOutput = "1 2 4 3 3 6 2 9 1 12 0 14 ";
    std::string actualOutput = console.get_test_output();
    //std::cout << "Debug output: '" << actualOutput << "'" << std::endl;
    ASSERT_EQUAL(actualOutput, expectedOutput);

END_TEST


BEGIN_SUITE()
    TEST(test_valid)
END_SUITE