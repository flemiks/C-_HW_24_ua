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
		if (!all_of(ownerName.begin(), ownerName.end(), ::isalpha)) {
			throw invalid_argument("Owner Name could contain only letters");
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
	void load(ifstream &in) {
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
		directoryList.push_back(make_unique<Directory>(companyName, ownerName, phoneNumber, address, businessActivity));
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
	vector<unique_ptr<Directory>> load() {
		ifstream in(fileName);
		if (!in.is_open()) {
			throw runtime_error("Failed to open file for writing: " + fileName);
		}
		for (auto& directory : directoryList) {
			directory->load(in);
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
	vector<unique_ptr<Directory>> directoryList;
	string fileName;
};

int main() {
	try {
		DirectoryList d1("Tech Innovations");
		d1.addDirectory("Tech Innovations", "John Doe", "1234567890", "123 Tech Street", "Technology");
		d1.save();
		d1.load();


	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	return 0;
}