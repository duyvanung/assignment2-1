#include "reader.h"
#include"account.h"
#include"file.h"
#include"menu.h"
#include"reader.h"
void reader::reader_menu() {
	system("cls");
	cout << "------------------------LIBRO (USER)------------------------" << endl;
	cout << "1. Edit profile" << endl << "2. Book request" << endl << "3. Notification" << endl << "0. Log out" << endl;
	int choice;
	do {
		cout << "Enter your choice: ";
		cin >> choice;
	} while (choice < 0 || choice >3);
	switch (choice)
	{
	case 0: {menu m; m.mainmenu(); }break;
	case 1: edit_profile(); break;
	case 2: break;
	case 3: break;
	default:
		break;
	}
}

void reader::sign_in() {
	menu m;
	m.loading();
	system("cls");
	cin.ignore();
	cout << "-------------------------SIGN IN-------------------------" << endl;
	int size = 0;
	string username, pass, st;
	fstream user_read("reader_data.txt", ios::in | ios::out);
	while (getline(user_read, st)) { size++; }
	cout << "Number of account: " << size << endl;
	account *arrayaccount = new account[size];
	user_read.clear();
	user_read.seekg(0, 0);
	for (int i = 0; i < size; i++) {
		getline(user_read, st, ';');
		arrayaccount[i].set_id(st);
		getline(user_read, st, ';');
		arrayaccount[i].set_username(st);
		getline(user_read, st, ';');
		arrayaccount[i].set_password(st);
		getline(user_read, st);
	}
	user_read.close();

	cout << "Enter your username: ";
	fflush(stdin);
	getline(cin, username);
	cout << "Enter your password: ";
	fflush(stdin);
	getline(cin, pass);
	//	fflush(stdin);
	int verify = 0;
	for (int i = 0; i < size; i++) {
		if (username == arrayaccount[i].get_username()) {
			if (pass == arrayaccount[i].get_password()) {
				verify = 0; // Dang nhap thanh cong
				id_signed_in=arrayaccount[i].get_id();
				break;
			}
			else {
				verify = 1; // Sai mat khau
				break;
			}
		}
		else verify = 2; //Chua tim duoc username trong file
	}
	if (verify == 2) {
		cout << "This user doesn't exist" << endl << "1. Try different account" << endl << "2. Back to main menu" << endl;
		int choice = 0;
		do {
			cout << "Enter your choice: ";
			cin >> choice;
		} while (choice < 1 || choice >2);
		switch (choice)
		{
		case 1: sign_in(); break;
		case 2: m.mainmenu();
		default:
			break;
		}
	}
	else if (verify == 1) {
		cout << "Password is invalid" << endl;
		cout << "1. Try to sign in again" << endl << "2. Back to main menu" << endl;
		int choice = 0;
		do {
			cout << "Enter your choice: ";
			fflush(stdin);
			cin >> choice;
		} while (choice < 1 || choice >2);
		switch (choice)
		{
		case 1: sign_in(); break;
		case 2: m.mainmenu();
		default:
			break;
		}
	}
	else if (verify == 0) {
		reader_menu();
	}
}
void reader::edit_profile() {
	fstream read_data("reader_data.txt", ios::in);
	file f;
	int size, position;
	size = f.size(read_data);
	read_data.close();
	account *a = new account[size];
	f.read_account(a, size);
	for (int i = 0; i < size; i++) {
		if (a[i].get_id() == id_signed_in) {
			position = i;
			break;
		}
	}
	system("cls");
	cout << "Kind of informaion you want to change: " << endl << "1. User name" << endl << "2. Password" << endl << "3. Full name" << endl << "4. Birthday" << endl << "5. Phone number" << endl << "0. Back"<<endl;
	int choice = 0;
	do {
		cout << "Enter your choice: ";
		cin >> choice;
	} while (choice < 0 || choice > 5);
	switch (choice)
	{
	case 0: {reader_menu(); } break;
	case 1: {cout << "Sorry, you can't change your username, press any key to return" << endl;
		system("pause>nul");
		edit_profile();
	} break;
	case 2: {
		system("cls");
		cout << "----------------- CHANGE PASSWORD -----------------" << endl;
		cout << "Current password: ";
		string pass, newpass;
		fflush(stdin);
		cin >> pass;
		while (pass != a[position].get_password()) {
			cout << "Invalid password" << endl << "Enter your current password again: ";
			fflush(stdin);
			cin >> pass;
		}
		cout << "Enter new password: ";
		fflush(stdin);
		cin >> newpass;
		menu m;
		while (m.verify_semicolon(newpass) == 1) {
			cout << "Your password word mustn't content char \';\', retype it: ";
			fflush(stdin);
			cin >> newpass;
		}
		if (m.verify_semicolon(newpass) == 0) {
			a[position].set_password(newpass);
			cout << "Success!!!" << endl;
			system("pause>nul");
			file w;
			w.write_account(a, size);
			reader_menu();
		}
	} break;
	case 3: {
		system("cls");
		cout << "----------------CHANGE YOUR NAME---------------------";
		cout << "Your current name: " << a[position].get_name() << endl;
		cout << "Enter your new name: ";
		string newname;
		cin >> newname;
		menu m;
		while (m.verify_semicolon(newname) == 1) {
			cout << "Your name mustn't content char \';\', retype it: ";
			cin >> newname;
		}
		if (m.verify_semicolon(newname) == 0) {
			a[position].set_name(newname);
			cout << "Success!!!" << endl;
			system("pause>nul");
			file w;
			w.write_account(a, size);
			reader_menu();
		}
	}
			break;
	case 4: {
		system("cls");
		cout << "----------------CHANGE BIRTHDAY---------------------";
		cout << "Your current birthday: " << a[position].get_birthday() << endl;
		cout << "Enter new birthday: ";
		string newbirth;
		cin >> newbirth;
		menu m;
		while (m.verify_semicolon(newbirth) == 1) {
			cout << "Your birthday mustn't content char \';\', retype it: ";
			cin >> newbirth;
		}
		if (m.verify_semicolon(newbirth) == 0) {
			a[position].set_birthday(newbirth);
			cout << "Success!!!" << endl;
			system("pause>nul");
			file w;
			w.write_account(a, size);
			reader_menu();
		}
	}
			break;
	case 5: {
		system("cls");
		cout << "----------------CHANGE PHONE---------------------";
		cout << "Your current birthday: " << a[position].get_phone() << endl;
		cout << "Enter new birthday: ";
		string newphone;
		fflush(stdin);
		cin >> newphone;
		menu m;
		while (m.verify_semicolon(newphone) == 1) {
			cout << "Your birthday mustn't content char \';\', retype it: ";
			fflush(stdin);
			cin >> newphone;
		}
		if (m.verify_semicolon(newphone) == 0) {
			a[position].set_phone(newphone);
			cout << "Success!!!" << endl;
			system("pause>nul");
			file w;
			w.write_account(a, size);
			reader_menu();
		}
	}
			break;
	default:
		break;
	}
	delete[] a;
}
