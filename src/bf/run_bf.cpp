#include <iostream>
#include <vector>
#include <string.h>

#include "bf/command_line_args.hpp"
#include "bf/compiler.hpp"
#include "bf/console.hpp"
#include "bf/vm.hpp"
#include "bf/operations.hpp"
#include "bf/mem_arg_types.hpp"
#include "bf/memory.hpp"

/*
./run_bf -r "++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++."
*/

int main(int argc, char *argv[]) 
{
    std::string input_code;
    if (!bf::CommandLineArgs::get_code_for_compilation(argc, argv, input_code)) {
        return 1;
    }

    bf::Compiler compiler{};
    bf::Program program = compiler.compile(input_code);

    bf::Console console{};
    bf::Memory tape{};
    bf::VM vm{tape, program, console};

    vm.run(); 

}