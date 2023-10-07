#ifndef TEST_BUILD

/*
*   This file is only active in non-test builds (i.e., builds where TEST_BUILD is not defined).
*/

#include <iostream>
#include <sstream>
#include "encoding/bit-grouper.h"
#include "encoding/encoding.h"
#include "encoding/eof-encoding.h"
#include "encoding/encoding-combiner.h"
#include "io/files.h"
#include "encoding/huffman/huffman-encoding.h"

/*
* This is the main entry point of your application.
* Note that it will only work in non-test builds.
*/
int main(int argc, char* argv[])
{
#ifdef NDEBUG

    std::cout << "Enter command and file paths (e.g., huffman compress file.txt file.hf): ";
    std::string userInput;
    std::getline(std::cin, userInput);

    std::cout << userInput << std::endl;

    std::stringstream ss(userInput);
    std::string huffman;
    std::string command;
    std::string inputFilePath;
    std::string outputFilePath;

    ss >> huffman >> command >> inputFilePath >> outputFilePath;

    std::cout << "command: " + command << std::endl;


    if (command == "compress")
    {
        io::DataSource<256> dataSource = io::create_file_data_source(inputFilePath);
        io::DataDestination<256> dataDestination = io::create_file_data_destination(outputFilePath);
        encoding::Encoding<256, 256> combine = encoding::eof_encoding<256>() | encoding::huffman::huffman_encoding<257>() | encoding::bit_grouper<8>();
        encoding::encode(dataSource, dataDestination, combine);
        std::cout << "Compression complete.\n";
    }
    else if (command == "decompress")
    {
        io::DataSource<256> dataSource = io::create_file_data_source(inputFilePath);
        io::DataDestination<256> dataDestination = io::create_file_data_destination(outputFilePath);
        encoding::Encoding<256, 256> combine = encoding::eof_encoding<256>() | encoding::huffman::huffman_encoding<257>() | encoding::bit_grouper<8>();
        encoding::decode(dataSource, dataDestination, combine);
        std::cout << "Decompression complete.\n";
    }
    else
    {
        std::cout << "Unknown command: " << command << "\n";
        return 1;
    }

    return 0;
#else
    std::cout << "You are running the debug build" << std::endl;
#endif
}

#endif