const base32 = require("../lib/base32.node");

console.log(base32.hello());
console.log(base32.version());

console.log("\nTest vector:\n");

// test vector
console.log("");
console.log("f");
console.log("fo");
console.log("foo");
console.log("foob");
console.log("fooba");
console.log("foobar");
console.log("");

console.log("\nEncoder test:\n");

// encoder test
console.log(base32.encode(""));
console.log(base32.encode("f"));
console.log(base32.encode("fo"));
console.log(base32.encode("foo"));
console.log(base32.encode("foob"));
console.log(base32.encode("fooba"));
console.log(base32.encode("foobar"));
console.log(base32.encode(""));

console.log(base32.encode("", false));
console.log(base32.encode("f", false));
console.log(base32.encode("fo", false));
console.log(base32.encode("foo", false));
console.log(base32.encode("foob", false));
console.log(base32.encode("fooba", false));
console.log(base32.encode("foobar", false));
console.log(base32.encode("", false));
console.log(base32.encode("", true));
console.log(base32.encode("f", true));
console.log(base32.encode("fo", true));
console.log(base32.encode("foo", true));
console.log(base32.encode("foob", true));
console.log(base32.encode("fooba", true));
console.log(base32.encode("foobar", true));
console.log(base32.encode("", true));

// console.log("\nDecoder test:\n");

// // decoder test
// // console.log(base32.decode(""));  // Napi::String doesn't like these, much!
// console.log(base32.decode("Zg==")); // Napi::String doesn't like these, also!
// console.log(base32.decode("Zm8="));
// console.log(base32.decode("Zm9v"));
// console.log(base32.decode("Zm9vYg=="));
// console.log(base32.decode("Zm9vYmE="));
// console.log(base32.decode("Zm9vYmFy"));
// // console.log(base32.decode(""));

// // encoder mode test
// console.log("\nEncoder non-URL alphabet test:\n");
// console.log("= %s", base32.encode("=", false));
// console.log("/ %s", base32.encode("/", false));
// console.log("- %s", base32.encode("-", false));
// console.log("_ %s", base32.encode("_", false));

// console.log("\nEncoder URL alphabet test:\n");
// console.log("= %s", base32.encode("=", true));
// console.log("/ %s", base32.encode("/", true));
// console.log("- %s", base32.encode("-", true));
// console.log("_ %s", base32.encode("_", true));

// // decoder mode test
// console.log("\nDecoder non-URL alphabet test:\n");
// console.log("PQ== %s", base32.decode("PQ==", false));
// console.log("Lw== %s", base32.decode("Lw==", false));
// console.log("LQ== %s", base32.decode("LQ==", false));
// console.log("XyA= %s", base32.decode("XyA=", false));

// console.log("\nDecoder URL alphabet test:\n");
// console.log("PQ== %s", base32.decode("PQ==", true));
// console.log("Lw== %s", base32.decode("Lw==", true));
// console.log("LQ== %s", base32.decode("LQ==", true));
// console.log("Xw== %s", base32.decode("Xw==", true));

// // encode/decode test
// console.log("\nStress test: encode/decode\n");
// console.log(base32.decode(base32.encode("foobar")));
