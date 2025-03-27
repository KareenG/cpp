#include <iostream>
#include <vector>

#include "mu_test.h"
#include "bf/compiler.hpp"
#include "bf/console.hpp"
#include "bf/vm.hpp"
#include "bf/operations.hpp"
#include "bf/mem_arg_types.hpp"
//#define BF_DEBUG
#include "bf/memory.hpp"
#include <stack>

bf::OpCode translate(char c) 
{
    std::unordered_map<char, bf::OpCode>::const_iterator it = bf::op_code_map.find(c);
    return it != bf::op_code_map.end() ? it->second : bf::OpCode::HALT;
}

bool validate(const std::string& source) 
{
    std::stack<size_t> bracket_stack;
    size_t index = 0;
    for (char c : source) {
        bf::OpCode op = translate(c);
        switch (op) {
            case bf::OpCode::LoopStart:
                bracket_stack.push(index);
                break;
            case bf::OpCode::LoopEnd:
                if (bracket_stack.empty()) {
                    return false;
                }
                bracket_stack.pop();
                break;
            default:
                break;
        }
        index++;
    }
    return bracket_stack.empty();
}

BEGIN_TEST(test_memory_initialization)
    bf::Memory memory(10);
    for (size_t i = 0; i < 10; ++i) {
        ASSERT_EQUAL(memory[i], 0);
    }
END_TEST

BEGIN_TEST(test_memory_read_write)
    bf::Memory memory(10);
    memory.write(42);
    ASSERT_EQUAL(memory.read(), 42);
END_TEST

BEGIN_TEST(test_memory_pointer_movement)
    bf::Memory memory(5);
    memory.write(1);
    memory.move_right();
    memory.write(2);
    ASSERT_EQUAL(memory[0], 1);
    ASSERT_EQUAL(memory[1], 2);
    memory.move_right();
    memory.move_right();
    memory.move_right();
    memory.move_right();
    ASSERT_EQUAL(memory.read(), 1);
END_TEST

BEGIN_TEST(test_memory_boundary_wrap_around)
    bf::Memory memory(3);
    memory.write(1);
    memory.move_left();
    memory.write(2);
    ASSERT_EQUAL(memory[2], 2);
    memory.move_right();
    ASSERT_EQUAL(memory.read(), 1);
END_TEST

BEGIN_TEST(test_memory_read_write_at_boundaries)
    bf::Memory memory(3);
    memory.write(99);
    memory.move_right();
    memory.move_right();
    memory.write(77);
    memory.move_right();
    ASSERT_EQUAL(memory.read(), 99);
    memory.move_left();
    ASSERT_EQUAL(memory.read(), 77);
END_TEST

/*-------------------------------------------------------------------------------------------------*/

BEGIN_TEST(test_program_initialization)
    std::vector<bf::OpCode> code = {bf::OpCode::Increment, bf::OpCode::Decrement, bf::OpCode::Output};
    bf::Program program(code);

    ASSERT_EQUAL(static_cast<int>(program.fetch_next()), static_cast<int>(bf::OpCode::Increment));
    ASSERT_EQUAL(static_cast<int>(program.fetch_next()), static_cast<int>(bf::OpCode::Decrement));
    ASSERT_EQUAL(static_cast<int>(program.fetch_next()), static_cast<int>(bf::OpCode::Output));
    ASSERT_EQUAL(static_cast<int>(program.fetch_next()), static_cast<int>(bf::OpCode::HALT));
END_TEST

BEGIN_TEST(test_program_jump_forward_and_backward)
    std::vector<bf::OpCode> code = {
        bf::OpCode::LoopStart, // 0
        bf::OpCode::Increment, // 1
        bf::OpCode::LoopEnd,   // 2
        bf::OpCode::Decrement  // 3
    };
    std::unordered_map<size_t, size_t> jump_table = {{0, 2}, {2, 0}};
    bf::Program program(code, jump_table);

    program.jump_forward_to_matching_end();
    ASSERT_EQUAL(static_cast<int>(program.fetch_current()), static_cast<int>(bf::OpCode::LoopEnd)); // Check if jumped to LoopEnd

    program.jump_backward_to_matching_start();
    ASSERT_EQUAL(static_cast<int>(program.fetch_current()), static_cast<int>(bf::OpCode::LoopStart)); // Should jump back to LoopStart
END_TEST

BEGIN_TEST(test_program_is_done)
    std::vector<bf::OpCode> code = {bf::OpCode::Increment, bf::OpCode::Decrement};
    bf::Program program(code);

    ASSERT_THAT(!program.is_done());
    program.fetch_next();
    program.fetch_next();
    ASSERT_THAT(program.is_done());
END_TEST

/*-------------------------------------------------------------------------------------------------*/

BEGIN_TEST(test_jump_table_construction)
    bf::Compiler compiler;
    std::string program_source = "[->+<]";
    bf::Program compiled_program = compiler.compile(program_source);
    
    const std::unordered_map<size_t, size_t>& jump_table = compiled_program.get_jump_table(); // Assume get_jump_table() exposes this data
    
    ASSERT_EQUAL(jump_table.at(0), 5);  // Start of loop '[' at index 0 jumps to ']' at index 5
    ASSERT_EQUAL(jump_table.at(5), 0);  // End of loop ']' at index 5 jumps back to '[' at index 0
END_TEST

BEGIN_TEST(test_opcode_vector_construction)
    bf::Compiler compiler;
    std::string program_source = "[->+<]";
    bf::Program compiled_program = compiler.compile(program_source);
    
    const std::vector<bf::OpCode>& opcodes = compiled_program.get_instructions();
    
    ASSERT_EQUAL(static_cast<int>(opcodes[0]), static_cast<int>(bf::OpCode::LoopStart));
    ASSERT_EQUAL(static_cast<int>(opcodes[1]), static_cast<int>(bf::OpCode::Decrement));
    ASSERT_EQUAL(static_cast<int>(opcodes[2]), static_cast<int>(bf::OpCode::MoveRight));
    ASSERT_EQUAL(static_cast<int>(opcodes[3]), static_cast<int>(bf::OpCode::Increment));
    ASSERT_EQUAL(static_cast<int>(opcodes[4]), static_cast<int>(bf::OpCode::MoveLeft));
    ASSERT_EQUAL(static_cast<int>(opcodes[5]), static_cast<int>(bf::OpCode::LoopEnd));
    ASSERT_EQUAL(static_cast<int>(opcodes[6]), static_cast<int>(bf::OpCode::HALT));  // Ensure HALT is added
END_TEST

BEGIN_TEST(test_bracket_validation)
    std::string valid_source = "[->+<]";
    std::string invalid_source = "[->+<";
    
    ASSERT_THAT(validate(valid_source) == true);
    
    ASSERT_THAT(validate(invalid_source) == false);
END_TEST

/*-------------------------------------------------------------------------------------------------*/

BEGIN_TEST(test_from_scratch)
    bf::Compiler compiler{};
    bf::Program program = compiler.compile("+++");

    std::ostringstream os;
    std::istringstream is("");

    bf::Console console{os, is};
    bf::Memory tape{};

    bf::VM vm{tape, program, console};

    vm.run(); 

    ASSERT_EQUAL(tape[0], 3);
    ASSERT_EQUAL(os.str(), "");
END_TEST

BEGIN_TEST(test_valid)
    std::vector<bf::OpCode> bf_code(68, bf::OpCode::Increment);
    
    std::ostringstream os;
    std::istringstream is("");

    bf::Console console{os, is};
    bf::Memory tape{};
    bf::Program program{bf_code};
    bf::VM vm{tape, program, console};

    vm.run(); 

    ASSERT_EQUAL(tape[0], 68);
    ASSERT_EQUAL(os.str(), "");
END_TEST


BEGIN_TEST(test_hello_world)
    // Brainfuck code to output "Hello World!"
    std::string bf_source = "++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++.";

    bf::Compiler compiler{};
    bf::Program program = compiler.compile(bf_source);

    std::ostringstream os;
    std::istringstream is("");

    bf::Console console{os, is};
    bf::Memory tape{};

    bf::VM vm{tape, program, console};

    vm.run(); 

    ASSERT_EQUAL(os.str(), "Hello World!\n");
END_TEST

BEGIN_TEST(test_echo_program)
    std::string bf_source = ",.++";

    bf::Compiler compiler{};
    bf::Program program = compiler.compile(bf_source);

    std::istringstream is("x");  
    std::ostringstream os;

    bf::Console console{os, is};
    bf::Memory tape{};

    bf::VM vm{tape, program, console};

    vm.run(); 
    ASSERT_EQUAL(tape[0], 'x' + 2);
    ASSERT_EQUAL(os.str(), "x");
END_TEST

BEGIN_SUITE()
    TEST(test_memory_initialization)
    TEST(test_memory_read_write)
    TEST(test_memory_pointer_movement)
    TEST(test_memory_boundary_wrap_around)
    TEST(test_memory_read_write_at_boundaries)

    TEST(test_program_initialization)
    TEST(test_program_jump_forward_and_backward)
    TEST(test_program_is_done)

    TEST(test_jump_table_construction)
    TEST(test_opcode_vector_construction)
    TEST(test_bracket_validation)

    TEST(test_from_scratch) 
    TEST(test_valid)
    TEST(test_hello_world)
    TEST(test_echo_program)
END_SUITE
