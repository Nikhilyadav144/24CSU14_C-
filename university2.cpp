#include <iostream>
#include <string>
using namespace std;

const int MAX_COURSES = 10;
const int MAX_STUDENTS = 50;
const int MAX_PROFS = 20;
const int MAX_DEPTS = 5;
const int MAX_ROOMS = 30;

class course;
class professor;
class student;

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
    
    void setn(string name) { n = name; }
    void seta(int age) { a = age; }
    void seti(string id) { i = id; }
    void setp(long long phone) { p = phone; }
    
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
public:
    course(string code, string title, int cred, string desc) {
        c = code;
        t = title;
        cr = cred;
        d = desc;
        p = nullptr;
        r = nullptr;
        numStudents = 0;
        for(int i = 0; i < MAX_STUDENTS; i++) {
            s[i] = nullptr;
        }
    }
    
    string gett() { return t; }
    void setp(professor* prof) { p = prof; }
    void setr(classroom* room) { r = room; }
    
    void addstudent(student* stu);
    void show();
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
        return sal + (y * 50000);
    }
};

class student : public person {
protected:
    string ed;
    string prog;
    float g;
    course* c[MAX_COURSES];
    int numCourses;
public:
    student(string name, int age, string id, long long phone, string enroll, string program, float gpa) 
        : person(name, age, id, phone) {
        ed = enroll;
        prog = program;
        g = gpa;
        numCourses = 0;
        for(int i = 0; i < MAX_COURSES; i++) {
            c[i] = nullptr;
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
        return pay - (numCourses * 50000);
    }
};

void course::addstudent(student* stu) {
    if(numStudents < MAX_STUDENTS) {
        s[numStudents++] = stu;
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
}

void student::addcourse(course* course) {
    if(numCourses < MAX_COURSES) {
        c[numCourses++] = course;
        course->addstudent(this);
    }
}

void professor::addcourse(course* course) {
    if(numCourses < MAX_COURSES) {
        c[numCourses++] = course;
        course->setp(this);
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
        double p = student::getpay();
        if(ta) p += 150000;
        if(ra) p += 200000;
        return p;
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
        return professor::getpay() + (p * 25000) + g;
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
        double p = professor::getpay() * 1.5;
        if(t) p *= 1.2;
        return p + g;
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
        double p = professor::getpay() * 2.0;
        return p + g + (a * 50000);
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
        if(numProfs < MAX_PROFS) {
            p[numProfs++] = prof;
        }
    }
    
    void addc(course* course) {
        if(numCourses < MAX_COURSES) {
            c[numCourses++] = course;
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
public:
    university(string name) : n(name) {
        numDepts = 0;
        numRooms = 0;
        for(int i = 0; i < MAX_DEPTS; i++) {
            d[i] = nullptr;
        }
        for(int i = 0; i < MAX_ROOMS; i++) {
            r[i] = nullptr;
        }
    }
    
    void addd(dept* dept) {
        if(numDepts < MAX_DEPTS) {
            d[numDepts++] = dept;
        }
    }
    
    void addr(classroom* room) {
        if(numRooms < MAX_ROOMS) {
            r[numRooms++] = room;
        }
    }
    
    void show() {
        cout << "uni: " << n << endl;
        cout << "depts: " << numDepts << endl;
        cout << "rooms: " << numRooms << endl;
    }
};

int main() {
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
    
    cout << "\n=== university information ===" << endl;
    uni.show();
    
    cout << "\n=== department information ===" << endl;
    d1.show();
    cout << endl;
    d2.show();
    
    cout << "\n=== professor information ===" << endl;
    p1.show();
    cout << endl;
    p2.show();
    
    cout << "\n=== student information ===" << endl;
    s1.show();
    cout << endl;
    s2.show();
    
    cout << "\n=== course information ===" << endl;
    c1.show();
    cout << endl;
    c2.show();
    
    return 0;
}