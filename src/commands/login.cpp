#include "../../include/commands/login.h"

void LoginCommand::execute() const {
  if (!Client::cookies.empty())
    throw std::runtime_error("ERROR: You are already logged in!");

  std::string username;
  std::cout << "username=";
  std::getline(std::cin, username);

  std::string password;
  std::cout << "password=";
  std::getline(std::cin, password);

  if (username.empty())
    throw std::runtime_error("ERROR: The username must not be empty!");

  if (username.find(' ') != std::string::npos)
    throw std::runtime_error("ERROR: The username must not contain spaces!");

  if (password.empty())
    throw std::runtime_error("ERROR: The password must not be empty!");

  if (password.find(' ') != std::string::npos)
    throw std::runtime_error("ERROR: The password must not contain spaces!");

  nlohmann::json user;
  user["username"] = username;
  user["password"] = password;

  Request::method = "POST";
  Request::route = "/api/v1/tema/auth/login";
  Request::body = user;

  const std::string request = Request::compute();
  Utils::send_to_server(request);
  std::string response = Utils::receive_from_server();

  int status_code = Utils::get_status_code(response);
  if (status_code < 200 || status_code >= 300)
    throw std::runtime_error("ERROR: The username or password is not valid!");

  Client::cookies.clear();
  Utils::add_cookie(response, "connect.sid");
  std::cout << "SUCCESS: Logged in successfully!" << std::endl;
}
