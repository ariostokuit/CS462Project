#pragma once

#include <any>
#include <stdexcept>
#include <memory>
#include <string>
#include <vector>
#include <list>

#include "TechnicalServices/Logging/LoggerHandler.hpp"
#include "Domain/Account/AccountHandler.hpp"
#include "Domain/Account/Reward.hpp"

namespace Domain::Account
{
  class CustomerAccount : public AccountHandler
  {
    public:
      // using AccountHandler::AccountHandler;  // inherit constructors
      CustomerAccount() {
        _logger << "Customer Account being used and has been successfully initialized";
      }

      // Operations
      void spendRewardPoints(std::string reward);
      int  getRewardPointBalance();
      void applyRewardToPurchase(std::string reward);
      std::list<Domain::Account::Reward *> getOwnedRewards();

      // Destructor
      // Pure virtual destructor helps force the class to be abstract, but must still be implemented
      ~CustomerAccount() noexcept override;
    private:
      std::shared_ptr<TechnicalServices::Logging::LoggerHandler> _loggerPtr = TechnicalServices::Logging::LoggerHandler::create();
      TechnicalServices::Logging::LoggerHandler &                _logger    = *_loggerPtr;
      std::list<Domain::Account::Reward *> _ownedRewards;
      int _rewardPoints = 1000;
  }; // class BorrowerAccount

  /*****************************************************************************
  ** Inline implementations
  ******************************************************************************/
  inline CustomerAccount::~CustomerAccount() noexcept
  {
    _logger << "Customer Account shutdown successfully";
  }

  inline void CustomerAccount::spendRewardPoints(std::string reward)
  {
    // if reward == "something" _ownedRewards.push_back(new Reward)
    _logger << "Responding to spendRewardPoints request with parameters: " + reward;
    _logger << "Added " + reward + " to owned rewards list";
    return;
  }

  inline int CustomerAccount::getRewardPointBalance()
  {
    _logger << "Responding to getRewardPointBalance request with parameters: ";
    _logger << "Current Reward Point Balance: " + std::to_string(_rewardPoints);
    return _rewardPoints;
  }

  inline void CustomerAccount::applyRewardToPurchase(std::string reward)
  {
    _logger << "Responding to applyRewardToPurchase request with parameters: " + reward;
    _logger << "Applied " + reward + " to current purchase";
    return;
  }

  inline std::list<Domain::Account::Reward *> CustomerAccount::getOwnedRewards()
  {
    _logger << "Responding to getOwnedRewards request with parameters: ";
    _logger << "You have a basic reward";
    return _ownedRewards;
  }
} // namespace Domain::Library
