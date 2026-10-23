#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

#include "address.h"
#include "credit_card.h"
#include "person.h"
#include "product.h"
#include "store.h"
#include "transaction.h"

using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::getline;

// Extra headers and names used by the added code.
#include <ctime>
#include <limits>
using std::string;
using std::numeric_limits;
using std::streamsize;

int main()
{
    //import from text files

    const int MAX_SIZE = 100;
    Person people[MAX_SIZE];
    product products[MAX_SIZE];
    credit_card cards[MAX_SIZE];
    string card_names[MAX_SIZE];
    int people_count, product_count, card_count;

    //add to store and other variables
    Store store1;

    ifstream people_file("people.txt");
    ifstream product_file("products.txt");
    ifstream card_file("credit_card.txt");

    if (!people_file || !product_file || !card_file)
    {
        cout << "Error: Could not open the input files.\n";
        cout << "Run the program from the folder containing the three text files.\n";
        return 1;
    }

    if (!(card_file >> card_count) || card_count < 1 || card_count > MAX_SIZE)
    {
        cout << "Error: Invalid credit card count.\n";
        return 1;
    }

    // Skip the rest of the number's line before reading a full name.
    card_file.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int i = 0; i < card_count; i++)
    {
        getline(card_file, card_names[i]);

        if (!(card_file >> cards[i].cc_number >> cards[i].limit
                       >> cards[i].current_balance) ||
            cards[i].cc_number <= 0 || cards[i].limit < 0 ||
            cards[i].current_balance < 0 ||
            cards[i].current_balance > cards[i].limit)
        {
            cout << "Error: Invalid credit card information.\n";
            return 1;
        }

        card_file.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    if (!(people_file >> people_count) || people_count < 1 ||
        people_count > MAX_SIZE)
    {
        cout << "Error: Invalid customer count.\n";
        return 1;
    }

    people_file.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int i = 0; i < people_count; i++)
    {
        string name, phone;
        address home;

        getline(people_file, name);
        getline(people_file, phone);
        getline(people_file, home.address_line1);

        // A blank second address line is valid, so do not skip it.
        getline(people_file, home.address_line2);
        getline(people_file, home.city);
        getline(people_file, home.state);
        getline(people_file, home.zip);

        if (!people_file || name.empty())
        {
            cout << "Error: Invalid customer information.\n";
            return 1;
        }

        // The card file is in a different order. Match each card by name.
        int card_index = -1;

        for (int j = 0; j < card_count; j++)
        {
            if (card_names[j] == name)
            {
                card_index = j;
                break;
            }
        }

        if (card_index == -1)
        {
            cout << "Error: No credit card found for " << name << ".\n";
            return 1;
        }

        people[i] = Person(name, phone, home, cards[card_index]);
        store1.add_customer(people[i]);
    }

    if (!(product_file >> product_count) || product_count < 1 ||
        product_count > MAX_SIZE)
    {
        cout << "Error: Invalid product count.\n";
        return 1;
    }

    product_file.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int i = 0; i < product_count; i++)
    {
        getline(product_file, products[i].name);
        getline(product_file, products[i].description);

        if (!(product_file >> products[i].price) || products[i].price <= 0 ||
            products[i].name.empty())
        {
            cout << "Error: Invalid product information.\n";
            return 1;
        }

        product_file.ignore(numeric_limits<streamsize>::max(), '\n');
        store1.add_product(products[i]);
    }

    //print store info after you finish importing info
    //from text files and add them to your store
    cout << "Store info: " << endl << endl;
    cout << store1.store_info() << endl << endl;

    //make random number of random transactions

    srand(static_cast<unsigned int>(time(0)));

    // 11 through 99 satisfies both transaction ranges given in the PDF.
    int attempts = rand() % 89 + 11;

    cout << "Attempting " << attempts << " random purchases.\n\n";

    for (int i = 0; i < attempts; i++)
    {
        int customer_index = rand() % people_count;
        int product_index = rand() % product_count;
        int quantity = rand() % 10 + 1;

        Person customer = store1.get_customer(customer_index);
        product item = store1.get_product(product_index);

        if (store1.make_purchase(customer, item, quantity))
        {
            cout << "Successful transaction!\nTransaction Details:\n";

            transaction purchase =
                store1.get_transaction(store1.num_transactions() - 1);

            cout << purchase.transaction_info() << "\n";
            people[customer_index] = store1.get_customer(customer_index);
        }
        else
        {
            cout << "Unsuccessful transaction!\nTransaction Details:\n";
            cout << "Person:\n" << customer.person_info();
            cout << "Product:\n" << item.product_info();
            cout << "Purchase Quantity: " << quantity << "\n\n";
        }
    }

    //print store info at the end
    cout << "Store info: " << endl << endl;
    cout << store1.store_info() << endl << endl;

    return 0;
}
