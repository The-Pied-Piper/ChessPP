#ifndef CHESSPP_ARGUMENT_H
#define CHESSPP_ARGUMENT_H

#include <string>
#include <vector>

namespace chesspp
{
/**
 * @brief Stores value of an actual command that was received.
 *
 */
struct Argument
{

    /**
     * @brief The value of the argument (eg. "on" for  the debug command)
     *
     */
    std::string value;

    /**
     * @brief The argument's parameters if it has any.
     *
     */
    std::vector<std::string> parameters;

    Argument(std::string &value, std::vector<std::string> &parameters)
        : value(value), parameters(parameters)
    {
    }
};
} // namespace chesspp

#endif