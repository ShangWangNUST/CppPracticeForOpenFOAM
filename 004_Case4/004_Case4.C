/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2023 OpenFOAM Foundation
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
    004_Case4

Description

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{
    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
    // Define the help message for this application
    argList::addNote(
        "Demonstrates how to handle command line options.\n"
        "\n"
        "Input arguments:\n"
        "-------------------------------------------\n"
        "   someWord --- does stuff\n"
        "   someScalar --- does more things\n"
    );

    // prepare argument list
    argList::noParallel();
    argList::validArgs.append("someWord");
    argList::validArgs.append("someScalar");

    // prepare options, string variable
    argList::addOption(
        "dict",
        "word",
        "Path to an additional dictionary (not really used now)"
    );

    // bool option, on/off depending on whether option is given or not
    argList::addBoolOption(
        "someSwitch",
        "Switches from A to B"
    );

    // integer variable
    argList::addOption(
        "someInt",
        "label",
        "Optional integer"
    );

    #include "setRootCase.H"
    #include "createTime.H"
    #include "createMesh.H"

    // Initialize field data from folder 0
    #include "createFields.H" 
    // create argument list
    // This is normally defined inside setRootCase.H
    // include "setRootCase.H"
    // Foam::argList args(argc, argv);
    // if (!args.checkRootCase()) {
    //     Foam::FatalError.exit();
    // }

    // read arguments
    const word someWord = args[1];
    // NOTE: the built-in method for converting strings to other data types
    const scalar someScalar = args.argRead<scalar>(2);

    Info << "Got argument infomation as follows:" << nl
         << "someWord = " << someWord << nl
         << "someScalar = " << someScalar << nl << endl;

    // read options
    // default path to some dictionary
    fileName dictPath(mesh.time().constant());
    
    // conditional execution based on an option being passed
    if (args.optionFound("dict")) {
        args.optionReadIfPresent("dict", dictPath);
        Info << "Got an override flag for dictionary path" << endl;
        dictionary myDict;
        const word dictName(someWord);
        // Create an IOobject - this holds the path to the dict and its name
        IOobject myDictIOobject
        (
            dictName,    // name of the file
            dictPath,    // path default or frome args
            mesh,        // reference to the mesh needed by the constructor
            IOobject::MUST_READ    // indicate that reading this dictionary is compulsory
        );
        // Check if the dictionary is present and follows the OF format
        if (!myDictIOobject.typeHeaderOk<dictionary>(true)) {
            FatalErrorIn(args.executable()) << "Cannot open specified refinement dictionary "
                << dictName << exit(FatalError);
        }
        // Initialise the dictionary object
        myDict = IOdictionary(myDictIOobject);

        Info << "The dictionary contents are as follows:" << nl
            << myDict << nl << endl;
    } else {
        Info << "Would read dict from " << dictPath << endl;
    }

    // switch option
    const bool someConstBool = args.optionFound("someSwitch");
    Info << "Boolean switch set to " << someConstBool << endl;

    // numeric value option - same as string variables really
    label someInt(0);
    args.optionReadIfPresent("someInt", someInt);
    Info << "Integer option value " << someInt << nl << endl;


    Info<< "End\n" << endl;

    return 0;
}


// ************************************************************************* //
