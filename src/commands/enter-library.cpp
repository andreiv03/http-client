#include "../../include/commands/enter-library.h"

void EnterLibraryCommand::execute() const {
  if (!Client::token.empty())
    throw std::runtime_error("ERROR: You already have access to the library!");

  Request::method = "GET";
  Request::route = "/api/v1/tema/library/access";
  Request::body = nullptr;

  const std::string request = Request::compute();
  Utils::send_to_server(request);
  std::string response = Utils::receive_from_server();

  int status_code = Utils::get_status_code(response);
  if (status_code < 200 || status_code >= 300)
    throw std::runtime_error("ERROR: You are not logged in!");

  Utils::get_token(response);
  std::cout << "SUCCESS: Access granted to the library!" << std::endl;
}
