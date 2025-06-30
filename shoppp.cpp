#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;
// prototypes start

char ownermenu();
char customermenu();
void header();
string who();
void add(string username, float password, string role);
void clearscreen();
void addproduct();
void view();
void modify();
void namenew();
void delproduct();
void check();
void search(string product);
void buy();
void bill();
void rate();
void savedata();
void dataload();
string getfield(string records, int field);

// prototypes end
// data structues start
const int TOTALUSER = 10;
const int MAX = 100;
string usernameA[TOTALUSER];
float passwordA[TOTALUSER];
string roleA[TOTALUSER];
string boughtitemA[TOTALUSER][MAX];
float boughtpriceA[TOTALUSER][MAX];
int count = 0;
string loginuser = " ";
string productA[MAX] = {"Soap", "Milk", "Bread", "Eggs", "Sugar", "Tea", "Oil", "Shampoo", "Paste", "Rice", "Pulses", "PalmOil", "Salt", "Chips", "Coffee", "Spices", "Flour", "Snacks", "Drink"};
int priceA[MAX] = {200, 230, 260, 180, 90, 200, 500, 150, 30, 300, 400, 345, 420, 70, 80, 50, 200, 530, 290};
int stockA[MAX] = {11, 21, 24, 26, 25, 45, 29, 6, 3, 32, 10, 30, 29, 22, 21, 19, 18, 21, 32};
float ratingA[100];
int boughtA[TOTALUSER];
int totalproducts = 19;
string name;
float newprice;
string lastbuy = " ";
float buyprice = 0.0;
string loginuserr = " ";
bool boughtitem = false;
int curidx = -1;

// data structures end
int main()
{
    dataload();

    add("admin", 123, "ADMIN");
    add("Ali", 123, "USER");

    while (true)
    {

        string w = who();

        if (w == "ADMIN")
        {
            system("CLS");
            char adminoption = ' ';
            while (true)
            {
                adminoption = ownermenu();
                if (adminoption == '1')
                {
                    // add product
                    addproduct();
                }
                else if (adminoption == '2')
                {
                    // view product
                    view();
                }
                else if (adminoption == '3')
                {
                    // update
                    modify();
                }
                else if (adminoption == '4')
                {
                    //  modify
                    namenew();
                }
                else if (adminoption == '5')
                {
                    // delete
                    delproduct();
                }
                else if (adminoption == '6')
                {
                    // check record
                    check();
                }
                else if (adminoption == '7')
                {
                    // logout
                    cout << " Thanks for using our Management System" << endl;
                    break;
                }
                else
                {
                    cout << " Wrong input";
                }
                clearscreen();
            }
        }
        else if (w == "USER")
        {
            system("CLS");
            char useroption = ' ';
            while (true)
            {
                useroption = customermenu();
                if (useroption == '1')
                {
                    // view product
                    view();
                }
                else if (useroption == '2')
                {
                    
                     cout << " Enter the product to search: ";
                      string product;
                    cin >> product;
                    search (product);
                    
                }
                else if (useroption == '3')
                {
                    //  buy
                    buy();
                }
                else if (useroption == '4')
                {
                    // bill
                    bill();
                }
                else if (useroption == '5')
                {
                    // rate
                    rate();
                }
                else if (useroption == '6')
                {
                    // logout
                    cout << " Thanks for using our Management System" << endl;
                    break;
                }

                else
                {
                    cout << " Invalid option";
                }
                clearscreen();
            }
        }
    }
    savedata(); // saving of data in file
}
void header()
{ // header
    cout << " ********************************************" << endl;
    cout << "           Shop  Management System            " << endl;
    cout << " ********************************************" << endl;
}
char ownermenu()
{ // ownermenu

    header();
    cout << " Welcome Owner " << endl;

    cout << " 1-Add New Product " << endl;
    cout << " 2-View The products" << endl;
    cout << " 3-Update the price" << endl;
    cout << " 4-Modify the product name" << endl;
    cout << " 5-Delete the product" << endl;
    cout << " 6-CHeck the product stock" << endl;
    cout << " 7-Logout" << endl;

    char option;
    cout << " Enter the option: ";
    cin >> option;
    return option;
    // using return taaky option ko wapis main program main de sakain
}
char customermenu()
{ // customer menu
    header();
    cout << " Welcome Customer" << endl;
    cout << " 1-View products  " << endl;
    cout << " 2-Search product " << endl;
    cout << " 3-Buy Product " << endl;
    cout << " 4-Generate the bill" << endl;
    cout << " 5-Rate our items" << endl;
    cout << " 6-Logout       " << endl;
    cout << " Enter the choice :";
    char choice;
    cin >> choice;
    return choice;
    // return is louar takay choice wapis main program ko de sakain
}
string who()
{
    while (true)
    {
        header();
        cout << " 1-Login\n";
        cout << " 2-Sign up\n";
        cout << "Enter an option\n";
        int choice;
        if (!cin >> choice)
        {
            cout << "Invalid option." << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }
        cin >> choice;
        if (choice == 1)
        {
            cout << "Enter the username(or type exit to close the program): " << endl;
            string user;
            cin >> user;
            if (user == "exit" || user == "Exit")
            {
                cout << "  Program exited" << endl;
                exit(0);
            }
            cout << " Enter the password: " << endl;
            float pass;
            cin >> pass;
            for (int i = 0; i < count; i++)
            {
                if (usernameA[i] == user && passwordA[i] == pass)
                {
                    loginuser = user;
                    curidx = i;
                    return roleA[i];
                }
            }
            cout << " Invalid username or password.Try again.\n";
            clearscreen();
        }
        else if (choice == 2)
        {
            string newuser;
            cout << " Enter the new username: ";
            cin >> newuser;
            bool found = false;
            for (int i = 0; i < count; i++)
            {
                if (usernameA[i] == newuser)
                {
                    found = true;
                    break;
                }
            }
            if (found)
            {
                cout << " This user already exists";
                clearscreen();
                continue;
            }
            cout << " Enter the password: ";
            float newpass;
            cin >> newpass;
            add(newuser, newpass, "USER");
            cout << " Sign up is succeessful.Plese login\n";
            clearscreen();
        }
        else
        {
            cout << " Invalid option.Try again\n";
        }
    }
}
void clearscreen()
{
    cout << " Press any key to continue...";
    cin.clear();
    cin.ignore(1000, '\n');
    cin.get();// charctrer ko read karnay kay liyae from buffer
    system("CLS");
}
void add(string username, float password, string role)
{

    if (count < TOTALUSER)
    {
        usernameA[count] = username;
        passwordA[count] = password;
        roleA[count] = role;
        boughtA[count] = 0;

        count++;
        savedata();
    }
    else
    {
        cout << " No more space to add " << endl;
    }
}

void addproduct()
{
      cout << " Enter the product: ";
    cin >> productA[totalproducts];

    cout << " Enter the price: ";
    cin >> priceA[totalproducts];

    cout << " Enter the stock quantity: ";
    cin >> stockA[totalproducts];
    cout << productA[totalproducts]<< " with Rs: " << priceA[totalproducts] << " is added with stock quantity: " << stockA[totalproducts]<< endl;

    totalproducts++;
    savedata();
}

void view()
{
    cout << " Available products are as follows" << endl;

    for (int i = 0; i < totalproducts; i++)
    {
        cout << i + 1 << " " << "\t" << productA[i] << "\t" << priceA[i] << "\t" << stockA[i] << endl;
    }
}
void modify()
{
    cout << " Available products are as follows" << endl;

    for (int i = 0; i < totalproducts; i++)
    {

        cout << i + 1 << " " << "\t" << productA[i] << "\t" << priceA[i] << endl;
    }

    cout << "Enter the name  of that  above product  whose price you want to modify: ";

    cin >> name;

    cout << "Enter the new price: ";
    cin >> newprice;
    bool found = false;
    for (int j = 0; j < totalproducts; j++)
    {
        if (productA[j] == name)
        {
            priceA[j] = newprice;
            cout << " Updated price of " << name << " is " << newprice;
            found = true;
            break;
        }
    }
    if (!found)
    {
        cout << "Product is not available" << endl;
    }
    savedata();
}

void namenew()
{
    cout << " Available products are as follows" << endl;

    for (int i = 0; i < totalproducts; i++)
    {
        cout << i + 1 << " " << "\t" << productA[i] << "\t" << priceA[i] << endl;
    }
    cout << " Enter the product whose name you want to change: ";
    string name;
    cin >> name;
    cout << "Update the name: ";
    string name1;
    cin >> name1;
    bool found = false;
    for (int j = 0; j < totalproducts; j++)
    {
        if (productA[j] == name)
        {
            productA[j] = name1;
            cout << " New name is " << name1;
            found = true;
            break;
        }
    }
    if (!found)
    {
        cout << "  Product is not available" << endl;
    }
    savedata();
}
void delproduct()
{
    cout << " Available products are as follows" << endl;

    for (int i = 0; i < totalproducts; i++)
    {
        cout << i + 1 << " " << "\t" << productA[i] << "\t" << priceA[i] << endl;
    }
    cout << " Enter the product you want to delete: ";
    string del;
    cin >> del;
    bool found = false;
    for (int i = 0; i < totalproducts; i++)
    {
        if (productA[i] == del)
        {

            for (int j = i; j < totalproducts - 1; j++)
            {
                productA[j] = productA[j + 1];
            }
            totalproducts--;
            found = true;
            savedata();
            cout << del << " has been deleted " << endl;
        }
    }
}
void check()
{
    cout << " Available stock is as follows: " << endl;
    for (int i = 0; i < totalproducts; i++)
    {
        cout << i + 1 << " " << "\t" << productA[i] << "\t" << stockA[i] << endl;
    }
    cout << " This is the available stock that is still present ";
}
void search(string product)
{
    
    bool found = false;
    for (int i = 0; i < totalproducts; i++)
    {
        
        if (productA[i] ==product )
        {
            found = true;
            cout << " Item " << product << " is available" << endl;
        }
    }
    if (!found)
    {
        cout << " Item is not available";
    }
}
void buy()
{
    cout << " Available products are as follows: " << endl;
    for (int i = 0; i < totalproducts; i++)
    {
        cout << i + 1 << "  " << productA[i] << " " << priceA[i] << endl;
    }
    cout << " Enter the product you want to buy: ";
    cin >> lastbuy;
    bool found = false;
    for (int j = 0; j < totalproducts; j++)
    {
        if (productA[j] == lastbuy)
        {
            found = true;
            int iddd = boughtA[curidx];
            boughtitemA[curidx][iddd] = lastbuy;
            boughtpriceA[curidx][iddd] = priceA[j];
            boughtA[curidx]++;
            stockA[j]--;
            savedata();

            cout << lastbuy << " is added to the cart" << endl;
            break;
        }
    }
    if (!found)
    {
        cout << " Product is not available" << endl;
    }
}
void bill()
{
    if (boughtA[curidx] == 0)
    {
        cout << " You have not bought anything yet\n";
        return;
    }
    float total = 0;
    cout << " Your purchased items:\n";
    for (int i = 0; i < boughtA[curidx]; i++)
    {
        cout << " " << boughtitemA[curidx][i] << ":Rs" << boughtpriceA[curidx][i] << endl;
        total += boughtpriceA[curidx][i];
    }
    cout << " Total amount:Rs " << total << endl;
    cout << "Enter payment: ";
    float pay;
    cin >> pay;
    float bill = pay - total;
    if (bill >= 0)
    {
        cout << "Return" << bill << endl;
    }
    else
    {
        cout << " Insufficient payment. You still have to pay :Rs" << -bill << endl;
    }
    savedata();
}
void rate()
{
    if (boughtA[curidx] == 0)
    {
        cout << " You have not bought anything yet\n";
        return;
    }
    for (int i = 0; i < boughtA[curidx]; i++)
    {

        cout << " Do you want to rate " << boughtitemA[curidx][i] << "?(1=yes,0=no):";
        int choice;
        cin >> choice;

        if (choice == 1)
        {
            int r;
            cout << " Enter your rating for  " << boughtitemA[curidx][i] << "(1 to 5)" << endl;
            cin >> r;

            if (r >= 1 && r <= 5)
            {
                cout << " You gave " << r << "stars to " << boughtitemA[curidx][i] << endl;
            }
            else
            {
                cout << " Invalid rating" << endl;
            }
            savedata();
        }
    }
}
void savedata()
{
    fstream file;
    file.open("shopdata.txt", ios::out);
    if (!file)
    {
        cout << " Error " << endl;
        return;
    }
    file << count << "\n";
    for (int i = 0; i < count; i++)
    {
        file << usernameA[i] << "," << passwordA[i] << "," << roleA[i] << "\n";
    }
    file << totalproducts << "\n";

    for (int i = 0; i < totalproducts; i++)
    {
        file << productA[i] << "," << priceA[i] << "," << stockA[i] << "\n";
    }
    for (int i = 0; i < count; i++)
    {
        file << boughtA[i] << "\n";
        for (int j = 0; j < boughtA[i]; j++)
        {
            file << boughtitemA[i][j] << "," << boughtpriceA[i][j] << "\n";
        }
    }
    for (int i = 0; i < totalproducts; i++)
    {
        file << ratingA[i] << "\n";
    }
    file.close();
}

string getfield(string record, int field)
{
    int commacount = 1;
    string item = "";
    for (int i = 0; i < record.length(); i++)
    {
        if (record[i] == ',')
        {
            commacount++;
        }
        else if (commacount == field)
        {
            item = item + record[i];
        }
    }
    return item;
}
void dataload()
{
    fstream file;
    file.open("shopdata.txt", ios ::in);
    if (!file.is_open())
    {
        cout << " No saved data has been found.\n";
        return;
    }
    file >> count;
    file.ignore();
    for (int i = 0; i < count; i++)
    {
        string line;
        getline(file, line);
        usernameA[i] = getfield(line, 1);
        passwordA[i] = stof(getfield(line, 2));
        roleA[i] = getfield(line, 3);
    }
    file >> totalproducts;
    file.ignore();
    for (int i = 0; i < totalproducts; i++)
    {
        string line;
        getline(file, line);
        productA[i] = getfield(line, 1);
        priceA[i] = stof(getfield(line, 2));
        stockA[i] = stoi(getfield(line, 3));
    }
    for (int i = 0; i < count; i++)
    {
        file >> boughtA[i];
        file.ignore();

        for (int j = 0; j < boughtA[i]; j++)
        {
            string line;
            getline(file, line);
            boughtitemA[i][j] = getfield(line, 1);
            boughtpriceA[i][j] = stof(getfield(line, 2));
        }
    }

    for (int i = 0; i < totalproducts; i++)
    {
        file >> ratingA[i];
        file.ignore();
    }
    file.close();
}
