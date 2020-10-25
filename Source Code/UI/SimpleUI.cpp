#include "UI/SimpleUI.hpp"

#include <any>         // any_cast()
#include <iomanip>     // setw()
#include <iostream>    // streamsize
#include <limits>      // numeric_limits
#include <memory>      // unique_ptr, make_unique<>()
#include <string>      // string, getline()
#include <vector>

#include "Domain/Library/Books.hpp"    // Include for now - will replace next increment
#include "Domain/Session/SessionHandler.hpp"

#include "TechnicalServices/Logging/LoggerHandler.hpp"
#include "TechnicalServices/Persistence/PersistenceHandler.hpp"




namespace UI
{
  // Default constructor
  SimpleUI::SimpleUI()
  : _bookHandler   ( std::make_unique<Domain::Library::Books>()                     ),   // will replace these with factory calls in the next increment
    _loggerPtr     ( TechnicalServices::Logging::LoggerHandler::create()            ),
    _persistentData( TechnicalServices::Persistence::PersistenceHandler::instance() )
  {
    _logger << "Simple UI being used and has been successfully initialized";
  }




  // Destructor
  SimpleUI::~SimpleUI() noexcept
  {
    _logger << "Simple UI shutdown successfully";
  }




  // Operations
  void SimpleUI::launch()
  {
    // 1) Fetch Role legal value list
    std::vector<std::string> roleLegalValues = _persistentData.findRoles();


    // 2) Present login screen to user and get username, password, and valid role
    Domain::Session::UserCredentials credentials  = {"", "", {""}};           // ensures roles[0] exists
    auto &                           selectedRole = credentials.roles[0];     // convenience alias

    std::unique_ptr<Domain::Session::SessionHandler> sessionControl;

    do
    {
      std::cin.ignore(  std::numeric_limits<std::streamsize>::max(), '\n' );

      std::cout << "  username: ";
      std::getline( std::cin, credentials.userName );

      std::cout << "  password: ";
      std::getline( std::cin, credentials.passPhrase );

      unsigned menuSelection;
      do
      {
        for( unsigned i = 0; i != roleLegalValues.size(); ++i )   std::cout << std::setw( 2 ) << i << " - " << roleLegalValues[i] << '\n';
        std::cout << "  role (0-" << roleLegalValues.size()-1 << "): ";
        std::cin  >> menuSelection;
      } while( menuSelection >= roleLegalValues.size() );

      selectedRole = roleLegalValues[menuSelection];


      // 3) Validate user is authorized for this role, and if so create session
      sessionControl = Domain::Session::SessionHandler::createSession( credentials );
      if( sessionControl != nullptr )
      {
        _logger << "Login Successful for \"" + credentials.userName + "\" as role \"" + selectedRole + "\"";
        break;
      }

      std::cout << "** Login failed\n";
      _logger << "Login failure for \"" + credentials.userName + "\" as role \"" + selectedRole + "\"";

    } while( true );


    // 4) Fetch functionality options for this role
    do
    {
      auto        commands = sessionControl->getCommands();
      std::string selectedCommand;
      unsigned    menuSelection;

      do
      {
        for( unsigned i = 0; i != commands.size(); ++i ) std::cout << std::setw( 2 ) << i << " - " << commands[i] << '\n';
        std::cout << std::setw( 2 ) << commands.size() << " - " << "Quit\n";

        std::cout << "  action (0-" << commands.size() << "): ";
        std::cin >> menuSelection;
      } while( menuSelection > commands.size() );

      if( menuSelection == commands.size() ) break;

      selectedCommand = commands[menuSelection];
      _logger << "Command selected \"" + selectedCommand + '"';


      /******************************************************************************************************************************
      **  5) The user interface will collect relevant information to execute the chosen command.  This section requires the UI to
      **     know what information to collect, and hence what the available commands are.  Our goal is loose (minimal) coupling, not
      **     no coupling. This can be achieved in a variety of ways, but one common way is to pass strings instead of strong typed
      **     parameters.
      ******************************************************************************************************************************/
      // if( selectedCommand == "Checkout Book" )
      // {
      //   std::vector<std::string> parameters( 3 );
      //
      //   std::cout << " Enter book's title:  ";  std::cin >> std::ws;  std::getline( std::cin, parameters[0] );
      //   std::cout << " Enter book's author: ";  std::cin >> std::ws;  std::getline( std::cin, parameters[1] );
      //   std::cout << " Enter book's ISBN:   ";  std::cin >> std::ws;  std::getline( std::cin, parameters[2] );
      //
      //   auto results = sessionControl->executeCommand( selectedCommand, parameters );
      //   if( results.has_value() ) _logger << "Received reply: \"" + std::any_cast<const std::string &>( results ) + '"';
      // }
      if ( selectedCommand == "Add Product to Shopping Cart" )
      {
        std::vector<std::string> emptyVector( 0 );
        std::vector<std::string> parameters( 2 );

        std::cout << "Which product do you want to add to your shopping cart? Please enter the number.\n";
        // prints out list of products
        auto productList = sessionControl->executeCommand( "View Products", emptyVector );
        if( productList.has_value() ) _logger << "Received reply: \"" + std::any_cast<const std::string &>( productList ) + '"';
        // Domain::Session::S
        std::cin >> std::ws;  std::getline( std::cin, parameters[0] );

        std::cout << "How many do you want to add to the shopping cart? ";
        std::cin >> std::ws;  std::getline( std::cin, parameters[1] );
        // calls add product
        auto results = sessionControl->executeCommand( selectedCommand, parameters );
        if( results.has_value() ) _logger << "Received reply: \"" + std::any_cast<const std::string &>( results ) + '"';
      }
      else if( selectedCommand == "Remove Product from Shopping Cart" )
      {
        std::vector<std::string> emptyVector( 0 );
        std::vector<std::string> parameters( 2 );

        std::cout << "Which product do you want to remove from your shopping cart? Please enter the number.\n";
        // prints out products in shopping cart
        auto shoppingCart = sessionControl->executeCommand( "View Shopping Cart", emptyVector );
        if( shoppingCart.has_value() ) _logger << "Received reply: \"" + std::any_cast<const std::string &>( shoppingCart ) + '"';
        std::cin >> std::ws;  std::getline( std::cin, parameters[0] );

        std::cout << "How many do you want to remove from the shopping cart? ";
        std::cin >> std::ws;  std::getline( std::cin, parameters[1] );
        // calls remove product
        auto results = sessionControl->executeCommand( selectedCommand, parameters );
        if( results.has_value() ) _logger << "Received reply: \"" + std::any_cast<const std::string &>( results ) + '"';
      }
      else if( selectedCommand == "View Products" )
      {
        std::vector<std::string> emptyVector( 0 );

        auto results = sessionControl->executeCommand( selectedCommand, emptyVector );
        if( results.has_value() ) _logger << "Received reply: \"" + std::any_cast<const std::string &>( results ) + '"';
      }
      else if( selectedCommand == "View Shopping Cart" )
      {
        std::vector<std::string> emptyVector( 0 );

        auto results = sessionControl->executeCommand( selectedCommand, emptyVector );
        if( results.has_value() ) _logger << "Received reply: \"" + std::any_cast<const std::string &>( results ) + '"';
      }
      else if( selectedCommand == "Initiate Checkout" )
      {
        std::vector<std::string> emptyVector( 0 );

        auto results = sessionControl->executeCommand( selectedCommand, emptyVector );
        if( results.has_value() ) _logger << "Received reply: \"" + std::any_cast<const std::string &>( results ) + '"';
      }
      else if( selectedCommand == "Select Delivery Options" )
      {
        std::vector<std::string> parameters( 3 );

        std::cout << "How do you want your order to be delivered?\n";
        std::cout << "1. Pick up at store\n";
        std::cout << "2. Delivered to specific address\n";
        std::cin >> std::ws;  std::getline( std::cin, parameters[0] );

        if (parameters[0] == "2") {
          std::cout << "Enter address to be delivered to: ";
          std::cin >> std::ws;  std::getline( std::cin, parameters[1] );
        }

        std::cout << "Enter miscellaneous instructions for delivery: ";
        std::cin >> std::ws;  std::getline( std::cin, parameters[2] );

        auto results = sessionControl->executeCommand( selectedCommand, parameters );
        if( results.has_value() ) _logger << "Received reply: \"" + std::any_cast<const std::string &>( results ) + '"';
      }
      else if( selectedCommand == "Pay for Products" )
      {
        std::vector<std::string> parameters( 4 );

        std::cout << "How do you want to pay for your order?\n";
        std::cout << "1. Credit/Debit\n";
        std::cout << "2. Cash\n";
        std::cin >> std::ws;  std::getline( std::cin, parameters[0] );

        if (parameters[0] == "1") {
          std::cout << "Enter your card number: ";
          std::cin >> std::ws;  std::getline( std::cin, parameters[1] );
          std::cout << "Enter your CCV number on the back of the card: ";
          std::cin >> std::ws;  std::getline( std::cin, parameters[2] );
          std::cout << "Enter the card's expiration date in the format MM/YY: ";
          std::cin >> std::ws;  std::getline( std::cin, parameters[3] );
        }

        auto results = sessionControl->executeCommand( selectedCommand, parameters );
        if( results.has_value() ) _logger << "Received reply: \"" + std::any_cast<const std::string &>( results ) + '"';
      }
      else if( selectedCommand == "Another command" ) /* ... */ {}

      else sessionControl->executeCommand( selectedCommand, {} );
    } while( true );

    _logger << "Ending session and terminating";
  }
}
