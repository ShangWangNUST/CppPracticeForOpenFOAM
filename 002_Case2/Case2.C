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

	// runTime and mesh are instances of objects (or classes).
	// If you are not familiar with what a class or object is, it is HIGHLY RECOMMENDED you visit this
	// website and only come back once you've read everything about classes, inheritance and polymorphism:
	// http://www.cplusplus.com/doc/tutorial/classes/
	// Note how the next lines call functions .timeName(), .C() and .Cf() implemented in the objects.
	// It is also important to realise that mesh.C() and .Cf() return vector fields denoting centres of each
    // cell and internal face.
	// Calling the mesh.C().size() method therefore yields the total size of the mesh.
	Info << "Hello there, the most recent time folder found is " << runTime.timeName() << nl
		 << "Mesh infomation:" << nl
         << "nPoints = " << mesh.points().size() << nl // <==> mesh.nPoints()
         << "nFaces = " << mesh.nFaces() << nl         // <==> mesh.faces().size()
         << "nInternalFaces = " << mesh.Cf().size() << nl // <==> mesh.nInternalFaces()
         << "nBoundaries = " << mesh.boundary().size() << nl
         << "nCells = " << mesh.C().size() << nl      // <==> mesh.nCells()
         << "nOwners = " << mesh.owner().size() << nl
         << "nNeighbours = " << mesh.neighbour().size() << nl << endl;

    // Iterate over every points
    Info << "Mesh info: Points" << endl;
    Info << "Points Number = " << mesh.nPoints() << endl;
    forAll(mesh.points(), pointI) {
        Info << "pointI = " << pointI << tab
             << "(x y z) = " << mesh.points()[pointI] << tab
             << "x = " << mesh.points()[pointI].x() << endl;
    }

    // for(label pointI = 0; pointI < mesh.points().size(); pointI++) {
    //     Info << "pointI = " << pointI << ", " << tab
    //          << "(x y z) = " << mesh.points()[pointI] << ", " << tab
    //          << "x = " << mesh.points()[pointI].x() << endl;
    // }

    // Iterate over every faces 
    Info << endl << "Mesh info: faces" << endl;
    Info << "Faces Number = " << mesh.nFaces() << endl;
    forAll(mesh.faces(), faceI) {
        Info << "faceI = " << faceI << tab
             << "faceIinfo = " << mesh.faces()[faceI] << tab
             << "faceIsize = " << mesh.faces()[faceI].size() << tab;
        forAll(mesh.faces()[faceI], vertexI) {
            Info << mesh.points()[mesh.faces()[faceI][vertexI]] << " ";
        }
        Info << endl;
    }

    // Each cell is constructed of faces - these may either be internal or constitute a
    // boundary, or a patch in OpenFOAM terms; internal faces have an owner cell
    // and a neighbour.
    Info << endl << "Mesh info: internalFaces and its owner cell and neighbour" << endl;
    Info << "InternalFaces Number = " << mesh.Cf().size() << endl;
    forAll(mesh.Cf(), faceI) {
        Info << "internalFaceI = " << faceI << tab
             << "centre = " << mesh.Cf()[faceI] << tab
             << "ownerCell = " << mesh.owner()[faceI] << tab
             << "neighbour = " << mesh.neighbour()[faceI] << endl;
    }

    // Boundary conditions may be accessed through the boundaryMesh object.
    // In reality, each boundary face is also included in the constant/polyMesh/faces
    // description. But, in that file, the internal faces are defined first.
    // In addition, the constant/polyMesh/boundary file defines the starting faceI
    // indices from which boundary face definitions start.
    // OpenFOAM also provides a macro definition for for loops over all entries
    // in a field or a list, which saves up on the amount of typing.
    Info << endl << "Mesh info: boundary" << endl;
    Info << "Boundary Number = " << mesh.boundaryMesh().size() << endl;
    forAll(mesh.boundaryMesh(), patchI)
        Info << "Patch = " << patchI << tab
             << "patchName = " << mesh.boundary()[patchI].name() << tab
             << "patchFaces = " << mesh.boundary()[patchI].Cf().size() << tab
             << "patchFaceStart = " << mesh.boundary()[patchI].start() << endl;
    Info << endl;
    
    // Faces adjacent to boundaries may be accessed as follows.
    // Also, a useful thing to know about a face is its normal vector and face area.
    label patchFaceI(0);
    forAll(mesh.boundaryMesh(), patchI)
        Info << "Patch = " << patchI << tab
             << "PatchFace = " << patchFaceI << tab
             << "AdjacentToCell = " << mesh.boundary()[patchI].patch().faceCells()[patchFaceI] << tab
             << "NormalVector = " << mesh.boundary()[patchI].Sf()[patchFaceI] << tab
             << "SurfaceArea = " << mag(mesh.boundary()[patchI].Sf()[patchFaceI]) << endl;
    Info << endl;

    // For internal faces, method .Sf() can be called directly on the mesh instance.
    // Moreover, there is a shorthand method .magSf() which returns the surface area
    // as a scalar.
    // For internal faces, the normal vector points from the owner to the neighbour
    // and the owner has a smaller cellI index than the neighbour. For boundary faces,
    // the normals always point outside of the domain (they have "imaginary" neighbours
    // which do not exist).

    // It is possible to look at the points making up each face in more detail.
    // First, we define a few shorthands by getting references to the respective
    // objects in the mesh. These are defined as constants since we do not aim to
    // alter the mesh in any way.
    // NOTE: these lists refer to the physical definition of the mesh and thus
    // include boundary faces. Use can be made of the mesh.boundary()[patchI].Cf().size()
    // and mesh.boundary()[patchI].start() methods to check whether the face is internal
    // or lies on a boundary.
    const faceList& fcs = mesh.faces();
    const List<point>& pts = mesh.points();
    const List<point>& cents = mesh.faceCentres();
    Info << endl << "Mesh info: faces and their infomaiton" << endl;
    forAll(fcs,faceI) {
        if (faceI < mesh.Cf().size())
            Info << "Internal face = ";
        else {
            forAll(mesh.boundary(), patchI)
                if ((mesh.boundary()[patchI].start() <= faceI) &&
                    (faceI < mesh.boundary()[patchI].start() + mesh.boundary()[patchI].Cf().size())) {
                        Info << "Face on patch  = " << patchI << tab 
                             << "faceI = ";
                        break; // exit the forAll loop prematurely
                }
        }

        Info << faceI << tab
             << "Center = " << cents[faceI] << tab
             << "VterticesNumber = " << fcs[faceI].size() << ": ";
        forAll(fcs[faceI], vertexI)
            // Note how fcs[faceI] holds the indices of points whose coordinates
            // are stored in the pts list.
            Info << " " << pts[fcs[faceI][vertexI]];
        Info << endl;
    }

    // In the original cavity tutorial, on which the test case is based,
    // the frontAndBack boundary is defined as and "empty" type. This is a special
    // BC case which may cause unexpected behaviour as its .Cf() field has size of 0.
    // Type of a patch may be checked to avoid running into this problem if there
    // is a substantial risk that an empty patch type will appear
    label patchID(0);
    const polyPatch& pp = mesh.boundaryMesh()[patchID];
    if (isA<emptyPolyPatch>(pp)) {
        // patch patchID is of type "empty".
        Info << "You will not see this." << endl;
    }

    // Patches may also be retrieved from the mesh using their name. This could be
    // useful if the user were to refer to a particular patch from a dictionary
    // (like when you do when calculating forces on a particular patch).
    Info << endl << "Spectial boundary find in a dict" << endl;
    word patchName("movingWall");
    patchID = mesh.boundaryMesh().findPatchID(patchName);
    Info << "Retrieved patch " << patchName << " at index " << patchID << " using its name only." << nl << endl;

    
    // Iterate over every cell
    Info << endl << "Mesh info: cells" << endl;
    forAll(mesh.C(), cellI) {
        Info << "cellI = " << cellI << tab
             << "Centre = " << mesh.C()[cellI] << endl;
    }

    Info << endl << "End\n" << endl;
    return 0;
}

// ************************************************************************* //