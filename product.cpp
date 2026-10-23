#include "product.h"
#include <sstream>
#include <iomanip>

using namespace std;

string product::product_info()
{
    ostringstream info;

    info << fixed << setprecision(2);
    info << "Name: " << name << "\n";
    info << "Description: " << description << "\n";
    info << "Price: $" << price << "\n";

    return info.str();
}
