#include "Domain/Order/OrderHandler.hpp"

#include <memory>       // unique_ptr, make_unique<>()

#include "Domain/Order/CustomerOrder.hpp"

namespace Domain::Order
{
  OrderHandler::~OrderHandler() noexcept = default;

  std::unique_ptr<OrderHandler> OrderHandler::createOrder(std::vector<std::string> cart)
  {
    return std::make_unique<Domain::Order::CustomerOrder> (cart);
  }
} // namespace Domain::Order
