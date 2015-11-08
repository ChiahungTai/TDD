/*
 * SoundexTest.cpp
 *
 *  Created on: 2015年11月6日
 *      Author: ctai
 */

#include "gmock/gmock.h"
#include "Soundex.h"

using std::string;
using namespace testing;

class SoundexEncoding : public Test {
public:
  Soundex soundex;
};

using testing::Eq;
#if 1
TEST(SoundexEncodingOld, RetainsSoleLetterOfOneLetterWord) {
	Soundex soundex;

	auto encoded = soundex.encode("A");
	ASSERT_THAT(encoded, Eq("A000"));
}

TEST(SoundexEncodingOld, PadsWithZerosToEnsureThreeDigits) {
  Soundex soundex;

  auto encoded = soundex.encode("1");
  ASSERT_THAT(encoded, Eq("1000"));
}

TEST_F(SoundexEncoding, RetainsSoleLetterOfOneLetterWord) {
  ASSERT_THAT(soundex.encode("A"), Eq("A000"));
}

TEST_F(SoundexEncoding, PadsWithZerosToEnsureThreeDigits) {
  ASSERT_THAT(soundex.encode("1"), Eq("1000"));
}

TEST_F(SoundexEncoding, ReplacesConsonantsWithAppropriateDigits) {
  EXPECT_THAT(soundex.encode("Ab"), Eq("A100"));
  EXPECT_THAT(soundex.encode("Ac"), Eq("A200"));
  EXPECT_THAT(soundex.encode("Ad"), Eq("A300"));
  ASSERT_THAT(soundex.encode("Ax"), Eq("A200"));
}

TEST_F(SoundexEncoding, IgnoreNonAlphabetics) {
  ASSERT_THAT(soundex.encode("A#"), Eq("A000"));
}

TEST_F(SoundexEncoding, ReplacesMultipleConsonantsWithDigits) {
  ASSERT_THAT(soundex.encode("Acdl"), Eq("A234"));
}

TEST_F(SoundexEncoding, LimitsLengthToFourCharacters) {
  ASSERT_THAT(soundex.encode("Dcdlb").length(), Eq(4u));
}

TEST_F(SoundexEncoding, IgnoreVowelLikeLetters) {
  ASSERT_THAT(soundex.encode("Baeiouhycdl"), Eq("B234"));
  ASSERT_THAT(soundex.encode("BaAeEiIoOuUhHyYcdl"), Eq("B234"));
}

TEST_F(SoundexEncoding, CombinesDuplicateEncodings) {
  ASSERT_THAT(soundex.encodedDigit('b'), Eq(soundex.encodedDigit('f')));
  ASSERT_THAT(soundex.encodedDigit('c'), Eq(soundex.encodedDigit('g')));
  ASSERT_THAT(soundex.encodedDigit('d'), Eq(soundex.encodedDigit('t')));
  ASSERT_THAT(soundex.encode("Abfcgdt"), Eq("A123"));
}

TEST_F(SoundexEncoding, UpperCasesFirstLetter) {
  ASSERT_THAT(soundex.encode("abcd"), StartsWith("A"));
}

TEST_F(SoundexEncoding, IgnoreCaseWhenEncodingConsonants) {
  ASSERT_THAT(soundex.encode("BCDL"), Eq(soundex.encode("Bcdl")));
}

TEST_F(SoundexEncoding, CombinesDuplicateCodesWhen2ndLetterDuplicate1st) {
  ASSERT_THAT(soundex.encode("Bbcd"), Eq("B230"));
}
#endif

TEST_F(SoundexEncoding, DoesNotCombineDuplicateEncodingsSeparatedByVowels) {
  ASSERT_THAT(soundex.encode("JBob"), Eq("J110"));
}
