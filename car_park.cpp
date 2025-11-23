#include <iostream>
#include <string>

using namespace std;

class OverflowException {
public:
    OverflowException() {
        cout << endl << "Exception created!" << endl;
    }
    OverflowException(const OverflowException&) {
        cout << "Exception copied!" << endl;
    }
    ~OverflowException() {
        cout << "Exception finished!\n" << endl;
    }
};

class Vehicle {
protected:
    string rNum;
    int rGads;
    string rValsts;

public:
    Vehicle() : rNum(""), rGads(0), rValsts("") {}
    Vehicle(string, int, string);
    virtual ~Vehicle() {
        cout << "Message from the \"Vehicle\" - destroyed!" << endl;
    }
    string GetRnum() const {
        return rNum;
    }
    int GetRgads() const {
        return rGads;
    }
    string GetRvalsts() const {
        return rValsts;
    }

    void SetRnum(string);
    void SetRgads(int);
    void SetRvalsts(string);

    friend ostream& operator<<(ostream& O, const Vehicle& obj);
};

class Car : public Vehicle {
private:
    unsigned int dzJauda;

public:
    Car() : Vehicle(), dzJauda(0) {}
    Car(string, int, string, unsigned int);
    virtual ~Car() {
        cout << "Message from the \"Car\" - destroyed!" << endl;
    }
    unsigned int GetdzJauda() const {
        return dzJauda;
    }
    void SetdzJauda(unsigned int dzJauda) {
        this->dzJauda = dzJauda;
    }
    friend ostream& operator<<(ostream& O, const Car& c);
};

class CarPark {
private:
    static const int DEFAULT_MAX_CARS = 2;
    Car** cars;
    int maxCars;
    int size;

public:
    CarPark(int maxCars = DEFAULT_MAX_CARS) : maxCars(maxCars), size(0) {
        cars = new Car * [maxCars]();
    }
    ~CarPark() {
        for (int i = 0; i < size; ++i) {
            delete cars[i];
        }
        delete[] cars;
        cout << "\nCarPark destroyed.\n" << endl;
    }
    static unsigned int GetDefaultMaxCars() {
        return DEFAULT_MAX_CARS;
    }

    CarPark& operator+=(const Car& obj);
    friend ostream& operator<<(ostream& O, const CarPark& cp);
};

Vehicle::Vehicle(string PrNum, int PrGads, string PrValsts) : rNum(PrNum), rGads(PrGads), rValsts(PrValsts) {}
void Vehicle::SetRnum(string rNum) {
    this->rNum = rNum;
}
void Vehicle::SetRgads(int rGads) {
    this->rGads = rGads;
}
void Vehicle::SetRvalsts(string rValsts) {
    this->rValsts = rValsts;
}
ostream& operator<<(ostream& O, const Vehicle& obj) {
    O << "Registracijas nr: " << obj.rNum << ", Gads: " << obj.rGads << ", Valsts: " << obj.rValsts;
    return O;
}

Car::Car(string PrNum, int PrGads, string PrValsts, unsigned int dzJauda) : Vehicle(PrNum, PrGads, PrValsts), dzJauda(dzJauda) {}
ostream& operator<<(ostream& O, const Car& c) {
    O << "Registracijas nr: " << c.GetRnum() << ", Gads: " << c.GetRgads() << ", Valsts: " << c.GetRvalsts() << ", Jauda: " << c.GetdzJauda() << endl;
    return O;
}

CarPark& CarPark::operator+=(const Car& obj) {
    if (size >= maxCars) {
        throw OverflowException();
    }
    cars[size++] = new Car(obj);
    return *this;
}
ostream& operator<<(ostream& O, const CarPark& cp) {
    for (int i = 0; i < cp.size; ++i) {
        O << "Car " << i + 1 << ": " << *cp.cars[i] << endl;
    }
    return O;
}

int main() {
    try {

        CarPark* cp = new CarPark(CarPark::GetDefaultMaxCars());

        Car car1("AB-0001", 2000, "Latvija", 150);
        Car car2("FF-4988", 1990, "Vacija", 200);
        Car car3("CD-5678", 2020, "Francija", 180);

        try {
            *cp += car1;
            cout << "\nNew car added!" << endl;
        }
        catch (const OverflowException&) {
            cout << "*** Error: maximal length exceeded! ***" << endl;
        }
        catch (...) {
            cout << "Unknown error!" << endl;
        }

        try {
            *cp += car2;
            cout << "\nNew car added!" << endl;
        }
        catch (const OverflowException&) {
            cout << "*** Error: maximal length exceeded! ***" << endl;
        }
        catch (...) {
            cout << "Unknown error!" << endl;
        }

        try {
            *cp += car3;
            cout << "\nNew car added!" << endl;
        }
        catch (const OverflowException&) {
            cout << "*** Error: maximal length exceeded! ***" << endl;
        }
        catch (...) {
            cout << "Unknown error!" << endl;
        }

        cout << *cp;
        delete cp;
    }
    catch (const OverflowException&) {
        cout << "CarPark full!" << endl;
    }

    return 0;
}