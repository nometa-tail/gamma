Algorithm Description

Algorithm: For a data block of a specified size, a segment of the "gamma" (keystream) of the same size is taken, and a bitwise XOR (Exclusive OR) operation is performed. Next, a bitwise cyclic shift (rotation) by a specified number of bits to the left or right is applied to the resulting block. Decryption is performed in reverse order: first, a cyclic shift is applied in the opposite direction, followed by the bitwise XOR operation with the same gamma blocks.

Program Modes

The program can be executed in two modes: encryption and decryption.

1. Encryption Mode

Input Parameters: The program accepts three command-line arguments (via the main function): the keyword encryption and two filenames. The first file is the source to be encrypted (must exist), and the second file is where the encrypted data will be saved.

Process: The program prompts the user for a password (an integer). The data from the first file is then encrypted and stored in the second file.

2. Decryption Mode

Input Parameters: The program accepts three command-line arguments: the keyword decryption and two filenames. The first file contains the encrypted data (must exist), and the second file is where the decrypted data will be stored.

Process: The program prompts the user for the password (the same integer used for encryption). The data from the first file is decrypted and written to the second file.
