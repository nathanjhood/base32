declare interface base32 {
  hello(): string;
  version(): string;
  encode(input: string): string;
  encode(input: string, hexMode: boolean): string;
  decode(input: string): string;
  decode(input: string, hexMode: boolean): string;
}
declare const base32: base32;
export = base32;
