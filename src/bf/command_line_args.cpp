#include <string.h>

#include "bf/command_line_args.hpp"

namespace bf {

bool CommandLineArgs::get_code_for_compilation(int argc, char* argv[], std::string& code) 
{
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <filename.bf> or " << argv[0] << " -r <code>\n";
        return false;
    }
    if (strcmp(argv[1], "-r") == 0) {
        if (argc < 3) {
            std::cerr << "Usage: " << argv[0] << " -r <code>\n";
            return false;
        }
        code = argv[2];
    } else {
        std::ifstream input_file(argv[1]);
        if (!input_file.is_open()) {
            std::cerr << "Error opening file: " << argv[1] << '\n';
            return false;
        }
        std::stringstream buffer;
        buffer << input_file.rdbuf();
        code = buffer.str();  // File content
    }
    return true;
}    

}       // namespace bf

