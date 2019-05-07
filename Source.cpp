#include <iostream>		
#include <windows.h>
#include <string>
#include <fstream>
#include <time.h>

using namespace std;

class ClientUnit	// ����� �������
{

private:
	string Name;			// ��� �������
	string Adress;				// ����� �������
	unsigned int AccountNumber;				// ������������ ����� ��������
	unsigned short int InternetTariff;				// ������� ����� �� ��������
	unsigned short int TVTariff;			// ������� ����� �� ��������� �����������
	int Balance;			// ���� �������
	string AccountStatus;			// ��������� ��������

public:
	// set
	void setName(string Name) { this->Name = Name; };			// ��������� �����
	void setAdress(string Adress) { this->Adress = Adress; };			// ��������� ������
	void setAccountNumber(int AccountNumber) { this->AccountNumber = AccountNumber; };				// ��������� ������������� ����������� ������
	void setInternetTariff(int InternetTariff) { this->InternetTariff = InternetTariff; };			// ��������� ������� ����� �� ��������
	void setTVTariff(int TVTariff) { this->TVTariff = TVTariff; };				// ��������� �������� ������ �� ��������� �����������
	void setBalance(int Balance) { this->Balance = Balance; };				// ��������� ��������� ����� �������
	void setAccountStatus(string AccountStatus) { this->AccountStatus = AccountStatus; };			// ��������� ��������� ��������

	void setAccountNull()			// ��������� ��������
	{
		this->Name = "Null";
		this->Adress = "Null";
		this->InternetTariff = 0;
		this->TVTariff = 0;
		this->Balance = 0;
		this->AccountStatus = "Null";
	};

	// get
	string getName() { return Name; };				// ������� �����
	string getAdress() { return Adress; };				// �������� ������
	int getAccountNumber() { return AccountNumber; };				// ������� ������ ��������
	int getTVTariff() { return TVTariff; };			// ������� ������� ����� �� ��������� �����������
	int getInternetTariff() { return InternetTariff; };				// �������� ������� ����� �� ��������
	bool Empty()			// ���� ��������� ���� - ����� true, ����� - false
	{
		if (this->Name == "Null")
			return true;
		else
			return false;
	};

	string getTVTariffName()			// ������� �������� ������ ���������� �����������
	{
		switch (TVTariff)
		{
		case 1: return "����";
			break;
		case 2: return "�������";
			break;
		case 3: return "����";
			break;
		default: return "�� ������������";
		}
	};

	string getInternetTariffName()				// ������� �������� ������ ���������
	{
		switch (InternetTariff)
		{
		case 3: return "����";
			break;
		case 5: return "������ 10";
			break;
		case 6: return "������ 35";
			break;
		case 8: return "������ 50";
			break;
		case 10: return "������ 100";
			break;
		default: return "�� ������������";
		}
	};

	int getBalance() { return Balance; };			// ������� ������� ��������
	string getAccountStatus() { return AccountStatus; };			// ������� ��������� ��������
};

void Initialization();				// ������� ��������� �������������
void ShowClientInformation(string name, int number);			// ������� ����������� ���������� � ��������
void Service();				// ������� ������������ ��������
void ClientBase();				// ������� ������ � ���������� �����
void UpdateInformation();			// ������� ���������� ���������� � ����
void Refill();				// ������� ���������� ���� 
void UnitOperation(string name);			// ������� ������ � ����������

//string getDate()
//{
//	string temp;
//	time_t rawtime;
//	struct tm * timeinfo;
//
//	time(&rawtime);
//	timeinfo = localtime(&rawtime);
//	temp = asctime(timeinfo);
//	return temp;
//}


ClientUnit Clients[20];				// ������ ��� �������� ���������� � ��������

void main()
{
	SetConsoleOutputCP(1251);	SetConsoleCP(1251);

	Initialization();

	for (int Start = 0; Start != 3;)	
	{
		system("cls");

		cout << "1. ������������ ����������� \n2. ������ � ���������� ����� \n3. ��������� ������ \n>> ";
		cin >> Start;

		switch (Start)
		{
		case 1:	Service();
			break;
		case 2: ClientBase();
			break;
		case 3:	UpdateInformation(); system("pause");
			break;
		default: cout << "������������ ������� \n"; system("pause");
		}
	}
}

void Service()
{
	for (int Choose = 0; Choose != 4;)
	{
		system("cls");

		cout << "1. ��������� ���� �������� \n2. �������� ������ �������� \n3. ���������� ������� �������� \n4. ����� \n>> ";
		cin >> Choose;

		switch (Choose)
		{
		case 1:	Refill();
			break;
		case 2: UnitOperation("new");
			break;
		case 3:	UnitOperation("frozen");
			break;
		case 4: // ����� 
			UpdateInformation();
			break;
		default: cout << "������������ �������\n"; system("pause");
		}
	}
}

void ClientBase()
{
	for (int Choose = 0; Choose != 4;)
	{
		system("cls");

		unsigned short int number;

		cout << "1. ���������� ����������� ���� \n2. ����� �������� \n3. ������� �������� \n4. ����� \n>> ";
		cin >> Choose;

		switch (Choose)
		{
		case 1:	ShowClientInformation("all", -1);
			break;
		case 2: system("cls");

				cout << "������� ������� ���� ��������(0 - 19) >> ";
				cin >> number;

				ShowClientInformation("current", number);
			break;
		case 3:	UnitOperation("del");
			break;
		case 4: // ����� 
				UpdateInformation();
			break;
		default: cout << "������������ �������\n"; system("pause");
		}
	}
}

void UnitOperation(string name)
{
	system("cls");

	if (name == "new")				// ����� �������
	{
		string Name, Adress;
		int Internet, TV, Balance;

		cout << "������� ��� ������ �������� >>";
		cin.get();
		getline(cin, Name);

		cout << "������� ����� ������ �������� >>";
		getline(cin, Adress);

		for (;;)
		{
			cout << "������� �������� ����� �������� \n0 - �� ������������\n 3 - ���� \n5 - ������ 10 \n6 - ������ 35 \n8 - ������ 50 \n10 - ������ 100 \n>>";
			cin >> Internet;

			if (Internet == 0 || Internet == 3 || Internet == 5 || Internet == 6 || Internet == 8 || Internet == 10)
				break;

			else
				cout << "������������ �������\n"; system("pause");
		}

		
		for (;;)
		{
			cout << "������� ����� ���������� ����������� �������� \n0 - �� ������������ \n1 - ���� \n2 - ������� \n3 - ���� \n>>";
			cin >> TV;

			if (TV == 0 || TV == 1 || TV == 2 || TV == 3)
				break;

			else
				cout << "������������ �������\n"; system("pause");
		}

		for (;;)
		{
			cout << "������� ��������� ������ ��������(0 - 5000) >>";
			cin >> Balance;

			if (Balance >= 0 && Balance <= 5000)
				break;

			else
				cout << "������������ �������\n"; system("pause");
		}

		bool flag = false;

		for (int i = 0; i < 20; i++)
		{
			if (Clients[i].Empty() == true)
			{
				flag = true;

				Clients[i].setName(Name);
				Clients[i].setAdress(Adress);
				Clients[i].setInternetTariff(Internet);
				Clients[i].setTVTariff(TV);
				Clients[i].setBalance(Balance);

				ofstream Report("AllReports.total", ios::app);

				if (Report.is_open())
				{
					// Report << getDate() << endl;
					Report << "�������� ����� �������, " << Name << endl << "��� �������� ������� ����: " << Clients[i].getAccountNumber() << endl << endl;

					Report.close();
				}

				else
					cout << "���������� ������� ���� \"AllReports.total\", ���������� � �������������� \n"; system("pause");

				break;
			}
		}

		if (flag = false)
			cout << "C����� ���������� \n"; system("pause");
	}

	if (name == "frozen")				// ����������� �������
	{
		int AccountNumber;	bool Find = false;

		system("cls");

		cout << "������� ����� �������� >> ";
		cin >> AccountNumber;

		for (int i = 0; i < 20; i++)
		{
			if (AccountNumber == Clients[i].getAccountNumber())
			{
				int tmp = Clients[i].getBalance();

				Clients[i].setAccountStatus("���������");

				Clients[i].setBalance(tmp - 20);
				Find = true;

				UpdateInformation();

				ofstream Report("AllReports.total", ios::app);

				if (Report.is_open())
				{
					// Report << getDate() << endl;
					Report << Clients[i].getAccountNumber() << ", " << Clients[i].getAdress() << endl;
					Report << "������� ���������" << endl << endl;

					Report.close();

					cout << "������� ������� ���������\n"; system("pause");
				}

				else
					cout << "���������� ������� ���� \"AllReports.total\", ���������� � �������������� \n"; system("pause");

				break;
			}
		}

		if (Find == false)
			cout << "������� �� ������\n"; system("pause");
	}

	if (name == "del")				// ��������/���������� ������������
	{
		int AccountNumber;	bool Find = false;

		system("cls");

		cout << "������� ����� �������� >> ";
		cin >> AccountNumber;

		for (int i = 0; i < 20; i++)
		{
			if (AccountNumber == Clients[i].getAccountNumber())
			{
				Find = true;

				ofstream Report("AllReports.total", ios::app);

				if (Report.is_open())
				{
					// Report << getDate() << endl;
					Report << "�������" << Clients[i].getName() << ", " << Clients[i].getAdress();
					Report << " ����� �� ����" << endl << endl;

					Report.close();
				}

				else
					cout << "���������� ������� ���� \"AllReports.total\", ���������� � �������������� \n"; system("pause");

				Clients[i].setAccountNull();

				break;
			}
		}

		if (Find == false)
			cout << "������� �� ������\n"; system("pause");
	}
}

void Refill()
{
	int AccountNumber;	bool Find = false;

	system("cls");

	cout << "������� ����� �������� >> ";
	cin >> AccountNumber;

	for (int i = 0; i < 20; i++)
	{
		if (AccountNumber == Clients[i].getAccountNumber())
		{
			int tmp = Clients[i].getBalance(), sum = 0;

			cout << "������� ����� >> ";
			cin >> sum;

			Clients[i].setBalance(tmp + sum);
			Find = true;

			UpdateInformation();

			ofstream Report("AllReports.total", ios::app);

			if (Report.is_open())
			{
				// Report << getDate() << endl;
				Report << "���� �������� " << Clients[i].getAccountNumber() << ", " << Clients[i].getAdress() << endl;
				Report << "�������� �� " << sum << "���" << endl << endl;

				Report.close();
			}

			else
				cout << "���������� ������� ���� \"AllReports.total\", ���������� � �������������� \n"; system("pause");


			break;
		}
	}

	if (Find == false)
		cout << "������� �� ������\n"; system("pause");
}

void UpdateInformation()			// ���������� ���������� � ����
{
	ofstream Client("ClientInformation.base");

	if (Client.is_open())
	{
		for (int i = 0; i < 20; i++)
		{
			Client << Clients[i].getName() << endl;
			Client << Clients[i].getAdress() << endl;
			Client << Clients[i].getAccountNumber() << endl;
			Client << Clients[i].getInternetTariff() << endl;
			Client << Clients[i].getTVTariff() << endl;
			Client << Clients[i].getBalance() << endl;
			Client << Clients[i].getAccountStatus() << endl << endl;
		}

		Client.close();
	}

	else
		cout << "���������� ������� ���� \"ClientInformation.base\", ���������� � �������������� \n";
}

void Initialization()
{
	ifstream Client("ClientInformation.base");

	if (Client.is_open())
	{
		string tmp;

		for (int i = 0; i < 20; i++)
		{
			getline(Client, tmp);	Clients[i].setName(tmp);
			getline(Client, tmp);	Clients[i].setAdress(tmp);
			getline(Client, tmp);	Clients[i].setAccountNumber(atoi(tmp.c_str()));
			getline(Client, tmp);	Clients[i].setInternetTariff(atoi(tmp.c_str()));
			getline(Client, tmp);	Clients[i].setTVTariff(atoi(tmp.c_str()));
			getline(Client, tmp);	Clients[i].setBalance(atoi(tmp.c_str()));
			getline(Client, tmp);	Clients[i].setAccountStatus(tmp);
			getline(Client, tmp);
		}

		Client.close();
	}

	else
		cout << "���������� ������� ���� \"ClientInformation.base\", ���������� � �������������� \n";

	cout << "������������� ���������" << endl;
	system("pause");
}

void ShowClientInformation(string name, int number)				// �������� ���������� � ���������
{
	system("cls");

	if (name == "all" && number == -1)
	{
		for (int i = 0; i < 20; i++)
		{
			cout << i << ". " << Clients[i].getAccountNumber() << ", ";
			cout << Clients[i].getName() << endl;
			cout << Clients[i].getAdress() << endl;
			cout << "������: " << Clients[i].getBalance() << " ��� \n";
			cout << "��������� ��������: " << Clients[i].getAccountStatus() << endl;
			cout << "��������� �����������: " << Clients[i].getTVTariffName() << ", " << Clients[i].getTVTariff() << " ���/���� \n";
			cout << "��������: " << Clients[i].getInternetTariffName() << ", " << Clients[i].getInternetTariff() << " ���/���� \n\n";
		}
	}

	if (name == "current" && number >= 0 && number < 20)
	{
		cout << Clients[number].getAccountNumber() << ", ";
		cout << Clients[number].getName() << endl;
		cout << Clients[number].getAdress() << endl;
		cout << "������: " << Clients[number].getBalance() << " ��� \n";
		cout << "��������� ��������: " << Clients[number].getAccountStatus() << endl;
		cout << "��������� �����������: " << Clients[number].getTVTariffName() << ", " << Clients[number].getTVTariff() << " ���/���� \n";
		cout << "��������: " << Clients[number].getInternetTariffName() << ", " << Clients[number].getInternetTariff() << " ���/���� \n";
	}

	system("pause");
}