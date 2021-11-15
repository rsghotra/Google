#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include <iostream>
using namespace std;


class Employee {
	private:
		string Name;
		string Company;
		int Age;
	public:
		Employee(string name, string company, int age) {
			this->Name = name;
			this->Company = company;
			this->Age = age; 
		}

		void IntroduceYourself() {
			std::cout << "Name - " << this->Name << std::endl;
			std::cout << "Company - " << Company << std::endl;
			std::cout << "Age - " << this->Age << std::endl;
		}

};

#endif