#include <fstream>
#include <string>
#include <filesystem>

#include "mu_test.h"

#include "palantir/encryption/encryption_abstract.hpp"
#include "palantir/encryption/rot13.hpp"
#include "palantir/encryption/atbash.hpp"
#include "palantir/encryption/caesar.hpp"
#include "palantir/encryption/vigenere.hpp"
#include "palantir/encryption/null_encryption.hpp"

#include "palantir/message_source/console_in.hpp"
#include "palantir/message_source/file_source.hpp"

#include "palantir/message_destination/console_out.hpp"
#include "palantir/message_destination/file_destination.hpp"

#include "palantir/message_destination/udp_destination.hpp"
#include "palantir/message_source/udp_source.hpp"
#include <thread>

BEGIN_TEST(test_rot13_text)
    palantir::Rot13 cipher{};
    std::string text = "The quick brown fox jumps over 13 lazy dogs.";
    std::string encoded = cipher.encode(text);
    ASSERT_EQUAL(encoded, "Gur dhvpx oebja sbk whzcf bire 13 ynml qbtf.");
    std::string decoded = cipher.decode(encoded);
    ASSERT_EQUAL(decoded, text);
END_TEST

/*-------------------------------------------------------------------------------*/

BEGIN_TEST(test_atbash_hebrew_text)
    palantir::Atbash cipher{};
    std::string text = "THE QUICK1 BROWN FOX jumps OVER the #LAZY DOG";
    std::string encoded = cipher.encode(text);
    ASSERT_EQUAL(encoded, "GSV JFRXP1 YILDM ULC qfnkh LEVI gsv #OZAB WLT");
    std::string decoded = cipher.decode(encoded);
    ASSERT_EQUAL(decoded, text);
END_TEST

/*-------------------------------------------------------------------------------*/

BEGIN_TEST(test_caesar_text)
    palantir::Caesar cipher{11};
    std::string text = "THE QUICK1 BROWN FOX jumps OVER the LAZY DOG";
    std::string encoded = cipher.encode(text);
    ASSERT_EQUAL(encoded, "ESP BFTNV1 MCZHY QZI ufxad ZGPC esp WLKJ OZR");
    std::string decoded = cipher.decode(encoded);
    ASSERT_EQUAL(decoded, text);
END_TEST

/*-------------------------------------------------------------------------------*/

BEGIN_TEST(test_vigenere_key_longer_than_text)
    palantir::Vigenere cipher("oculorhinolaryngology");
    std::string text = "attacking tonight";
    std::string encoded = cipher.encode(text);
    ASSERT_EQUAL(encoded, "ovnlqbpvt hznzeuz");
    std::string decoded = cipher.decode(encoded);
    ASSERT_EQUAL(decoded, text);
END_TEST

BEGIN_TEST(test_vigenere_key_shorter_than_text)
    palantir::Vigenere cipher("LEMON");
    std::string text = "attackatdawn";
    std::string encoded = cipher.encode(text);
    ASSERT_EQUAL(encoded, "lxfopvefrnhr");
    std::string decoded = cipher.decode(encoded);
    ASSERT_EQUAL(decoded, text);
END_TEST

BEGIN_TEST(test_vigenere_key_same_len_as_text)
    palantir::EncryptionAbstract *cipher = new palantir::Vigenere("LEMON");
    //palantir::Vigenere cipher("LEMON");
    std::string text = "HelLo";
    std::string encoded = cipher->encode(text);
    ASSERT_EQUAL(encoded, "SixZb");
    std::string decoded = cipher->decode(encoded);
    ASSERT_EQUAL(decoded, text);
    delete cipher;
END_TEST

/*-------------------------------------------------------------------------------*/

BEGIN_TEST(test_null_encryption)
    palantir::NullEncryption cipher{};
    std::string text = "attacking tonight";
    std::string encoded = cipher.encode(text);
    ASSERT_EQUAL(encoded, text);
    std::string decoded = cipher.decode(encoded);
    ASSERT_EQUAL(decoded, text);
END_TEST

/*-------------------------------------------------------------------------------*/

// BEGIN_TEST(test_console_input)
//     std::string input = "Hello, World!\n";
//     std::istringstream iss(input);
//     std::streambuf* cinBackup = std::cin.rdbuf();  // backup cin's streambuf
//     std::cin.rdbuf(iss.rdbuf());                  // assign streambuf to cin

//     palantir::Console console;
//     std::string message = console.get_message();
//     //bool fullyProcessed = console.is_fully_processed();

//     std::cin.rdbuf(cinBackup);  // restore cin's original streambuf

//     palantir::Rot13 cipher{};
//     std::string enctypted_mes = cipher.encode(message);

//     ASSERT_EQUAL(message, "Hello, World!\n");
//     //ASSERT_EQUAL(fullyProcessed, true);
//     ASSERT_EQUAL(enctypted_mes, "Uryyb, Jbeyq!\n");

// END_TEST

/*-------------------------------------------------------------------------------*/

BEGIN_TEST(test_console_live_input)
    palantir::Console console;
    std::string message;

    std::cout << "Enter some text (Ctrl+D to end): " << '\n';

    while (!console.is_fully_processed()) {
        message += console.get_message();
    }
    
    std::cout << "\nYou entered:\n" << message << '\n';
    
    ASSERT_THAT(!message.empty());
END_TEST

/*-------------------------------------------------------------------------------*/

BEGIN_TEST(test_console_output_send_message)
    palantir::ConsoleOutput console_out;
    std::ostringstream oss;
    std::streambuf* cout_backup = std::cout.rdbuf();

    std::cout.rdbuf(oss.rdbuf());

    std::string test_message = "Hello, World!";
    console_out.send_message(test_message);

    std::cout.rdbuf(cout_backup);

    std::string expected_output = test_message + "\n";
    ASSERT_EQUAL(oss.str(), expected_output);

END_TEST

/*-------------------------------------------------------------------------------*/

BEGIN_TEST(test_file_source_get_message)
    const std::string test_file_name = "test_input.txt";
    std::ofstream outFile(test_file_name);
    outFile << "Hello, World!\nSecond Line!";
    outFile.close();

    palantir::FileSource file_source(test_file_name);
    std::string first_message = file_source.get_message();
    std::string second_message = file_source.get_message();
    
    ASSERT_EQUAL(first_message, "Hello, World!\n");
    ASSERT_EQUAL(second_message, "Second Line!\n");
    ASSERT_THAT(file_source.is_fully_processed());

    std::filesystem::remove(test_file_name);
END_TEST

/*-------------------------------------------------------------------------------*/

BEGIN_TEST(test_file_destination_send_message)
    const std::string test_file_name = "test_output.txt";
    palantir::FileDestination file_dest(test_file_name);

    std::string test_message = "Hello, File!";
    file_dest.send_message(test_message);

    std::ifstream in_file(test_file_name);
    std::string file_content;
    std::getline(in_file, file_content);

    ASSERT_EQUAL(file_content, test_message);

    in_file.close();
    std::filesystem::remove(test_file_name);
END_TEST

/*-------------------------------------------------------------------------------*/

// BEGIN_TEST(test_console_to_file)
//     const std::string test_file_name = "test_output_from_console.txt";
//     palantir::FileDestination file_dest(test_file_name);

//     std::cout << "Enter text (Ctrl+D to end):" << '\n';
//     std::string line;
//     while (std::getline(std::cin, line)) {
//         file_dest.send_message(line);
//     }

//     std::ifstream test_file(test_file_name);
//     std::string content;
//     std::cout << "\nContents of " << test_file_name << ":" << '\n';
//     while (getline(test_file, content)) {
//         std::cout << content << '\n';
//     }
//     test_file.close();

// END_TEST

BEGIN_TEST(test_console_to_file)
    const std::string test_file_name = "test_output_from_console.txt";
    palantir::FileDestination file_dest(test_file_name);

    std::cout << "Enter text (Ctrl+D to end):" << '\n';
    std::vector<std::string> inputLines;
    std::string line;
    while (std::getline(std::cin, line)) {
        file_dest.send_message(line);
        inputLines.push_back(line);
    }

    std::ifstream test_file(test_file_name);
    std::vector<std::string> fileLines;
    while (getline(test_file, line)) {
        if (!line.empty()) {
            fileLines.push_back(line);
        }
    }
    test_file.close();

    // Display the contents of the file for visual verification
    std::cout << "\nContents of " << test_file_name << ":" << '\n';
    for (const auto& l : fileLines) {
        std::cout << l << '\n';
    }

    // Verify that the last entries in the file match the input lines
    bool match = true;
    auto it = fileLines.end() - inputLines.size();
    for (const auto& inputLine : inputLines) {
        if (*it != inputLine) {
            match = false;
            break;
        }
        ++it;
    }

    ASSERT_THAT(match);

END_TEST

/*-------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------------*/
BEGIN_TEST(test_udp_communication)
    const std::string testMessage = "Hello UDP World!";
    const int testPort = 12345; // Ensure this port is open and not used by other applications
    const std::string localhost = "127.0.0.1";

    palantir::UdpDestination destination(localhost, testPort);

    palantir::UdpSource source(localhost, testPort);

    // Run receiver in a separate thread to ensure it's ready to receive ????????????????
    // std::string receivedMessage;
    // std::thread receiver([&]() {
    //     receivedMessage = destination.receive_message(); // Blocking receive
    // });

    // // Give the receiver a moment to start properly
    // std::this_thread::sleep_for(std::chrono::milliseconds(100));

    // // Simulate sending
    // source.send_message(testMessage);

    // // Wait for the receiver thread to finish
    // receiver.join();

    // // Test the received message
    // ASSERT_EQUAL(receivedMessage, testMessage);
END_TEST

/*-------------------------------------------------------------------------------*/

BEGIN_SUITE()

    TEST(test_rot13_text)

    TEST(test_atbash_hebrew_text)

    TEST(test_caesar_text)

    TEST(test_vigenere_key_longer_than_text)
    TEST(test_vigenere_key_shorter_than_text)
    TEST(test_vigenere_key_same_len_as_text)

    TEST(test_null_encryption)

    //TEST(test_console_live_input)
    TEST(test_file_source_get_message)


    TEST(test_console_output_send_message)
    TEST(test_file_destination_send_message)
    //TEST(test_udp_communication)
    
    TEST(test_console_to_file)

END_SUITE