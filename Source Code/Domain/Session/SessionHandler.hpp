#pragma once

#include <any>
#include <memory>      // unique_ptr
#include <stdexcept>   // runtime_error
#include <string>
#include <vector>

#include "TechnicalServices/Persistence/PersistenceHandler.hpp"
#include "Domain/ShoppingCart/ShoppingCartHandler.hpp"
#include "Domain/Account/AccountHandler.hpp"


namespace Domain::Session
{
  // Import the User Credentials type from the lower layer and publish it as your own
  using TechnicalServices::Persistence::UserCredentials;


  // Library Package within the Domain Layer Abstract class
  // The SessionHandler abstract class serves as the generalization of all user commands
  class SessionHandler
  {
    public:
      // Constructors and assignment operations
      SessionHandler()                                           = default;  // default ctor
      SessionHandler( const SessionHandler &  original )         = default;  // copy ctor
      SessionHandler(       SessionHandler && original )         = default;  // move ctor

      // Exceptions
      struct SessionException : std::runtime_error {using runtime_error   ::runtime_error;   };
      struct   BadCommand     : SessionException   {using SessionException::SessionException;};

      // Object Factory returning a specialized object specific to the specified user and role
      static std::unique_ptr<SessionHandler> createSession( const UserCredentials & credentials );


      // Operations
      virtual std::vector<std::string> getCommands   ()                                                                     = 0; // retrieves the list of actions (commands)
      virtual std::any                 executeCommand( const std::string & command, const std::vector<std::string> & args ) = 0; // Throws BadCommand
      virtual void signOff() = 0;
      // virtual std::unique_ptr<Domain::ShoppingCart::ShoppingCartHandler> getCart() = 0;
      // virtual std::unique_ptr<Domain::Account::AccountHandler> getAccount() = 0;

      // Destructor
      // Pure virtual destructor helps force the class to be abstract, but must still be implemented
      virtual ~SessionHandler() noexcept = 0;


    protected:
      // Copy assignment operators, protected to prevent mix derived-type assignments
      SessionHandler & operator=( const SessionHandler &  rhs ) = default;  // copy assignment
      SessionHandler & operator=(       SessionHandler && rhs ) = default;  // move assignment

  };    // class SessionHandler
} // namespace Domain::Session
