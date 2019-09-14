#ifndef CHESSPP_PARSER_H
#define CHESSPP_PARSER_H

#include <string>
#include <vector>

/**
 * @brief Parses strings into UCI commands
 *
 */
class Parser
{
private:
    /* data */
public:

    /**
     * @brief Converts a string into a vector with any whitespace as a delimiter
     *
     * @param command A string containing the command to be parsed
     * @return A vector of strings containing the tokens in the command string
     */
    std::vector<std::string> tokenise(std::string const& input);
};

#endif