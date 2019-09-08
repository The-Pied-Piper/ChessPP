#ifndef CHESSPP_UCI_H
#define CHESSPP_UCI_H

#include <string>
#include <vector>

/**
 * @brief Parses strings into UCI commands for a chess engine
 *
 */
class Engine
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