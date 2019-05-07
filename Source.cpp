#include <iostream>		
#include <windows.h>
#include <string>
#include <fstream>
#include <time.h>

using namespace std;

class ClientUnit	// Класс клиента
{

private:
	string Name;			// Имя клиента
	string Adress;				// Адрес клиента
	unsigned int AccountNumber;				// Персональный номер аккаунта
	unsigned short int InternetTariff;				// Дневная плата за интернет
	unsigned short int TVTariff;			// Дневная плата за кабельное телевидение
	int Balance;			// Счёт клиента
	string AccountStatus;			// Состояние аккаунта

public:
	// set
	void setName(string Name) { this->Name = Name; };			// Установка имени
	void setAdress(string Adress) { this->Adress = Adress; };			// Установка адреса
	void setAccountNumber(int AccountNumber) { this->AccountNumber = AccountNumber; };				// Установка персонального клиентского номера
	void setInternetTariff(int InternetTariff) { this->InternetTariff = InternetTariff; };			// Установка дневной платы за интернет
	void setTVTariff(int TVTariff) { this->TVTariff = TVTariff; };				// Установка дневного тарифа за кабельное телевидение
	void setBalance(int Balance) { this->Balance = Balance; };				// Установка состояния счёта клиента
	void setAccountStatus(string AccountStatus) { this->AccountStatus = AccountStatus; };			// Установка состояние аккаунта

	void setAccountNull()			// Обнуление аккаунта
	{
		this->Name = "Null";
		this->Adress = "Null";
		this->InternetTariff = 0;
		this->TVTariff = 0;
		this->Balance = 0;
		this->AccountStatus = "Null";
	};

	// get
	string getName() { return Name; };				// Возврат имени
	string getAdress() { return Adress; };				// Возврать адреса
	int getAccountNumber() { return AccountNumber; };				// Возврат номера аккаунта
	int getTVTariff() { return TVTariff; };			// Возврат дневной платы за кабельное телевидение
	int getInternetTariff() { return InternetTariff; };				// Возврать дневной платы за интернет
	bool Empty()			// Если экземпляр пуст - вернёт true, иначе - false
	{
		if (this->Name == "Null")
			return true;
		else
			return false;
	};

	string getTVTariffName()			// Возврат названия тарифа кабельного телевидения
	{
		switch (TVTariff)
		{
		case 1: return "Мини";
			break;
		case 2: return "Средний";
			break;
		case 3: return "Мега";
			break;
		default: return "Не используется";
		}
	};

	string getInternetTariffName()				// Возврат названия тарифа интернета
	{
		switch (InternetTariff)
		{
		case 3: return "Мини";
			break;
		case 5: return "Безлим 10";
			break;
		case 6: return "Безлим 35";
			break;
		case 8: return "Безлим 50";
			break;
		case 10: return "Безлим 100";
			break;
		default: return "Не используется";
		}
	};

	int getBalance() { return Balance; };			// Возврат баланса аккаунта
	string getAccountStatus() { return AccountStatus; };			// Возврат состояния аккаунта
};

void Initialization();				// Функция начальной инициализации
void ShowClientInformation(string name, int number);			// Функция отображения информации о клиентах
void Service();				// Функция обслуживания клиентов
void ClientBase();				// Функция работы с клиентской базой
void UpdateInformation();			// Функция обновления информации в базе
void Refill();				// Функция пополнения счёт 
void UnitOperation(string name);			// Функций работы с абоненрами

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


ClientUnit Clients[20];				// Массив для хранения информации о клиентах

void main()
{
	SetConsoleOutputCP(1251);	SetConsoleCP(1251);

	Initialization();

	for (int Start = 0; Start != 3;)	
	{
		system("cls");

		cout << "1. Обслуживание посетителей \n2. Работа с клиентской базой \n3. Завершить работу \n>> ";
		cin >> Start;

		switch (Start)
		{
		case 1:	Service();
			break;
		case 2: ClientBase();
			break;
		case 3:	UpdateInformation(); system("pause");
			break;
		default: cout << "Некорректный вариант \n"; system("pause");
		}
	}
}

void Service()
{
	for (int Choose = 0; Choose != 4;)
	{
		system("cls");

		cout << "1. Пополнить счёт абонента \n2. Добавить нового абонента \n3. Заморозить аккаунт абонента \n4. Выход \n>> ";
		cin >> Choose;

		switch (Choose)
		{
		case 1:	Refill();
			break;
		case 2: UnitOperation("new");
			break;
		case 3:	UnitOperation("frozen");
			break;
		case 4: // Выход 
			UpdateInformation();
			break;
		default: cout << "Некорректный вариант\n"; system("pause");
		}
	}
}

void ClientBase()
{
	for (int Choose = 0; Choose != 4;)
	{
		system("cls");

		unsigned short int number;

		cout << "1. Постотреть абонентскую базу \n2. Найти абонента \n3. Удалить абонента \n4. Выход \n>> ";
		cin >> Choose;

		switch (Choose)
		{
		case 1:	ShowClientInformation("all", -1);
			break;
		case 2: system("cls");

				cout << "Введите лицевой счёт абонента(0 - 19) >> ";
				cin >> number;

				ShowClientInformation("current", number);
			break;
		case 3:	UnitOperation("del");
			break;
		case 4: // Выход 
				UpdateInformation();
			break;
		default: cout << "Некорректный вариант\n"; system("pause");
		}
	}
}

void UnitOperation(string name)
{
	system("cls");

	if (name == "new")				// Новый аккаунт
	{
		string Name, Adress;
		int Internet, TV, Balance;

		cout << "Введите имя нового абонента >>";
		cin.get();
		getline(cin, Name);

		cout << "Введите адрес нового абонента >>";
		getline(cin, Adress);

		for (;;)
		{
			cout << "Введите интернет тариф абонента \n0 - Не используется\n 3 - Мини \n5 - Безлим 10 \n6 - Безлим 35 \n8 - Безлим 50 \n10 - Безлим 100 \n>>";
			cin >> Internet;

			if (Internet == 0 || Internet == 3 || Internet == 5 || Internet == 6 || Internet == 8 || Internet == 10)
				break;

			else
				cout << "Некорректный вариант\n"; system("pause");
		}

		
		for (;;)
		{
			cout << "Введите тариф кабельного телевидения абонента \n0 - Не используется \n1 - Мини \n2 - Средний \n3 - Мега \n>>";
			cin >> TV;

			if (TV == 0 || TV == 1 || TV == 2 || TV == 3)
				break;

			else
				cout << "Некорректный вариант\n"; system("pause");
		}

		for (;;)
		{
			cout << "Введите начальный баланс абонента(0 - 5000) >>";
			cin >> Balance;

			if (Balance >= 0 && Balance <= 5000)
				break;

			else
				cout << "Некорректный вариант\n"; system("pause");
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
					Report << "Добавлен новый абонент, " << Name << endl << "Ему присвоен лицевой счёт: " << Clients[i].getAccountNumber() << endl << endl;

					Report.close();
				}

				else
					cout << "Невозможно открыть файл \"AllReports.total\", обратитесь к администратору \n"; system("pause");

				break;
			}
		}

		if (flag = false)
			cout << "Cписок переполнен \n"; system("pause");
	}

	if (name == "frozen")				// Замораживаю аккаунт
	{
		int AccountNumber;	bool Find = false;

		system("cls");

		cout << "Введите номер аккаунта >> ";
		cin >> AccountNumber;

		for (int i = 0; i < 20; i++)
		{
			if (AccountNumber == Clients[i].getAccountNumber())
			{
				int tmp = Clients[i].getBalance();

				Clients[i].setAccountStatus("Заморожен");

				Clients[i].setBalance(tmp - 20);
				Find = true;

				UpdateInformation();

				ofstream Report("AllReports.total", ios::app);

				if (Report.is_open())
				{
					// Report << getDate() << endl;
					Report << Clients[i].getAccountNumber() << ", " << Clients[i].getAdress() << endl;
					Report << "Аккаунт заморожен" << endl << endl;

					Report.close();

					cout << "Аккаунт успешно заморожен\n"; system("pause");
				}

				else
					cout << "Невозможно открыть файл \"AllReports.total\", обратитесь к администратору \n"; system("pause");

				break;
			}
		}

		if (Find == false)
			cout << "Абонент не найден\n"; system("pause");
	}

	if (name == "del")				// Удаление/отключение пользователя
	{
		int AccountNumber;	bool Find = false;

		system("cls");

		cout << "Введите номер аккаунта >> ";
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
					Report << "Аккаунт" << Clients[i].getName() << ", " << Clients[i].getAdress();
					Report << " удалён из базы" << endl << endl;

					Report.close();
				}

				else
					cout << "Невозможно открыть файл \"AllReports.total\", обратитесь к администратору \n"; system("pause");

				Clients[i].setAccountNull();

				break;
			}
		}

		if (Find == false)
			cout << "Абонент не найден\n"; system("pause");
	}
}

void Refill()
{
	int AccountNumber;	bool Find = false;

	system("cls");

	cout << "Введите номер аккаунта >> ";
	cin >> AccountNumber;

	for (int i = 0; i < 20; i++)
	{
		if (AccountNumber == Clients[i].getAccountNumber())
		{
			int tmp = Clients[i].getBalance(), sum = 0;

			cout << "Введите сумму >> ";
			cin >> sum;

			Clients[i].setBalance(tmp + sum);
			Find = true;

			UpdateInformation();

			ofstream Report("AllReports.total", ios::app);

			if (Report.is_open())
			{
				// Report << getDate() << endl;
				Report << "Счёт абонента " << Clients[i].getAccountNumber() << ", " << Clients[i].getAdress() << endl;
				Report << "Пополнен на " << sum << "руб" << endl << endl;

				Report.close();
			}

			else
				cout << "Невозможно открыть файл \"AllReports.total\", обратитесь к администратору \n"; system("pause");


			break;
		}
	}

	if (Find == false)
		cout << "Абонент не найден\n"; system("pause");
}

void UpdateInformation()			// Обновление информации в базе
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
		cout << "Невозможно открыть файл \"ClientInformation.base\", обратитесь к администратору \n";
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
		cout << "Невозможно открыть файл \"ClientInformation.base\", обратитесь к администратору \n";

	cout << "Инициализация завершена" << endl;
	system("pause");
}

void ShowClientInformation(string name, int number)				// Показать информацию о абонентах
{
	system("cls");

	if (name == "all" && number == -1)
	{
		for (int i = 0; i < 20; i++)
		{
			cout << i << ". " << Clients[i].getAccountNumber() << ", ";
			cout << Clients[i].getName() << endl;
			cout << Clients[i].getAdress() << endl;
			cout << "Баланс: " << Clients[i].getBalance() << " руб \n";
			cout << "Состояние аккаунта: " << Clients[i].getAccountStatus() << endl;
			cout << "Кабельное телевидение: " << Clients[i].getTVTariffName() << ", " << Clients[i].getTVTariff() << " руб/день \n";
			cout << "Интернет: " << Clients[i].getInternetTariffName() << ", " << Clients[i].getInternetTariff() << " руб/день \n\n";
		}
	}

	if (name == "current" && number >= 0 && number < 20)
	{
		cout << Clients[number].getAccountNumber() << ", ";
		cout << Clients[number].getName() << endl;
		cout << Clients[number].getAdress() << endl;
		cout << "Баланс: " << Clients[number].getBalance() << " руб \n";
		cout << "Состояние аккаунта: " << Clients[number].getAccountStatus() << endl;
		cout << "Кабельное телевидение: " << Clients[number].getTVTariffName() << ", " << Clients[number].getTVTariff() << " руб/день \n";
		cout << "Интернет: " << Clients[number].getInternetTariffName() << ", " << Clients[number].getInternetTariff() << " руб/день \n";
	}

	system("pause");
}