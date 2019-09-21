#ifndef CHESSPP_ARGUMENT_H
#define CHESSPP_ARGUMENT_H

#include <string>

namespace chesspp
{
/**
 * @brief Stores value of an actual command that was received.
 *
 */
struct Argument
{

    /**
     * @brief The value of the argument (eg. "on" for debugging)
     *
     */
    std::string value = NULL;

    /**
     * @brief The value of the parameter if it has any. Will be `NULL` if the
     *        argument takes no parameters
     *
     */
    std::string parameter = NULL;

    Argument(std::string value, std::string parameter)
        : value(value), parameter(parameter)
    {
    }
};
} // namespace chesspp

#endif