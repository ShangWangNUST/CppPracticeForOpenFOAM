/*********** Field Data Initialization With Files ***********/
// 1-1. Read single scalar field data
// from a given file in a target folder
word externalPath(mesh.time().path()/"-externalField");
word internalPath(runTime.timeName());

Info<< "[1-1] Reading single scalar field\n" << nl << nl;
volScalarField phi
(
    IOobject
    (
        "phi",
        internalPath,
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh 
);

// 1-2. Read single vector field data
// from a given file in a target folder
Info<< "[1-2] Reading single vector field\n" << nl << nl;
volVectorField E
(
    IOobject
    (
        "E",
        internalPath,
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

// 1-3. Read scalar field data in different 
// files from in a target folder
Info<< "[1-3] Reading many scalar fields\n" << nl << nl;

label fieldN = 3;
List<autoPtr<volScalarField>> phiMany;
// PtrList<volScalarField> TiPtr(N);
phiMany.setSize(fieldN);
forAll (phiMany, iField)
{
    word nameTi ("phi" + name(iField));
    phiMany[iField].reset
    (
        new volScalarField
        (
            IOobject
            (
                nameTi,
                externalPath,
                mesh,
                IOobject::MUST_READ,
                IOobject::AUTO_WRITE
            ),
            mesh
        )
    );
}

// 1-4. Read vector field data in different 
// files from in a target folder
Info<< "[1-4] Reading vector fields\n" << nl << nl;

label fieldM = 3;
List<autoPtr<volVectorField>> EMany;
// PtrList<volVectorField> EMany(fieldM);
EMany.setSize(fieldM);
forAll (EMany, jField)
{
    word nameEi ("E" + name(jField));
    EMany[jField].reset
    (
        new volVectorField
        (
            IOobject
            (
                nameEi,
                externalPath,
                mesh,
                IOobject::MUST_READ,
                IOobject::AUTO_WRITE
            ),
            mesh
        )
    );
}

/*********** Field Data Initialization Within Code ***********/
// 2-1. Initialize a 0 scalar field
Info<< "[2-1] Initialize a 0 scalar field\n" << nl << nl;
volScalarField phiNew
(
    IOobject
    (
        "phiNew",
        internalPath,
        mesh,
        IOobject::NO_READ,      // No-read
        IOobject::AUTO_WRITE
    ),
    mesh,
    dimensionedScalar(dimensionSet(1, 2, -3, 0, 0, -1, 0), 0.)
);

// 2-2. Initialize a (0 0 0) vector field
Info<< "[2-2] Initialize a (0 0 0) vector field\n" << nl << nl;
volVectorField ENew
(
    IOobject
    (
        "ENew",
        internalPath,
        mesh,
        IOobject::NO_READ,      // No-read
        IOobject::AUTO_WRITE
    ),
    mesh,
    dimensionedVector(dimensionSet(1, 1, -3, 0, 0, -1, 0), vector(0., 0., 0.))
);

/*********** Node Data From A File ***********/
// 3-1. Initialize a 0 scalar field
Info<< "[3-1] Reading point scalar field\n" << endl;
pointMesh pMesh(mesh);
word namePoint("pointScalar");
pointScalarField pointScalar
(
    IOobject
    (
        namePoint,
        externalPath,
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    pMesh
);
    
Info<< "[3-2] Reading point vector field\n" << endl;
namePoint = "pointVector";
pointVectorField pointVector
(
    IOobject
    (
        namePoint,
        externalPath,
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    pMesh
);
