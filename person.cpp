//code for person class here
#include "person.h"

Person::Person(string name, string phone, address person_address,
               credit_card person_credit_card)
{
    name_ = name;
    phone_ = phone;
    person_address_ = person_address;
    person_credit_card_ = person_credit_card;
}

Person::Person()
{
    name_ = "";
    phone_ = "";
    person_address_ = address();
    person_credit_card_ = credit_card();
}

void Person::name(string name)
{
    name_ = name;
}

string Person::name()
{
    return name_;
}

void Person::phone(string phone)
{
    phone_ = phone;
}

string Person::phone()
{
    return phone_;
}

void Person::person_address(address person_address)
{
    person_address_ = person_address;
}

address Person::person_address()
{
    return person_address_;
}

void Person::person_credit_card(credit_card person_credit_card)
{
    person_credit_card_ = person_credit_card;
}

credit_card Person::person_credit_card()
{
    return person_credit_card_;
}

string Person::person_info()
{
    return "Name: " + name_ + "\nPhone: " + phone_ + "\nAddress:\n" +
           person_address_.address_info() + "Credit Card:\n" +
           person_credit_card_.credit_card_info();
}
