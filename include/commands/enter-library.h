#pragma once

#include "../client.h"
#include "../command.h"
#include "../request.h"
#include "../utils.h"

#include <iostream>
#include <string>

class EnterLibraryCommand : public Command {
public:
  void execute() const override;
};
