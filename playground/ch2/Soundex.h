/*
 * Soundex.h
 *
 *  Created on: 2015年11月6日
 *      Author: ctai
 */

#ifndef PLAYGROUND_CH2_SOUNDEX_H_
#define PLAYGROUND_CH2_SOUNDEX_H_

#include <unordered_map>

using std::string;

class Soundex {
public:
  static const size_t MaxCodeLength {4};
  static const string NotADigit;

  string encode(const string& word) const
  {
    return zeroPad(upperFront(head(word)) + tail(encodedDigits(word)));
  }

  static string encodedDigit(char letter)
  {
    const std::unordered_map<char, string> encodings
    {
      {'b', "1"}, {'f', "1"}, {'p', "1"}, {'v', "1"},
      {'c', "2"}, {'g', "2"}, {'j', "2"}, {'k', "2"}, {'q', "2"}, {'s', "2"}, {'x', "2"}, {'z', "2"},
      {'d', "3"}, {'t', "3"},
      {'l', "4"},
      {'m', "5"}, {'m', "5"},
      {'r', "6"},
    };
    auto it = encodings.find(lower(letter));
    return it == encodings.end() ? NotADigit : it->second;
  }

private:
  static string upperFront(const string& word) {
    return string(1, std::toupper(static_cast<unsigned char>(word.front())));
  }

  static char lower(const char& c) {
    return std::tolower(static_cast<unsigned char>(c));
  }

  static string head(const string& word)
  {
    return word.substr(0, 1);
  }

  static string tail(const string& word)
  {
    return word.substr(1);
  }

  static string encodedDigits(const string& word)
  {
    string encoding;
    encodeHead(encoding, word);
    encodeTail(encoding, word);
    return encoding;
  }

  static void encodeHead(string& encoding, const string& word) {
    encoding += encodedDigit(word.front());
  }

  static void encodeTail(string& encoding, const string& word) {
    for (auto i = 1u; i < word.length(); ++i) {
      if (isCompleted(encoding)) {
        break;
      }
      encodeLetter(encoding, word[i], word[i-1]);
    }
  }

  static void encodeLetter(string& encoding, char letter, char lastLetter) {
    auto digit = encodedDigit(letter);
    if (digit != NotADigit &&
        (digit != lastDigit(encoding) || isVowel(lastLetter))) {
      encoding += digit;
    }
  }

  static bool isVowel(char letter) {
    return string("aeiou").find(letter) != string::npos;
  }

  static string lastDigit(const string& encoding) {
    if (encoding.empty()) {
      return NotADigit;
    }
    return string(1, encoding.back());
  }

  static bool isCompleted(const string& word) {
    return word.length() == MaxCodeLength;
  }

  static string zeroPad(const string& word)
  {
    auto zerosNeeded = MaxCodeLength - word.length();
    return word + string(zerosNeeded, '0');
  }
};

const string Soundex::NotADigit {"*"};

#endif /* PLAYGROUND_CH2_SOUNDEX_H_ */
