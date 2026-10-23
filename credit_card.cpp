#include "credit_card.h"
#include <sstream>
#include <iomanip>

using namespace std;

bool credit_card::make_purchase(double purchase_amount)
{
    if (purchase_amount <= 0 || purchase_amount > limit - current_balance)
        return false;

    current_balance += purchase_amount;
    return true;
}

bool credit_card::make_payment(double payment_amount)
{
    if (payment_amount <= 0 || payment_amount > current_balance)
        return false;

    current_balance -= payment_amount;
    return true;
}

string credit_card::credit_card_info()
{
    // A stringstream builds a string using the same style as cout.
    ostringstream info;

    info << fixed << setprecision(2);
    info << "Credit card number: " << cc_number << "\n";
    info << "Credit Card Limit: $" << limit << "\n";
    info << "Current Balance: $" << current_balance << "\n";

    return info.str();
}
