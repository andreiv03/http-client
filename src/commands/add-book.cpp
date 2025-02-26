#include "../../include/commands/add-book.h"

void AddBookCommand::execute() const {
  if (Client::token.empty())
    throw std::runtime_error("ERROR: You do not have access to the library!");

  std::string title;
  std::cout << "title=";
  std::getline(std::cin, title);
  Utils::format_field(title);

  std::string author;
  std::cout << "author=";
  std::getline(std::cin, author);
  Utils::format_field(author);

  std::string genre;
  std::cout << "genre=";
  std::getline(std::cin, genre);
  Utils::format_field(genre);

  std::string publisher;
  std::cout << "publisher=";
  std::getline(std::cin, publisher);
  Utils::format_field(publisher);

  std::string page_count;
  std::cout << "page_count=";
  std::getline(std::cin, page_count);

  if (title.empty())
    throw std::runtime_error("ERROR: The title must not be empty!");

  if (author.empty())
    throw std::runtime_error("ERROR: The author must not be empty!");

  if (genre.empty())
    throw std::runtime_error("ERROR: The genre must not be empty!");

  if (publisher.empty())
    throw std::runtime_error("ERROR: The publisher must not be empty!");

  if (page_count.empty())
    throw std::runtime_error("ERROR: The page_count must not be empty!");

  if (strtol(page_count.c_str(), nullptr, 10) == 0)
    throw std::runtime_error(
        "ERROR: The page_count must be a positive integer!");

  nlohmann::json book;
  book["title"] = title;
  book["author"] = author;
  book["genre"] = genre;
  book["publisher"] = publisher;
  book["page_count"] = strtol(page_count.c_str(), nullptr, 10);

  Request::method = "POST";
  Request::route = "/api/v1/tema/library/books";
  Request::body = book;

  const std::string request = Request::compute();
  Utils::send_to_server(request);
  std::string response = Utils::receive_from_server();

  int status_code = Utils::get_status_code(response);
  if (status_code < 200 || status_code >= 300)
    throw std::runtime_error("ERROR: Something went wrong adding the book!");

  std::cout << "SUCCESS: Book added successfully!" << std::endl;
}
