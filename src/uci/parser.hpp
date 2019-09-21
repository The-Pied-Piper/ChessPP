/**
 * @file parser.hpp
 * @author Umar Khan
 * @date 2019-09-14
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef SRC_UCI_PARSER_H
#define SRC_UCI_PARSER_H

#include <string>
#include <vector>

namespace chesspp
{
/**
 * @brief Parses strings into UCI commands
 *
 */
class Parser
{
private:
    /**
     * @brief Converts a string to lower case
     *
     * @param text The string to be lower cased
     * @return The string with all upper case characters converted to lower case
     */
    static std::string tolower(std::string const &text);

public:
    /**
     * @brief Converts a string into a vector with any whitespace as a delimiter
     *
     * @param command A string containing the command to be parsed
     * @return A vector of strings containing the tokens in the command string
     */
    static std::vector<std::string> tokenise(std::string const &input);
};

} // namespace chesspp

#endif