#include "store.h"
#include <iostream>

using namespace std;

Store::Store()
{
    num_customers_ = 0;
    num_products_ = 0;
    num_transactions_ = 0;

    for (int i = 0; i < 100; i++)
    {
        products_[i] = product();
        transactions_[i] = transaction();
    }
}

void Store::num_customers(int count)
{
    if (count >= 0 && count <= 100)
        num_customers_ = count;
}

int Store::num_customers()
{
    return num_customers_;
}

void Store::num_products(int count)
{
    if (count >= 0 && count <= 100)
        num_products_ = count;
}

int Store::num_products()
{
    return num_products_;
}

void Store::num_transactions(int count)
{
    if (count >= 0 && count <= 100)
        num_transactions_ = count;
}

int Store::num_transactions()
{
    return num_transactions_;
}

bool Store::add_customer(Person customer)
{
    if (num_customers_ >= 100)
        return false;

    customers_[num_customers_] = customer;
    num_customers_++;

    return true;
}

int Store::find_customer(Person customer)
{
    for (int i = 0; i < num_customers_; i++)
    {
        if (customers_[i].name() == customer.name() &&
            customers_[i].person_credit_card().cc_number ==
            customer.person_credit_card().cc_number)
            return i;
    }

    return -1;
}

bool Store::update_customer(int index, Person customer)
{
    if (index < 0 || index >= num_customers_)
        return false;

    if (find_customer(customer) != index)
        return false;

    customers_[index] = customer;

    return true;
}

Person Store::get_customer(int index)
{
    if (index < 0 || index >= num_customers_)
        return Person();

    return customers_[index];
}

bool Store::add_product(product item)
{
    if (num_products_ >= 100)
        return false;

    products_[num_products_] = item;
    num_products_++;

    return true;
}

product Store::get_product(int index)
{
    if (index < 0 || index >= num_products_)
        return product();

    return products_[index];
}

bool Store::add_transaction(transaction new_transaction)
{
    if (num_transactions_ >= 100)
        return false;

    transactions_[num_transactions_] = new_transaction;
    num_transactions_++;

    return true;
}

transaction Store::get_transaction(int index)
{
    if (index < 0 || index >= num_transactions_)
        return transaction();

    return transactions_[index];
}

bool Store::make_purchase(Person customer, product item, int amount)
{
    int index = find_customer(customer);

    if (index == -1)
    {
        cout << "Error: Customer is not in this store.\n";
        return false;
    }

    if (amount <= 0 || item.price <= 0)
    {
        cout << "Error: Quantity and price must be positive.\n";
        return false;
    }

    if (num_transactions_ >= 100)
    {
        cout << "Error: The transaction array is full.\n";
        return false;
    }

    customer = customers_[index];

    credit_card card = customer.person_credit_card();
    double total = item.price * amount;

    if (!card.make_purchase(total))
    {
        cout << "Error: Purchase would exceed the credit limit.\n";
        return false;
    }

    customer.person_credit_card(card);
    update_customer(index, customer);

    transaction new_transaction;

    new_transaction.transaction_number = num_transactions_ + 1;
    new_transaction.customer = customer;
    new_transaction.purchased_item = item;
    new_transaction.quantity = amount;

    add_transaction(new_transaction);

    return true;
}

string Store::customer_info()
{
    string info = "Customers:\n";

    for (int i = 0; i < num_customers_; i++)
        info += customers_[i].person_info() + "\n";

    return info;
}

string Store::product_info()
{
    string info = "Products:\n";

    for (int i = 0; i < num_products_; i++)
        info += products_[i].product_info() + "\n";

    return info;
}

string Store::transaction_info()
{
    string info = "All Transactions:\n";

    for (int i = 0; i < num_transactions_; i++)
        info += transactions_[i].transaction_info() + "\n";

    return info;
}

string Store::store_info()
{
    return customer_info() + "\n" + product_info() + "\n" + transaction_info();
}

string Store::purchase_history(Person customer)
{
    string info = "";

    for (int i = 0; i < num_transactions_; i++)
    {
        if (transactions_[i].customer.name() == customer.name() &&
            transactions_[i].customer.person_credit_card().cc_number ==
            customer.person_credit_card().cc_number)
            info += transactions_[i].transaction_info() + "\n";
    }

    return info;
}
