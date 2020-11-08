#pragma once

#include <any>
#include <stdexcept>
#include <memory>
#include <string>
#include <vector>

#include "Domain/Session/SessionHandler.hpp"
#include "TechnicalServices/Logging/LoggerHandler.hpp"
#include "Domain/ShoppingCart/ShoppingCartHandler.hpp"
#include "Domain/Account/AccountHandler.hpp"

namespace Domain::Session
{
  class CustomerSession : public SessionHandler
  {
    public:
      // using SessionHandler::SessionHandler;  // inherit constructors
      CustomerSession() {
        _logger << "Customer Session being used and has been successfully initialized";
      }

      // Operations
      std::vector<std::string> getCommands() override;  // retrieves the list of actions (commands)
      std::any                 executeCommand( const std::string & command, const std::vector<std::string> & args ) override;
      void signOff() override;
      // std::unique_ptr<Domain::ShoppingCart::ShoppingCartHandler> getCart() override;
      // std::unique_ptr<Domain::Account::AccountHandler> getAccount() override;

      // Destructor
      // Pure virtual destructor helps force the class to be abstract, but must still be implemented
      ~CustomerSession() noexcept override;
    private:
      // std::string role = "Customer";
      std::shared_ptr<TechnicalServices::Logging::LoggerHandler> _loggerPtr = TechnicalServices::Logging::LoggerHandler::create();
      TechnicalServices::Logging::LoggerHandler &                _logger    = *_loggerPtr;
      // std::unique_ptr<Domain::ShoppingCart::ShoppingCartHandler> _cart  = Domain::ShoppingCart::ShoppingCartHandler::createShoppingCart();
      // std::unique_ptr<Domain::Account::AccountHandler> _account = Domain::Account::AccountHandler::createAccount();
  }; // class BorrowerSession

  /*****************************************************************************
  ** Inline implementations
  ******************************************************************************/
  inline CustomerSession::~CustomerSession() noexcept
  {
    _logger << "Customer Session shutdown successfully";
  }

  inline void CustomerSession::signOff()
  {
    _logger << "Signing off of Customer Session";
    // CustomerSession::~CustomerSession();
  }

  inline std::vector<std::string> CustomerSession::getCommands()
  {
    return { "Sign out", "Get Role"};
  }
  inline std::any CustomerSession::executeCommand( const std::string & command, const std::vector<std::string> & args )
  {
    std::string parameters;
    for( const auto & arg : args )  parameters += '"' + arg + "\"  ";
    _logger << "Responding to \"" + command + "\" request with parameters: " + parameters;

    return "Execute none";
  }

  // inline std::unique_ptr<Domain::ShoppingCart::ShoppingCartHandler> CustomerSession::getCart()
  // {
  //   return _cart;
  // }
  //
  // inline std::unique_ptr<Domain::Account::AccountHandler> CustomerSession::getAccount()
  // {
  //   return _account;
  // }
} // namespace Domain::Library
