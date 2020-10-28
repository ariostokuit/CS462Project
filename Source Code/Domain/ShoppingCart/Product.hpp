#pragma once

#include <string>
#include "Domain/ShoppingCart/ProductDescription.hpp"

namespace Domain::ShoppingCart
{
  class Product
  {
    public:
      virtual double getPrice() const = 0;
      virtual std::string getDescription() const = 0;
      virtual ~Product() = 0;
  }; // class Product
  inline Product::~Product() {}

  class Pizza : public Product
  {
  public:
    Pizza()
      {
        // prodDes = ProductDescription(10, "Delicious pizza");
        name = "Pizza";
      }

    double getPrice() const override
    { return prodDes._price; }

    std::string getDescription() const override
    { return prodDes._description; }

    virtual ~Pizza() {}

  private:
    std::string name;
    Domain::ShoppingCart::ProductDescription prodDes = Domain::ShoppingCart::ProductDescription(10, "Delicious pizza");
  };

  class Breadstick : public Product
  {
  public:
    Breadstick()
    {
      // prodDes = ProductDescription(10, "Delicious breadstick");
      name = "Breadstick";
    }

    double getPrice() const override
    { return prodDes._price; }

    std::string getDescription() const override
    { return prodDes._description; }

    virtual ~Breadstick() {}

  private:
    std::string name;
    Domain::ShoppingCart::ProductDescription prodDes = Domain::ShoppingCart::ProductDescription(10, "Delicious breadstick");
  };

  class CocaCola : public Product
  {
  public:
    CocaCola()
      {
        // prodDes = ProductDescription(10, "Delicious Coca Cola");
        name = "Coca Cola";
      }

    double getPrice() const override
    { return prodDes._price; }

    std::string getDescription() const override
    { return prodDes._description; }

    virtual ~CocaCola() {}

  private:
    std::string name;
    Domain::ShoppingCart::ProductDescription prodDes = Domain::ShoppingCart::ProductDescription(10, "Delicious Coca Cola");
  };
} // namespace Domain::ShoppingCart
