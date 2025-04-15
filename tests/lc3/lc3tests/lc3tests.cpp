#include <string>
#include <cstdint>

#include "mu_test.h"

#include "lc3/program_loader.hpp"
#include "lc3/program_counter.hpp"
#include "lc3/memory.hpp"
#include "lc3/registers.hpp"
#include "lc3/console.hpp"
#include "lc3/trap_handler.hpp"
#include "lc3/decoder_detail/bits.hpp"
#include "lc3/decoder_detail/bit_manipulations.hpp"
#include "lc3/decoder.hpp"
#include "lc3/alu.hpp"
#include "lc3/cpu.hpp"

/**
 * @brief xxd print10.bin - in terminal
 * This gives a hex dump of the actual file (origin + instructions), so you can 
 * directly validate instruction encodings without guessing offsets.
 */

BEGIN_TEST(loads_print10_correctly)
    const std::string file_path = "print10.bin";
    lc3::Memory memory;
    lc3::ProgramLoader loader(file_path, memory);

    uint16_t base = memory.get_program_start();
    ASSERT_THAT(base == 0x3000);

    ASSERT_EQUAL(memory.read(base + 0), 0xE00A);  // LEA R0, HI
    ASSERT_EQUAL(memory.read(base + 1), 0x2408);  // LD R2, TEN
    ASSERT_EQUAL(memory.read(base + 2), 0x2806);  // LD R4, ZERO
    ASSERT_EQUAL(memory.read(base + 3), 0xF022);  // PUTS
    ASSERT_EQUAL(memory.read(base + 4), 0x1921);  // ADD R4, R4, #1
    ASSERT_EQUAL(memory.read(base + 5), 0x7800);  // STR R4, R0, #0
    ASSERT_EQUAL(memory.read(base + 6), 0x14BF);  // ADD R2, R2, #-1
    ASSERT_EQUAL(memory.read(base + 7), 0x0BFB);  // BRnp LOOP_START
    ASSERT_EQUAL(memory.read(base + 8), 0xF025);  // HALT

    ASSERT_EQUAL(memory.read(base +11), '0');
    ASSERT_EQUAL(memory.read(base +12), ':');
    ASSERT_EQUAL(memory.read(base +13), ' ');
    ASSERT_EQUAL(memory.read(base +14), 'I');
    ASSERT_EQUAL(memory.read(base +15), ' ');
    ASSERT_EQUAL(memory.read(base +16), 'L');
    ASSERT_EQUAL(memory.read(base +17), 'o');
    ASSERT_EQUAL(memory.read(base +18), 'v');
    ASSERT_EQUAL(memory.read(base +19), 'e');
    ASSERT_EQUAL(memory.read(base +20), ' ');
    ASSERT_EQUAL(memory.read(base +21), 'C');
    ASSERT_EQUAL(memory.read(base +22), '+');
    ASSERT_EQUAL(memory.read(base +23), '+');
    ASSERT_EQUAL(memory.read(base + 24), '!');
    ASSERT_EQUAL(memory.read(base + 25), '!');
    ASSERT_EQUAL(memory.read(base + 26), '\n');  // newline now correct
    ASSERT_EQUAL(memory.read(base + 27), '\0'); // null terminator
END_TEST

BEGIN_TEST(sign_extend_positive_5bit)
    ASSERT_EQUAL(lc3::decoder::bit_manipulations::sign_extend(0b01111, 5), 15);
END_TEST

BEGIN_TEST(sign_extend_negative_6bit)
    ASSERT_EQUAL(lc3::decoder::bit_manipulations::sign_extend(0b111000, 6), -8);
END_TEST

BEGIN_TEST(sign_extend_positive_9bit)
    ASSERT_EQUAL(lc3::decoder::bit_manipulations::sign_extend(0b011111111, 9), 255);
END_TEST

BEGIN_TEST(sign_extend_negative_11bit)
    ASSERT_EQUAL(lc3::decoder::bit_manipulations::sign_extend(0b10111111111, 11), -513);
END_TEST

BEGIN_TEST(sign_extend_9bit_110101111)
    uint16_t raw = 0b110101111; // 0x96
    int16_t result = lc3::decoder::bit_manipulations::sign_extend(raw, 9);
    ASSERT_EQUAL(result, -81);  // Expected result after extending to 16 bits
END_TEST

BEGIN_TEST(run_print10_program)
    const std::string file_path = "print10.bin";
    lc3::Memory memory;
    lc3::ProgramLoader loader(file_path, memory);

    std::ostringstream os;
    std::istringstream is;
    lc3::Console console(os, is);

    lc3::CPU cpu(memory, console);

    cpu.run();

    std::ostringstream expected;
    for (int i = 0; i < 10; ++i) {
        expected << i << ": I Love C++!!\n";
    }

    ASSERT_EQUAL(os.str(), expected.str());
END_TEST

BEGIN_TEST(run_fib22_program)
    lc3::Memory memory;
    lc3::ProgramLoader loader("fib22.bin", memory); // Patches TRAP vectors

    std::ostringstream os;
    lc3::Console console(os);
    lc3::CPU cpu(memory, console);

    cpu.run();

    const std::string expected =
        "1\n1\n2\n3\n5\n8\n13\n21\n34\n55\n89\n144\n233\n377\n610\n987\n1597\n2584\n4181\n6765\n10946\n17711\n";

    const std::string actual = os.str();

    ASSERT_EQUAL(actual.size(), expected.size());

    for (size_t i = 0; i < expected.size(); ++i) {
        ASSERT_EQUAL(
            (int)(unsigned char)actual[i],
            (int)(unsigned char)expected[i]
        );
    }
END_TEST

// BEGIN_TEST(run_2048_program)
//     lc3::Memory memory;
//     lc3::ProgramLoader loader("2048.bin", memory);  // load the game binary

//     lc3::Console console{std::cout, std::cin};  // use standard console I/O
//     lc3::CPU cpu(memory, console);

//     cpu.run();  // interactively play the game

// END_TEST

BEGIN_TEST(run_2048_program)
    lc3::Memory memory;
    lc3::ProgramLoader loader("2048.bin", memory); // Load binary

    std::istringstream input_stream("y\n");  // Automatically reply "y" to ANSI terminal prompt
    std::ostringstream output_stream;

    lc3::Console console(std::cout, std::cin);//output_stream, input_stream
    lc3::CPU cpu(memory, console);


    // memory.write(0xC1C0, 0x3000);  // Assume 0x3000 points to a valid string
    // memory.write(0x3000, 'y');     // null-terminated
    // memory.write(0x3001, 0x0000);

    cpu.run();
END_TEST

BEGIN_TEST(run_rogue_program)
    lc3::Memory memory;
    lc3::ProgramLoader loader("rogue.bin", memory);

    std::istringstream is("k\ndsdsdddsdsdsddsdddsdsdddddsdsddddsdddddddsds\nn\n");
    std::ostringstream os;

    lc3::Console console(os, is);
    lc3::CPU cpu(memory, console);

    cpu.run();  // Execute the game

    std::string output = os.str();

    std::cout << "=== BEGIN OUTPUT ===\n";
    std::cout << output;
    std::cout << "=== END OUTPUT ===\n";

    ASSERT_THAT(output.find("You survived!") != std::string::npos);  // Success message
    ASSERT_THAT(output.find("On to another dungeon? (n)o or any key to continue.") != std::string::npos);     // Prompt to continue
END_TEST


BEGIN_SUITE(lc3_tests)
    TEST(loads_print10_correctly)

    TEST(sign_extend_positive_5bit)
    TEST(sign_extend_negative_6bit)
    TEST(sign_extend_positive_9bit)
    TEST(sign_extend_negative_11bit)
    TEST(sign_extend_9bit_110101111)

    TEST(run_print10_program)

    TEST(run_fib22_program)

    //TEST(run_2048_program)

    TEST(run_rogue_program)

END_SUITE