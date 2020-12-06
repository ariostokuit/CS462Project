#pragma once

#include <string>
#include "Domain/ShoppingCart/ProductDescription.hpp"

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

  struct PizzaFactory
  {
    static Pizza * createProduct() { return new Pizza(); }
  };

  struct BreadstickFactory
  {
    static Breadstick * createProduct() { return new Breadstick(); }
  };

  struct CocaColaFactory
  {
    static CocaCola * createProduct() { return new CocaCola(); }
  };
} // namespace Domain::ShoppingCart
