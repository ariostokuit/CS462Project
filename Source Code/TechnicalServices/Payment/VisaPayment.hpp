#pragma once

#include <string>
#include <memory>

#include "TechnicalServices/Payment/PaymentHandler.hpp"
#include "TechnicalServices/Logging/SimpleLogger.hpp"


namespace TechnicalServices::Payment
{
  class VisaPayment : public TechnicalServices::Payment::PaymentHandler
  {
    public:
      //Constructors
      VisaPayment() : _loggerPtr( std::make_unique<TechnicalServices::Logging::SimpleLogger>() )
      {
        _logger << "Visa Payment being used and has been successfully initialized";
      }

      // Operations
      bool executePayment( const int cardNumber, const std::string expirationDate, const int ccvNumber );

      // Destructor
      ~VisaPayment() noexcept override;


    protected:
    private:
      std::unique_ptr<TechnicalServices::Logging::LoggerHandler> _loggerPtr;
      TechnicalServices::Logging::LoggerHandler & _logger = *_loggerPtr;
  }; // class VisaPayment

  /*****************************************************************************
  ** Inline implementations
  ******************************************************************************/

  inline VisaPayment::~VisaPayment() noexcept
  {
    _logger << "Visa Payment shutdown successfully";
  }

  inline bool VisaPayment::executePayment( const int cardNumber, const std::string expirationDate, const int ccvNumber )
  {
    _logger << "Visa Payment successfully executed";
    return true;
  }
} // namespace TechnicalServices::Payment
