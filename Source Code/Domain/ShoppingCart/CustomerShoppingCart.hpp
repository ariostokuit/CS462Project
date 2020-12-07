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
#include "Domain/ShoppingCart/Pizza.hpp"
#include "Domain/ShoppingCart/Breadstick.hpp"
#include "Domain/ShoppingCart/CocaCola.hpp"
#include "Domain/Order/OrderHandler.hpp"
#include "TechnicalServices/Persistence/PersistenceHandler.hpp"

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
      std::vector<std::string> viewProducts();
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
      for (int i = 0; i < quantity; ++i) {
        _cart.push_back(PizzaFactory::createProduct());
      }
    } else if (product == "Breadstick") {
      for (int i = 0; i < quantity; ++i) {
        _cart.push_back(BreadstickFactory::createProduct());
      }
    } else if (product == "Coca Cola") {
      for (int i = 0; i < quantity; ++i) {
        _cart.push_back(CocaColaFactory::createProduct());
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

  inline std::vector<std::string> CustomerShoppingCart::viewProducts()
  {
    std::vector<std::string> productList = {};
    auto & persistantData = TechnicalServices::Persistence::PersistenceHandler::instance();
    auto requestedProductList = persistantData["Component.Product"];
    _logger << "Responding to viewProducts request with parameters: ";
    _logger << "Product list:";
    if ( requestedProductList == "All") {
      productList.push_back("Pizza");      _logger << "Pizza";
      productList.push_back("Breadstick"); _logger << "Breadstick";
      productList.push_back("CocaCola");   _logger << "CocaCola";
    } else if ( requestedProductList == "Pizza") {
      productList.push_back("Pizza");      _logger << "Pizza";
    } else if ( requestedProductList == "Breadstick") {
      productList.push_back("Breadstick"); _logger << "Breadstick";
    } else if ( requestedProductList == "CocaCola") {
      productList.push_back("CocaCola");   _logger << "CocaCola";
    } else if ( requestedProductList == "Pizza Breadstick") {
      productList.push_back("Pizza");      _logger << "Pizza";
      productList.push_back("Breadstick"); _logger << "Breadstick";
    } else if ( requestedProductList == "Pizza CocaCola") {
      productList.push_back("Pizza");      _logger << "Pizza";
      productList.push_back("CocaCola");   _logger << "CocaCola";
    } else if ( requestedProductList == "Breadstick CocaCola") {
      productList.push_back("Breadstick"); _logger << "Breadstick";
      productList.push_back("CocaCola");   _logger << "CocaCola";
    }
    return productList;
  }

  inline std::unique_ptr<Domain::Order::OrderHandler> CustomerShoppingCart::initiateCheckout()
  {
    _logger << "Responding to initiateCheckout request with parameters: ";
    std::vector<std::string> prodNames;
    for (auto it = _cart.begin(); it != _cart.end(); ++it) {
      prodNames.push_back((*it)->getName());
    }
    auto order = Domain::Order::OrderHandler::createOrder(prodNames);
    _cart.clear();
    _logger << "Cart is emptied";
    return order;
  }

} // namespace Domain::Library
