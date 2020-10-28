#pragma once

#include <string>
#include "Domain/Account/RewardDescription.hpp"

namespace Domain::Account
{
  class Reward
  {
    public:
      virtual int         getPointCost()   const = 0;
      virtual std::string getDescription() const = 0;
      virtual double      getDiscount()    const = 0;
      virtual ~Reward() = 0;
  }; // class Reward
  inline Reward::~Reward() {}

  class BasicReward : public Reward
  {
  public:
    BasicReward()
      {
        name = "BasicReward";
      }

    int getPointCost() const override
    { return rwdDes._pointCost; }

    std::string getDescription() const override
    { return rwdDes._description; }

    double getDiscount() const override
    { return rwdDes._discount; }

    virtual ~BasicReward() {}

  private:
    std::string name;
    Domain::Account::RewardDescription rwdDes = Domain::Account::RewardDescription(100, "Just a Basic Reward", 10.0);
  };

} // namespace Domain::Account
