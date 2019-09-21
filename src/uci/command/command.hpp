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

#include "chesspp/argument.hpp"

// #include <chesspp/argument.hpp>

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
 * @brief Base class for all UCI commands
 *
 * @tparam function The callback to execute the command
 */
template <typename function>
class Command
{
private:
    /**
     * @brief The name of the command (eg. "debug")
     *
     */
    std::string name;

    std::vector<ArgumentDefinition> accepted_arguments;

    const function callback;

public:
    /**
     * @brief Construct a new Command object
     *
     * @param callback
     */
    Command(function const &callback)
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
