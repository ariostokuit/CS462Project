#include "Domain/Session/Session.hpp"

#include <string>
#include <any>
#include <vector>

namespace  // anonymous (private) working area
{
  // 1)  First define all system events (commands, actions, requests, etc.)
  #define STUB(functionName)  std::any functionName( Domain::Session::SessionBase & /*session*/, const std::vector<std::string> & /*args*/ ) \
                              { return {}; }  // Stubbed for now

  // STUB( addProduct                )
  // STUB( removeProduct             )
  // STUB( viewProduct               )
  // STUB( viewShoppingCart          )
  // STUB( initiateCheckout          )
  // STUB( orderInstructions         )
  // STUB( makePayment               )
  STUB( viewRewardPoints          )
  STUB( spendRewardPoints         )
  STUB( viewRewards               )
  STUB( applyRewardToPurchase     )
  STUB( manageOrder               )
  STUB( manageActionLog           )
  STUB( manageProductAvailability )

  std::any addProduct( Domain::Session::SessionBase & session, const std::vector<std::string> & args )
  {
    // still need to call addProduct from ShoppingCart
    std::string results;

    // check if quantity is 1 or more
    int quantity = std::stoi(args[1], nullptr, 10);
    if (quantity < 1) {
      results += "Quantity is less than 1. Please input an integer 1 or greater.";
      session._logger << results;
      return {results};
    }
    // hard coded values for now
    int selection = std::stoi(args[0], nullptr, 10);
    // might use switch statement later
    if (selection == 1) {
      results += "Adding " + args[1] + " Pizza to shopping cart.";
    } else if (selection == 2) {
      results += "Adding " + args[1] + " Breadstick to shopping cart.";
    } else if (selection == 3) {
      results += "Adding " + args[1] + " Coca Cola to shopping cart.";
    } else { // check if customer input something else
      results += "Please enter the number or product name.";
    }
    session._logger << results;
    return {results};
  }

  std::any removeProduct( Domain::Session::SessionBase & session, const std::vector<std::string> & args )
  {
    // still need to call removeProduct from ShoppingCart
    std::string results;
    // check if quantity is 1 or more
    int quantity = std::stoi(args[1], nullptr, 10);
    if (quantity < 1) {
      results += "Quantity is less than 1. Please input an integer 1 or greater.";
      session._logger << results;
      return {results};
    }
    // hard coded values for now
    int selection = std::stoi(args[0], nullptr, 10);
    // might use switch statement later
    if (selection == 0) {
      results += "Removing " + args[1] + " Pizza from shopping cart.";
    } else if (selection == 1) {
      results += "Removing " + args[1] + " Breadstick from shopping cart.";
    } else if (selection == 2) {
      results += "Removing " + args[1] + " Coca Cola from shopping cart.";
    } else { // check if customer input something else
      results += "Please enter the number or product name.";
    }
    session._logger << results;
    return {results};
  }

  std::any viewProduct( Domain::Session::SessionBase & session, const std::vector<std::string> & args )
  {
    // should call viewProduct from ShoppingCart
    // results are hard coded for now
    std::string results;
    results += "\n1. Pizza\n";
    results += "2. Breadstick\n";
    results += "3. Coca Cola\n";
    session._logger << "Products viewed";
    return {results};
  }

  std::any viewShoppingCart( Domain::Session::SessionBase & session, const std::vector<std::string> & args )
  {
    // should call viewShoppingCart from ShoppingCart
    // results are hard coded for now
    std::string results;
    results += "\nShopping Cart:\n";
    results += "Qty\tProduct Name\n";
    results += "1\tPizza\n";
    results += "1\tBreadstick\n";
    results += "1\tCoca Cola\n";
    session._logger << "Shopping Cart viewed";
    return {results};
  }
  std::any initiateCheckout( Domain::Session::SessionBase & session, const std::vector<std::string> & args )
  {
    std::string results;
    results += "\nInitiating checkout...\n\n";
    results += "Order\n";
    results += "\nQty\tProduct\t\tTotal\n";
    results += "1\tPizza\t\t$10.00\n";
    results += "1\tBreadstick\t$5.00\n";
    results += "1\tCoca Cola\t$1.00\n";
    results += "\n\tSub Total:\t$16.00\n";
    results += "\tTax:\t\t$1.36\n";
    session._logger << "Chectout initated";
    return {results};
  }

  std::any orderInstructions( Domain::Session::SessionBase & session, const std::vector<std::string> & args )
  {
    std::string results;
    results += "Order\n";
    results += "\nQty\tProduct\t\tTotal\n";
    results += "1\tPizza\t\t$10.00\n";
    results += "1\tBreadstick\t$5.00\n";
    results += "1\tCoca Cola\t$1.00\n";
    results += "\n\tSub Total:\t$16.00\n";
    results += "\tTax:\t\t$1.36\n";
    if (args[0] == "1") {
      results += "\tDelivery Fee:\t$0.00\n";
      results += "\tTotal:\t\t$17.36\n";
      results += "\nPick up order at store with instructions \"" + args[2] + "\"\n";
      session._logger << "Pick up order at store with instructions " + args[2];
    } else {
      results += "\tDelivery Fee:\t$5.00\n";
      results += "\tTotal:\t\t$22.36\n";
      results += "\nDeliver order to " + args[1] + " with instructions \"" + args[2] + "\"\n";
      session._logger << "Deliver order to " + args[1] + " with instructions \"" + args[2] + "\"";
    }

    return {results};
  }

  std::any makePayment( Domain::Session::SessionBase & session, const std::vector<std::string> & args )
  {
    std::string results;

    if (args[0] == "1") {
      // insert card authenticator here
      results += "Order paid with card. Payment successful.";
    } else {
      results += "Order paid with cash. Payment successful.";
    }

    session._logger << results;
    return {results};
  }

  // std::any checkoutBook( Domain::Session::SessionBase & session, const std::vector<std::string> & args )
  // {
  //   // TO-DO  Verify there is such a book and the mark the book as being checked out by user
  //   std::string results = "Title \"" + args[0] + "\" checkout by \"" + session._credentials.userName + '"';
  //   session._logger << "checkoutBook:  " + results;
  //   return {results};
  // }

}    // anonymous (private) working area

namespace Domain::Session
{
  SessionBase::SessionBase( const std::string & description, const UserCredentials & credentials ) : _credentials( credentials ), _name( description )
  {
    _logger << "Session \"" + _name + "\" being used and has been successfully initialized";
  }

  SessionBase::~SessionBase() noexcept
  {
    _logger << "Session \"" + _name + "\" shutdown successfully";
  }

  std::vector<std::string> SessionBase::getCommands()
  {
    std::vector<std::string> availableCommands;
    availableCommands.reserve( _commandDispatch.size() );

    for( const auto & [command, function] : _commandDispatch ) availableCommands.emplace_back( command );

    return availableCommands;
  }

  std::any SessionBase::executeCommand( const std::string & command, const std::vector<std::string> & args )
  {
    std::string parameters;
    for( const auto & arg : args )  parameters += '"' + arg + "\"  ";
    _logger << "Responding to \"" + command + "\" request with parameters: " + parameters;

    auto it = _commandDispatch.find( command );
    if( it == _commandDispatch.end() )
    {
      std::string message = __func__;
      message += " attempt to execute \"" + command + "\" failed, no such command";

      _logger << message;
      throw BadCommand( message );
    }

    auto results = it->second( *this, args);

    if( results.has_value() )
    {
      // The type of result depends on function called.  Let's assume strings for now ...
      _logger << "Responding with: \"" + std::any_cast<const std::string &>( results ) + '"';
    }

    return results;
  }

  // 2) Now map the above system events to roles authorized to make such a request.  Many roles can request the same event, and many
  //    events can be requested by a single role.
  CustomerSession::CustomerSession( const UserCredentials & credentials ) : SessionBase( "Customer", credentials )
  {
    _commandDispatch = { {"Add Product to Shopping Cart",      addProduct           },
                         {"Remove Product from Shopping Cart", removeProduct        },
                         {"View Products",                     viewProduct          },
                         {"View Shopping Cart",                viewShoppingCart     },
                         {"Initiate Checkout",                 initiateCheckout     },
                         {"Select Delivery Options",           orderInstructions    },
                         {"Pay for Products",                  makePayment          },
                         {"View Reward Points",                viewRewardPoints     },
                         {"Spend Reward Points",               spendRewardPoints    },
                         {"View Rewards",                      viewRewards          },
                         {"Apply Rewards to Purchase",         applyRewardToPurchase} };
  }

  StoreEmployeeSession::StoreEmployeeSession( const UserCredentials & credentials ) : SessionBase( "Store Employee", credentials )
  {
    _commandDispatch = { {"Manage Orders", manageOrder} };
  }

  ITEmployeeSession::ITEmployeeSession( const UserCredentials & credentials ) : SessionBase( "IT Employee", credentials )
  {
    _commandDispatch = { {"Manage Action Log", manageActionLog} };
  }

  CorporateEmployeeSession::CorporateEmployeeSession( const UserCredentials & credentials ) : SessionBase( "Corporate Employee", credentials )
  {
    _commandDispatch = { {"Manage Product Availability", manageProductAvailability} };
  }
}    // namespace Domain::Session
