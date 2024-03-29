/**
 * @file addon.cpp
 * @author Nathan J. Hood (nathanjood@googlemail.com)
 * @brief Exports 'base32' as a binary NodeJS addon.
 * @version 0.1
 * @date 2024-01-03
 *
 * @copyright Copyright (c) 2024 Nathan J. Hood (nathanjood@googlemail.com)
 *
 */

// Required header and C++ flag
#if __has_include(<napi.h>) && BUILDING_NODE_EXTENSION

#include "base32/version.h"
#include "base32/base32.hpp"

#include <napi.h>

namespace base32 {

namespace addon {

Napi::Value Hello(const Napi::CallbackInfo& info)
{
  return Napi::String::New(info.Env(), "base32 is online!");
}

Napi::Value Version(const Napi::CallbackInfo& info)
{
  return Napi::String::New(info.Env(), base32_VERSION);
}

/**
 * @brief
 *
 * @param args
 * @return Napi::Value
 */
Napi::Value Encode(const Napi::CallbackInfo& args)
{
  Napi::Env env = args.Env();

  // Arguments required: at least one, and no more than two
  if (args.Length() < 1)
  {
    Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  // Param 1 must be the string to encode
  if (!args[0].IsString())
  {
    Napi::TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  // Param 2 (if any) must be boolean. If unset, non-URL alphabet is used.
  if (!args[1].IsBoolean() && args.Length() > 1)
  {
    Napi::TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  // Construct a string to hold the encoder's output
#if HAS_STRING_VIEW_H
  std::string_view encodedArg;
#else
  std::string      encodedArg;
#endif

  // Set whether to use the URL alphabet or not...
  bool hexMode = args[1].ToBoolean().Value();

  try {

    // Try to encode the string
    encodedArg = base32::encode(args[0].ToString(), hexMode );

  } catch (const std::exception &x) {

    // If there was an error...
    std::string message(x.what());
    message += '\n';
    message += "base32: could not encode the following input argument:\n";
    message += args[0].As<Napi::String>();

    // Throw a javascript-side exception
    Napi::TypeError::New(env, message).ThrowAsJavaScriptException();

#if !HAS_STRING_VIEW_H
    // Clear the old string
    encodedArg.clear();
#endif
    message.clear();

    // Return null
    return env.Null();
  }

  try {

    // Construct a Napi string containing the encoder output
    Napi::String out = Napi::String::New(env, encodedArg.data());
#if !HAS_STRING_VIEW_H
    // Clear the old string
    encodedArg.clear();
#endif

    // Return the Napi string
    return out;

  } catch (const std::exception &x) {

    // If there was an error...
    std::string message(x.what());
    message += '\n';
    message += "base32: could not encode the following input argument:\n";
    message += args[0].As<Napi::String>();

    // Throw a javascript-side exception
    Napi::TypeError::New(env, message).ThrowAsJavaScriptException();

#if !HAS_STRING_VIEW_H
    // Clear the old string
    encodedArg.clear();
#endif
    message.clear();

    // Return null
    return env.Null();
  }
}

/**
 * @brief
 *
 * @param args
 * @return Napi::Value
 */
Napi::Value Decode(const Napi::CallbackInfo& args)
{
  Napi::Env env = args.Env();

  // Arguments required: at least one, and no more than two
  if (args.Length() < 1)
  {
    Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  // Param 1 must be the string to encode
  if (!args[0].IsString())
  {
    Napi::TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  // Param 2 (if any) must be boolean. If unset, non-URL alphabet is used.
  if (!args[1].IsBoolean() && args.Length() > 1)
  {
    Napi::TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  // Construct a string to hold the arg
  std::string      str(args[0].ToString().Utf8Value());
  bool hexMode = args[1].ToBoolean().Value();

  // Construct a fancy char array to hold the decoder's output
  std::vector<base32::BYTE> decodedArg;

  try {

    decodedArg = base32::decode(str /*, hexMode */);

  } catch (const std::exception &x) {

    // If there was an error...
    std::string message(x.what());
    message += '\n';
    message += "base32: could not decode the following input argument:\n";
    message += args[0].As<Napi::String>();

    // Throw a javascript-side exception
    Napi::TypeError::New(env, message).ThrowAsJavaScriptException();

    // Clear the old array
    decodedArg.clear();
    message.clear();

    // Return null
    return env.Null();
  }

  try {

    // Try to construct a Napi string containing the decoder output
    Napi::String out = Napi::String::New(env, std::string(decodedArg.begin(), decodedArg.end()));

    // Clear the old array
    decodedArg.clear();

    // Return the string
    return out;

  } catch (const std::exception &x) {

    // If there was an error...
    std::string message(x.what());
    message += '\n';
    message += "base32: could not construct the decoded argument into a string:\n";
    message += args[0].As<Napi::String>();

    // Throw a javascript-side exception
    Napi::TypeError::New(env, message).ThrowAsJavaScriptException();

    // Clear the old array
    decodedArg.clear();
    message.clear();

    // Return null
    return env.Null();
  }
}

// Construct an 'initializer' object that carries our functions
Napi::Object Init(Napi::Env env, Napi::Object exports)
{

  // Export a chosen C++ function under a given Javascript key
  exports.Set(
    Napi::String::New(env, "hello"), // Name of function on Javascript side...
    Napi::Function::New(env, Hello)  // Name of function on C++ side...
  );

  exports.Set(
    Napi::String::New(env, "version"),
    Napi::Function::New(env, Version)
  );

  exports.Set(
    Napi::String::New(env, "encode"),
    Napi::Function::New(env, Encode)
  );

  exports.Set(
    Napi::String::New(env, "decode"),
    Napi::Function::New(env, Decode)
  );

  // The above will expose the C++ function 'Hello' as a javascript function named 'hello', etc...

  return exports;
}

// Register a new addon with the intializer function defined above
NODE_API_MODULE(base32, Init) // (name to use, initializer to use)

// The above attaches the functions exported in 'Init()' to the name used in the fist argument.
// The C++ functions are then obtainable on the Javascript side under e.g. 'base32.hello()'

} // namespace addon

// Here, we can extend the base32 source file with Napi overloads.

// /**
//  * @brief
//  *
//  * @param s
//  * @return std::string
//  */
// std::string encode(const Napi::String& s) {
//   return base32::_encode<Napi::String>(s.As<std::string>());
// }
// template std::string base32::encode(const Napi::String& s);

// /**
//  * @brief
//  *
//  * @param s
//  * @return std::vector<base32::BYTE>
//  */
// std::vector<base32::BYTE> decode(const Napi::String& s) {
//   return base32::_decode<Napi::String>(s.As<std::string>());
// }
// template std::vector<base32::BYTE> base32::decode(const Napi::String& s);

// Napi::String byte_vector_to_napi_string(const std::vector<base32::BYTE>& b) {

//   auto in = (const char *)b.data();
//   Napi::String out;

//   return out;
// }

// static std::vector<base32::BYTE> napi_string_to_byte_vector(const Napi::String& s) {
//   std::vector<base32::BYTE> out;
//   return out;
// }

} // namespace base32

#else
 #warning "Warning: Cannot find '<napi.h>'"
#endif // __has_include(<napi.h>) && BUILDING_NODE_EXTENSION
