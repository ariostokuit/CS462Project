#include "Domain/Account/AccountHandler.hpp"

#include <memory>       // unique_ptr, make_unique<>()

#include "Domain/Account/CustomerAccount.hpp"

namespace Domain::Account
{
  AccountHandler::~AccountHandler() noexcept = default;

  std::unique_ptr<AccountHandler> AccountHandler::createAccount()
  {
    return std::make_unique<Domain::Account::CustomerAccount> ();
  }
} // namespace Domain::Account
