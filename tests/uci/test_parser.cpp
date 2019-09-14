#include "string"
#include "vector"

#include "gtest/gtest.h"
#include "chesspp/parser.hpp"

TEST(Parser, tokenise_test_generic) {
    Parser parser;
    std::vector<std::string> tokens =  parser.tokenise("This is a test");
    EXPECT_EQ("This", tokens[0]);
    EXPECT_EQ("is", tokens[1]);
    EXPECT_EQ("a", tokens[2]);
    EXPECT_EQ("test", tokens[3]);
}

TEST(Parser, tokenise_test_tabs) {
    Parser parser;
    std::vector<std::string> tokens =  parser.tokenise("This\tis a test");
    EXPECT_EQ("This", tokens[0]);
    EXPECT_EQ("is", tokens[1]);
    EXPECT_EQ("a", tokens[2]);
    EXPECT_EQ("test", tokens[3]);
}

TEST(Parser, tokenise_test_multiple_spaces) {
    Parser parser;
    std::vector<std::string> tokens =  parser.tokenise("This   is  a test");
    EXPECT_EQ("This", tokens[0]);
    EXPECT_EQ("is", tokens[1]);
    EXPECT_EQ("a", tokens[2]);
    EXPECT_EQ("test", tokens[3]);
}

TEST(Parser, tokenise_test_mixed_white_space) {
    Parser parser;
    std::vector<std::string> tokens =  parser.tokenise("This \t \t\t is \ta test");
    EXPECT_EQ("This", tokens[0]);
    EXPECT_EQ("is", tokens[1]);
    EXPECT_EQ("a", tokens[2]);
    EXPECT_EQ("test", tokens[3]);
}

TEST(Parser, tokenise_test_trailing_white_space) {
    Parser parser;
    std::vector<std::string> tokens =  parser.tokenise("This is a test \t\t ");
    EXPECT_EQ("This", tokens[0]);
    EXPECT_EQ("is", tokens[1]);
    EXPECT_EQ("a", tokens[2]);
    EXPECT_EQ("test", tokens[3]);
}

TEST(Parser, tokenise_test_leading_white_space) {
    Parser parser;
    std::vector<std::string> tokens =  parser.tokenise(" \t \t  This is a test");
    EXPECT_EQ("This", tokens[0]);
    EXPECT_EQ("is", tokens[1]);
    EXPECT_EQ("a", tokens[2]);
    EXPECT_EQ("test", tokens[3]);
}

TEST(Parser, tokenise_test_trailing_and_leading_white_space) {
    Parser parser;
    std::vector<std::string> tokens =  parser.tokenise(" \t This is a test \t\t");
    EXPECT_EQ("This", tokens[0]);
    EXPECT_EQ("is", tokens[1]);
    EXPECT_EQ("a", tokens[2]);
    EXPECT_EQ("test", tokens[3]);
}