//  Zeyu Zhao
//  codeblock for Windows
//  Assignment_10
//
//  Thanks for your help joe, it's been a really nice quarter:)
//
//  Created by zhaozeyu on 22/03/2018.
//  Copyright © 2018 zhaozeyu. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Quadrilateral{
protected:
    string type;
    int side1;
    int side2;
public:
    Quadrilateral(int = 0, int = 0);
    int getside1(){
        return side1;
    }
    int getside2(){
        return side2;
    }
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    virtual string shape() const = 0;
    virtual ~Quadrilateral(){};
};

Quadrilateral* createQuadrilateralFromString(string = "");

Quadrilateral::Quadrilateral(int a, int b){
    side1 = a;
    side2 = b;
}

ostream& operator<<(ostream& out,Quadrilateral& a){
    if(a.getside1()==a.getside2()){
        out<<a.shape()<<":  side "<<a.getside1()<<"  area="<<a.area()<<"  perimeter="<<a.perimeter();
        return out;
    }
    else{
        out<<a.shape()<<":  sides "<<a.getside1()<<" and "<<a.getside2()<<"  area="<<a.area()<<"  perimeter="<<a.perimeter();
        return out;
    }
}

class Rectangle: public Quadrilateral{
public:
    Rectangle(int a, int b):Quadrilateral(a, b){}//side stored in the base class
    virtual double area() const;
    virtual double perimeter() const;
    virtual string shape() const;
    virtual ~Rectangle(){};
};

double Rectangle::area() const{
    return side1*side2;
}

double Rectangle::perimeter() const{
    return 2*side1+2*side2;
}

string Rectangle::shape() const{
    return "Rectangle";
}

class Square: public Rectangle{
public:
    Square(int a):Rectangle(a, a){}
    double area() const;
    double perimeter() const;
    string shape() const;
    ~Square(){};
};

double Square::area() const{
    return side1*side2;
}

double Square::perimeter() const{
    return 4*side1;
}

string Square::shape() const{
    return "Square";
}

class Parallelogram: public Quadrilateral{
protected:
    int height;
public:
    Parallelogram(int a, int b, int d):Quadrilateral(a, b), height(d){}
    virtual double area() const;
    virtual double perimeter() const;
    virtual string shape() const;
    virtual ~Parallelogram(){};
};

double Parallelogram::area() const{
    return side1*height;
}

double Parallelogram::perimeter() const{
    return 2*side1+2*side2;
}

string Parallelogram::shape() const{
    return "Parallelogram";
}

class Rhombus: public Parallelogram{
public:
    Rhombus(int a, int d):Parallelogram(a, a, d){}
    double area() const;
    double perimeter() const;
    string shape() const;
    ~Rhombus(){};
};

double Rhombus::area() const{
    return side1*height;
}

double Rhombus::perimeter() const{
    return 4*side1;
}

string Rhombus::shape() const{
    return "Rhombus";
}

Quadrilateral* createQuadrilateralFromString(string as){
    Quadrilateral* ptr;
    string shape;
    int a;
    int b = 0;
    int c = 0;
    size_t pos = 0;
    pos = as.find(' ');
    shape = as.substr(0,pos);
    size_t pos3 =0;
    pos3 = as.rfind(' ');
    if(pos == pos3){
        a = stoi(as. substr(pos+1));
    }
    else{
        size_t pos2 = 0;
        pos2 = as.find(' ', pos+1);
        if(pos3 == pos2){//for situation that there are different arguments
            a = stoi(as. substr(pos+1, pos2));
            b = stoi(as. substr(pos2+1, pos3));
        }
        else{
            a = stoi(as. substr(pos+1, pos2));
            b = stoi(as. substr(pos2+1, pos3));
            c = stoi(as. substr(pos3+1));
        }
    }
    if(shape == "rectangle"){
        ptr = new Rectangle(a, b);
        return ptr;
    }
    else if(shape == "square"){
        ptr = new Square(a);
        return ptr;
    }
    else if(shape == "parallelogram"){
        ptr = new Parallelogram(a, b, c);
        return ptr;
    }
    else if(shape == "rhombus"){
        ptr = new Rhombus(a, b);
        return ptr;
    }
    else{
        cout<<"Out of range"<<endl;
        exit(-3);
        return nullptr;
    }
}

int main()
{
    const string filename = "Input File.txt";   // use your filename here
    ifstream fin(filename.c_str());
    if (!fin)
    {
        cerr << "Unable to open " << filename << endl;
        exit(1);
    }
    string buffer;
    Quadrilateral* ptrQuad;
    while (getline(fin,buffer))
    {
        // Process only valid input
        if (buffer.size() > 1)
        {
            ptrQuad = createQuadrilateralFromString(buffer);
            cout << *ptrQuad << endl;
            delete ptrQuad;
        }
    }
    fin.close();
}
