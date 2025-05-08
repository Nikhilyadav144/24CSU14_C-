#include <iostream>
#include <string>
#include <fstream>
using namespace std;

const int MAX_COURSES = 10;
const int MAX_STUDENTS = 50;
const int MAX_PROFS = 20;
const int MAX_DEPTS = 5;
const int MAX_ROOMS = 30;

class course;
class professor;
class student;

class UniversitySystemException {
protected:
    string msg;
    string details;
public:
    UniversitySystemException(string message, string info = "") {
        msg = message;
        details = info;
    }
    
    virtual string getMessage() const { return msg; }
    virtual string getDetails() const { return details; }
    
    virtual void log() {
        ofstream logFile("university_errors.log", ios::app);
        if(logFile.is_open()) {
            logFile << "Error: " << msg << endl;
            logFile << "Details: " << details << endl;
            logFile << "------------------------" << endl;
            logFile.close();
        }
    }
};

class EnrollmentException : public UniversitySystemException {
public:
    EnrollmentException(string message, string info = "") 
        : UniversitySystemException(message, info) {}
};

class GradeException : public UniversitySystemException {
public:
    GradeException(string message, string info = "") 
        : UniversitySystemException(message, info) {}
};

class PaymentException : public UniversitySystemException {
public:
    PaymentException(string message, string info = "") 
        : UniversitySystemException(message, info) {}
};

class ValidationException : public UniversitySystemException {
public:
    ValidationException(string message, string info = "") 
        : UniversitySystemException(message, info) {}
};

class person {
private:
    string n;
    int a;
    string i;
    long long p;
protected:
    double pay;
public:
    person(string name, int age, string id, long long phone) {
        if(name.empty()) throw ValidationException("Invalid name", "Name cannot be empty");
        if(age < 0 || age > 120) throw ValidationException("Invalid age", "Age must be between 0 and 120");
        if(id.empty()) throw ValidationException("Invalid ID", "ID cannot be empty");
        if(phone < 1000000000) throw ValidationException("Invalid phone", "Phone number must be valid");
        
        n = name;
        a = age;
        i = id;
        p = phone;
        pay = 0.0;
    }
    virtual ~person() {}
    
    string getn() { return n; }
    int geta() { return a; }
    string geti() { return i; }
    long long getp() { return p; }
    
    void setn(string name) { 
        if(name.empty()) throw ValidationException("Invalid name", "Name cannot be empty");
        n = name; 
    }
    void seta(int age) { 
        if(age < 0 || age > 120) throw ValidationException("Invalid age", "Age must be between 0 and 120");
        a = age; 
    }
    void seti(string id) { 
        if(id.empty()) throw ValidationException("Invalid ID", "ID cannot be empty");
        i = id; 
    }
    void setp(long long phone) { 
        if(phone < 1000000000) throw ValidationException("Invalid phone", "Phone number must be valid");
        p = phone; 
    }
    
    virtual void show() {
        cout << "name: " << n << endl;
        cout << "age: " << a << endl;
        cout << "id: " << i << endl;
        cout << "phone: " << p << endl;
    }
    
    virtual double getpay() {
        return pay;
    }
};

class classroom {
private:
    string r;
    int cap;
    bool p;
    bool o;
public:
    classroom(string room, int c, bool proj) {
        if(room.empty()) throw ValidationException("Invalid room", "Room number cannot be empty");
        if(c <= 0) throw ValidationException("Invalid capacity", "Capacity must be positive");
        
        r = room;
        cap = c;
        p = proj;
        o = false;
    }
    
    string getr() { return r; }
    int getcap() { return cap; }
    bool getp() { return p; }
    bool geto() { return o; }
    
    void seto(bool s) { o = s; }
};

class course {
private:
    string c;
    string t;
    int cr;
    string d;
    professor* p;
    classroom* r;
    student* s[MAX_STUDENTS];
    int numStudents;
    bool enrollmentOpen;
    string prerequisites[MAX_COURSES];
    int numPrerequisites;
    string semester;
public:
    course(string code, string title, int cred, string desc) {
        if(code.empty()) throw ValidationException("Invalid code", "Course code cannot be empty");
        if(title.empty()) throw ValidationException("Invalid title", "Course title cannot be empty");
        if(cred <= 0) throw ValidationException("Invalid credits", "Credits must be positive");
        
        c = code;
        t = title;
        cr = cred;
        d = desc;
        p = nullptr;
        r = nullptr;
        numStudents = 0;
        enrollmentOpen = true;
        numPrerequisites = 0;
        semester = "";
        for(int i = 0; i < MAX_STUDENTS; i++) {
            s[i] = nullptr;
        }
    }
    
    string gett() { return t; }
    void setp(professor* prof) { p = prof; }
    void setr(classroom* room) { r = room; }
    
    void addstudent(student* stu);
    void show();
    
    void closeEnrollment() { enrollmentOpen = false; }
    void openEnrollment() { enrollmentOpen = true; }
    bool isEnrollmentOpen() { return enrollmentOpen; }
    
    void addPrerequisite(string prereq) {
        if(numPrerequisites < MAX_COURSES) {
            prerequisites[numPrerequisites++] = prereq;
        }
    }
    
    void setSemester(string sem) { semester = sem; }
    string getSemester() { return semester; }
    
    bool hasPrerequisite(string prereq) {
        for(int i = 0; i < numPrerequisites; i++) {
            if(prerequisites[i] == prereq) return true;
        }
        return false;
    }
};

class professor : public person {
protected:
    string d;
    string s;
    string h;
    double sal;
    int y;
    course* c[MAX_COURSES];
    int numCourses;
public:
    professor(string name, int age, string id, long long phone, string dept, string spec, string hire) 
        : person(name, age, id, phone) {
        if(dept.empty()) throw ValidationException("Invalid department", "Department cannot be empty");
        if(spec.empty()) throw ValidationException("Invalid specialization", "Specialization cannot be empty");
        if(hire.empty()) throw ValidationException("Invalid hire date", "Hire date cannot be empty");
        
        d = dept;
        s = spec;
        h = hire;
        sal = 0.0;
        y = 0;
        numCourses = 0;
        for(int i = 0; i < MAX_COURSES; i++) {
            c[i] = nullptr;
        }
    }
    
    virtual void show() override {
        person::show();
        cout << "dept: " << d << endl;
        cout << "spec: " << s << endl;
        cout << "hire date: " << h << endl;
        cout << "years: " << y << endl;
        cout << "salary: ₹" << sal << endl;
        cout << "courses: " << numCourses << endl;
    }
    
    void addcourse(course* course);
    
    virtual double getpay() override {
        try {
            if(sal < 0) throw PaymentException("Invalid salary", "Salary cannot be negative");
            return sal + (y * 50000);
        }
        catch(PaymentException& e) {
            e.log();
            throw;
        }
    }
};

class student : public person {
protected:
    string ed;
    string prog;
    float g;
    course* c[MAX_COURSES];
    int numCourses;
    float grades[MAX_COURSES];
public:
    student(string name, int age, string id, long long phone, string enroll, string program, float gpa) 
        : person(name, age, id, phone) {
        if(enroll.empty()) throw ValidationException("Invalid enrollment date", "Enrollment date cannot be empty");
        if(program.empty()) throw ValidationException("Invalid program", "Program cannot be empty");
        if(gpa < 0 || gpa > 4.0) throw ValidationException("Invalid GPA", "GPA must be between 0 and 4.0");
        
        ed = enroll;
        prog = program;
        g = gpa;
        numCourses = 0;
        for(int i = 0; i < MAX_COURSES; i++) {
            c[i] = nullptr;
            grades[i] = 0.0;
        }
    }
    
    virtual void show() override {
        person::show();
        cout << "enroll date: " << ed << endl;
        cout << "program: " << prog << endl;
        cout << "gpa: " << g << endl;
        cout << "courses: " << numCourses << endl;
    }
    
    void addcourse(course* course);
    
    virtual double getpay() override {
        try {
            if(pay < 0) throw PaymentException("Invalid payment", "Payment cannot be negative");
            return pay - (numCourses * 50000);
        }
        catch(PaymentException& e) {
            e.log();
            throw;
        }
    }
    
    void setGrade(int courseIndex, float grade) {
        if(courseIndex < 0 || courseIndex >= numCourses) {
            throw GradeException("Invalid course index", "Course index out of range");
        }
        if(grade < 0 || grade > 4.0) {
            throw GradeException("Invalid grade", "Grade must be between 0 and 4.0");
        }
        grades[courseIndex] = grade;
    }
    
    float getGrade(int courseIndex) {
        if(courseIndex < 0 || courseIndex >= numCourses) {
            throw GradeException("Invalid course index", "Course index out of range");
        }
        return grades[courseIndex];
    }
    
    float calculateGPA() {
        if(numCourses == 0) return 0.0;
        float sum = 0.0;
        for(int i = 0; i < numCourses; i++) {
            sum += grades[i];
        }
        return sum / numCourses;
    }
    
    int getNumCourses() const { return numCourses; }
    course* getCourse(int index) const { 
        if(index < 0 || index >= numCourses) return nullptr;
        return c[index]; 
    }
};

void course::addstudent(student* stu) {
    try {
        if(!enrollmentOpen) {
            throw EnrollmentException("Enrollment closed", "Course enrollment is not open");
        }
        if(numStudents >= MAX_STUDENTS) {
            throw EnrollmentException("Course full", "Maximum number of students reached");
        }
        
        // Check prerequisites
        for(int i = 0; i < numPrerequisites; i++) {
            bool hasPrereq = false;
            for(int j = 0; j < stu->getNumCourses(); j++) {
                course* enrolledCourse = stu->getCourse(j);
                if(enrolledCourse && enrolledCourse->gett() == prerequisites[i]) {
                    hasPrereq = true;
                    break;
                }
            }
            if(!hasPrereq) {
                throw EnrollmentException("Prerequisites not met", "Student has not completed required prerequisites");
            }
        }
        
        s[numStudents++] = stu;
    }
    catch(EnrollmentException& e) {
        e.log();
        throw;
    }
}

void course::show() {
    cout << "code: " << c << endl;
    cout << "title: " << t << endl;
    cout << "credits: " << cr << endl;
    cout << "desc: " << d << endl;
    if(p) cout << "prof: " << p->getn() << endl;
    if(r) cout << "room: " << r->getr() << endl;
    cout << "students: " << numStudents << endl;
    cout << "enrollment: " << (enrollmentOpen ? "open" : "closed") << endl;
    cout << "semester: " << semester << endl;
    if(numPrerequisites > 0) {
        cout << "prerequisites: ";
        for(int i = 0; i < numPrerequisites; i++) {
            cout << prerequisites[i] << " ";
        }
        cout << endl;
    }
}

void student::addcourse(course* course) {
    try {
        if(numCourses >= MAX_COURSES) {
            throw EnrollmentException("Maximum courses reached", "Student cannot enroll in more courses");
        }
        if(!course->isEnrollmentOpen()) {
            throw EnrollmentException("Enrollment closed", "Course enrollment is not open");
        }
        c[numCourses++] = course;
        course->addstudent(this);
    }
    catch(EnrollmentException& e) {
        e.log();
        throw;
    }
}

void professor::addcourse(course* course) {
    try {
        if(numCourses >= MAX_COURSES) {
            throw EnrollmentException("Maximum courses reached", "Professor cannot teach more courses");
        }
        c[numCourses++] = course;
        course->setp(this);
    }
    catch(EnrollmentException& e) {
        e.log();
        throw;
    }
}

class undergrad : public student {
private:
    string m;
    string min;
    string gd;
public:
    undergrad(string name, int age, string id, long long phone, string enroll, string program, float gpa,
             string major, string minor, string grad) 
        : student(name, age, id, phone, enroll, program, gpa) {
        if(major.empty()) throw ValidationException("Invalid major", "Major cannot be empty");
        if(minor.empty()) throw ValidationException("Invalid minor", "Minor cannot be empty");
        if(grad.empty()) throw ValidationException("Invalid graduation date", "Graduation date cannot be empty");
        
        m = major;
        min = minor;
        gd = grad;
    }
    
    void show() override {
        student::show();
        cout << "major: " << m << endl;
        cout << "minor: " << min << endl;
        cout << "grad date: " << gd << endl;
    }
};

class grad : public student {
private:
    string r;
    professor* adv;
    string t;
    bool ta;
    bool ra;
public:
    grad(string name, int age, string id, long long phone, string enroll, string program, float gpa,
         string research, professor* advisor, string thesis) 
        : student(name, age, id, phone, enroll, program, gpa) {
        if(research.empty()) throw ValidationException("Invalid research", "Research area cannot be empty");
        if(thesis.empty()) throw ValidationException("Invalid thesis", "Thesis topic cannot be empty");
        
        r = research;
        adv = advisor;
        t = thesis;
        ta = false;
        ra = false;
    }
    
    void show() override {
        student::show();
        cout << "research: " << r << endl;
        cout << "thesis: " << t << endl;
        if(adv) cout << "advisor: " << adv->getn() << endl;
        cout << "ta: " << (ta ? "yes" : "no") << endl;
        cout << "ra: " << (ra ? "yes" : "no") << endl;
    }
    
    void setta(bool s) { ta = s; }
    void setra(bool s) { ra = s; }
    
    double getpay() override {
        try {
            double p = student::getpay();
            if(ta) p += 150000;
            if(ra) p += 200000;
            if(p < 0) throw PaymentException("Invalid payment", "Payment cannot be negative");
            return p;
        }
        catch(PaymentException& e) {
            e.log();
            throw;
        }
    }
};

class asstprof : public professor {
private:
    int p;
    double g;
public:
    asstprof(string name, int age, string id, long long phone, string dept, string spec, string hire) 
        : professor(name, age, id, phone, dept, spec, hire) {
        p = 0;
        g = 0.0;
    }
    
    void show() override {
        professor::show();
        cout << "rank: asst prof" << endl;
        cout << "papers: " << p << endl;
        cout << "grants: ₹" << g << endl;
    }
    
    double getpay() override {
        try {
            double pay = professor::getpay() + (p * 25000) + g;
            if(pay < 0) throw PaymentException("Invalid payment", "Payment cannot be negative");
            return pay;
        }
        catch(PaymentException& e) {
            e.log();
            throw;
        }
    }
};

class assocprof : public professor {
private:
    bool t;
    double g;
public:
    assocprof(string name, int age, string id, long long phone, string dept, string spec, string hire) 
        : professor(name, age, id, phone, dept, spec, hire) {
        t = false;
        g = 0.0;
    }
    
    void show() override {
        professor::show();
        cout << "rank: assoc prof" << endl;
        cout << "tenured: " << (t ? "yes" : "no") << endl;
        cout << "grants: ₹" << g << endl;
    }
    
    double getpay() override {
        try {
            double p = professor::getpay() * 1.5;
            if(t) p *= 1.2;
            p += g;
            if(p < 0) throw PaymentException("Invalid payment", "Payment cannot be negative");
            return p;
        }
        catch(PaymentException& e) {
            e.log();
            throw;
        }
    }
};

class fullprof : public professor {
private:
    bool t;
    double g;
    int a;
public:
    fullprof(string name, int age, string id, long long phone, string dept, string spec, string hire) 
        : professor(name, age, id, phone, dept, spec, hire) {
        t = true;
        g = 0.0;
        a = 0;
    }
    
    void show() override {
        professor::show();
        cout << "rank: full prof" << endl;
        cout << "tenured: yes" << endl;
        cout << "grants: ₹" << g << endl;
        cout << "admin work: " << a << endl;
    }
    
    double getpay() override {
        try {
            double p = professor::getpay() * 2.0;
            p += g + (a * 50000);
            if(p < 0) throw PaymentException("Invalid payment", "Payment cannot be negative");
            return p;
        }
        catch(PaymentException& e) {
            e.log();
            throw;
        }
    }
};

class dept {
private:
    string n;
    string l;
    double b;
    professor* p[MAX_PROFS];
    course* c[MAX_COURSES];
    int numProfs;
    int numCourses;
public:
    dept(string name, string loc, double budget) {
        if(name.empty()) throw ValidationException("Invalid name", "Department name cannot be empty");
        if(loc.empty()) throw ValidationException("Invalid location", "Location cannot be empty");
        if(budget < 0) throw ValidationException("Invalid budget", "Budget cannot be negative");
        
        n = name;
        l = loc;
        b = budget;
        numProfs = 0;
        numCourses = 0;
        for(int i = 0; i < MAX_PROFS; i++) {
            p[i] = nullptr;
        }
        for(int i = 0; i < MAX_COURSES; i++) {
            c[i] = nullptr;
        }
    }
    
    void addp(professor* prof) {
        try {
            if(numProfs >= MAX_PROFS) {
                throw EnrollmentException("Maximum professors reached", "Department cannot have more professors");
            }
            p[numProfs++] = prof;
        }
        catch(EnrollmentException& e) {
            e.log();
            throw;
        }
    }
    
    void addc(course* course) {
        try {
            if(numCourses >= MAX_COURSES) {
                throw EnrollmentException("Maximum courses reached", "Department cannot have more courses");
            }
            c[numCourses++] = course;
        }
        catch(EnrollmentException& e) {
            e.log();
            throw;
        }
    }
    
    void show() {
        cout << "dept: " << n << endl;
        cout << "loc: " << l << endl;
        cout << "budget: ₹" << b << endl;
        cout << "profs: " << numProfs << endl;
        cout << "courses: " << numCourses << endl;
    }
};

class university {
private:
    string n;
    dept* d[MAX_DEPTS];
    classroom* r[MAX_ROOMS];
    int numDepts;
    int numRooms;
    string currentSemester;
public:
    university(string name) : n(name) {
        if(name.empty()) throw ValidationException("Invalid name", "University name cannot be empty");
        
        numDepts = 0;
        numRooms = 0;
        currentSemester = "";
        for(int i = 0; i < MAX_DEPTS; i++) {
            d[i] = nullptr;
        }
        for(int i = 0; i < MAX_ROOMS; i++) {
            r[i] = nullptr;
        }
    }
    
    void addd(dept* dept) {
        try {
            if(numDepts >= MAX_DEPTS) {
                throw EnrollmentException("Maximum departments reached", "University cannot have more departments");
            }
            d[numDepts++] = dept;
        }
        catch(EnrollmentException& e) {
            e.log();
            throw;
        }
    }
    
    void addr(classroom* room) {
        try {
            if(numRooms >= MAX_ROOMS) {
                throw EnrollmentException("Maximum rooms reached", "University cannot have more rooms");
            }
            r[numRooms++] = room;
        }
        catch(EnrollmentException& e) {
            e.log();
            throw;
        }
    }
    
    void setSemester(string semester) {
        if(semester.empty()) throw ValidationException("Invalid semester", "Semester cannot be empty");
        currentSemester = semester;
    }
    
    string getSemester() { return currentSemester; }
    
    void show() {
        cout << "uni: " << n << endl;
        cout << "depts: " << numDepts << endl;
        cout << "rooms: " << numRooms << endl;
        cout << "current semester: " << currentSemester << endl;
    }
};

void showmenu() {
    cout << "\n=== University System Menu ===" << endl;
    cout << "1. Show university info" << endl;
    cout << "2. Show department info" << endl;
    cout << "3. Show professor info" << endl;
    cout << "4. Show student info" << endl;
    cout << "5. Show course info" << endl;
    cout << "6. Enroll student in course" << endl;
    cout << "7. Assign professor to course" << endl;
    cout << "8. Close course enrollment" << endl;
    cout << "9. Open course enrollment" << endl;
    cout << "10. Set semester" << endl;
    cout << "11. Add course prerequisite" << endl;
    cout << "12. Enter student grade" << endl;
    cout << "13. Calculate student GPA" << endl;
    cout << "14. Exit" << endl;
    cout << "Enter choice: ";
}

int main() {
    try {
        university uni("my uni");
        
        classroom r1("101", 30, true);
        classroom r2("102", 25, false);
        uni.addr(&r1);
        uni.addr(&r2);
        
        dept d1("cs", "building a", 75000000);
        dept d2("engg", "building b", 100000000);
        uni.addd(&d1);
        uni.addd(&d2);
        
        professor p1("dr.nikhil", 45, "pr001", 7303420333LL, "cs", "ai", "2010-04-15");
        professor p2("dr.lakshay", 50, "pr002", 9910625639LL, "engg", "robotics", "2008-03-20");
        d1.addp(&p1);
        d2.addp(&p2);
        
        student s1("meet yadav", 19, "s001", 9953747875LL, "2025-05-05", "cs", 3.8);
        student s2("mehul batra", 22, "s002", 9996312013LL, "2025-5-05", "ds", 3.5);
        
        course c1("cs101", "intro to focp", 3, "basic focp");
        course c2("eng201", "engg", 4, "adv engg");
        d1.addc(&c1);
        d2.addc(&c2);
        
        c1.setp(&p1);
        c2.setp(&p2);
        c1.setr(&r1);
        c2.setr(&r2);
        
        s1.addcourse(&c1);
        s2.addcourse(&c2);
        
        int choice;
        while(true) {
            showmenu();
            cin >> choice;
            
            try {
                switch(choice) {
                    case 1:
                        cout << "\n=== university information ===" << endl;
                        uni.show();
                        break;
                        
                    case 2:
                        cout << "\n=== department information ===" << endl;
                        d1.show();
                        cout << endl;
                        d2.show();
                        break;
                        
                    case 3:
                        cout << "\n=== professor information ===" << endl;
                        p1.show();
                        cout << endl;
                        p2.show();
                        break;
                        
                    case 4:
                        cout << "\n=== student information ===" << endl;
                        s1.show();
                        cout << endl;
                        s2.show();
                        break;
                        
                    case 5:
                        cout << "\n=== course information ===" << endl;
                        c1.show();
                        cout << endl;
                        c2.show();
                        break;
                        
                    case 6:
                        cout << "\nEnrolling student in course..." << endl;
                        s1.addcourse(&c2);
                        break;
                        
                    case 7:
                        cout << "\nAssigning professor to course..." << endl;
                        c1.setp(&p2);
                        break;
                        
                    case 8:
                        cout << "\nClosing course enrollment..." << endl;
                        c1.closeEnrollment();
                        break;
                        
                    case 9:
                        cout << "\nOpening course enrollment..." << endl;
                        c1.openEnrollment();
                        break;
                        
                    case 10: {
                        cout << "\nEnter semester (e.g., Fall 2024): ";
                        string semester;
                        cin.ignore();
                        getline(cin, semester);
                        uni.setSemester(semester);
                        c1.setSemester(semester);
                        c2.setSemester(semester);
                        break;
                    }
                        
                    case 11:
                        cout << "\nAdding prerequisite..." << endl;
                        c2.addPrerequisite("cs101");
                        break;
                        
                    case 12: {
                        cout << "\nEnter course index (0-" << s1.getNumCourses()-1 << "): ";
                        int courseIndex;
                        cin >> courseIndex;
                        cout << "Enter grade (0-4.0): ";
                        float grade;
                        cin >> grade;
                        s1.setGrade(courseIndex, grade);
                        break;
                    }
                        
                    case 13:
                        cout << "\nCalculating GPA..." << endl;
                        cout << "GPA: " << s1.calculateGPA() << endl;
                        break;
                        
                    case 14:
                        return 0;
                        
                    default:
                        cout << "Invalid choice!" << endl;
                }
            }
            catch(UniversitySystemException& e) {
                cout << "Error: " << e.getMessage() << endl;
                cout << "Details: " << e.getDetails() << endl;
                e.log();
            }
        }
    }
    catch(UniversitySystemException& e) {
        cout << "Error: " << e.getMessage() << endl;
        cout << "Details: " << e.getDetails() << endl;
        e.log();
    }
    
    return 0;
}