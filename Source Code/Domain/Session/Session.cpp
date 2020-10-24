#include "Domain/Session/Session.hpp"

#include <string>
#include <any>
#include <vector>

namespace  // anonymous (private) working area
{
  // 1)  First define all system events (commands, actions, requests, etc.)
  #define STUB(functionName)  std::any functionName( Domain::Session::SessionBase & /*session*/, const std::vector<std::string> & /*args*/ ) \
                              { return {}; }  // Stubbed for now

  STUB( manageActionLog           )
  STUB( manageFavorite            )
  STUB( manageOrder               )
  STUB( manageProductAvailability )
  STUB( manageReview              )
  STUB( manageRewardPoint         )
  STUB( manageShoppingCart        )
  STUB( purchaseProducts          )
  STUB( sortProduct               )

  std::any initiateCheckout( Domain::Session::SessionBase & session, const std::vector<std::string> & args )
  {
    std::string results;
    results += "\nQty\tProduct\t\tTotal\n";
    results += "1\tCheese Pizza\t$10.00\n";
    results += "\n\tSub Total:\t$10.00\n";
    return {results};
  }
  std::any orderInstructions( Domain::Session::SessionBase & session, const std::vector<std::string> & args )
  {
    // TO-DO  Verify there is such a book and the mark the book as being checked out by user
    std::string results;
    results += "\nQty\tProduct\t\tTotal\n";
    results += "1\tCheese Pizza\t$10.00\n";
    results += "\n\tSub Total:\t$10.00\n";
    if (args[0] == "1") {
      results += "\tDelivery Fee:\t$0.00\n";
      results += "\tTax:\t\t$0.85\n";
      results += "\tTotal:\t\t$10.85\n";
      results += "\nPick up order at store with instructions " + args[2] + "\n";
    } else {
      results += "\tDelivery Fee:\t$5.00\n";
      results += "\tTax:\t\t$0.85\n";
      results += "\tTotal:\t\t$15.85\n";
      results += "\nDeliver order to " + args[1] + " with instructions " + args[2] + "\n";
    }

    session._logger << "Products purchased.";
    return {results};
  }

  std::any checkoutBook( Domain::Session::SessionBase & session, const std::vector<std::string> & args )
  {
    // TO-DO  Verify there is such a book and the mark the book as being checked out by user
    std::string results = "Title \"" + args[0] + "\" checkout by \"" + session._credentials.userName + '"';
    session._logger << "checkoutBook:  " + results;
    return {results};
  }

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
    _commandDispatch = { {"Sort Products",        sortProduct        },
                         {"Manage Shopping Cart", manageShoppingCart },
                         {"Purchase Products",    purchaseProducts   },
                         {"Initate Checkout",     initiateCheckout   },
                         {"Order Instructions",   orderInstructions  },
                         {"Manage Reward Points", manageRewardPoint  },
                         {"Manage Reviews",       manageReview       },
                         {"Manage Favorites",     manageFavorite     }, };
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
