#ifndef CHKSUM_H_INCLUDED
#define CHKSUM_H_INCLUDED

//chksum - xor8
//Parity byte or parity word[edit]
//The simplest checksum algorithm is the so-called longitudinal parity check,
//which breaks the data into "words" with a fixed number n of bits, and then
//computes the exclusive or of all those words. The result is appended to
//the message as an extra word. To check the integrity of a message, the receiver
//computes the exclusive or (XOR) of all its words, including the checksum;
//if the result is not a word with n zeros, the receiver knows that a transmission
//error occurred.
//With this checksum, any transmission error that flips a single bit of the message,
//or an odd number of bits, will be detected as an incorrect checksum. However,
//an error that affects two bits will not be detected if those bits lie at the
//same position in two distinct words. If the affected bits are independently
//chosen at random, the probability of a two-bit error being undetected is 1/n.
unsigned char chksum_xor8(unsigned char * str, unsigned short length);

//chksum - modular sum
//Modular sum[edit]
//A variant of the previous algorithm is to add all the "words" as unsigned binary
//numbers, discarding any overflow bits, and append the two's complement of the
//total as the checksum. To validate a message, the receiver adds all the words
//in the same manner, including the checksum; if the result is not a word full
//of zeros, an error must have occurred. This variant too detects any single-bit
//error, but the promodular sum is used in SAE J1708.[1]
unsigned char chksum_msum(unsigned char * str, unsigned short length);


//fletcher 16 checksum
unsigned short chksum_fletcher16(unsigned char *data, unsigned short len );


#endif // CHKSUM_H_INCLUDED
