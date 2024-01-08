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
   * @param string
   */
  encode(string: string): string;
  /**
   * Takes a string input, and returns a base32-encoded copy. Also accepts a
   * boolean, to specify if the input contains URL-like characters.
   * @param string
   * @param urlMode
   */
  encode(string: string, urlMode: boolean): string;
  /**
   * Takes a base32-encoded string input, and returns a decoded copy.
   * @param string
   */
  decode(string: string): string;
  /**
   * Takes a base32-encoded string input, and returns a decoded copy. Also
   * accepts a boolean, to specify if the input contains URL-like characters.
   * @param string
   * @param urlMode
   */
  decode(string: string, urlMode: boolean): string;
}
const base32: base32 = require('../build/lib/base32.node');
export = base32;
