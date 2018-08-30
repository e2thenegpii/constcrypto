This code is a little project I was working on to generate the AES-sboxs at compile time.

I got started after a brief conversation with a coworker about Software Reverse Engineering and how if you really want to confuse a SRE'er then you can use a nonstandard S-Box for AES.  I wanted to see if I could implement a library that could generate a "cryptographically sound" S-Box that could be used as a replacement for the standard GF2^8 modulo 0x1B polynomial.  It turns out there are 30 primitive polynomials over GF2^8.  You could also potentially use a different affine transform, but I would be much more cautious about the affine transform if you actually intend to use this somewhere (which I'm strongly encouraging you NOT to do).

To Build it:
1. You'll need a C++17 compiler I used gcc version 8.1 successfully
2. gcc-8 --std=c++17 -c sbox.cpp -o sbox.o
3. gcc-8 --std=c++17 main.cpp -o main

Running the code you should see the standard AES sbox and round constants.  You can tweak the sbox to link in by changing the template argument to the initialize_aes_sbox and initialize_inverse_aes_sbox functions, they should be the same however, if you want your AES implementation you link it against to actually work.  A little bit of effort went into idiot proofing the choice of polynomial and a template structure polynomial checker is provided in the form of is_cyclic_over_gf256<uint8_t polynomial>.  If you don't care about an invertable S-Box and just want a random permutation of each of the values [0, 256) then pick a polynomial and a generator index (a value on the interval [0, 128) ).  For S-Box generation the generator index is irrelevant however.

Using this one could presumably implement a full AES to execute at compile-time, though what you could possibly want to encrypt at compile-time is beyond me.
