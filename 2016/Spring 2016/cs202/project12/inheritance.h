/********************************************************************/
/*                          BASE CLASS                              */
/********************************************************************/
class Shape
{
    public:
        virtual ~Shape() {}

        virtual float calculateAreaOrVolume() = 0;
        virtual float calculatePerimeterOrSurfaceArea() = 0;
        virtual void print() = 0;

        bool is3D() {
            return isThreeDimensional;
        }

    protected:
        bool isThreeDimensional;
};

/********************************************************************/
/*                       DERIVED CLASSES                            */
/********************************************************************/

class Rectangle : public Shape
{
    public:
        Rectangle(float=10.0f,float=10.0f);

        virtual float calculateAreaOrVolume();
        virtual float calculatePerimeterOrSurfaceArea();
        virtual void print();

    protected:
        float length;
        float width;
};



class RectangularPrism : public Rectangle
{
    public:
        RectangularPrism(float=10.0f,float=10.0f,float=10.0f);

        float calculateAreaOrVolume();
        float calculatePerimeterOrSurfaceArea();
        void print();

    protected:
        float height;
};



class Circle : public Shape
{
    public:
        Circle(float=10.0f);

        virtual float calculateAreaOrVolume();
        virtual float calculatePerimeterOrSurfaceArea();
        virtual void print();

    protected:
        float radius;
};



class Cylinder : public Circle
{
    public:
        Cylinder(float=10.0f, float=10.0f);

        float calculateAreaOrVolume();
        float calculatePerimeterOrSurfaceArea();
        void print();

    protected:
        float height;
};
