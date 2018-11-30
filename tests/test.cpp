#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Base64EncoderDecoder.h"


TEST(BlockEncoderTest, NotFullBlock) {
    ASSERT_EQ(encodeBuffer(std::array<char, 3>({'w', 'Q', 0})), "d1E=");
    ASSERT_EQ(encodeBuffer(std::array<char, 3>({'!', '$', 0})), "ISQ=");
    ASSERT_EQ(encodeBuffer(std::array<char, 3>({'{', 0, 0})), "ew==");
}

TEST(BlockEncoderTest, FullBlock) {
    ASSERT_EQ(encodeBuffer(std::array<char, 3>({'S', 'a', 'd'})), "U2Fk");
    ASSERT_EQ(encodeBuffer(std::array<char, 3>({'`', '\'', '\\'})), "YCdc");
    ASSERT_EQ(encodeBuffer(std::array<char, 3>({'-', '-', '-'})), "LS0t");
    ASSERT_EQ(encodeBuffer(std::array<char, 3>({'\n', '\n', '\n'})), "CgoK");
}

TEST(EncoderTest, EmptyString) {
    ASSERT_EQ(base64Encode(""), "");
}

TEST(EncoderTest, OneLineTest) {
    ASSERT_EQ(base64Encode("sadness"), "c2FkbmVzcw==");
    ASSERT_EQ(base64Encode("Hello, my dear friend!"), "SGVsbG8sIG15IGRlYXIgZnJpZW5kIQ==");
    ASSERT_EQ(base64Encode("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+="),
              "QUJDREVGR0hJSktMTU5PUFFSU1RVVldYWVphYmNkZWZnaGlqa2xtbm9wcXJzdHV2d3h5ejAxMjM0NTY3ODkrPQ==");
    ASSERT_EQ(base64Encode(")wevw*we))qwdqw1!!>?<{-%$#@"), "KXdldncqd2UpKXF3ZHF3MSEhPj88ey0lJCNA");
    ASSERT_EQ(base64Encode(
            "Man is distinguished, not only by his reason, but by this singular passion from other animals, which is a lust of the mind, that by a perseverance of delight in the continued and indefatigable generation of knowledge, exceeds the short vehemence of any carnal pleasure."),
              "TWFuIGlzIGRpc3Rpbmd1aXNoZWQsIG5vdCBvbmx5IGJ5IGhpcyByZWFzb24sIGJ1dCBieSB0aGlzIHNpbmd1bGFyIHBhc3Npb24gZnJvbSBvdGhlciBhbmltYWxzLCB3aGljaCBpcyBhIGx1c3Qgb2YgdGhlIG1pbmQsIHRoYXQgYnkgYSBwZXJzZXZlcmFuY2Ugb2YgZGVsaWdodCBpbiB0aGUgY29udGludWVkIGFuZCBpbmRlZmF0aWdhYmxlIGdlbmVyYXRpb24gb2Yga25vd2xlZGdlLCBleGNlZWRzIHRoZSBzaG9ydCB2ZWhlbWVuY2Ugb2YgYW55IGNhcm5hbCBwbGVhc3VyZS4=");
}

TEST(EncoderTest, MultiLineTest) {
    std::string testText1 = R"(part 1
part 2
part 3
part 4)";
    std::string testText2 = R"(



)";
    ASSERT_EQ(base64Encode(testText1), "cGFydCAxCnBhcnQgMgpwYXJ0IDMKcGFydCA0");
    ASSERT_EQ(base64Encode(testText2), "CgoKCg==");
}

TEST(Base64Check, Base64Check) {
    ASSERT_FALSE(isBase64String(")ioiwoeviwevjnO&&&&"));
    ASSERT_FALSE(isBase64String("ABCDE-"));
    ASSERT_FALSE(isBase64String("yhw\n"));
    ASSERT_TRUE(isBase64String("9=+A"));
    ASSERT_TRUE(isBase64String("a==Wk=W+ar=D"));
    ASSERT_TRUE(isBase64String("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+="));
}

TEST(BlockDecoderTest, EqualitySignTermination) {
    ASSERT_EQ(decodeBuffer(std::array<char, 4>({'a', '2', 'E', '='})), "ka");
    ASSERT_EQ(decodeBuffer(std::array<char, 4>({'I', 'U', 'A', '='})), "!@");
    ASSERT_EQ(decodeBuffer(std::array<char, 4>({'C', 'm', 'A', '='})), "\n`");
    ASSERT_EQ(decodeBuffer(std::array<char, 4>({'e', 'g', '=', '='})), "z");
    ASSERT_EQ(decodeBuffer(std::array<char, 4>({'I', 'w', '=', '='})), "#");
}

TEST(BlockDecoderTest, NonEqualitySignTermination) {
    ASSERT_EQ(decodeBuffer(std::array<char, 4>({'U', '0', 'F', 'E'})), "SAD");
    ASSERT_EQ(decodeBuffer(std::array<char, 4>({'C', 'g', 'o', '5'})), "\n\n9");
    ASSERT_EQ(decodeBuffer(std::array<char, 4>({'X', 'C', 'c', 'i'})), "\\\'\"");
}

TEST(DecoderTest, EmptyStringTest) {
    ASSERT_EQ(base64Decode(""), "");
}

TEST(DecoderTest, GoodStringTest) {
    ASSERT_EQ(base64Decode("VGhpcyBpcyBhIHNhbXBsZSB0ZXN0Lg=="), "This is a sample test.");
    ASSERT_EQ(base64Decode("MzI6"), "32:");
    ASSERT_EQ(base64Decode(
            "T3VyIGxhc3Qga2luZywKICAgIFdob3NlIGltYWdlIGV2ZW4gYnV0IG5vdyBhcHBlYXInZCB0byB1cywKICAgIFdhcywgYXMgeW91IGtub3csIGJ5IEZvcnRpbmJyYXMgb2YgTm9yd2F5LAogICAgVGhlcmV0byBwcmljaydkIG9uIGJ5IGEgbW9zdCBlbXVsYXRlIHByaWRlLAogICAgRGFyJ2QgdG8gdGhlIGNvbWJhdDsgaW4gd2hpY2ggb3VyIHZhbGlhbnQgSGFtbGV0CiAgICAoRm9yIHNvIHRoaXMgc2lkZSBvZiBvdXIga25vd24gd29ybGQgZXN0ZWVtJ2QgaGltKQogICAgRGlkIHNsYXkgdGhpcyBGb3J0aW5icmFzOyB3aG8sIGJ5IGEgc2VhbCdkIGNvbXBhY3QsCiAgICBXZWxsIHJhdGlmaWVkIGJ5IGxhdyBhbmQgaGVyYWxkcnksCiAgICBEaWQgZm9yZmVpdCwgd2l0aCBoaXMgbGlmZSwgYWxsIHRob3NlIGhpcyBsYW5kcwogICAgV2hpY2ggaGUgc3Rvb2Qgc2VpeidkIG9mLCB0byB0aGUgY29ucXVlcm9yOwogICAgQWdhaW5zdCB0aGUgd2hpY2ggYSBtb2lldHkgY29tcGV0ZW50CiAgICBXYXMgZ2FnZWQgYnkgb3VyIGtpbmc7IHdoaWNoIGhhZCByZXR1cm4nZAogICAgVG8gdGhlIGluaGVyaXRhbmNlIG9mIEZvcnRpbmJyYXMsCiAgICBIYWQgaGUgYmVlbiB2YW5xdWlzaGVyLCBhcywgYnkgdGhlIHNhbWUgY29tYXJ0CiAgICBBbmQgY2FycmlhZ2Ugb2YgdGhlIGFydGljbGUgZGVzaWduJ2QsCiAgICBIaXMgZmVsbCB0byBIYW1sZXQu"), R"(Our last king,
    Whose image even but now appear'd to us,
    Was, as you know, by Fortinbras of Norway,
    Thereto prick'd on by a most emulate pride,
    Dar'd to the combat; in which our valiant Hamlet
    (For so this side of our known world esteem'd him)
    Did slay this Fortinbras; who, by a seal'd compact,
    Well ratified by law and heraldry,
    Did forfeit, with his life, all those his lands
    Which he stood seiz'd of, to the conqueror;
    Against the which a moiety competent
    Was gaged by our king; which had return'd
    To the inheritance of Fortinbras,
    Had he been vanquisher, as, by the same comart
    And carriage of the article design'd,
    His fell to Hamlet.)");
}

TEST(DecoderTest, BadStringTest) {
    ASSERT_EQ(base64Decode("ABC"), "");
    ASSERT_EQ(base64Decode("cXFuh"), "qqn");
    ASSERT_EQ(base64Decode("VGhpcyBpcyBhIHRlc3QgZm9yIGEgc3RyaW5nIHdpdGggd3JvbmcgbnVtYmVyIG9mIGNoYXJzLg==="),
              "This is a test for a string with wrong number of chars.");
}

TEST(DecoderTest, InvalidStringTest) {
    ASSERT_THROW(base64Decode("8)p"), std::invalid_argument);
    ASSERT_THROW(base64Decode("Invalid string!"), std::invalid_argument);
}