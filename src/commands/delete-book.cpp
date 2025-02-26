#include "../../include/commands/delete-book.h"

void DeleteBookCommand::execute() const {
  if (Client::token.empty())
    throw std::runtime_error("ERROR: You do not have access to the library!");

  std::string id;
  std::cout << "id=";
  std::getline(std::cin, id);

  if (id.empty())
    throw std::runtime_error("ERROR: The id must not be empty!");

  if (strtol(id.c_str(), nullptr, 10) == 0)
    throw std::runtime_error("ERROR: The id must be a positive integer!");

  Request::method = "DELETE";
  Request::route = "/api/v1/tema/library/books/" + id;
  Request::body = nullptr;

  const std::string request = Request::compute();
  Utils::send_to_server(request);
  std::string response = Utils::receive_from_server();

  int status_code = Utils::get_status_code(response);
  if (status_code < 200 || status_code >= 300)
    throw std::runtime_error("ERROR: Something went wrong deleting the book!");

  std::cout << "SUCCESS: Book deleted successfully!" << std::endl;
}
