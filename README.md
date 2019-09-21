# Chess++

[![CircleCI](https://circleci.com/gh/The-Pied-Piper/ChessPP.svg?style=svg)](https://circleci.com/gh/The-Pied-Piper/ChessPP)

A chess UCI adapter. Provides an easy to use API for consuming and producing UCI commands.

## NOTE: This Library is still under development.

## Table of Contents
1. [Getting Started](#getting-started)
    1. [Installation](#installation)
    1. [Usage](#usage)
        1. [Register A Command](#register-a-command)
        1. [Issue A Command](#issue-a-command)
        1. [Start](#start)

## Installation

The package can be build most easily using cmake:

```cmake
add_subdirectory(/path/to/Chess++)
target_link_libraries(My_project PUBLIC
    Chess++
    ...
)
```

## Usage


### Registering A Command

To tell the UCI what to do when it recieves a command on standard input we simply have to pass it the callback we would like to run:

```c++
#include <vector>
#include <chesspp/uci.hpp>


void debug_command(std::vector<Argument> const & args){
    if(args[0].value == "on") {
        // switch debugging on
    } else {
        // switch debugging off
    }
}

int main()
{
    chesspp::UCI uci;
    // Register debug_command with the UCI
    uci.register_command("debug", debug_command);
    return 0;
}
```

### Issue command

To issue a command just tell the UCI the name of the command folowed by a vector containing any arguments:

```c++
#include <vector>
#include <chesspp/uci.hpp>

int main(){
    chesspp::UCI uci;
    std::vector<string> arguments = {"on"};
    uci.issue_command("debug", arguments);
    return 0;
}
```

The UCI will now make sure that the command is valid before issuing it.

### Start

To tell the UCI to start listening for commands we jsut call the start function along with the mode ("engine" or "interface"):

```c++
#include <chesspp/uci.hpp>

int main(){
    chesspp::UCI uci;
    uci.start("engine"); // Start listening for commands issued to the engine from the interface
    return 0;
}


