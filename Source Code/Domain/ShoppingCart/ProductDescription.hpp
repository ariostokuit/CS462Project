#pragma once

#include <string>

namespace Domain::ShoppingCart
{
  class ProductDescription
  {
    public:
      // constructor
      ProductDescription(double price, std::string description) {
        _price = price;
        _description = description;
      }

      // attributes
      double _price;
      std::string _description;

  }; // class ProductDescription
} // namespace Domain::ShoppingCart
