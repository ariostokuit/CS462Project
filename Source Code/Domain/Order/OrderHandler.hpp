#pragma once

#include <any>
#include <memory>      // unique_ptr
#include <stdexcept>   // runtime_error
#include <string>
#include <vector>
#include <list>
#include "Domain/ShoppingCart/Product.hpp"

namespace Domain::Order
{

  class OrderHandler
  {
    public:
      // Constructors and assignment operations
      OrderHandler()                                 = default;  // default ctor
      OrderHandler( const OrderHandler &  original ) = default;  // copy ctor
      OrderHandler(       OrderHandler && original ) = default;  // move ctor

      // Exceptions
      struct OrderException : std::runtime_error {using runtime_error   ::runtime_error;   };
      struct   BadCommand     : OrderException   {using OrderException::OrderException;};

      // Object Factory returning a specialized object specific to the specified user and role
      static std::unique_ptr<OrderHandler> createOrder(std::list<Domain::ShoppingCart::Product *> cart);

      // Operations
      virtual double getTotal() = 0;
      virtual void orderInstruction(std::string address, std::string instructions) = 0;
      virtual void makePayment(int cardNumber, std::string expirationDate, int ccvNumber) = 0;

      // Destructor
      // Pure virtual destructor helps force the class to be abstract, but must still be implemented
      virtual ~OrderHandler() noexcept = 0;


    protected:
      // Copy assignment operators, protected to prevent mix derived-type assignments
      OrderHandler & operator=( const OrderHandler &  rhs ) = default;  // copy assignment
      OrderHandler & operator=(       OrderHandler && rhs ) = default;  // move assignment

  };    // class OrderHandler
} // namespace Domain::Order
