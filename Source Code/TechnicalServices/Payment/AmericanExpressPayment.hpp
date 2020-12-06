#pragma once

#include <string>

#include "TechnicalServices/Payment/PaymentHandler.hpp"
#include "TechnicalServices/Logging/SimpleLogger.hpp"


namespace TechnicalServices::Payment
{
  class AmericanExpressPayment : public TechnicalServices::Payment::PaymentHandler
  {
    public:
      //Constructors
      AmericanExpressPayment() {
        _logger << "AmericanExpress Payment being used and has been successfully initialized";
      }

      // Operations
      bool executePayment( const int cardNumber, const std::string expirationDate, const int ccvNumber );

      // Destructor
      ~AmericanExpressPayment() noexcept override;


    protected:
    private:
      std::unique_ptr<TechnicalServices::Logging::LoggerHandler> _loggerPtr;
      TechnicalServices::Logging::LoggerHandler & _logger = *_loggerPtr;
  }; // class AmericanExpressPayment

  /*****************************************************************************
  ** Inline implementations
  ******************************************************************************/

  inline AmericanExpressPayment::~AmericanExpressPayment() noexcept
  {
    _logger << "AmericanExpress Payment shutdown successfully";
  }

  inline bool AmericanExpressPayment::executePayment( const int cardNumber, const std::string expirationDate, const int ccvNumber )
  {
    _logger << "AmericanExpress Payment successfully executed";
    return true;
  }
} // namespace TechnicalServices::Payment
