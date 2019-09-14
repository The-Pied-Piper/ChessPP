#include "chesspp/parser.hpp"

std::vector<std::string> Parser::tokenise(std::string const &input)
{

    std::vector<std::string> result;
    std::string token = "";

    for (size_t i = 0; i < input.length(); i++)
    {
        char const letter = input[i];
        if (isspace(letter) and token.length() > 0)
        {
            result.push_back(token);
            token = "";
        }
        else if (not isspace(letter))
        {
            token.push_back(letter);

            // Save to result if last iteration
            if (i == input.length() - 1)
            {
                result.push_back(token);
                token = "";
            }
        }
    }
    return result;
}

std::string Parser::tolower(std::string const& text) {
    std::string result = "";
    for (char character : text) {
        result.push_back(character);
    }
    return result;
}
