#include "../include/utils.h"

const int Utils::BUFFER_SIZE = 4096;
const std::string Utils::LINE_SEPARATOR = "\r\n";
const std::string Utils::HOST = "34.246.184.49";
const int Utils::PORT = 8080;

int Utils::open_connection() {
  int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

  if (socket_fd < 0)
    throw std::runtime_error("ERROR: Failed to open socket connection!");

  struct sockaddr_in server_address {};
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(PORT);
  inet_aton(HOST.c_str(), &server_address.sin_addr);

  if (connect(socket_fd, reinterpret_cast<const sockaddr *>(&server_address),
              sizeof(server_address)) < 0)
    throw std::runtime_error("ERROR: Failed to connect to the server!");

  return socket_fd;
}

void Utils::send_to_server(const std::string &request) {
  size_t total_bytes_sent = 0;

  while (total_bytes_sent < request.size()) {
    ssize_t bytes_sent =
        write(Client::socket_fd, request.c_str() + total_bytes_sent,
              request.size() - total_bytes_sent);

    if (bytes_sent < 0)
      throw std::runtime_error("ERROR: Failed to write to socket!");

    if (bytes_sent == 0)
      break;

    total_bytes_sent += bytes_sent;
  }
}

std::string Utils::receive_from_server() {
  std::string response;
  size_t header_end = 0, body_length = 0;

  while (true) {
    std::array<char, BUFFER_SIZE> buffer{};
    ssize_t bytes_read = read(Client::socket_fd, buffer.data(), BUFFER_SIZE);

    if (bytes_read < 0)
      throw std::runtime_error("ERROR: Failed to read from socket!");

    if (bytes_read == 0)
      break;

    response.append(buffer.data(), bytes_read);
    header_end = response.find(LINE_SEPARATOR + LINE_SEPARATOR);

    if (header_end != std::string::npos) {
      size_t body_length_start = response.find("Content-Length: ");
      header_end += LINE_SEPARATOR.size() * 2;

      if (body_length_start == std::string::npos)
        continue;

      body_length_start += sizeof("Content-Length: ") - 1;
      body_length =
          std::strtol(response.data() + body_length_start, nullptr, 10);
      break;
    }
  }

  while (response.size() < header_end + body_length) {
    std::array<char, BUFFER_SIZE> buffer{};
    ssize_t bytes_read = read(Client::socket_fd, buffer.data(), BUFFER_SIZE);

    if (bytes_read < 0)
      throw std::runtime_error("ERROR: Failed to read from socket!");

    if (bytes_read == 0)
      break;

    response.append(buffer.data(), bytes_read);
  }

  return response.empty() ? response
                          : response.substr(response.find("HTTP/1.1"));
}

int Utils::get_status_code(const std::string &response) {
  std::string status_code = response.substr(9, 3);
  return std::stoi(status_code);
}

void Utils::add_cookie(const std::string &response,
                       const std::string &cookie_name) {
  size_t cookie_start = response.find(cookie_name + "=");
  size_t cookie_end = response.find(LINE_SEPARATOR, cookie_start);
  std::string cookie = response.substr(cookie_start, cookie_end - cookie_start);
  Client::cookies.push_back(cookie);
}

void Utils::get_token(const std::string &response) {
  const std::string token_key = R"({"token":")";
  size_t token_start = response.find(token_key) + sizeof(token_key) - 1;
  size_t token_end = response.find('\"', token_start);
  std::string token = response.substr(token_start, token_end - token_start);
  Client::token = token;
}

void Utils::format_field(std::string &field) {
  std::string formatted_field;

  for (char &character : field)
    if (character != '_')
      formatted_field.push_back(character);

  field = formatted_field;
}
