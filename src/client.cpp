#include "../include/client.h"

std::map<std::string, CommandName> Client::commands;
int Client::socket_fd;
std::string Client::token;
std::vector<std::string> Client::cookies;

void Client::start() {
  initialize_commands();

  while (true) {
    std::string command_name;
    std::getline(std::cin, command_name);

    if (command_name == "exit")
      break;

    auto it = commands.find(command_name);
    if (it == commands.end()) {
      std::cerr << "ERROR: The command is not valid!" << std::endl;
      continue;
    }

    try {
      socket_fd = Utils::open_connection();
      execute_command(it->second);
      close(socket_fd);
    } catch (const std::runtime_error &error) {
      std::cerr << error.what() << std::endl;
      close(socket_fd);
    }
  }
}

void Client::execute_command(CommandName command_name) {
  std::unique_ptr<Command> command;

  switch (command_name) {
  case REGISTER:
    command = std::make_unique<RegisterCommand>();
    break;
  case LOGIN:
    command = std::make_unique<LoginCommand>();
    break;
  case ENTER_LIBRARY:
    command = std::make_unique<EnterLibraryCommand>();
    break;
  case GET_BOOKS:
    command = std::make_unique<GetBooksCommand>();
    break;
  case GET_BOOK:
    command = std::make_unique<GetBookCommand>();
    break;
  case ADD_BOOK:
    command = std::make_unique<AddBookCommand>();
    break;
  case DELETE_BOOK:
    command = std::make_unique<DeleteBookCommand>();
    break;
  case LOGOUT:
    command = std::make_unique<LogoutCommand>();
    break;
  default:
    break;
  }

  command->execute();
}

void Client::initialize_commands() {
  commands = {{"register", REGISTER},
              {"login", LOGIN},
              {"enter_library", ENTER_LIBRARY},
              {"get_books", GET_BOOKS},
              {"get_book", GET_BOOK},
              {"add_book", ADD_BOOK},
              {"delete_book", DELETE_BOOK},
              {"logout", LOGOUT},
              {"exit", EXIT}};
}

int main() {
  Client::start();
  return 0;
}
