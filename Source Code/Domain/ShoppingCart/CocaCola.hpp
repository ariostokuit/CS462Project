#pragma once

#include <string>
#include "Domain/ShoppingCart/Product.hpp"
#include "Domain/ShoppingCart/ProductDescription.hpp"

namespace Domain::ShoppingCart
{
  // CocaCola Product Concrete Product
  class CocaCola : public Product
  {
  public:
    CocaCola() : Product() {}

    std::string getName() const override
    { return _name; }

    double getPrice() const override
    { return prodDes._price; }

    std::string getDescription() const override
    { return prodDes._description; }

    virtual ~CocaCola() {}

  private:
    std::string _name = "CocaCola";
    Domain::ShoppingCart::ProductDescription prodDes = Domain::ShoppingCart::ProductDescription(1, "Delicious Coca Cola");
  };

  struct CocaColaFactory
  {
    static CocaCola * createProduct() { return new CocaCola(); }
  };
} // namespace Domain::ShoppingCart
