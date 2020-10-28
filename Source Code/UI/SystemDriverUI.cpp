#include "UI/SystemDriverUI.hpp"

#include "Domain/Session/SessionHandler.hpp"
// #include "Domain/Session/CustomerSession.hpp"
#include "TechnicalServices/Logging/LoggerHandler.hpp"

#include "Domain/ShoppingCart/ShoppingCartHandler.hpp"


namespace UI
{
  // Default constructor
  SystemDriverUI::SystemDriverUI()
  : _loggerPtr( TechnicalServices::Logging::LoggerHandler::create() )
  {
    _logger << "Contracted UI being used and has been successfully initialized";
  }




  // Destructor
  SystemDriverUI::~SystemDriverUI() noexcept
  {
    _logger << "Contracted UI shutdown successfully";
  }




  // Operations
  void SystemDriverUI::launch()
  {
    {
      _logger << "Starting scenario 1: Purchase Products";

      auto session    = Domain::Session::SessionHandler::createSession( {"James", "Vu", {"Customer"}} );
      auto role = session->getRole();
      if (role == "Customer") {
        auto cart   = Domain::ShoppingCart::ShoppingCartHandler::createShoppingCart();
        cart->addProduct("Pizza", 1);
        auto order = cart->initiateCheckout();
        order->orderInstruction("123 Street", "Keep warm");
        auto total = order->getTotal();
        order->makePayment(1234, "12/06", 567);
      }
      //session->singOff();

      _logger << "Completed scenario 1";
    }
  }
}    // namespace UI
