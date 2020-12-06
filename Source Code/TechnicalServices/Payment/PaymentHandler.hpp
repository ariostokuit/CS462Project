#pragma once
#include <stdexcept>  // runtime_error
#include <iostream>
#include <memory>     // unique_ptr
#include <string>


namespace TechnicalServices::Payment
{
  class PaymentHandler
  {
    public:
      // Exceptions
      struct PaymentException    : std::runtime_error {using runtime_error  ::runtime_error;};
      struct   BadPaymentRequest : PaymentException    {using PaymentException::PaymentException;     };

      // Payment Factory, throws BadPaymentRequest
      static std::unique_ptr<PaymentHandler> create();    // must be static


      // Operations
      virtual bool executePayment( const int cardNumber, const std::string expirationDate, const int ccvNumber ) = 0;


      // Destructor
      // Pure virtual destructor helps force the class to be abstract, but must still be implemented
      virtual ~PaymentHandler() noexcept = 0;


    protected:
      // Copy assignment operators, protected to prevent mix derived-type assignments
      PaymentHandler & operator=( const PaymentHandler  & rhs ) = delete;    // copy assignment
      PaymentHandler & operator=(       PaymentHandler && rhs ) = delete;    // move assignment
  };





  /*****************************************************************************
  ** Inline default implementations
  ******************************************************************************/
  inline PaymentHandler::~PaymentHandler() noexcept = default;
} // namespace TechnicalServices::Payment
