declare interface base32 {
  hello(): string;
  version(): string;
  encode(string: string): string;
  encode(string: string, urlMode: boolean): string;
  decode(string: string): string;
  decode(string: string, urlMode: boolean): string;
}
declare const base32: base32;
export = base32;
