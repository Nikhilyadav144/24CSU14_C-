#include <iostream>
#include <string>
using namespace std;
class Person {
private:
    string name;
    int age;
    string id;
    long int contactInfo;
public:
    Person(string n,int a,string i,long int c) {
        name=n;
        age=a;
        id=i;
        contactInfo=c;
    }
    string getName(){return name;}
    int getAge(){return age;}
    string getId(){return id;}
    long int getContactInfo(){return contactInfo;}
    void setName(string n){name=n;}
    void setAge(int a){age=a;}
    void setId(string i){id=i;}
    void setContactInfo(long int c){contactInfo=c;}
    virtual void displayInfo() {
        cout<<"Name: "<<name<<endl;
        cout<<"Age: "<<age<<endl;
        cout<<"ID: "<<id<<endl;
        cout<<"Phone Number: "<<contactInfo<<endl;
    }
};
class Student:public Person {
private:
    string enrollmentDate;
    string program;
    float gpa;
public:
    Student(string n,int a,string i,long int c,string e,string p,float g):Person(n,a,i,c) {
        enrollmentDate=e;
        program=p;
        gpa=g;
    }
    string getEnrollmentDate(){return enrollmentDate;}
    string getProgram(){return program;}
    float getGpa(){return gpa;}
    void setEnrollmentDate(string e){enrollmentDate=e;}
    void setProgram(string p){program=p;}
    void setGpa(float g){gpa=g;}
    void displayInfo() override {
        Person::displayInfo();
        cout<<"Enrollment Date: "<<enrollmentDate<<endl;
        cout<<"Program: "<<program<<endl;
        cout<<"GPA: "<<gpa<<endl;
    }
};
class Professor:public Person {
private:
    string department;
    string specialization;
    string hireDate;
public:
    Professor(string n,int a,string i,long int c,string d,string s,string h):Person(n,a,i,c) {
        department=d;
        specialization=s;
        hireDate=h;
    }
    string getDepartment(){return department;}
    string getSpecialization(){return specialization;}
    string getHireDate(){return hireDate;}
    void setDepartment(string d){department=d;}
    void setSpecialization(string s){specialization=s;}
    void setHireDate(string h){hireDate=h;}
    void displayInfo() override {
        Person::displayInfo();
        cout<<"Department: "<<department<<endl;
        cout<<"Specialization: "<<specialization<<endl;
        cout<<"Hire Date: "<<hireDate<<endl;
    }
};
class Course {
private:
    string code;
    string title;
    int credits;
    string description;
public:
    Course(string c,string t,int cr,string d) {
        code=c;
        title=t;
        credits=cr;
        description=d;
    }
    string getCode(){return code;}
    string getTitle(){return title;}
    int getCredits(){return credits;}
    string getDescription(){return description;}
    void setCode(string c){code=c;}
    void setTitle(string t){title=t;}
    void setCredits(int cr){credits=cr;}
    void setDescription(string d){description=d;}
    void displayInfo() {
        cout<<"Course Code: "<<code<<endl;
        cout<<"Title: "<<title<<endl;
        cout<<"Credits: "<<credits<<endl;
        cout<<"Description: "<<description<<endl;
    }
};
class Department {
private:
    string name;
    string location;
    double budget;
public:
    Department(string n,string l,double b) {
        name=n;
        location=l;
        budget=b;
    }
    string getName(){return name;}
    string getLocation(){return location;}
    double getBudget(){return budget;}
    void setName(string n){name=n;}
    void setLocation(string l){location=l;}
    void setBudget(double b){budget=b;}
    void displayInfo() {
        cout<<"Department Name: "<<name<<endl;
        cout<<"Location: "<<location<<endl;
        cout<<"Budget: $"<<budget<<endl;
    }
};
int main() {
    Person person1("Krish sharma",18,"P001",8851770747);
    Person person2("Manjeet yadav",20,"P002",9899891897);
    Student student1("Meet yadav",19,"S001",9953747875,"2025-05-05","Computer science",3.8);
    Student student2("Mehul batra",22,"S002",9996312013,"2025-5-05","Data science",3.5);
    Professor prof1("Dr.Nikhil",45,"PR001",7303420333,"Computer science","AI","2010-04-15");
    Professor prof2("Dr.Lakshay",50,"PR002",9910625639,"Engineering","Robotics","2008-03-20");
    Course course1("CS101","Introduction to FOCP",3,"Basic FOCP concepts");
    Course course2("ENG201","Engineering",4,"Advanced engineering");
    Department dept1("Computer Science","Building A",1000000.00);
    Department dept2("Engineering","Building B",1500000.00);

    cout<<"\n=== Person Information ==="<<endl;
    person1.displayInfo();
    cout<<endl;
    person2.displayInfo();

    cout<<"\n=== Student Information ==="<<endl;
    student1.displayInfo();
    cout<<endl;
    student2.displayInfo();

    cout<<"\n=== Professor Information ==="<<endl;
    prof1.displayInfo();
    cout<<endl;
    prof2.displayInfo();

    cout<<"\n=== Course Information ==="<<endl;
    course1.displayInfo();
    cout<<endl;
    course2.displayInfo();

    cout<<"\n=== Department Information ==="<<endl;
    dept1.displayInfo();
    cout<<endl;
    dept2.displayInfo();

    return 0;
}