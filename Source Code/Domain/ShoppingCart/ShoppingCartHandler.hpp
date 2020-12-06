#pragma once

#include <any>
#include <memory>      // unique_ptr
#include <stdexcept>   // runtime_error
#include <string>
#include <vector>
#include "Domain/Order/OrderHandler.hpp"

namespace Domain::ShoppingCart
{

  class ShoppingCartHandler
  {
    public:
      // Constructors and assignment operations
      ShoppingCartHandler()                                        = default;  // default ctor
      ShoppingCartHandler( const ShoppingCartHandler &  original ) = default;  // copy ctor
      ShoppingCartHandler(       ShoppingCartHandler && original ) = default;  // move ctor

      // Exceptions
      struct ShoppingCartException : std::runtime_error {using runtime_error   ::runtime_error;   };
      struct   BadCommand     : ShoppingCartException   {using ShoppingCartException::ShoppingCartException;};

      // Object Factory returning a specialized object specific to the specified user and role
      static std::unique_ptr<ShoppingCartHandler> createShoppingCart();

      // Operations
      virtual void addProduct(std::string product, int quantity) = 0;
      virtual void removeProduct(std::string product, int quantity) = 0;
      virtual std::vector<std::string> viewProducts() = 0;
      virtual std::unique_ptr<Domain::Order::OrderHandler> initiateCheckout() = 0;

      // Destructor
      // Pure virtual destructor helps force the class to be abstract, but must still be implemented
      virtual ~ShoppingCartHandler() noexcept = 0;


    protected:
      // Copy assignment operators, protected to prevent mix derived-type assignments
      ShoppingCartHandler & operator=( const ShoppingCartHandler &  rhs ) = default;  // copy assignment
      ShoppingCartHandler & operator=(       ShoppingCartHandler && rhs ) = default;  // move assignment

  };    // class ShoppingCartHandler
} // namespace Domain::ShoppingCart
