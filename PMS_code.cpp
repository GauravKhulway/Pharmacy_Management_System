#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
#include <sstream>
using namespace std;

class Date
{
	private:
		int day;
		int month;
		int year;

	public:
		Date(){};
		Date(int day, int month, int year)
		{
			this->day = day;
			this->month = month;
			this->year = year;
		}

		int getDay(){	return day;	}
		int getMonth(){	return month;	}
		int getYear(){	return year;	}

		void showDate()
		{
			cout << day << "/" << month << "/" << year;
		}
};

class Medicine
{
	private:
		string company;
		string medicine;
		int quantity;
		int id;
		int price;
		Date d;

	public:
		Medicine();
		Medicine(string company, string medicine, int quantity, int id, int price, int day, int month, int year);

		void setQuantity(int);
		void setPrice(int);

		string getMedicine();
		string getCompany();
		int getQuantity();
		int getId();
		int getPrice();

		int getDay(){	d.getDay();	}
		int getMonth(){	d.getMonth();	}
		int getYear(){	d.getYear();	}
		void showDate(){	d.showDate(); }

		static int counter;
		static int sortFlag;
		virtual string getType(){	}
};

int Medicine::counter = 0;
int Medicine::sortFlag = 0;

//Definition
Medicine::Medicine()
{
	company="NULL";
	medicine="NULL";
	quantity=0;
	id=0;
	price=0;
}

Medicine::Medicine(string company, string name, int quantity, int id, int price, int day, int month, int year)
{
	this->company = company;
	this->medicine = name;
	this->quantity = quantity;
	this->id = id;
	this->price = price;
	d = Date(day,month,year);
	Medicine::counter++;

}

void Medicine::setQuantity(int q)
{
	this->quantity = q;

	cout << quantity;
}

void Medicine::setPrice(int p)
{
	this->price = p;
}

string Medicine::getCompany()
{
	return company;
}

string Medicine::getMedicine()
{
	return medicine;
}

int Medicine::getQuantity()
{
	return quantity;
}

int Medicine::getId()
{
	return id;
}

int Medicine::getPrice()
{
	return price;
}


class Liquid:public Medicine
{
	private:
		string type;
	public:
		Liquid(string company, string name, int quantity, int id, int price, int day, int month, int year);
		string getType()
		{
			return type;
		}
};

Liquid::Liquid(string company, string name, int quantity, int id, int price, int day, int month, int year) : Medicine(company, name, quantity, id, price, day, month, year)
{
	type = "LIQUID";
}

class Tablet:public Medicine
{
	private:
		string type;
	public:
		Tablet(string company, string name, int quantity, int id, int price, int day, int month, int year);
		string getType()
		{
			return type;
		}
};

Tablet::Tablet(string company, string name, int quantity, int id, int price, int day, int month, int year) : Medicine(company, name, quantity, id, price, day, month, year)
{
	type = "TABLET";
}



//Prototype
void gotoxy(int x, int y);
void showList(Medicine *ob[]);
void showList(Medicine *ob, int found);
void entry(Medicine *ob[], string op);
void save(Medicine *ob[]);
void load(Medicine *ob[]);
void upercase(string &na);
int searchByID(int id, Medicine *ob[]);
int searchByName(string name, Medicine *ob[]);
void edit(Medicine *ob, int found);
bool idCheck(Medicine *ob[],int id);
bool inputDate(int &day, int &month, int &year);
void positive(int &input);
int castToInt(string x);
bool checkInt(string x);
bool dateInput(int &date, int &month , int &year);


void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void showList(Medicine *ob[], int found)
{
	gotoxy(0,3);
	cout << "Medcine Name";
	gotoxy(20,3);
	cout << "Company Name";
	gotoxy(40,3);
	cout << "ID";
	gotoxy(50,3);
	cout << "Price";
	gotoxy(65,3);
	cout << "Quantity";
	gotoxy(80,3);
	cout << "Type";
	gotoxy(95,3);
	cout << "Expiry Date";

	gotoxy(0,5);
	cout << ob[found]->getMedicine();
	gotoxy(20,5);
	cout << ob[found]->getCompany();
	gotoxy(40,5);
	cout << ob[found]->getId();
	gotoxy(50,5);
	cout << "Rs." << ob[found]->getPrice();
	gotoxy(65,5);
	cout << ob[found]->getQuantity();
	gotoxy(80,5);
	cout << ob[found]->getType();
	gotoxy(95,5);
	ob[found]->showDate();

	cout << endl << endl;
}

void showList(Medicine *ob[])
{
	if(Medicine::counter!=0)
	{
		cout << "Medcine Name";
		gotoxy(20,0);
		cout << "Company Name";
		gotoxy(40,0);
		cout << "ID";
		gotoxy(50,0);
		cout << "Price";
		gotoxy(65,0);
		cout << "Quantity";
		gotoxy(80,0);
		cout << "Type";
		gotoxy(95,0);
		cout << "Expiry Date";
		for(int i=0 ; i < Medicine::counter ; i++)
		{
			gotoxy(0,i+2);
			cout << ob[i]->getMedicine();
			gotoxy(20,i+2);
			cout << ob[i]->getCompany();
			gotoxy(40,i+2);
			cout << ob[i]->getId();
			gotoxy(50,i+2);
			cout << "Rs." << ob[i]->getPrice();
			gotoxy(65,i+2);
			cout << ob[i]->getQuantity();
			gotoxy(80,i+2);
			cout << ob[i]->getType();
			gotoxy(95,i+2);
			ob[i]->showDate();
		}
	}
	else
	{
		cout << "No Entry Found";
	}
	cout << endl << endl;
	system("pause");
}

void entry(Medicine *ob[], string op)
{
	int d,m,y;
	string company,name;
	int quantity,id,price;
	string temp;

	system("cls");
	cout << "Enter Company Name: ";
	cin.ignore();
	getline(cin,company);
	cout << "Enter Medicine Name: ";
	getline(cin,name);

	do{
		do{
			cout << "Enter ID: ";
			cin >> temp;
		}while(!checkInt(temp));
		id = castToInt(temp);
	}while(idCheck(ob,id));

	do{
		cout << "Enter Quantity: ";
		cin >> temp;
	}while(!checkInt(temp));
	quantity = castToInt(temp);

	do{
		cout << "Price: ";
		cin >> temp;
	}while(!checkInt(temp));
	price = castToInt(temp);

	int flag = 0;
	do
	{
		flag = dateInput(d,m,y);
	}while(flag == 0);
	positive(quantity);
	positive(id);
	positive(price);
	int count = Medicine::counter;
	upercase(company);
	upercase(name);
	if(op.compare("1")==0)
	{
		ob[count] = new Tablet(company,name,quantity,id,price,d,m,y);
	}
	else
	{
		ob[count] = new Liquid(company,name,quantity,id,price,d,m,y);
	}
	Medicine::sortFlag = 1;
}



void save(Medicine *ob[])
{
	ofstream myfile;
	myfile.open("data.bin", ios::out);

	for(int i=0 ; i<Medicine::counter ; i++)
	{
class Date
{
	private:
		int day;
		int month;
		int year;

	public:
		Date(){};
		Date(int day, int month, int year)
		{
			this->day = day;
			this->month = month;
			this->year = year;
		}

		int getDay(){	return day;	}
		int getMonth(){	return month;	}
		int getYear(){	return year;	}

		void showDate()
		{
			cout << day << "/" << month << "/" << year;
		}
};		myfile << ob[i]->getMedicine() << endl;
		myfile << ob[i]->getCompany() << endl;
		myfile << ob[i]->getId() << endl;
		myfile << ob[i]->getQuantity() << endl;
		myfile << ob[i]->getPrice() << endl;
		myfile << ob[i]->getType() << endl;
		myfile << ob[i]->getDay() << endl;
		myfile << ob[i]->getMonth() << endl;
		myfile << ob[i]->getYear() << endl;
	}
	myfile.close();
}

void load(Medicine *ob[])
{
	ifstream myfile;
	myfile.open("data.bin", ios::in);

	string company,name,type;
	int quantity,id,price;

	int day,month,year;

	int count = 0;
	if(!myfile.fail())
	{
		while(myfile>>name)
		{
			myfile>>company;
			myfile>>id;
			myfile>>quantity;
			myfile>>price;
			myfile>>type;
			myfile>>day;
			myfile>>month;
			myfile>>year;
			count = Medicine::counter;
			if(type == "TABLET")
			{
				ob[count] = new Tablet(company,name,quantity,id,price,day,month,year);
			}
			else
			{
				ob[count] = new Liquid(company,name,quantity,id,price,day,month,year);
			}
			count++;
		}
	}
	myfile.close();
}

void upercase(string &na)
{
	for(int i=0 ; i<na.length() ; i++)
	{
		if(na[i] >= 97 && na[i] <= 122 )
		{
			na[i]-=32;
		}
	}
}

int searchByID(int id, Medicine *ob[])
{
	for(int i=0 ; i<Medicine::counter ; i++)
	{
		if(id == ob[i]->getId())
		{
			return i;
		}
	}

	cout << "\nNo Medicine With Given ID was found...." << endl << endl;
	Sleep(600);
	return -1;
}


int searchByName(string name, Medicine *ob[])
{
	upercase(name);
	for(int i=0 ; i<Medicine::counter ; i++)
	{
		string name1 = ob[i]->getMedicine();
		if(name.compare(name1)==0)
		{
			return i;
		}
	}

	cout << "\nNo Medicine With Given Name was Found....." << endl << endl;
	Sleep(600);
	return -1;
}


void sortByName(Medicine *ob[])
{
	for(int i=0 ; i<Medicine::counter ; i++)
	{
		for(int j=i+1 ; j<Medicine::counter ; j++)
		{
			string name1 = ob[i]->getMedicine();
			string name2 = ob[j]->getMedicine();
 			if(name1.compare(name2)==1)
			{
				Medicine *temp = ob[i];
				ob[i] = ob[j];
				ob[j] = temp;
			}
		}
	}
	Medicine::sortFlag = 0;
}

void edit(Medicine *ob[], int found)
{
	int op;
	cout << "\n1. Edit Quantity" << endl;
	cout << "2. Edit Price" << endl;
	cout << "3. Delete Product" << endl;
	cout << "0. Back To Main Menu" << endl;
	cout << "Select Option: ";
	cin >> op;

	if(op == 1)
	{
		int quantity;
		cout << "\nChange Quantity: ";
		cin >> quantity;
		ob[found]->setQuantity(quantity);
	}

	else if(op == 2)
	{
		int price;
		cout << "\nChange Price: ";
		cin >> price;
		ob[found]->setPrice(price);
	}

	else if(op == 3)
	{
		ob[found] = NULL;
		delete ob[found];
		while(found < Medicine::counter)
		{
			ob[found] = ob[found+1];
			found++;
		}
		ob[found] = NULL;
		delete ob[found];
		Medicine::counter--;
	}

	else if(op == 0){}

	else
	{
		cout << "\nWrong Input, Back to Main Menu...";
		Sleep(600);
	}
}

bool idCheck(Medicine *ob[],int id)
{
	for(int i=0 ; i<Medicine::counter ; i++)
	{
		if(id == ob[i]->getId())
		{
			cout << "Error : ID Already Exists" << endl;
			return true;
		}
	}
	return false;
}


void positive(int &input)
{
	if(input<0)
	{
		input *= -1;
	}
}


int castToInt(string x)
{
	stringstream ss;
	ss << x;
	int casted;
	ss >> casted;
	return casted;
}

bool checkInt(string x)
{
	if(x[0] == '-' || (x[0] >= 48 && x[0] <= 57))
	{
		for(int i=1 ; i < x.length() ; i++)
		{
			if((x[i] >= 48 && x[i] <= 57));
			else
			{
				cout << "Not Valid Input, Retry..." << endl;
				Sleep(600);
				return false;
			}
		}
	}

	else
	{
		cout << "Not Valid Input, Retry..." << endl;
		Sleep(600);
		return false;
	}
	return true;
}

bool dateInput(int &day, int &month , int &year)
{
	string date;
	cin.sync();
	cout << "Enter Date (DD/MM/YYYY): ";
	getline(cin,date);
	char flush;
	stringstream ss;

	ss << date;
	ss >> day;
	ss >> flush;
	ss >> month;
	ss >> flush;
	ss >> year;
}

void assign(Medicine *ob, Medicine *order[]);
int check(int id,Medicine *order[]);
int ptotal(Medicine *order[]);

class Order
{
	public:
		void take_order(Medicine *ob[], Medicine *order[]);
		void order_list(Medicine *order[]);
		void order_small(Medicine *order[]);
		void delete_order(Medicine *order[]);
		void print_recipt(Medicine *ob[], Medicine *order[]);
		static int order;
};

int Order::order = 0;

void Order::take_order(Medicine *ob[], Medicine *order[])
{
	string op3;
	system("cls");
	cout << "\n\n\t1. Search by ID: " << endl;
	cout << "\n\t2. Search by Medicine Name: " << endl;
	cout << "\n\t0. Back To Order Menu" << endl;
	cout << "\n\tSelect Option: ";
	cin >> op3;

	if(op3 == "1" || op3 == "2")
	{
		int found = -1;
		if(op3 == "1")
		{
			system("cls");
			int id;
			cout << "\nEnter ID You Wanna Search: ";
			cin >> id;
			found = searchByID(id,ob);
		}

		else if(op3 == "2")
		{
			system("cls");
			string name;
			cout << "\nEnter Medicine Name You Wanna Search: ";
			cin.ignore();
			getline(cin,name);
			found = searchByName(name,ob);
		}


		if(found != -1)
		{
			int forder = check(ob[found]->getId(),order);

			if(forder == -1)
			{
				cout << endl;
				showList(ob,found);
				int flag=0;
				do{
					string temp;
					do{
						cout << "Enter Quantity: ";
						cin >> temp;
					}while(!checkInt(temp));
					int quantity = castToInt(temp);
					positive(quantity);
					if(quantity != 0)
					{
						if(quantity <= ob[found]->getQuantity())
						{
							assign(ob[found],order);
							order[Order::order-1]->setQuantity(quantity);
							order[Order::order-1]->setPrice(quantity*order[Order::order-1]->getPrice());
							flag = 1;
						}

						else
						{
							cout << "Not Enough Quantity, Retry.." << endl;
							Sleep(400);
						}
					}

					else
					{
						flag = 1;
					}
				}while(flag==0);
			}

			else
			{
				cout << "Product Already Exist";
				Sleep(600);
			}
		}
	}

	else if(op3 == "0"){}

	else
	{
		cout << "\nWrong Input, Back to Order Menu...";
		Sleep(600);
	}
}


void Order::order_list(Medicine *order[])
{
	system("cls");
	if(Order::order!=0)
	{
		cout << "Medcine Name";
		gotoxy(20,0);
		cout << "Company Name";
		gotoxy(40,0);
		cout << "ID";
		gotoxy(50,0);
		cout << "Expiry Date";
		gotoxy(66,0);
		cout << "Quantity";
		gotoxy(79,0);
		cout << "Type";
		gotoxy(90,0);
		cout << "Price";
		gotoxy(103,0);
		cout << "Total Price";
		for(int i=0 ; i < Order::order ; i++)
		{
			gotoxy(0,i+2);
			cout << order[i]->getMedicine();
			gotoxy(20,i+2);
			cout << order[i]->getCompany();
			gotoxy(40,i+2);
			cout << order[i]->getId();
			gotoxy(50,i+2);
			order[i]->showDate();
			gotoxy(66,i+2);
			cout << order[i]->getQuantity();
			gotoxy(79,i+2);
			cout << order[i]->getType();
			gotoxy(90,i+2);
			cout << "Rs." << order[i]->getPrice()/order[i]->getQuantity();
			gotoxy(103,i+2);
			cout << "Rs." << order[i]->getPrice();
		}
	}
	else
	{
		cout << "No Entry Found";
	}
	cout << endl << endl;
}

void Order::order_small(Medicine *order[])
{
	if(Order::order != 0)
	{
		gotoxy(55,0);
		cout << "S#";
		gotoxy(60,0);
		cout << "Medicine";
		gotoxy(80,0);
		cout << "Price/1";
		gotoxy(92,0);
		cout << "Quantity";
		gotoxy(104,0);
		cout << "Total Price";
		for(int i=0 ; i<Order::order ; i++)
		{
			gotoxy(55,i+2);
			cout << i;
			gotoxy(60,i+2);
			cout << order[i]->getMedicine();
			gotoxy(80,i+2);
			cout << "Rs." << order[i]->getPrice()/order[i]->getQuantity();
			gotoxy(92,i+2);
			cout << order[i]->getQuantity();
			gotoxy(104,i+2);
			cout << "Rs." << order[i]->getPrice();
		}
	}
}

void Order::delete_order(Medicine *order[])
{
	int del;

	if(Order::order != 0)
	{
		string temp;
		do
		{
			cout << "Enter S#: ";
			cin >> temp;
		}while(!checkInt(temp));
		int del = castToInt(temp);
		positive(del);

		if(del < Order::order)
		{
			char op;
			cout << "Confirm Y/N: ";
			cin >> op;
			if(op == 'y' || op == 'Y')
			{
				order[del] = NULL;
				delete order[del];
				while(del < Medicine::counter)
				{
					order[del] = order[del+1];
					del++;
				}
				order[del] = NULL;
				delete order[del];
				Order::order--;
			}
		}
		else
		{
			cout << "No Entry Found";
			Sleep(600);
		}

	}

	else
	{
		system("cls");
		cout << "Order Menu Is Empty";
		Sleep(600);
	}
}

void Order::print_recipt(Medicine *ob[], Medicine *order[])
{
	int total;
	if(Order::order!=0)
	{
		total = ptotal(order);
	}

	Order::order_list(order);
	gotoxy(0,Order::order+2);
	cout << "________________________________________________________________________________________________________________________";
	gotoxy(103,Order::order+4);
	//cout << "Rs." << total << endl << endl;

	gotoxy(44,Order::order+7);
	string op;
	cout << "Bill Paid (Y/N): ";
	cin >> op;

	if(op == "Y" || op == "y")
	{
		for(int i=0 ; i<Order::order ; i++)
		{
			int found,id;
			id = order[i]->getId();
			found = searchByID(id,ob);
			ob[found]->setQuantity(ob[found]->getQuantity()-order[i]->getQuantity());
			order[i] == NULL;
			delete order[i];
		}
		Order::order = 0;
	}
	else
	{
		gotoxy(40,Order::order+7);
		cout << "Back to Order Menu...";
		Sleep(600);
	}
}

//Function
void assign(Medicine *ob, Medicine *order[])
{
	string company = ob->getCompany();
	string name = ob->getMedicine();
	int quantity = ob->getQuantity();
	int id = ob->getId();
	int price = ob->getPrice();
	int d = ob->getDay();
	int m = ob->getMonth();
	int y = ob->getYear();

	string type = ob->getType();

	int count = Order::order;
	if(type == "TABLET")
	{
		order[count] = new Tablet(company,name,quantity,id,price,d,m,y);
	}

	else
	{
		order[count] = new Liquid(company,name,quantity,id,price,d,m,y);
	}
	Order::order++;
	Medicine::counter--;
}

int check(int id,Medicine *order[])
{
	for(int i=0 ; i<Order::order ; i++)
	{
		if(id == order[i]->getId())
		{
			return i;
		}
	}
	return -1;
}

int ptotal(Medicine *order[])
{
	int total;
	for(int i=0 ; i < Order::order ; i++)
	{
		total+=order[i]->getPrice();
	}
	return total;
}


int main()
{
	Medicine *stock[100];
	string op1;
	load(stock);
	do{
		system("cls");
		 cout<< "\n\n";
        cout<< "\t\t\t\t    ==========================================================\n";
        cout<< "\t\t\t\t                        Pharmacy Management\n";
        cout<< "\t\t\t\t    ==========================================================\n";
        cout<< "\t\t\t\t ===================================================================\n";
        cout<< "\t\t\t\t                           Main Menu\n";
        cout<< "\t\t\t\t ===================================================================\n";
		cout << "\n\t\t\t\t\t||     1. Product Managing                       ||" << endl;
		cout << "\n\t\t\t\t\t||     2. Product List                           ||" << endl;
		cout << "\n\t\t\t\t\t||     3. Order                                  ||" << endl;
		cout << "\n\t\t\t\t\t||     0. Exit                                   ||\n" << endl;
		cout<< "\t\t\t\t ===================================================================\n";


		cout << "\n\t\t\t\t\t\tSelect Option: ";
		cin >> op1;

		if(op1 == "1")
		{
			string op2;
			system("cls");
			cout << "\n\n\t1. Add new Product" << endl;
			cout << "\n\n\t2. Search, Edit, Delete Product" << endl;
			cout << "\n\n\t0. Back To Main Menu" << endl;
			cout << "\n\n\tSelect Option: ";
			cin >> op2;

			if(op2 == "1")
			{
				system("cls");
				string op3;
				cout << "\n\t1. Tablet" << endl;
				cout << "\n\t2. Liquid" << endl;
				cout << "\n\t0. Back To Main Menu" << endl;
				cout << "\n\n\tSelect Option: ";
				cin >> op3;

				if(op3 == "1")
				{
				    cout<<"\n\n";
					entry(stock,op3);
				}

				else if(op3 == "2")
				{
				    cout<<"\n\n";
					entry(stock,op3);
				}

				else if(op3 == "0"){}

				else
				{
					cout << "\nWrong Input, Back to Main Menu...";
					Sleep(600);
				}
			}

			else if(op2 == "2")
			{
				string op3;
				system("cls");
				cout << "\n\n\n\t\t1. Search by ID: " << endl;
				cout << "\n\t\t2. Search by Medicine Name: " << endl;
				cout << "\n\t\t0. Back To Main Menu" << endl;
				cout << "\n\t\tSelect Option: ";
				cin >> op3;

				if(op3 == "1" || op3 == "2")
				{
					int found = -1;
					if(op3 == "1")
					{
						string temp;
						do
						{
							system("cls");
							cout << "\nEnter ID you want to search: ";
							cin >> temp;
							cout<<"\n\n";
						}while(!checkInt(temp));
						int id = castToInt(temp);
						found = searchByID(id,stock);
					}

					else if(op3 == "2")
					{
						system("cls");
						string name;
						cout << "\n\nEnter Medicine Name you want to search: ";
						cin.ignore();
						getline(cin,name);
                        cout<<"\n\n";
						found = searchByName(name,stock);
					}

					if(found != -1)
					{
						showList(stock,found);
						edit(stock,found);
					}
				}

				else if(op3 == "0"){}

				else
				{
					cout << "\nWrong Input, Back to Main Menu...";
					Sleep(600);
				}
			}

			else if(op2 == "0"){}

			else
			{
				cout << "\nWrong Input, Back to Main Menu...";
				Sleep(600);
			}
		}

		else if(op1 == "2")
		{
			system("cls");

			if(Medicine::sortFlag!=0)
			{
				sortByName(stock);
			}
			showList(stock);
		}

		else if(op1 == "3")
		{
			string op2;
			Medicine *order[100];
			Order odr;
			do
			{
				system("cls");
				cout << "\n\t1. Add Order" << endl;
				cout << "\n\t2. Delete Order" << endl;
				cout << "\n\t3. Order List" << endl;
				cout << "\n\t4. Recipt" << endl;
				cout << "\n\t0. Back to Main Menu" << endl;
				//odr.order_small(order);
				cout << "\n\n\tSelection Option: ";
				cin >> op2;

				if(op2 == "1")
				{
					odr.take_order(stock,order);
				}

				else if(op2 == "2")
				{
					system("cls");
					odr.order_small(order);
					gotoxy(0,0);
					odr.delete_order(order);
				}

				else if(op2 == "3")
				{
					odr.order_list(order);
					system("pause");
				}

				else if(op2 == "4")
				{
					odr.print_recipt(stock,order);
				}

				else if(op2 == "0"){}

				else
				{
					cout << "\nWrong Input, Back to Order Menu...";
					Sleep(600);
				}
			}while(op2 != "0");
		}

		else if(op1 == "0")
		{
			char ch;
			cout << "\n\nSave Record (Y/N): ";
			cin.ignore();
			cin >> ch;
			if(ch == 'Y' || ch == 'y')
			{
				if(Medicine::sortFlag!=0)
				{
					sortByName(stock);
				}
				save(stock);
			}
		}

		else
		{
			cout << "Wrong Input, Please Try Again";
			Sleep(600);
		}
	}while(op1 != "0");
}
