#pragma once

#include <string>

namespace Domain::Account
{
  class RewardDescription
  {
    public:
      // constructor
      RewardDescription(int pointCost, std::string description, double discount) {
        _pointCost   = pointCost;
        _description = description;
        _discount    = discount;
      }

      // attributes
      int         _pointCost;
      std::string _description;
      double      _discount;

  }; // class RewardDescription
} // namespace Domain::Account
