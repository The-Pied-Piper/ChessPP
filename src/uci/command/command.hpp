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
#include <exception>

#include "chesspp/argument.hpp"

namespace chesspp
{

/**
 * @brief This exception is thrown when the command encounters a sequence of
 *        arguments that is could not parse.
 *
 */
class ArgumentParseException : public std::exception
{
    virtual const char *what() const throw()
    {
        return "Could not parse the arguments";
    }
};

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
     * @brief Indicates the number of tokens (words) the argument expects
     *        in it's parameters. 0 means no parameters are expected, while -1
     *        indicates an arbitary number of tokens. In the latter case all
     *        tokens untill the next valid argument definition are included in
     *        the parameters list.
     */
    int const num_parameters;

    ArgumentDefinition(
        std::vector<std::string> const &values,
        int const &num_parameters = 0)
        : values(values), num_parameters(num_parameters)
    {
    }
};

/**
 * @brief Represents a UCI command
 *
 */
class Command
{
private:
    /**
     * @brief The name of the command (eg. "debug")
     *
     */
    std::string name;

    /**
     * @brief Holds the the definition for the arguments that this command will
     *        accept
     *
     */
    std::vector<ArgumentDefinition> accepted_arguments;

    /**
     * @brief The callback to run when this command needs to be executed.
     *
     */
    void (*callback)(std::vector<Argument>) = nullptr;

    /**
     * @brief This function matches a string to an ArgumentDefinition value.
     *
     * @param argument_string The string to use for matching
     *
     * @return ArgumentDefinition const* A pointer to the argument that has a
     *         matching value to the given string. If no match is found then a
     *         `nullptr` is returned.
     */
    ArgumentDefinition const *find_argument(
        std::string const &argument_string) const;

public:
    /**
     * @brief Construct a new Command object
     *
     * @param name The name of the command
     * @param accepted_arguments A vector containing the arguments that this command accepts
     */
    Command(
        std::string const &name,
        std::vector<ArgumentDefinition> const &accepted_arguments)
        : name(name), accepted_arguments(accepted_arguments)
    {
    }

    /**
     * @brief This function parses a vector of argument strings into a vector of
     *        Argument objects
     *
     * @return std::vector<Argument> const& The list of parsed arguments
     *
     * @throw ArgumentParseException
     */
    std::vector<Argument> parse_arguments(
        std::vector<std::string> const &argument_strings) const;

    /**
     * @brief Issues the command over stdout with the given arguments
     *
     * @throw ArgumentParseException
     */
    void issue(std::vector<std::string> const &arguments) const;
};

} // namespace chesspp

#endif
