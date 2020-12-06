#include <memory>    // unique_ptr

#include "TechnicalServices/Payment/PaymentHandler.hpp"
#include "TechnicalServices/Payment/VisaPayment.hpp"
#include "TechnicalServices/Payment/AmericanExpressPayment.hpp"
#include "TechnicalServices/Persistence/PersistenceHandler.hpp"


namespace TechnicalServices::Payment
{
  std::unique_ptr<PaymentHandler> PaymentHandler::create()
  {
    auto & persistantData  = TechnicalServices::Persistence::PersistenceHandler::instance();
    auto   requestedPayment = persistantData["Component.Payment"];

    if( requestedPayment == "Visa" )             return std::make_unique<VisaPayment>();
    if( requestedPayment == "American Express" ) return std::make_unique<AmericanExpressPayment>();

    throw BadPaymentRequest( "Unknown Payment object requested: \"" + requestedPayment + "\"\n  detected in function " + __func__ );
  }
}    // namespace TechnicalServices::Payment
