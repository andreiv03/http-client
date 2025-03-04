#pragma once

#include "command.h"
#include "commands/add-book.h"
#include "commands/delete-book.h"
#include "commands/enter-library.h"
#include "commands/get-book.h"
#include "commands/get-books.h"
#include "commands/login.h"
#include "commands/logout.h"
#include "commands/register.h"
#include "utils.h"

#include <arpa/inet.h>
#include <iostream>
#include <map>
#include <netinet/in.h>
#include <stdexcept>
#include <string>
#include <sys/socket.h>
#include <vector>

class Client {
public:
  static std::map<std::string, CommandName> commands;
  static int socket_fd;
  static std::string token;
  static std::vector<std::string> cookies;

  static void start();

  static void execute_command(CommandName command_name);

  static void initialize_commands();
};
