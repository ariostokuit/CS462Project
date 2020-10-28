#pragma once

#include <any>
#include <stdexcept>
#include <memory>
#include <string>
#include <vector>
#include <list>

#include "TechnicalServices/Logging/LoggerHandler.hpp"
#include "Domain/ShoppingCart/ShoppingCartHandler.hpp"
#include "Domain/ShoppingCart/Product.hpp"
#include "Domain/Order/OrderHandler.hpp"

namespace Domain::ShoppingCart
{
  class CustomerShoppingCart : public ShoppingCartHandler
  {
    public:
      // using ShoppingCartHandler::ShoppingCartHandler;  // inherit constructors
      CustomerShoppingCart() {
        _logger << "Customer Shopping Cart being used and has been successfully initialized";
      }

      // Operations
      void addProduct(std::string product, int quantity);
      void removeProduct(std::string product, int quantity);
      std::unique_ptr<Domain::Order::OrderHandler> initiateCheckout();
      // Destructor
      // Pure virtual destructor helps force the class to be abstract, but must still be implemented
      ~CustomerShoppingCart() noexcept override;
    private:
      std::shared_ptr<TechnicalServices::Logging::LoggerHandler> _loggerPtr = TechnicalServices::Logging::LoggerHandler::create();
      TechnicalServices::Logging::LoggerHandler &                _logger    = *_loggerPtr;
      std::list<Domain::ShoppingCart::Product *> _cart;
  }; // class BorrowerShoppingCart

  /*****************************************************************************
  ** Inline implementations
  ******************************************************************************/
  inline CustomerShoppingCart::~CustomerShoppingCart() noexcept
  {
    _logger << "Customer Shopping Cart shutdown successfully";
  }

  inline void CustomerShoppingCart::addProduct(std::string product, int quantity)
  {
    if (product == "Pizza") {
      for (unsigned int i = 0; i < quantity; ++i) {
        _cart.push_back(new Domain::ShoppingCart::Pizza());
      }
    } else if (product == "Breadstick") {
      for (unsigned int i = 0; i < quantity; ++i) {
        _cart.push_back(new Domain::ShoppingCart::Breadstick());
      }
    } else if (product == "Coca Cola") {
      for (unsigned int i = 0; i < quantity; ++i) {
        _cart.push_back(new Domain::ShoppingCart::CocaCola());
      }
    }
    _logger << "Responding to addProduct request with parameters: " + product + ", " + std::to_string(quantity);
    _logger << "Added " + std::to_string(quantity) + " " + product + " to Customer Shopping Cart";
    return;
  }

  inline void CustomerShoppingCart::removeProduct(std::string product, int quantity)
  {
    return;
  }

  inline std::unique_ptr<Domain::Order::OrderHandler> CustomerShoppingCart::initiateCheckout()
  {
    auto order = Domain::Order::OrderHandler::createOrder(_cart);
    return order;
  }

} // namespace Domain::Library
