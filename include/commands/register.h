#pragma once

#include "../client.h"
#include "../command.h"
#include "../request.h"
#include "../utils.h"

#include <iostream>
#include <nlohmann/json.hpp>
#include <string>

class RegisterCommand : public Command {
public:
  void execute() const override;
};
