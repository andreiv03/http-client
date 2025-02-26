#include "../include/request.h"

std::string Request::method;
std::string Request::route;
nlohmann::json Request::body;

std::string Request::compute() {
  const std::string protocol = "HTTP/1.1";
  std::ostringstream request;

  request << method << " " << route << " " << protocol << Utils::LINE_SEPARATOR;
  request << "Host: " << Utils::HOST << Utils::LINE_SEPARATOR;

  if (!Client::token.empty())
    request << "Authorization: Bearer " << Client::token
            << Utils::LINE_SEPARATOR;

  std::string body_data = body.dump();
  if (!body.empty())
    request << "Content-Type: application/json" << Utils::LINE_SEPARATOR
            << "Content-Length: " << body_data.size() << Utils::LINE_SEPARATOR;

  if (!Client::cookies.empty()) {
    request << "Cookie: ";

    for (size_t index = 0; index < Client::cookies.size(); ++index) {
      request << Client::cookies[index];
      if (index != Client::cookies.size() - 1)
        request << "; ";
    }

    request << Utils::LINE_SEPARATOR;
  }

  request << Utils::LINE_SEPARATOR;

  if (!body.empty())
    request << body_data << Utils::LINE_SEPARATOR;

  return request.str();
}
