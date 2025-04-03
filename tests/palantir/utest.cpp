#include <fstream>
#include <string>
#include <filesystem>

#include "mu_test.h"

#include "palantir/encryption/encryption_abstract.hpp"
//#include "palantir/encryption/char_encryption.hpp"
#include "palantir/encryption/rot13.hpp"
#include "palantir/encryption/atbash.hpp"
#include "palantir/encryption/caesar.hpp"
#include "palantir/encryption/vigenere.hpp"
#include "palantir/encryption/null_encryption.hpp"
#include "palantir/encryption/xor.hpp"


#include "palantir/message_source/console_in.hpp"
#include "palantir/message_source/file_source.hpp"

#include "palantir/message_destination/console_out.hpp"
#include "palantir/message_destination/file_destination.hpp"

#include "palantir/message_destination/udp_destination.hpp"
#include "palantir/message_source/udp_source.hpp"

#include "palantir/message_destination/tcp_destination.hpp"
#include "palantir/message_source/tcp_source.hpp"

#include "palantir/udp/udp_client.hpp"
#include "palantir/udp/udp_server.hpp"

#include "palantir/tcp/tcp_client.hpp"
#include "palantir/tcp/tcp_server.hpp"

#include "palantir/messenger.hpp"

#include <thread>  // For threading to simulate simultaneous actions

BEGIN_TEST(test_rot13_text)
    palantir::Rot13 rot13{};
    palantir::EncryptionAbstract& cipher = rot13;
    std::string text = "The quick brown fox jumps over 13 lazy dogs.";
    std::string encoded = cipher.encode(text);
    ASSERT_EQUAL(encoded, "Gur dhvpx oebja sbk whzcf bire 13 ynml qbtf.");
    std::string decoded = cipher.decode(encoded);
    ASSERT_EQUAL(decoded, text);
END_TEST

/*-------------------------------------------------------------------------------*/

BEGIN_TEST(test_atbash_text)
    palantir::Atbash atbash{};
    palantir::EncryptionAbstract& cipher = atbash;
    std::string text = "THE QUICK1 BROWN FOX jumps OVER the #LAZY DOG";
    std::string encoded = cipher.encode(text);
    ASSERT_EQUAL(encoded, "GSV JFRXP1 YILDM ULC qfnkh LEVI gsv #OZAB WLT");
    std::string decoded = cipher.decode(encoded);
    ASSERT_EQUAL(decoded, text);
END_TEST

/*-------------------------------------------------------------------------------*/

BEGIN_TEST(test_caesar_text)
    palantir::Caesar caesar{11};
    palantir::EncryptionAbstract& cipher = caesar;
    std::string text = "THE QUICK1 BROWN FOX jumps OVER the LAZY DOG";
    std::string encoded = cipher.encode(text);
    ASSERT_EQUAL(encoded, "ESP BFTNV1 MCZHY QZI ufxad ZGPC esp WLKJ OZR");
    std::string decoded = cipher.decode(encoded);
    ASSERT_EQUAL(decoded, text);
END_TEST

/*-------------------------------------------------------------------------------*/

BEGIN_TEST(test_vigenere_key_longer_than_text)
    palantir::Vigenere vigenere{"oculorhinolaryngology"};
    palantir::EncryptionAbstract& cipher = vigenere;
    std::string text = "attacking tonight";
    std::string encoded = cipher.encode(text);
    ASSERT_EQUAL(encoded, "ovnlqbpvt hznzeuz");
    std::string decoded = cipher.decode(encoded);
    ASSERT_EQUAL(decoded, text);
END_TEST

BEGIN_TEST(test_vigenere_key_shorter_than_text)
    
    palantir::Vigenere vigenere{"LEMON"};
    palantir::EncryptionAbstract& cipher = vigenere;
    std::string text = "attackatdawn";
    std::string encoded = cipher.encode(text);
    ASSERT_EQUAL(encoded, "lxfopvefrnhr");
    std::string decoded = cipher.decode(encoded);
    ASSERT_EQUAL(decoded, text);
END_TEST

BEGIN_TEST(test_vigenere_key_same_len_as_text)
    palantir::EncryptionAbstract *cipher = new palantir::Vigenere{"LEMON"};
    std::string text = "HelLo";
    std::string encoded = cipher->encode(text);
    ASSERT_EQUAL(encoded, "SixZb");
    std::string decoded = cipher->decode(encoded);
    ASSERT_EQUAL(decoded, text);
    delete cipher;
END_TEST

/*-------------------------------------------------------------------------------*/

BEGIN_TEST(test_null_encryption)
    palantir::EncryptionAbstract *cipher = new palantir::NullEncryption{};
    std::string text = "attacking tonight";
    std::string encoded = cipher->encode(text);
    ASSERT_EQUAL(encoded, text);
    std::string decoded = cipher->decode(encoded);
    ASSERT_EQUAL(decoded, text);
END_TEST

/*-------------------------------------------------------------------------------*/

BEGIN_TEST(test_xor_encryptor)
    std::string key = "\x1F"; // \x1F\x1F\x1F\x1F\x1F\x1F\x1F\x1F\x1F\x1F\x1F\x1F\x1F\x1F\x1F
    palantir::EncryptionAbstract *cipher = new palantir::XorEncryptor{key};
    std::string text = "attacking tonight";

    std::string encoded = cipher->encode(text);
    // Assuming the encoded string from your test setup
    ASSERT_EQUAL(encoded, "~kk~|tvqx?kpqvxwk");

    std::string decoded = cipher->decode(encoded);
    ASSERT_EQUAL(decoded, text);
END_TEST

/*-------------------------------------------------------------------------------*/

BEGIN_TEST(test_console_live_input)
    palantir::ConsoleInput console;
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
// works at first time between every two consesetive tests
// test_output.txt must exists and be empty
BEGIN_TEST(test_file_destination_send_message)  
    const std::string test_file_name = "test_output.txt";
    palantir::FileDestination file_dest(test_file_name);

    std::string test_message = "Hello, File!";
    file_dest.send_message(test_message);
    std::ifstream in_file(test_file_name);
    std::string file_content;

    std::getline(in_file, file_content);

    in_file.close();

    ASSERT_EQUAL(file_content, test_message);
    
    std::filesystem::remove(test_file_name);
END_TEST

/*-------------------------------------------------------------------------------*/

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
    while (std::getline(test_file, line)) {
        if (!line.empty()) {
            fileLines.push_back(line);
        }
    }
    test_file.close();

    std::cout << "\nContents of " << test_file_name << ":" << '\n';
    for (std::vector<std::string>::const_iterator l = fileLines.begin(); l != fileLines.end(); ++l) {
        std::cout << *l << '\n';
    }

    bool match = true;
    if (fileLines.size() >= inputLines.size()) {
        std::vector<std::string>::const_iterator it = fileLines.end() - inputLines.size();
        for (std::vector<std::string>::const_iterator inputLine = inputLines.begin(); inputLine != inputLines.end(); ++inputLine, ++it) {
            if (*it != *inputLine) {
                match = false;
                break;
            }
        }
    } else {
        match = false;
    }

    ASSERT_THAT(match);

END_TEST

/*-------------------------------------------------------------------------------*/

BEGIN_TEST(test_udp_source_receive_using_udp_client)
    // Setup UdpSource to receive messages
    palantir::UdpSource udpSource{1139};
    std::string expected_result{"Hello"};
    
    // Setup UdpClient to send message to UdpSource
    palantir::UdpClient udpClient("127.0.0.1", 1139);
    udpClient.send_message(expected_result);

    std::string result = udpSource.get_message();

    ASSERT_EQUAL(result, expected_result);
END_TEST

/*-------------------------------------------------------------------------------*/

BEGIN_TEST(udp_destination_send_message_using_udp_server)
    // Setup UdpServer to receive messages
    int listening_port = 1138;
    palantir::UdpServer udpServer(listening_port);

    // Setup UdpDestination to send messages to the UdpServer
    palantir::UdpDestination udpDestination{"127.0.0.1", listening_port};
    std::string expected_message = "Test message";
    udpDestination.send_message(expected_message);

    std::string received_message = udpServer.receive();

    ASSERT_EQUAL(received_message, expected_message);
END_TEST

/*-------------------------------------------------------------------------------*/

BEGIN_TEST(full_test_example_udp_to_udp)
    palantir::EncryptionAbstract* rot13 = new palantir::Rot13();
    palantir::EncryptionAbstract* vigenere = new palantir::Vigenere("LEMON");
    palantir::EncryptionAbstract* caesar = new palantir::Caesar(-7);
    palantir::EncryptionAbstract* null_enc = new palantir::NullEncryption();
    palantir::EncryptionAbstract* atbash = new palantir::Atbash();
    
    std::vector<palantir::EncryptionAbstract*> encryptions{rot13, vigenere, caesar, null_enc, atbash};
    palantir::Messenger m(encryptions);

    palantir::UdpSource us{1138};
    palantir::FileSource fs("myfile.txt");
    palantir::UdpDestination udp("127.0.0.1", 1138);

    // Simulate processing a message read from file, encrypted and sent over UDP
    m.process(fs, udp);

    std::string received = us.get_message();

    ASSERT_EQUAL(received, "BLWUS blwus\n");
    delete rot13;
    delete vigenere;
    delete caesar;
    delete null_enc;
    delete atbash;

END_TEST

/*-------------------------------------------------------------------------------*/

BEGIN_TEST(console_to_udp_vigenere_long_input)
    palantir::Vigenere v{"key"};
    palantir::Messenger m{v};
    palantir::ConsoleInput consoleInput;
    palantir::UdpDestination udp("127.0.0.1", 4321);
    palantir::UdpSource udp_receiver(4321);
    std::istringstream input("The passcode is: 12345! Please confirm.");
    std::cin.rdbuf(input.rdbuf());
    m.process(consoleInput, udp);
    std::string result = udp_receiver.get_message();
    ASSERT_EQUAL(result, "Dlc zeqcgmni gc: 12345! Tjoeqo gmxjgbq.\n");
END_TEST

/*-------------------------------------------------------------------------------*/

// BEGIN_TEST(test_tcp_source_receive_using_tcp_client)
//     // Setup UdpSource to receive messages
//     palantir::TcpSource tcpSource{1144};
//     std::string expected_result{"Hello"};
    
//     // Setup UdpClient to send message to UdpSource
//     palantir::TcpClient tcpClient("127.0.0.1", 1144);

//     ASSERT_THAT(tcpClient.connect_to_server());

//     tcpClient.send_message(expected_result);
    
//     std::string result = tcpSource.get_message();
//     tcpClient.close_connection();
//     ASSERT_EQUAL(result, expected_result);
// END_TEST

// BEGIN_TEST(test_tcp_source_receive_using_tcp_client)
//     // Setup TcpSource to receive messages
//     palantir::TcpSource tcpSource(1144);  // Listen on port 1144
//     std::string expected_result{"Hello"};
//     sleep(1);
//     // Create TcpClient and connect to the server (TcpSource)
//     palantir::TcpClient tcpClient("127.0.0.1", 1144);

//     // Ensure the client successfully connects before sending the message
//     ASSERT_THAT(tcpClient.connect_to_server());

//     // Send the message from TcpClient to TcpSource in a separate thread
//     std::thread clientThread([&] {
//         // Send message from TcpClient to TcpSource
//         tcpClient.send_message(expected_result);
        
//         // Close the client connection immediately after sending the message
//         tcpClient.close_connection();
//     });

//     // Retrieve the message from TcpSource
//     std::string result = tcpSource.get_message();

//     // Ensure that the message received matches the expected result
//     ASSERT_EQUAL(result, expected_result);

//     // Join the client thread to ensure it's completed
//     clientThread.join();

//     // Verify that the TcpSource handled the client's disconnection properly
//     ASSERT_THAT(tcpSource.is_fully_processed());

// END_TEST


/*-------------------------------------------------------------------------------*/

BEGIN_SUITE(palantir_tests)

    TEST(test_rot13_text)

    TEST(test_atbash_text)

    TEST(test_caesar_text)

    TEST(test_vigenere_key_longer_than_text)
    TEST(test_vigenere_key_shorter_than_text)
    TEST(test_vigenere_key_same_len_as_text)

    TEST(test_null_encryption)

    TEST(test_xor_encryptor)

    TEST(test_file_source_get_message)

    TEST(test_console_output_send_message)
    TEST(test_file_destination_send_message)
    
    TEST(test_console_to_file)

    TEST(test_udp_source_receive_using_udp_client)
    TEST(udp_destination_send_message_using_udp_server)

    TEST(full_test_example_udp_to_udp)
    TEST(console_to_udp_vigenere_long_input)

    //TEST(test_tcp_source_receive_using_tcp_client)

    //TEST(test_tcp_source_receive_using_tcp_client)

END_SUITE