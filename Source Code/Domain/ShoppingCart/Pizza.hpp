#pragma once

#include <string>
#include "Domain/ShoppingCart/Product.hpp"
#include "Domain/ShoppingCart/ProductDescription.hpp"

namespace Domain::ShoppingCart
{
  // Pizza Product Concrete Product
  class Pizza : public Product
  {
  public:
    Pizza() : Product() {}

    std::string getName() const override
    { return _name; }

    double getPrice() const override
    { return prodDes._price; }

    std::string getDescription() const override
    { return prodDes._description; }

    virtual ~Pizza() {}

  private:
    std::string _name = "Pizza";
    Domain::ShoppingCart::ProductDescription prodDes = Domain::ShoppingCart::ProductDescription(10, "Delicious pizza");
  };

  struct PizzaFactory
  {
    static Pizza * createProduct() { return new Pizza(); }
  };

} // namespace Domain::ShoppingCart
