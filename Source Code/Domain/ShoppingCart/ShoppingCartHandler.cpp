#include "Domain/ShoppingCart/ShoppingCartHandler.hpp"

#include <memory>       // unique_ptr, make_unique<>()

#include "Domain/ShoppingCart/CustomerShoppingCart.hpp"

namespace Domain::ShoppingCart
{
  ShoppingCartHandler::~ShoppingCartHandler() noexcept = default;

  std::unique_ptr<ShoppingCartHandler> ShoppingCartHandler::createShoppingCart()
  {
    return std::make_unique<Domain::ShoppingCart::CustomerShoppingCart> ();
  }
} // namespace Domain::ShoppingCart
