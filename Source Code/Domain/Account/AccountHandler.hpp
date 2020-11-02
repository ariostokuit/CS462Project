#pragma once

#include <any>
#include <memory>      // unique_ptr
#include <stdexcept>   // runtime_error
#include <string>
#include <vector>
#include <list>
#include "Domain/Account/Reward.hpp"

namespace Domain::Account
{

  class AccountHandler
  {
    public:
      // Constructors and assignment operations
      AccountHandler()                                   = default;  // default ctor
      AccountHandler( const AccountHandler &  original ) = default;  // copy ctor
      AccountHandler(       AccountHandler && original ) = default;  // move ctor

      // Exceptions
      struct AccountException : std::runtime_error {using runtime_error   ::runtime_error;   };
      struct   BadCommand     : AccountException   {using AccountException::AccountException;};

      // Object Factory returning a specialized object specific to the specified user and role
      static std::unique_ptr<AccountHandler> createAccount();

      // Operations
      virtual std::string spendRewardPoints(std::string reward) = 0;
      virtual int getRewardPointBalance() = 0;
      virtual void applyRewardToPurchase(std::string reward) = 0;
      virtual std::list<Domain::Account::Reward *> getOwnedRewards() = 0;

      // Destructor
      // Pure virtual destructor helps force the class to be abstract, but must still be implemented
      virtual ~AccountHandler() noexcept = 0;


    protected:
      // Copy assignment operators, protected to prevent mix derived-type assignments
      AccountHandler & operator=( const AccountHandler &  rhs ) = default;  // copy assignment
      AccountHandler & operator=(       AccountHandler && rhs ) = default;  // move assignment

  };    // class AccountHandler
} // namespace Domain::Account
