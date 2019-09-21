/**
 * @file command.hpp
 * @author Umar Khan
 * @brief Descripes an UCI command
 * @date 2019-09-14
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef SRC_UCI_COMMAND_H
#define SRC_UCI_COMMAND_H

#include <string>
#include <vector>
#include <iostream>

namespace chesspp
{

/**
 * @brief Defines an argument that the command will accept as valid.
 *
 */
struct ArgumentDefinition
{
    /**
     * @brief Holds acceptable values that the argument might take on
     *        (eg. for debug this would be ["on", "off"]). If nothing is defined
     *        then the argument will accept any value at all.
     *
     */
    std::vector<std::string> values;

    /**
     * @brief Whether or not the argument expects a parameter. If this is true
     *        the next token is taken as this argument's parameter otherwise the
     *        next token is it's own argument.
     */
    const bool has_parameter = NULL;

    ArgumentDefinition(
        std::vector<std::string> const &values,
        bool const has_parameter)
        : values(values), has_parameter(has_parameter)
    {
    }
};

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

/**
 * @brief Base class for all UCI commands
 *
 * @tparam functor The callback to execute the command
 */
template <typename functor>
class Command
{
private:
    /**
     * @brief The name of the command (eg. "debug")
     *
     */
    std::string name;

    std::vector<ArgumentDefinition> accepted_arguments;

    const functor callback;

public:
    /**
     * @brief Construct a new Command object
     *
     * @param callback
     */
    Command(functor &const callback)
        : callback(callback)
    {
    }

    bool check(std::string const &arguments) const;

    /**
     * @brief Issues the command over stdout with the given arguments
     *
     */
    void issue(std::vector<std::string> const &arguments) const
    {
        std::string output = name;
        if (not check(arguments))
        {
            // TODO: replace this with an exception
            return;
        }
        for (const std::string argument : arguments)
        {
            output.append(" " + argument);
        }

        std::cout << output << "\n";
    }
};

} // namespace chesspp

#endif
