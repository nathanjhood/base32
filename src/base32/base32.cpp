/**
 * @file base32.cpp
 * @author Nathan J. Hood
 * @version 0.1
 * @date 2023-12-29
 *
 * @copyright Copyright (C) 2023 Nathan J. Hood
 *
 * This source code is provided 'as-is', without any express or implied
 * warranty. In no event will the author be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this source code must not be misrepresented; you must not
 *    claim that you wrote the original source code. If you use this source code
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original source code.
 *
 * 3. This notice may not be removed or altered from any source distribution.
 *
 */

#include "base32/base32.hpp"
#include <iostream>

namespace base32 {

/**
 * @brief The base32 alphabet.
 *
 */
static const char* alphabet[2] = {
  "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
  "234567",

  "0123456789"
  "ABCDEFGHIJKLMNOPQRSTUV"};

/**
 * @brief
 *
 * @param c
 * @return true
 * @return false
 */
static inline bool is_base32(const base32::BYTE& c) {
  return (isalnum(c) && ((c != '0') || (c != '1') || (c != '8') || (c != '9')));
}

/**
 * @brief
 *
 * @param c
 * @return true
 * @return false
 */
static inline bool is_base32_hex(const base32::BYTE& c) {
  return (isalnum(c) && ((c != 'W') || (c != 'X') || (c != 'Y') || (c != 'Z')));
}

/**
 * @brief Convert 'char' to 'unsigned char' without casting.
 *
 * @param c
 * @return unsigned char
 */
static unsigned char to_unsigned_char (char c) {
  return c;
}

template <typename Str>
/**
 * @brief
 *
 * @tparam Str - can be used with String = const std::string& or std::string_view (requires at least C++17)
 * @param s
 * @return std::string
 *
 * @note This is a static method (no header signature declaration).
 */
static std::string _encode(Str s, bool hex = false)
{
  return base32::encode(reinterpret_cast<const base32::BYTE*>(s.data()), s.length(), hex);
}

// std::string encode(const base32::BYTE* buf, unsigned int bufLen) {

//   static const char* b32str = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";

//   std::string out;

//   while (inlen && outlen)
//     {
//       *out++ = b32str[(to_uchar (in[0]) >> 3) & 0x1f];
//       if (!--outlen)
//         break;
//       *out++ = b32str[((to_uchar (in[0]) << 2) + (--inlen ? to_uchar (in[1]) >> 6 : 0)) & 0x1f];
//       if (!--outlen)
//         break;
//       *out++ =
//         (inlen ? b32str[(to_uchar (in[1]) >> 1) & 0x1f] : '=');
//       if (!--outlen)
//         break;
//       *out++ = (inlen ? b32str[((to_uchar (in[1]) << 4) + (--inlen ? to_uchar (in[2]) >> 4 : 0)) & 0x1f] : '=');
//       if (!--outlen)
//         break;
//       *out++ = (inlen ? b32str[((to_uchar (in[2]) << 1) + (--inlen ? to_uchar (in[3]) >> 7 : 0)) & 0x1f] : '=');
//       if (!--outlen)
//         break;
//       *out++ = (inlen ? b32str[(to_uchar (in[3]) >> 2) & 0x1f] : '=');
//       if (!--outlen)
//         break;
//       *out++ = (inlen ? b32str[((to_uchar (in[3]) << 3) + (--inlen ? to_uchar (in[4]) >> 5 : 0)) & 0x1f] : '=');
//       if (!--outlen)
//         break;
//       *out++ = inlen ? b32str[to_uchar (in[4]) & 0x1f] : '=';
//       if (!--outlen)
//         break;
//       if (inlen)
//         inlen--;
//       if (inlen)
//         in += 5;
//     }

//   if (outlen)
//     *out = '\0';
// }

std::string encode(const base32::BYTE* buf, unsigned int bufLen, bool hex) {

  std::string out;
  int i = 0;
  int j = 0;
  base32::BYTE stream[5];
  base32::BYTE index[8];

  const char* base32_alphabet_ = base32::alphabet[hex];

  out.reserve(bufLen);

  // While we still have data left in the input buffer...
  while (bufLen--) {

    // ...Fill the array with the input buffer's values (incrementally).
    stream[i++] = *(buf++);

    // If we have exactly 40 bits input... ('fast encoder')
    if (i == 5) {
      index[0] = base32_alphabet_[( to_unsigned_char(stream[0]) >> 3)                                        & 0x1f];
      index[1] = base32_alphabet_[((to_unsigned_char(stream[0]) << 2) + ( to_unsigned_char(stream[1]) >> 6)) & 0x1f];
      index[2] = base32_alphabet_[( to_unsigned_char(stream[1]) >> 1)                                        & 0x1f];
      index[3] = base32_alphabet_[((to_unsigned_char(stream[1]) << 4) + ( to_unsigned_char(stream[2]) >> 4)) & 0x1f];
      index[4] = base32_alphabet_[((to_unsigned_char(stream[2]) << 1) + ( to_unsigned_char(stream[3]) >> 7)) & 0x1f];
      index[5] = base32_alphabet_[( to_unsigned_char(stream[3]) >> 2)                                        & 0x1f];
      index[6] = base32_alphabet_[((to_unsigned_char(stream[3]) << 3) + ( to_unsigned_char(stream[4]) >> 5)) & 0x1f];
      index[7] = base32_alphabet_[  to_unsigned_char(stream[4])                                              & 0x1f];

      // ...write them to the output buffer...
      for(i = 0; (i < 8) ; i++)
        out += index[i];
      i = 0; // ...and set the iterator index to 0.
    }
  }

  // If we have input less than 40 bits, the iterator index will not be 0 yet... so...
  if (i)
  {
    // Take the remaining 5 values of the index as j...
    for(j = i; j < 5; j++)
      stream[j] = '\0';

    // index[0] =         base32_alphabet_[( to_unsigned_char(stream[0]) >> 3)                                                   & 0x1f];
    // index[1] =         base32_alphabet_[((to_unsigned_char(stream[0]) << 2) + (  --j ? to_unsigned_char(stream[1]) >> 6 : 0)) & 0x1f];
    // index[2] = ( --j ? base32_alphabet_[( to_unsigned_char(stream[1]) >> 1)                                                   & 0x1f] : '=');
    // index[3] = ( --j ? base32_alphabet_[((to_unsigned_char(stream[1]) << 4) + (  --j ? to_unsigned_char(stream[2]) >> 4 : 0)) & 0x1f] : '=');
    // index[4] = ( --j ? base32_alphabet_[((to_unsigned_char(stream[2]) << 1) + (  --j ? to_unsigned_char(stream[3]) >> 7 : 0)) & 0x1f] : '=');
    // index[5] = ( --j ? base32_alphabet_[( to_unsigned_char(stream[3]) >> 2)                                                   & 0x1f] : '=');
    // index[6] = ( --j ? base32_alphabet_[((to_unsigned_char(stream[3]) << 3) + (  --j ? to_unsigned_char(stream[4]) >> 5 : 0)) & 0x1f] : '=');
    // index[7] = ( --j ? base32_alphabet_[  to_unsigned_char(stream[4])                                                         & 0x1f] : '=');

    index[0] = base32_alphabet_[( to_unsigned_char(stream[0]) >> 3)                                        & 0x1f];
    index[1] = base32_alphabet_[((to_unsigned_char(stream[0]) << 2) + ( to_unsigned_char(stream[1]) >> 6)) & 0x1f];
    index[2] = base32_alphabet_[( to_unsigned_char(stream[1]) >> 1)                                        & 0x1f];
    index[3] = base32_alphabet_[((to_unsigned_char(stream[1]) << 4) + ( to_unsigned_char(stream[2]) >> 4)) & 0x1f];
    index[4] = base32_alphabet_[((to_unsigned_char(stream[2]) << 1) + ( to_unsigned_char(stream[3]) >> 7)) & 0x1f];
    index[5] = base32_alphabet_[( to_unsigned_char(stream[3]) >> 2)                                        & 0x1f];
    index[6] = base32_alphabet_[((to_unsigned_char(stream[3]) << 3) + ( to_unsigned_char(stream[4]) >> 5)) & 0x1f];
    index[7] = base32_alphabet_[  to_unsigned_char(stream[4])                                              & 0x1f];

    // for (j = 0; (j < i + 1); j++)
    //   out += index[j];

    for (j = 0; (j < i); j++) {
      out += index[j];
      i++;
    }

    // Fill the remaining bits with padding
    while((i++ < 5))
      out += '=';
  }

  return out;
}

template <typename Str>
/**
 * @brief
 *
 * @param encoded_string
 * @return std::vector<base32::BYTE>
 *
 * @note This is a static method (no header signature declaration).
 */
static std::vector<base32::BYTE> _decode(const Str& encoded_string) {

  // The below is under construction!

  std::vector<base32::BYTE> out;
  int i = 0;
  int j = 0;
  int in_ = 0;
  int in_len = encoded_string.size();
  base32::BYTE index[4];
  base32::BYTE stream[3];

  out.reserve(in_len);

  std::string base32_alphabet(base32::alphabet[0]);

  bool is_base32_ = false;
  if (0) {
    is_base32_ = is_base32_hex(encoded_string[in_]);
  } else {
    is_base32_ = is_base32    (encoded_string[in_]);
  }

  while (in_len-- && (encoded_string[in_] != '=') && is_base32_) {

    index[i++] = encoded_string[in_];
    in_++;

    if (i == 4) {
      for (i = 0; i < 4; i++)
        index[i] = base32_alphabet.find(index[i]);

      stream[0] = ( index[0]        << 2) + ((index[1] & 0x30) >> 4);
      stream[1] = ((index[1] & 0xf) << 4) + ((index[2] & 0x3c) >> 2);
      stream[2] = ((index[2] & 0x3) << 6) +   index[3];

      for (i = 0; (i < 3); i++)
          out.push_back(stream[i]);
      i = 0;
    }
  }

  if (i) {
    for (j = i; j < 4; j++)
      index[j] = 0;

    for (j = 0; j < 4; j++)
      index[j] = base32_alphabet.find(index[j]);

    stream[0] = ( index[0]        << 2) + ((index[1] & 0x30) >> 4);
    stream[1] = ((index[1] & 0xf) << 4) + ((index[2] & 0x3c) >> 2);
    stream[2] = ((index[2] & 0x3) << 6) +   index[3];

    for (j = 0; (j < i - 1); j++) out.push_back(stream[j]);
  }

  return out;
}

std::string encode(const std::string& s, bool hex) {
  return base32::_encode<std::string>(s, hex);
}

std::vector<base32::BYTE> decode(const std::string& s) {
  return base32::_decode<std::string>(s);
}

std::vector<base32::BYTE> decode(const std::vector<base32::BYTE>& s) {
  return base32::_decode<std::vector<base32::BYTE>>(s);
}

// Interfaces with std::string_view rather than const std::string&
// Requires C++17
#if HAS_STRING_VIEW_H
std::string encode(const std::string_view& s, bool hex) {
  return base32::_encode<std::string_view>(s, hex);
}
std::vector<base32::BYTE> decode(const std::string_view& s) {
  return base32::_decode<std::string_view>(s);
}
#endif

template std::string _encode(const std::string& s, bool hex);
template std::vector<base32::BYTE> _decode(const std::string& encoded_string);
#if HAS_STRING_VIEW_H
template std::string _encode(const std::string_view& s, bool hex);
template std::vector<base32::BYTE> _decode(const std::string_view& encoded_string);
#endif

} // namespace base32
