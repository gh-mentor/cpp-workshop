#ifndef ORDERPROCESSOR_H
#define ORDERPROCESSOR_H

#include <iostream>
#include <vector>
#include <stdexcept>
#include <memory>

class OrderItem {
public:
    OrderItem(int product_id, int quantity, double price);
    int getProductID() const;
    int getQuantity() const;
    double getPrice() const;

private:
    int product_id;
    int quantity;
    double price;
};

class Customer {
public:
    Customer(const std::string& name);
    std::string getName() const;

private:
    std::string name;
};

class Order {
public:
    Order(std::shared_ptr<Customer> customer, const std::vector<OrderItem>& items);
    std::shared_ptr<Customer> getCustomer() const;
    const std::vector<OrderItem>& getItems() const;

private:
    std::shared_ptr<Customer> customer;
    std::vector<OrderItem> items;
};

class OrderProcessor {
public:
    void processOrder(const std::shared_ptr<Order>& order);
    void processPayment(const std::shared_ptr<Order>& order);

private:
    void validateOrder(const std::shared_ptr<Order>& order);
};

#endif // ORDERPROCESSOR_H