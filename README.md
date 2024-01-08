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

## Thanks for reading!

[Nathan J. Hood](https://github.com/nathanjhood)

## Acknowledgements:

- ["The Base16, Base32, and Base64 Data Encodings"](https://datatracker.ietf.org/doc/html/rfc4648); S. Josefsson (Copyright (C) 2006 The Internet Society).

- 'base32.cpp'; The central encode/decode algorithm is a heavily modified implementation taken from René Nyffenegger's 'base64.cpp' (Copyright (C) 2004-2008 René Nyffenegger) from the below discussion:

- [https://stackoverflow.com/questions/180947/base64-decode-snippet-in-c](https://stackoverflow.com/questions/180947/base64-decode-snippet-in-c)

- [A more recent (version 2) revision of that algorithm is also publically available](https://renenyffenegger.ch/notes/development/Base64/Encoding-and-decoding-base-64-with-cpp/). My reasons for adapting an earlier version is because I intend to attempt several other encode/decode algorithms using a similar approach to this implementation, which has slightly less of the functionality tailored specifically for base64, and thus shall be more adaptable into other forms.
