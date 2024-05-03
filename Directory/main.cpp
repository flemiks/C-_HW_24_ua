#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <algorithm> 

using namespace std;


class Directory {
public:
	Directory() {};
	Directory(string companyName, string ownerName, string phoneNumber, string address, string businessActivity) {
		setCompanyName(companyName);
		setOwnerName(ownerName);
		setPhoneNumber(phoneNumber);
		setAddress(address);
		setBusinessActivity(businessActivity);
	};
	void setCompanyName(string companyName){
		if (companyName.empty()) {
			throw invalid_argument("Company Name couldn't be empty");
		}
		this->companyName = companyName;
	}
	void setOwnerName(string ownerName) {
		if (ownerName.empty()) {
			throw invalid_argument("Owner Name couldn't be empty");
		}
		if (any_of(ownerName.begin(), ownerName.end(), ::isdigit)) {
			throw invalid_argument("Owner Name couldn't contain digits");
		}
		this->ownerName = ownerName;
	}
	void setPhoneNumber(string phoneNumber) {
		if (phoneNumber.empty()) {
			throw invalid_argument("Phone Number couldn't be empty");
		}
		if (!all_of(phoneNumber.begin(), phoneNumber.end(), ::isdigit)) {
			throw invalid_argument("Phone Number only contain only digit");
		}
		this->phoneNumber = phoneNumber;
	}
	void setAddress(string address) {
		if (address.empty()) {
			throw invalid_argument("Address couldn't be empty");
		}
		this->address = address;
	}
	void setBusinessActivity(string businessActivity) {
		if (businessActivity.empty()) {
			throw invalid_argument("Business Activity couldn't be empty");
		}
		this->businessActivity = businessActivity;
	}
	string getCompanyName() const {
		return companyName;
	}
	string getOwnerName() const {
		return ownerName;
	}
	string getPhoneNumber() const {
		return phoneNumber;
	}
	string getAddress() const {
		return address;
	}
	string getBusinessActivity() const {
		return businessActivity;
	}
	void save(ofstream &out) const {
		out << companyName << "," << ownerName << "," << phoneNumber << "," << address << "," << businessActivity << "\n";
	}
	void load(istream &in) {
		string line;
		if (getline(in, line)) {
			stringstream ss(line);
			getline(ss, companyName, ',');
			getline(ss, ownerName, ',');
			getline(ss, phoneNumber, ',');
			getline(ss, address, ',');
			getline(ss, businessActivity);
		}
	}
	void print() {
		cout << "Company Name: " << companyName << ", Owner Name: " << ownerName << ", Phone Number: " << phoneNumber << ", Address: " << address << ", Business Activity: " << businessActivity << endl;
	}
private:
	string companyName;
	string ownerName;
	string phoneNumber;
	string address;
	string businessActivity;
};

class DirectoryList {
public:
	DirectoryList() {};
	DirectoryList(string fileName) {
		setFileName(fileName);
	};
	void setFileName(string fileName) {
		if (fileName.empty()) {
			throw invalid_argument("File Name couldn't be empty");
		}
		this->fileName = fileName;
	}
	void addDirectory(string companyName, string ownerName, string phoneNumber, string address, string businessActivity) {
		directoryList.push_back(make_shared<Directory>(companyName, ownerName, phoneNumber, address, businessActivity));
	}
	void save() {
		ofstream out(fileName);
		if (!out.is_open()) {
			throw runtime_error("Failed to open file for writing: " + fileName);
		}
		for (auto& directory : directoryList) {
			directory->save(out);
		}
	}
	vector<shared_ptr<Directory>> load() {
		ifstream in(fileName);
		string line;
		if (!in.is_open()) {
			throw runtime_error("Failed to open file for writing: " + fileName);
		}
		while (getline(in, line))
		{
			auto directory = make_shared<Directory>();
			stringstream ss(line);
			(*directory).load(ss);
			directoryList.push_back(directory);
		}
		return directoryList;
	}

	void findCompanyName(string companyName) {
		bool isFind = false;
		for (auto& directory : directoryList) {
			if (directory->getCompanyName() == companyName) {
				directory->print();
				isFind = true;
			}
		}
		if (!isFind) {
			cout << "Nothing was found";
		}
	}
	void findOwnerName(string ownerName) {
		bool isFind = false;
		for (auto& directory : directoryList) {
			if (directory->getOwnerName() == ownerName) {
				directory->print();
				isFind = true;
			}
		}
		if (!isFind) {
			cout << "Nothing was found";
		}
	}
	void findPhoneNumber(string phoneNumber) {
		bool isFind = false;
		for (auto& directory : directoryList) {
			if (directory->getPhoneNumber() == phoneNumber) {
				directory->print();
				isFind = true;
			}
		}
		if (!isFind) {
			cout << "Nothing was found";
		}
	}
	void findBusinessActivity(string businessActivity) {
		bool isFind = false;
		for (auto& directory : directoryList) {
			if (directory->getBusinessActivity() == businessActivity) {
				directory->print();
				isFind = true;
			}
		}
		if (!isFind) {
			cout << "Nothing was found";
		}
	}
	void printAll() {
		for (auto& directory : directoryList) {
			directory->print();
		}
	}
private:
	vector<shared_ptr<Directory>> directoryList;
	string fileName;
};

int main() {
	try {
		DirectoryList d1("Tech Innovations");
		d1.addDirectory("Tech Innovations", "John1Doe", "1234567890", "123 Tech Street", "Technology");
		d1.addDirectory("Page Turners", "Alice Monroe", "3245678901", "456 Book Blvd", "Retail");
		d1.addDirectory("Daily Brews", "Mohamed Ali", "2345678901", "789 Coffee Road", "Cafe");
		d1.addDirectory("Tech Repairs", "Sara Lee", "1234567891", "123 Fix Street", "Technology Services");
		d1.addDirectory("Justitia Law", "Robert King", "9876543210", "321 Justice Ave", "Legal Services");
		d1.addDirectory("Bloom Flowers", "Fiona Chen", "1234598765", "654 Floral St", "Florist");
		d1.addDirectory("Green Thumb Landscaping", "Carlos Herb", "1234578901", "321 Green Road", "Landscaping");
		d1.addDirectory("AutoFix Mechanics", "Nina Morris", "9876501234", "789 Engine Block", "Automotive Repairs");
		d1.addDirectory("Fit & Fine Gym", "Leo Armstrong", "4567890123", "456 Workout Way", "Health & Fitness");
		d1.addDirectory("Clicks Digital", "Emma Clark", "2345601234", "101 Web Street", "Digital Marketing");
		d1.addDirectory("Happy Paws Vet", "Annie Smith", "8901234567", "123 Pet Lane", "Veterinary Services");
		d1.addDirectory("Tesla", "Elon Mask", "8901234567", "123 Pet Lane", "Car creating");
		d1.save();
		DirectoryList d2("Tech Innovations");
		d2.load();
		d2.printAll();
		cout << endl;
		d2.findBusinessActivity("Digital Marketing");


	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	return 0;
}