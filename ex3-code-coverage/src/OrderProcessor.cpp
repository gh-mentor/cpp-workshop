#include "OrderProcessor.h"

// OrderItem implementation
OrderItem::OrderItem(int product_id, int quantity, double price)
    : product_id(product_id), quantity(quantity), price(price) {}

int OrderItem::getProductID() const {
    return product_id;
}

int OrderItem::getQuantity() const {
    return quantity;
}

double OrderItem::getPrice() const {
    return price;
}

// Customer implementation
Customer::Customer(const std::string& name) : name(name) {}

std::string Customer::getName() const {
    return name;
}

// Order implementation
Order::Order(std::shared_ptr<Customer> customer, const std::vector<OrderItem>& items)
    : customer(customer), items(items) {}

std::shared_ptr<Customer> Order::getCustomer() const {
    return customer;
}

const std::vector<OrderItem>& Order::getItems() const {
    return items;
}

// OrderProcessor implementation
void OrderProcessor::processOrder(const std::shared_ptr<Order>& order) {
    validateOrder(order);

    for (const auto& item : order->getItems()) {
        if (item.getProductID() == 0) {
            if (item.getPrice() > 100) {
                std::cout << "High value item with no product ID." << std::endl;
            } else {
                std::cout << "Low value item with no product ID." << std::endl;
            }
        } else {
            if (item.getPrice() > 100) {
                std::cout << "High value item with product ID." << std::endl;
            } else {
                std::cout << "Low value item with product ID." << std::endl;
            }
        }
    }

    processPayment(order);
}

void OrderProcessor::processPayment(const std::shared_ptr<Order>& order) {
    std::cout << "Processing payment for order." << std::endl;
}

void OrderProcessor::validateOrder(const std::shared_ptr<Order>& order) {
    if (!order) {
        throw std::invalid_argument("order cannot be None");
    }

    if (order->getItems().empty()) {
        throw std::invalid_argument("Order must have at least one item.");
    }

    for (const auto& item : order->getItems()) {
        if (item.getQuantity() <= 0) {
            throw std::invalid_argument("Item quantity must be greater than zero.");
        }
    }

    if (!order->getCustomer()) {
        throw std::invalid_argument("Order must have a customer.");
    }
}