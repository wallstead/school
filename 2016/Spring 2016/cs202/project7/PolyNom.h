#include <iostream>
using namespace std;

class PolyNom {
public:
    PolyNom();
    PolyNom(int, int*);
    PolyNom(const PolyNom&);
    ~PolyNom();

    int solve(int);

    PolyNom& operator=(const PolyNom&);
    bool operator==(const PolyNom&);
    bool operator!=(const PolyNom&);
    PolyNom operator*(const PolyNom&);
    PolyNom operator*(const int);
    friend PolyNom operator+(const PolyNom&, const PolyNom&);
    friend PolyNom operator-(const PolyNom&, const PolyNom&);
    friend ostream &operator<<(ostream&, const PolyNom&);
    friend istream &operator>>(istream&, PolyNom&);

private:
    int *coefficients;
    int maxDegree;
};
