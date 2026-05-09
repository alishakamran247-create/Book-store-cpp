#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Function prototypes
void add_record();
void display_records();
void search_by_name(const string& book_name);
void search_by_genre(const string& genre);
void update_record(const string& book_name);
void delete_record(int id);

int main() {
	int choice;

	do {
		cout << "Welcome to Book Store\n";
		cout << "Press 1 to add new record\n";
		cout << "Press 2 to display all records\n";
		cout << "Press 3 to search record by Book name\n";
		cout << "Press 4 to search record by Genre\n";
		cout << "Press 5 to update record by Book name\n";
		cout << "Press 6 to delete record by ID\n";
		cout << "Press 7 to exit\n";
		cout << "Enter your choice: ";
		cin >> choice;
		cin.ignore(); // Clear newline after choice

		switch (choice) {
		case 1: add_record(); break;
		case 2: display_records(); break;
		case 3: {
					string book_name;
					cout << "Enter Book Name: ";
					getline(cin, book_name);
					search_by_name(book_name);
					break;
		}
		case 4: {
					string genre;
					cout << "Enter Genre: ";
					getline(cin, genre);
					search_by_genre(genre);
					break;
		}
		case 5: {
					string book_name;
					cout << "Enter Book Name to Update: ";
					getline(cin, book_name);
					update_record(book_name);
					break;
		}
		case 6: {
					int id;
					cout << "Enter ID to Delete: ";
					cin >> id;
					delete_record(id);
					break;
		}
		case 7: cout << "Exiting...\n"; break;
		default: cout << "Invalid choice! Please try again.\n";
		}
	} while (choice != 7);

	return 0; // Added return statement
}

void add_record() {
	ofstream file("bookstore.txt", ios::app);
	if (!file) {
		cout << "Error opening file!\n";
		return;
	}

	int id;
	string book_name, genre, publisher, mobile, address;

	cout << "Enter ID: ";
	cin >> id; // Read ID directly
	cin.ignore(); // Clear the newline character
	cout << "Enter Book Name: ";
	getline(cin, book_name);
	cout << "Enter Genre: ";
	getline(cin, genre);
	cout << "Enter Publisher: ";
	getline(cin, publisher);
	cout << "Enter Mobile: ";
	getline(cin, mobile);
	cout << "Enter Address: ";
	getline(cin, address);

	file << id << "," << book_name << "," << genre << "," << publisher << ","
		<< mobile << "," << address << endl;

	file.close();
	cout << "Record added successfully!\n";
}

void display_records() {
	ifstream file("bookstore.txt");
	if (!file) {
		cout << "Error opening file!\n";
		return;
	}

	int id;
	string book_name, genre, publisher, mobile, address;

	cout << "All Records:\n";
	while (file.good()) {
		file >> id;
		file.ignore(); // Ignore the comma after ID
		getline(file, book_name, ',');
		getline(file, genre, ',');
		getline(file, publisher, ',');
		getline(file, mobile, ',');
		getline(file, address);

		if (file) { // Check if the read was successful
			cout << "ID: " << id << ", Book Name: " << book_name
				<< ", Genre: " << genre << ", Publisher: " << publisher
				<< ", Mobile: " << mobile << ", Address: " << address << endl;
		}
	}

	file.close();
}

void search_by_name(const string& book_name) {
	ifstream file("bookstore.txt");
	if (!file) {
		cout << "Error opening file!\n";
		return;
	}

	int id;
	string name, genre, publisher, mobile, address;
	bool found = false;

	while (file.good()) {
		file >> id;
		file.ignore(); // Ignore the comma after ID
		getline(file, name, ',');
		getline(file, genre, ',');
		getline(file, publisher, ',');
		getline(file, mobile, ',');
		getline(file, address);

		if (name == book_name) {
			cout << "Record Found: ID: " << id << ", Book Name: " << name
				<< ", Genre: " << genre << ", Publisher: " << publisher
				<< ", Mobile: " << mobile << ", Address: " << address << endl;
			found = true;
			break; // Exit once found
		}
	}

	if (!found) {
		cout << "No record found for Book Name: " << book_name << endl;
	}

	file.close();
}

void search_by_genre(const string& genre) {
	ifstream file("bookstore.txt");
	if (!file) {
		cout << "Error opening file!\n";
		return;
	}

	int id;
	string book_name, current_genre, publisher, mobile, address;
	bool found = false;

	while (file.good()) {
		file >> id;
		file.ignore(); // Ignore the comma after ID
		getline(file, book_name, ',');
		getline(file, current_genre, ',');
		getline(file, publisher, ',');
		getline(file, mobile, ',');
		getline(file, address);

		if (current_genre == genre) {
			cout << "Record Found: ID: " << id << ", Book Name: " << book_name
				<< ", Genre: " << current_genre << ", Publisher: " << publisher
				<< ", Mobile: " << mobile << ", Address: " << address << endl;
			found = true;
		}
	}

	if (!found) {
		cout << "No records found for Genre: " << genre << endl;
	}

	file.close();
}

void update_record(const string& book_name) {
	ifstream file("bookstore.txt");
	if (!file) {
		cout << "Error opening file!\n";
		return;
	}

	ofstream temp_file("temp.txt");
	if (!temp_file) {
		cout << "Error creating temporary file!\n";
		return;
	}

	int id;
	string name, genre, publisher, mobile, address;
	bool found = false;

	while (file.good()) {
		file >> id;
		file.ignore(); // Ignore the comma after ID
		getline(file, name, ',');
		getline(file, genre, ',');
		getline(file, publisher, ',');
		getline(file, mobile, ',');
		getline(file, address);

		if (name == book_name) {
			cout << "Updating Record for Book Name: " << name << endl;
			found = true;
			cout << "Enter new ID: ";
			cin >> id; // Read new ID
			cin.ignore(); // Clear the newline character
			cout << "Enter new Book Name: ";
			getline(cin, name);
			cout << "Enter new Genre: ";
			getline(cin, genre);
			cout << "Enter new Publisher: ";
			getline(cin, publisher);
			cout << "Enter new Mobile: ";
			getline(cin, mobile);
			cout << "Enter new Address: ";
			getline(cin, address);
		}
		temp_file << id << "," << name << "," << genre << "," << publisher
			<< "," << mobile << "," << address << endl;
	}

	if (!found) {
		cout << "No record found for Book Name: " << book_name << endl;
	}

	file.close();
	temp_file.close();
	remove("bookstore.txt");
	rename("temp.txt", "bookstore.txt");
}

void delete_record(int id) {
	ifstream file("bookstore.txt");
	if (!file) {
		cout << "Error opening file!\n";
		return;
	}

	ofstream temp_file("temp.txt");
	if (!temp_file) {
		cout << "Error creating temporary file!\n";
		return;
	}

	int current_id;
	string book_name, genre, publisher, mobile, address;
	bool found = false;

	while (file.good()) {
		file >> current_id;
		file.ignore(); // Ignore the comma after current ID
		getline(file, book_name, ',');
		getline(file, genre, ',');
		getline(file, publisher, ',');
		getline(file, mobile, ',');
		getline(file, address);

		if (current_id != id) {
			temp_file << current_id << "," << book_name << "," << genre
				<< "," << publisher << "," << mobile << "," << address << endl;
		}
		else {
			found = true;
		}
	}

	if (found) {
		cout << "Record with ID: " << id << " has been deleted successfully.\n";
	}
	else {
		cout << "No record found with ID: " << id << endl;
	}

	file.close();
	temp_file.close();
	remove("bookstore.txt");
	rename("temp.txt", "bookstore.txt");
}

