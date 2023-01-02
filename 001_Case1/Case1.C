/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2011-2020 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Application
    customizedFoam

Description
    practice c++ in OpenFOAM formation.

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{
    // Initialise OF case
    #include "setRootCase.H"

    // Create the time system(instance called runTime) and fvMesh(instance called mesh)
    #include "createTime.H"
    #include "createMesh.H"

    // Get access to a custom dictionary
    dictionary myDict;
    const word dictName("testDict");

    // Create an IOobject - this holds the path to the dict and its name
    IOobject myDictIOobject
    (
        dictName,              // name of the file
        mesh.time().constant(),// path to where the file is: ./constant
        mesh,                  // reference to the mesh needed by the constructor
        IOobject::MUST_READ    // indicate that reading this dictionary is compulsory
    );

    // Check if the dictionary is present and follows the OF format
    if (!myDictIOobject.headerOk()) {
        FatalErrorIn(args.executable()) << "Cannot open specified refinement dictionary "
            << dictName << exit(FatalError);
    }
    // Initialise the dictionary object
    myDict = IOdictionary(myDictIOobject);
        
    // Read various pieces of information from the main part of the dictionary
    // Lookup which does not need to be told what type of variable we're looking for and
    // uses the standard C++ stringstream syntax
    word someWord;
    myDict.lookup("someWord") >> someWord;

    // This template method needs to know the type of the variable and can provide
    // a default value if the entry is not found in the dictionary
    label someLable ( myDict.lookupOrDefault<label>("someLable", 0) );
    scalar someScalar( myDict.lookupOrDefault<scalar>("someScalar", 1.0) );    

    // A switch is a neat feature allowing boolean values to be read from a dict,
    // it supports the OpenFOAM yes/on/true/1 and no/off/false/0 values automatically.
    bool someBool ( myDict.lookupOrDefault<Switch>("someBool",true) );

    // Lookup vector
    Vector<scalar> someVector( myDict.lookup("someVector") );

    // Lookup tensor
    tensor someTensor( myDict.lookup("someTensor") );

    // Lists of values may also be read in the same way
    List<scalar> someList ( myDict.lookup("someList") );

    // This type of container is particularly interesting - it associates entries with
    // given key values (here of word type but can be anything); useful when
    // associating things by indices in a list is less handy
    HashTable<vector,word> someHashTable ( myDict.lookup("someHashTable") );

    // Summarise what's been read and print in the console
    Info << nl << "Read the following:" << nl << nl
         << "someWord " << someWord << nl << nl
         << "someLable " << someLable << nl << nl
         << "someScalar " << someScalar << nl << nl
         << "someBool " << someBool << nl << nl
         << "someVector " << someVector << nl
         << "Vector x component: " << someVector.x() << nl
         << "Vector y component: " << someVector.y() << nl
         << "Vector z component: " << someVector.z() << nl << nl
         << "someTensor " << someTensor << nl
         << "Tensor xx component: " << someTensor.xx() << nl
         << "Tensor yz component: " << someTensor.yz() << nl
         << "Tensor zy component: " << someTensor.zy() << nl << nl
         << "someList " << someList << nl << nl
         << "someHashTable " << someHashTable << nl << nl         
         << endl;

    // Create a custom directory and write an output file
    // Create the output path directory
    fileName outputDir = mesh.time().path()/"postProcessing";
    // Creathe the directory
    mkDir(outputDir);

    // File pointer to direct the output to
	autoPtr<OFstream> fout;
    // Open the file in the newly created directory
    fout.reset(new OFstream(outputDir/"customOutputFile.dat"));

    // Write stuff
    fout() << "# This is a header" << endl;
    fout() << "0 1 2 3 4 5" << endl;

    // Append to the imported hash table and wirte it too
    someHashTable.insert("newKey", vector(1., 0., 0.));
    fout() << someHashTable << endl;

    Info<< "End\n" << endl;
    return 0;
}

// ************************************************************************* //