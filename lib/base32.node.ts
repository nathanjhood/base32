/**
 * The 'base32' C++ addon interface.
 */
interface base32 {
  /**
   * Returns a string, confirming the module is online.
   * @returns string
   */
  hello(): string;
  /**
   * Returns a string, confirming the module version number.
   * @returns string
   */
  version(): string;
  /**
   * Takes a string input, and returns a base32-encoded copy.
   * @param input
   */
  encode(input: string): string;
  /**
   * Takes a string input, and returns a base32-encoded copy. Also accepts a
   * boolean, to specify if the input contains URL-like characters.
   * @param input
   * @param urlMode
   */
  encode(input: string, hexMode: boolean): string;
  /**
   * Takes a base32-encoded string input, and returns a decoded copy.
   * @param input
   */
  decode(input: string): string;
  /**
   * Takes a base32-encoded string input, and returns a decoded copy. Also
   * accepts a boolean, to specify if the input contains URL-like characters.
   * @param input
   * @param hexMode
   */
  decode(input: string, hexMode: boolean): string;
}
const base32: base32 = require('../build/lib/base32.node');
export = base32;
