#pragma once

#include <string>
#include "Domain/ShoppingCart/Product.hpp"
#include "Domain/ShoppingCart/ProductDescription.hpp"

namespace Domain::ShoppingCart
{
  // Breadstick Product Concrete Product
  class Breadstick : public Product
  {
  public:
    Breadstick() : Product() {}

    std::string getName() const override
    { return _name; }

    double getPrice() const override
    { return prodDes._price; }

    std::string getDescription() const override
    { return prodDes._description; }

    virtual ~Breadstick() {}

  private:
    std::string _name = "Breadstick";
    Domain::ShoppingCart::ProductDescription prodDes = Domain::ShoppingCart::ProductDescription(5, "Delicious breadstick");
  };

  struct BreadstickFactory
  {
    static Breadstick * createProduct() { return new Breadstick(); }
  };

} // namespace Domain::ShoppingCart
