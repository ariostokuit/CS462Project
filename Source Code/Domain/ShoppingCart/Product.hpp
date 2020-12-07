#pragma once

#include <string>

namespace Domain::ShoppingCart
{
  // Product Abstract Product Interface
  class Product
  {
    public:
      Product() {}

      virtual std::string getName() const = 0;
      virtual double getPrice() const = 0;
      virtual std::string getDescription() const = 0;

      virtual ~Product() = 0; // force the class to be abstract
  }; // class Product
  inline Product::~Product() {}
  
} // namespace Domain::ShoppingCart
