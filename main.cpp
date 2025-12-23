#include <iostream>
#include <fstream>
#include <random>
#include <cstring>

using namespace std;

// Function for cyclic right shift by n bits
uint32_t rotate_right(uint32_t value, int n) {
    return (value >> n) | (value << (32 - n));
}

// Function for cyclic left shift by n bits
uint32_t rotate_left(uint32_t value, int n) {
    return (value << n) | (value >> (32 - n));
}

void shifr_deshifr(const char *in, char *out, int len, int key, bool shifr = true) {
    int len1 = len / 4; // Number of full 4-byte blocks
    int len2 = len % 4; // Size of the last incomplete block
    if (len2) len1++;   // Account for the last incomplete block

    mt19937 bas(key);
    uniform_int_distribution<uint32_t> gen(0, 0xffffffff);

    for (int i = 0; i < len1; i++) {
        int size = 4;
        if (len2 && i == len1 - 1)
            size = len2;

        uint32_t rez = 0;
        memcpy(&rez, in + 4 * i, size);

        if (shifr) {
            // Encryption mode: XOR with gamma -> right shift by 3 bits
            uint32_t gamma = gen(bas);
            rez ^= gamma;
            if (size == 4) {
                rez = rotate_right(rez, 3);
            }
        } else {
            // Decryption mode: left shift by 3 bits -> XOR with gamma
            if (size == 4) {
                rez = rotate_left(rez, 3);
            }
            uint32_t gamma = gen(bas);
            rez ^= gamma;
        }
        memcpy(out + 4 * i, &rez, size);
    }
}

int main(int argc, const char* argv[]) {
    if (argc != 4) {
        cerr << "Error: Use 3 parameters\n";
        return 1;
    }

    const string mode(argv[1]);
    const string file_name1(argv[2]);
    const string file_name2(argv[3]);

    if (mode != "encryption" && mode != "decryption") {
        cerr << "Error: Invalid mode\n";
        return 1;
    }

    // Password request
    int password;
    cout << "Enter password: ";
    cin >> password;

    // Opening the input file
    ifstream in_file(file_name1, ios::binary);
    if (!in_file) {
        cerr << "Error: Cannot open input file\n";
        return 1;
    }

    // Determining file size
    in_file.seekg(0, ios::end);
    int file_size = in_file.tellg();
    in_file.seekg(0, ios::beg);

    // Reading data from file
    char* buffer_in = new char[file_size];
    in_file.read(buffer_in, file_size);
    in_file.close();

    // Data processing
    char* buffer_out = new char[file_size];
    shifr_deshifr(buffer_in, buffer_out, file_size, password, mode == "encryption");

    // Writing result to the output file
    ofstream out_file(file_name2, ios::binary);
    if (!out_file) {
        cerr << "Error: Cannot open output file\n";
        return 1;
    }
    out_file.write(buffer_out, file_size);
    out_file.close();

    // Memory cleanup
    delete[] buffer_in;
    delete[] buffer_out;

    cout << "Success.\n";
    return 0;
}