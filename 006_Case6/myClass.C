#include "myClass.H"

myClass::myClass()
{
    radius = 0;
}

myClass::~myClass()
{}

scalar myClass::calcArea () const
{
    Info << "Calling myClass::calcArea()" << endl;
    return Foam::constant::mathematical::pi * radius * radius;
}

void myClass::meshOpFunc(fvMesh& mesh)
{
    Info << "myClass got a mesh, cellNum = " << mesh.C().size() << endl;
    radius = mesh.C().size();
}
