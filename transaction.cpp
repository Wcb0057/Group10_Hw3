#include "transaction.h"
#include <sstream>

using namespace std;

string transaction::transaction_info()
{
    ostringstream info;

    info << "Transaction #: " << transaction_number << "\n";
    info << "Customer:\n" << customer.person_info();
    info << "Product:\n" << purchased_item.product_info();
    info << "Quantity: " << quantity << "\n";

    return info.str();
}
