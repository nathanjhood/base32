# base32

Base32 encode/decode CLI in C++.

```.sh
$ base32 [OPTIONS] [FILE]...
```

Base32 encode/decode functions in NodeJs.

```.js
import base32 from "@nathanjhood/base32";

console.log(base32.encode("foobar"));
```

## Coming soon

*PLEASE NOTE: This project is under construction; as of writing, the encode function is working but missing a few chars on longer strings. The decode function is actually the base64 decode algorithm as a plaeholder; this function will be ported to base32 shortly. Stay tuned!*

## About

The encoding process represents 40-bit groups of input bits as output
strings of 8 encoded characters.  Proceeding from left to right, a
40-bit input group is formed by concatenating 5 8bit input groups.
These 40 bits are then treated as 8 concatenated 5-bit groups, each
of which is translated into a single character in the base 32
alphabet.

```.txt
  <===========>                                                                   1st character
                  <===========>                                                   2nd character
                                  <===========>                                   3rd character
                                                  <===========>                   4th character
                                                                  <===========>   5th character
+---------------+---------------+---------------+---------------+---------------+
| <     1     > | <     2     > | <     3     > | <     4     > | <     5     > | 5 groups (8 bits)
+---------------+---------------+---------------+---------------+---------------+
|0 1 2 3 4 5 6 7|8 9 0 1 2 3 4 5|6 7 8 9 0 1 2 3|4 5 6 7 8 9 0 1|2 3 4 5 6 7 8 9| Stream  (40 bits)
+---------+-----+---+---------+-+-------+-------+-+---------+---+-----+---------+
|<   1   >|<   2   >|<   3   >|<   4   >|<   5   >|<   6   >|<   7   >|<   8   >| 8 groups (5 bits)
+---------+---------+---------+---------+---------+---------+---------+---------+
|5 4 3 2 1|5 4 3 2 1|5 4 3 2 1|5 4 3 2 1|5 4 3 2 1|5 4 3 2 1|5 4 3 2 1|5 4 3 2 1| Index   (40 bits)

                                                                       <=======>  8th character
                                                             <=======>            7th character
                                                   <=======>                      6th character
                                         <=======>                                5th character
                               <=======>                                          4th character
                     <=======>                                                    3rd character
           <=======>                                                              2nd character
 <=======>                                                                        1st character
```

Each 5-bit group is used as an index into an array of 32 printable
characters.  The character referenced by the index is placed in the
output string.  These characters, identified in the table below, are
selected from US-ASCII digits and uppercase letters.

When a bit stream is encoded via the base 32 encoding, the
bit stream must be presumed to be ordered with the most-significant-
bit first.  That is, the first bit in the stream will be the high-
order bit in the first 8bit byte, the eighth bit will be the low-
order bit in the first 8bit byte, and so on.

A 33-character subset of US-ASCII is used, enabling 5 bits to be
represented per printable character.  (The extra 33rd character, "=",
is used to signify a special processing function.)

```.txt
                  The Base 32 Alphabet

  Value Encoding  Value Encoding  Value Encoding  Value Encoding
      0 A             9 J            18 S            27 3
      1 B            10 K            19 T            28 4
      2 C            11 L            20 U            29 5
      3 D            12 M            21 V            30 6
      4 E            13 N            22 W            31 7
      5 F            14 O            23 X
      6 G            15 P            24 Y         (pad) =
      7 H            16 Q            25 Z
      8 I            17 R            26 2
```

## Thanks for reading!

[Nathan J. Hood](https://github.com/nathanjhood)

## Acknowledgements:

- ["The Base16, Base32, and Base64 Data Encodings"](https://datatracker.ietf.org/doc/html/rfc4648); S. Josefsson (Copyright (C) 2006 The Internet Society).

- 'base32.cpp'; The central encode/decode algorithm is a heavily modified implementation taken from René Nyffenegger's 'base64.cpp' (Copyright (C) 2004-2008 René Nyffenegger) from the below discussion:

- [https://stackoverflow.com/questions/180947/base64-decode-snippet-in-c](https://stackoverflow.com/questions/180947/base64-decode-snippet-in-c)

- [A more recent (version 2) revision of that algorithm is also publically available](https://renenyffenegger.ch/notes/development/Base64/Encoding-and-decoding-base-64-with-cpp/). My reasons for adapting an earlier version is because I intend to attempt several other encode/decode algorithms using a similar approach to this implementation, which has slightly less of the functionality tailored specifically for base64, and thus shall be more adaptable into other forms.
