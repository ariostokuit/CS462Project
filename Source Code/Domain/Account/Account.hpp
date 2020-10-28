#pragma once

#include "Domain/Account/AccountHandler.hpp"

namespace Domain::Account
{
  class Account : public Domain::Account::AccountHandler
  {
  public:
    // Constructors
    using AccountHandler::AccountHandler; // inherit constructors
    // Operations

    // Destructor
   ~Account() noexcept override;
 };

}
