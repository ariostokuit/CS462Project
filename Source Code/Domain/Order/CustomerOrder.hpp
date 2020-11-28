#pragma once

#include <any>
#include <stdexcept>
#include <memory>
#include <string>
#include <vector>

#include "TechnicalServices/Logging/LoggerHandler.hpp"
#include "Domain/Order/OrderHandler.hpp"
#include "Domain/ShoppingCart/Product.hpp"

namespace Domain::Order
{
  class CustomerOrder : public OrderHandler
  {
    public:
      // using OrderHandler::OrderHandler;  // inherit constructors
      CustomerOrder(std::vector<std::string> cart) {
        _logger << "Customer Order being used and has been successfully initialized";
        _subtotal = 0;
        for (auto it = cart.begin(); it != cart.end(); ++it) {
          if (*it == "Pizza") {
            _subtotal += 10;
          } else if (*it == "Breadstick") {
            _subtotal += 5;
          } else if (*it == "Coca Cola") {
            _subtotal += 1;
          } else {
            _logger << *it + " is not a product";
          }

        }
        _tax = _subtotal * _taxrate;
      }

      // Operations
      double calculateTotal();
      void setOrderInstruction(std::string address, std::string instructions);
      std::string makePayment(int cardNumber, std::string expirationDate, int ccvNumber);
      // Destructor
      // Pure virtual destructor helps force the class to be abstract, but must still be implemented
      ~CustomerOrder() noexcept override;
    private:
      std::shared_ptr<TechnicalServices::Logging::LoggerHandler> _loggerPtr = TechnicalServices::Logging::LoggerHandler::create();
      TechnicalServices::Logging::LoggerHandler &                _logger    = *_loggerPtr;
      // need to change attribute initalization later
      double      _taxrate     = 0.085;
      double      _deliveryFee = 5.00;
      double      _total;
      double      _subtotal;
      double      _tax;
      bool        _delivery    = false;
      std::string _address;
      std::string _instructions;
      // std::list<Domain::Order::Product *> cart;
  }; // class BorrowerOrder

  /*****************************************************************************
  ** Inline implementations
  ******************************************************************************/
  inline CustomerOrder::~CustomerOrder() noexcept
  {
    _logger << "Customer Order shutdown successfully";
  }

  inline double CustomerOrder::calculateTotal()
  {
    _logger << "Responding to calculateTotal request with parameters: ";
    _total = 0.0;
    if (_delivery) { _total += _deliveryFee; }
    _total += _subtotal;
    _total += _tax;
    _logger << "Total is " + std::to_string(_total);
    return _total;
  }

  inline void CustomerOrder::setOrderInstruction(std::string address, std::string instructions)
  {
    _address      = address;
    // address is not empty, make delivery true
    if (address != "") {
      _delivery = true;
    }
    _instructions = instructions;
    _logger << "Responding to setOrderInstruction request with parameters: " + address + ", " + instructions;
    _logger << "Order instructions received";
    return;
  }

  inline std::string CustomerOrder::makePayment(int cardNumber, std::string expirationDate, int ccvNumber)
  {
    _logger << "Responding to makePayment request with parameters: " + std::to_string(cardNumber) + ", " + expirationDate + ", " + std::to_string(ccvNumber);

    std::string results =  "Payment successfully made";
    _logger << "Responding with: " + results;
    return results;
  }

} // namespace Domain::Library
