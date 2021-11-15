#include <iostream>
#include <vector>
using std::string;
using std::cout;
using std::endl;
/*
Four Concepts of OOP:

1. Encapsulation: Access Modifiers, Constructors
2. Abstraction: Interface, Abstract Class, Pure Virtual Function
3. Inheritence
4. Polymorphism: Base clase pointer can refer to derived class objects;
*/

class AbstractEmployee {
	virtual void AskForPromotion()=0;
};

class Employee: AbstractEmployee {
	protected:
		string Name;
	private:
		int Age;
		string Company;
	public:
		Employee(string name, int age, string company) {
			this->Name = name;
			this->Age = age;
			this->Company = company;
		}
		
		void SetName(string name) {
			if(name != "Apply Board") {
				this->Name = name;
			}
		}
		void SetAge(int age) {
			if(age >= 18) {
				this->Age = age;
			}
		}
		void SetCompany(string company) {
			this->Company = company;
		}
		string GetName() {
			return this->Name;
		}
		int GetAge() {
			return this->Age;
		}
		string GetCompany() {
			return this->Company;
		}
		
		void IntroduceYourself() {
			cout << "Name - " << Name << endl;
			cout << "Age  - " << Age << endl;
			cout << "Company - " << Company << endl;
		}
		void AskForPromotion() {
			if(this->Age > 30) {
				cout << Name << " got promoted!" << std::endl;
			} else {
				cout << Name << " , sorry NO promotion for you!" << std::endl;
			}
		}
		virtual void Work() {
			cout << Name << " is checking email, task backlog, performing tasks..." << endl;
		}
};

class Developer:public Employee {
public:
	string FavProgrammingLanguage;
	Developer(string name, int age, string company, string favProgrammingLanguage): Employee(name, age, company) {
		this->FavProgrammingLanguage = favProgrammingLanguage;
	}
	void FixBug(){
		//protected member give direct access to attributes of base class to derived class method;
		//derived class by default can not access base class attribute
		cout << this->Name << " fixed bug using " << this->FavProgrammingLanguage << endl;
	}
	void Work() {
		cout << Name << " is writing " << FavProgrammingLanguage << " code" << endl;
	}
};

class Teacher: public Employee {
public:
	string Subject;
	Teacher(string name, int age, string company, string Subject): Employee(name, age, company) {
		this->Subject = Subject;
	}
	void PrepareLesson() {
		cout << Name << " is preparing " << Subject << " lesson" << std::endl;
	}
	void Work() {
		cout << Name << " is teaching " << Subject  << endl;
	}
};

int main() {
	// Developer d("Saldina", 25, "YT", "C++");
	// Teacher t("Jack", 35, "Cool School", "History");
	Employee* emp1 = new Developer("Saldina", 25, "YT", "C++");
	Employee* emp2 = new Teacher("Jack", 35, "Cool School", "History");
	emp1->Work();
	emp2->Work();
	return 0;
}

