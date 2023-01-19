// Include the basic OpenFOAM include file - this allows the most common OF-native
// types, such as labels, fvMesh, etc. to be used in this class just as in the
// basic utilities.
#include "fvCFD.H"

class myClass
{
private:
    scalar radius;

public:
    myClass();
    ~myClass();

    // Access operators - allow the internal value to be set or retrieved.
    // Defined as inline to make the code run faster by avoiding expensive linking.
    // .set() method defined as const as it is not allowed to modify any of the class fields.
    inline scalar get() const
    {
        return radius;
    }
    inline void set(scalar r)
    {
        radius = r;
    }

    // Calculate the area of a circle with a given radius
    scalar calcArea () const;

    // A function which accepts a reference to the mesh and does some operations
    // on it but without modifying it.
    // Passing a reference rather than the entire mesh object instance by value
    // is much more memory efficient - in short, only one mesh object exists
    // and this method only learns to talk to it rather than make a new, separate copy.
    void meshOpFunc(fvMesh& mesh);
};