#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

#include "command.hpp"
#include "chesspp/argument.hpp"

void chesspp::Command::issue(std::vector<std::string> const &arguments) const
{
    // Add the name of the command to the output
    std::string output = name;

    // Make sure that the arguments can be parsed. This will throw an
    // ArgumentParseException if we can't parse the arguments.
    parse_arguments(arguments);

    // Add arguments to the output string
    for (const std::string argument : arguments)
    {
        output.append(" " + argument);
    }

    // Print output to stdout.
    std::cout << output << "\n";
}

std::vector<chesspp::Argument> chesspp::Command::parse_arguments(
    std::vector<std::string> const &argument_strings) const
{
    // Convert the strings into Argument objects
    std::vector<Argument> arguments = get_arguments(argument_strings);

    // Check if all the required arguments are included.
    if (not check_required_arguments(arguments))
    {
        throw MissingArgumentException();
    }

    return arguments;
}

chesspp::ArgumentDefinition const *chesspp::Command::find_argument(
    std::string const &argument_string) const
{
    for (ArgumentDefinition const &accepted_argument : accepted_arguments)
    {
        for (std::string const &value : accepted_argument.values)
        {
            if (value == argument_string)
            {
                return &accepted_argument;
            }
        }
    }
    return nullptr;
}

std::vector<chesspp::Argument> chesspp::Command::get_arguments(
    std::vector<std::string> const &argument_strings) const
{
    // Stores the arguments we will return
    std::vector<chesspp::Argument> arguments;

    // Stores parameters for the argument being parsed.
    std::vector<std::string> parameters;

    // Start parsing tokens from the back to the front.
    for (auto it = argument_strings.rbegin(); it != argument_strings.rend(); ++it)
    {
        std::string argument_string = *it;

        // Try to find a matching argument definition
        chesspp::ArgumentDefinition const *arg_def = find_argument(argument_string);

        // If the token does not match an argument definition then add it as a
        // parameter.
        if (arg_def == nullptr or (arg_def->num_parameters != -1 and
                                   arg_def->num_parameters != parameters.size()))
        {
            parameters.push_back(argument_string);
        }

        // Otherwise add it to the argument list
        else
        {
            // Since we are iterating in reverse we need to reverse parameters.
            std::reverse(parameters.begin(), parameters.end());

            // Create the argument and add it to the result list
            chesspp::Argument argument(argument_string, parameters);
            arguments.push_back(argument);

            // empty the parameter list for the new argument.
            parameters.clear();
        }
    }

    // If something went wrong we will have some parameters left over
    if (not parameters.empty())
    {
        throw ArgumentParseException();
    }

    // Reverse arguments to get proper order, since we iterated in reverse.
    std::reverse(arguments.begin(), arguments.end());

    // Return result
    return arguments;
}

std::vector<chesspp::ArgumentDefinition> const chesspp::Command::get_required_arguments() const
{
    // stores the required arguments that we need to find
    std::vector<ArgumentDefinition> required_arguments;

    // loop over the accepted arguments looking for ones that have the required
    // flag.
    for (ArgumentDefinition const &argument : accepted_arguments)
    {
        if (argument.required)
        {
            required_arguments.push_back(argument);
        }
    }
    return required_arguments;
}

bool chesspp::Command::check_required_arguments(std::vector<chesspp::Argument> arguments) const
{
    std::vector<chesspp::ArgumentDefinition> const &required_arguments = get_required_arguments();

    for (ArgumentDefinition const &required_argument : required_arguments)
    {
        bool found = false;
        for (Argument const &argument : arguments)
        {
            for (std::string const &value : required_argument.values)
            {
                if (value == argument.value)
                {
                    found = true;
                    break;
                }
            }
            if (found)
            {
                break;
            }
        }
        if (not found)
        {
            return false;
        }
    }
    return true;
}
