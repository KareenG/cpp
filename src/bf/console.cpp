#include "bf/console.hpp"
#include <iostream>

namespace bf {

Console::Console(Mode mode, const std::string& test_data)
: mode(mode)
, test_input_buffer(test_data) 
{
}

Console::Console(const Console& other)
: mode(other.mode)
, test_output_buffer()
, test_input_buffer() 
{
    if (mode == Mode::DEBUG) {
        test_input_buffer.str(other.test_input_buffer.str());
        test_output_buffer.str(other.test_output_buffer.str());
        test_input_buffer.clear(); // Clear any error flags
        test_output_buffer.clear(); // Clear any error flags
    }
}

void Console::set_test_data(const std::string& test_data) 
{
    if (mode == Mode::DEBUG) {
        test_input_buffer.str(test_data);
        test_input_buffer.clear();
    }
}

void Console::write(int c) 
{
    if (mode == Mode::Runtime) {
        std::cout << c << ' ';
    } else {
        test_output_buffer << c << ' ';
    }
}

unsigned char Console::read() 
{
    if (mode == Mode::Runtime) {
        char c;
        std::cin.get(c);
        return c;
    } else {
        char c = 0;
        test_input_buffer.get(c);
        return c;
    }
}

std::string Console::get_test_output() const 
{
    return test_output_buffer.str();
}

void Console::clear_test_output() 
{
    test_output_buffer.str(std::string()); 
    test_output_buffer.clear();
}

}