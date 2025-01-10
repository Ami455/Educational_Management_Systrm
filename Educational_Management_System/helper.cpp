
#include "helper.h"


namespace Faculty {

double Helper::Probability()
{
    return rand() * 0.1 / RAND_MAX;
}

int Helper::ReadInt(int low, int high)
{
    //read input as stream to avoid any stream problems
    string input;
    cin >> input;

    istringstream myStringObj (input);

    int value;
    myStringObj >> value;

    if(myStringObj.fail())
    {
        cout<< "ERROR: Expected integer input.. Try ahain - Enter number ";
        return ReadInt(low, high);
    }

    if (low<=value && value <= high)
    {
        return value;
    }

    cout << "ERROR: Expected range is low = " << low<< ", high = " << high << "...Try again - Enter number ";
    return ReadInt(low, high);
}


string Helper::ToString(int value, int length)
{
    ostringstream oss;
    oss << value;
    string ret = oss.str();

    while ((int)ret.size() < length)
    {
        ret = "0" + ret;
    }

    return ret;
}

int Helper::RunMenu(vector<string> &menu)
{
    cout<< "\n\nPlease make a choice:\n";

    for(int i = 0; i< (int)menu.size(); ++i)
    {
        cout << "\t" << i + 1 << " - " << menu[i] << "\n";
    }

    cout << "\tEnter Choice: ";

    return Helper::ReadInt(1, menu.size());
}

}
