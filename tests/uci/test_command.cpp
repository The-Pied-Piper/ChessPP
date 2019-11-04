#include "gtest/gtest.h"
#include "uci/command/command.hpp"


/*******************************************************************************
 *                        Test parse_arguments( ... )
*******************************************************************************/

TEST(Command, parse_arguments_test_no_parameter)
{
    std::vector<chesspp::ArgumentDefinition> accpeted_arguments = {
        chesspp::ArgumentDefinition({"value1", "value2"}, 0, true),
        chesspp::ArgumentDefinition({"value3", "value4", "value5"}, -1),
        chesspp::ArgumentDefinition({"value6"}, 3)};

    chesspp::Command const test_command("test_command", accpeted_arguments);
    std::vector<std::string> args = {"value2"};
    std::vector<chesspp::Argument> arguments = test_command.parse_arguments(args);
    EXPECT_EQ("value2", arguments[0].value);
    EXPECT_TRUE(arguments[0].parameters.empty());
    EXPECT_EQ(1, arguments.size());
}

TEST(Command, parse_arguments_test_any_parameters)
{
    std::vector<chesspp::ArgumentDefinition> accpeted_arguments = {
        chesspp::ArgumentDefinition({"value1", "value2"}, 0),
        chesspp::ArgumentDefinition({"value3", "value4", "value5"}, -1, true),
        chesspp::ArgumentDefinition({"value6"}, 3)};

    chesspp::Command const test_command("test_command", accpeted_arguments);
    std::vector<std::string> args = {"value5", "param0", "param1", "param2", "param3"};
    std::vector<chesspp::Argument> arguments = test_command.parse_arguments(args);
    EXPECT_EQ("value5", arguments[0].value);
    EXPECT_EQ("param0", arguments[0].parameters[0]);
    EXPECT_EQ("param1", arguments[0].parameters[1]);
    EXPECT_EQ("param2", arguments[0].parameters[2]);
    EXPECT_EQ("param3", arguments[0].parameters[3]);
    EXPECT_EQ(4, arguments[0].parameters.size());
    EXPECT_EQ(1, arguments.size());
}

TEST(Command, parse_arguments_test_fixed_parameters)
{
    std::vector<chesspp::ArgumentDefinition> accpeted_arguments = {
        chesspp::ArgumentDefinition({"value1", "value2"}, 0),
        chesspp::ArgumentDefinition({"value3", "value4", "value5"}, -1),
        chesspp::ArgumentDefinition({"value6"}, 3, true)};

    chesspp::Command const test_command("test_command", accpeted_arguments);
    std::vector<std::string> args = {"value6", "param0", "param1", "param2"};
    std::vector<chesspp::Argument> arguments = test_command.parse_arguments(args);
    EXPECT_EQ("value6", arguments[0].value);
    EXPECT_EQ("param0", arguments[0].parameters[0]);
    EXPECT_EQ("param1", arguments[0].parameters[1]);
    EXPECT_EQ("param2", arguments[0].parameters[2]);
    EXPECT_EQ(3, arguments[0].parameters.size());
    EXPECT_EQ(1, arguments.size());
}

TEST(Command, parse_arguments_test_multiple_arguments)
{
    std::vector<chesspp::ArgumentDefinition> accpeted_arguments = {
        chesspp::ArgumentDefinition({"value1", "value2"}, 0),
        chesspp::ArgumentDefinition({"value3", "value4", "value5"}, -1, true),
        chesspp::ArgumentDefinition({"value6"}, 3),
        chesspp::ArgumentDefinition({"value7", "value8", "value9"}, 0),
        chesspp::ArgumentDefinition({"value10"}, 0),
        };

    chesspp::Command const test_command("test_command", accpeted_arguments);
    std::vector<std::string> args = {
        "value6", "param0", "param1", "param2",
        "value5", "param00", "param01",
        "value7"};
    std::vector<chesspp::Argument> arguments = test_command.parse_arguments(args);

    // Test first argument
    EXPECT_EQ("value6", arguments[0].value);
    EXPECT_EQ("param0", arguments[0].parameters[0]);
    EXPECT_EQ("param1", arguments[0].parameters[1]);
    EXPECT_EQ("param2", arguments[0].parameters[2]);
    EXPECT_EQ(3, arguments[0].parameters.size());

    // Test second argument
    EXPECT_EQ("value5", arguments[1].value);
    EXPECT_EQ("param00", arguments[1].parameters[0]);
    EXPECT_EQ("param01", arguments[1].parameters[1]);
    EXPECT_EQ(2, arguments[1].parameters.size());

    // Test third argument
    EXPECT_EQ("value7", arguments[2].value);
    EXPECT_EQ(0, arguments[2].parameters.size());

    EXPECT_EQ(3, arguments.size());
}

TEST(Command, parse_arguments_test_equal_param)
{
    std::vector<chesspp::ArgumentDefinition> accpeted_arguments = {
        chesspp::ArgumentDefinition({"value1", "value2"}, 0),
        chesspp::ArgumentDefinition({"value3", "value4", "value5"}, -1, true),
        chesspp::ArgumentDefinition({"value6"}, 3),
        chesspp::ArgumentDefinition({"value7", "value8", "value9"}, 0),
        chesspp::ArgumentDefinition({"value10"}, 0),
        };

    chesspp::Command const test_command("test_command", accpeted_arguments);
    std::vector<std::string> args = {
        "value6", "param0", "param1", "param2",
        "value4", "param0", "param1"};
    std::vector<chesspp::Argument> arguments = test_command.parse_arguments(args);

    // Test first argument
    EXPECT_EQ("value6", arguments[0].value);
    EXPECT_EQ("param0", arguments[0].parameters[0]);
    EXPECT_EQ("param1", arguments[0].parameters[1]);
    EXPECT_EQ("param2", arguments[0].parameters[2]);
    EXPECT_EQ(3, arguments[0].parameters.size());

    // Test second argument
    EXPECT_EQ("value4", arguments[1].value);
    EXPECT_EQ("param0", arguments[1].parameters[0]);
    EXPECT_EQ("param1", arguments[1].parameters[1]);
    EXPECT_EQ(2, arguments[1].parameters.size());

    EXPECT_EQ(2, arguments.size());
}

TEST(Command, parse_arguments_test_bad_param_number)
{
    std::vector<chesspp::ArgumentDefinition> accpeted_arguments = {
        chesspp::ArgumentDefinition({"value1", "value2"}, 0),
        chesspp::ArgumentDefinition({"value3", "value4", "value5"}, -1),
        chesspp::ArgumentDefinition({"value6"}, 3),
        chesspp::ArgumentDefinition({"value7", "value8", "value9"}, 0),
        chesspp::ArgumentDefinition({"value10"}, 0),
        };

    chesspp::Command const test_command("test_command", accpeted_arguments);
    std::vector<std::string> args = {
        "value1",
        "value6", "param0", "param1"};

    EXPECT_THROW(test_command.parse_arguments(args), chesspp::ArgumentParseException);
}

TEST(Command, parse_arguments_test_bad_argument_name)
{
    std::vector<chesspp::ArgumentDefinition> accpeted_arguments = {
        chesspp::ArgumentDefinition({"value1", "value2"}, 0),
        chesspp::ArgumentDefinition({"value3", "value4", "value5"}, -1),
        chesspp::ArgumentDefinition({"value6"}, 3),
        chesspp::ArgumentDefinition({"value7", "value8", "value9"}, 0),
        chesspp::ArgumentDefinition({"value10"}, 0),
        };

    chesspp::Command const test_command("test_command", accpeted_arguments);
    std::vector<std::string> args = {
        "bad-value",
        "value6", "param0", "param1", "param2"};

    EXPECT_THROW(test_command.parse_arguments(args), chesspp::ArgumentParseException);
}

TEST(Command, parse_arguments_test_missing_required)
{
    std::vector<chesspp::ArgumentDefinition> accpeted_arguments = {
        chesspp::ArgumentDefinition({"value1", "value2"}, 0, true),
        chesspp::ArgumentDefinition({"value3", "value4", "value5"}, -1),
        chesspp::ArgumentDefinition({"value6"}, 3),
        chesspp::ArgumentDefinition({"value7", "value8", "value9"}, 0, true),
        chesspp::ArgumentDefinition({"value10"}, 0),
        };

    chesspp::Command const test_command("test_command", accpeted_arguments);
    std::vector<std::string> args = {
        "value1",
        "value6", "param0", "param1", "param2"};

    EXPECT_THROW(test_command.parse_arguments(args), chesspp::MissingArgumentException);
}
