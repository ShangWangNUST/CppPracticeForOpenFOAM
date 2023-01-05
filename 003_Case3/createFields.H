// This reads a dictionary file.
Info << "Reading physicalProperties" << endl;

// Definition of a dict
IOdictionary physicalProperties
(
	IOobject
	(
		"physicalProperties", // name of the dictionary
		runTime.constant(), // location in the case - this one is in constant
		mesh, // needs the mesh object reference to do some voodoo - unimportant now
		IOobject::MUST_READ_IF_MODIFIED, // the file will be re-read if it gets modified during time stepping
		IOobject::NO_WRITE // read-only
	)
);

// Create a scalar constant for kinematic viscosity by reading the value from the dictionary.
dimensionedScalar nu
(
	"nu", // name of the variable
	dimViscosity, // dimensions
	// TIP: to check how this is defined, run:
	// grep -r dimViscosity $FOAM_SRC/OpenFOAM/
	// This returns:
	/*/opt/openfoam30/src/OpenFOAM/dimensionSet/dimensionSets.C:const dimensionSet dimViscosity(dimArea/dimTime);
	/opt/openfoam30/src/OpenFOAM/dimensionSet/dimensionSets.C:const dimensionSet dimDynamicViscosity(dimDensity*dimViscosity);
	/opt/openfoam30/src/OpenFOAM/dimensionSet/dimensionSets.H:extern const dimensionSet dimViscosity;*/
	// So, it becomes apparent we should check dimensionSets.C, which contain:
	/*const dimensionSet dimLength(0, 1, 0, 0, 0, 0, 0);
	const dimensionSet dimTime(0, 0, 1, 0, 0, 0, 0);
	const dimensionSet dimArea(sqr(dimLength));
	const dimensionSet dimViscosity(dimArea/dimTime);*/
	// This is what gets used here. But, an alternative would be to type in the units directly:
	// dimensionSet(0,2,-1,0,0,0,0),
	physicalProperties.lookup("nu") // this takes the value from the dictionary and returns it, passing it to the object constructor as an argument
);
Info << "//----------------< Reading result: nu >----------------//" << nl << nu << nl << endl;

// These read the fields p and U from the time folders, as specified in system/controlDict (i.e. latestTime, startTime, etc.)
Info<< "Reading field p" << endl;
volScalarField p
(
    IOobject
    (
        "p",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);
Info << "//----------------< Reading result: p >----------------//" << nl 
     << p << nl << endl;

Info << "Reading field U" << endl;
volVectorField U // note that velocity is a vector field
(
	IOobject
	(
		"U",
		runTime.timeName(),
		mesh,
		IOobject::MUST_READ,
		IOobject::AUTO_WRITE
	),
	mesh
);
Info << "//----------------< Reading result: U >----------------//" << nl 
     << U << nl << endl;


// Field data infomation
Info << "//----------------< p field out(with dimension): internal + boundary >----------------//" << nl 
     << p << nl << endl; // 有量纲的 内部 + 边界

Info << "//----------------< p.internalField()(with dimension): internal + boundary >----------------//" << nl 
     << p.internalField() << nl << endl; // 有量纲的 内部 + 边界

Info << "//----------------< p.ref()(with dimension): internal + boundary >----------------//" << nl 
     << p.ref() << nl << endl; // 有量纲的 内部 + 边界

Info << "//----------------< p.primitiveField()(without dimension): internal >----------------//" << nl 
     << p.primitiveField() << nl << endl; // 无量纲的 内部

Info << "//----------------< p.primitiveFieldRef()(without dimension): internal >----------------//" << nl 
     << p.primitiveFieldRef() << nl << endl; // 无量纲的 内部

Info << "//----------------< p.boundaryField()(without dimension): boundary >----------------//" << nl 
     << p.boundaryField() << nl << endl; // 无量纲的 边界

Info << "//----------------< p.boundaryFieldRef()(without dimension): boundary >----------------//" << nl 
     << p.boundaryFieldRef() << nl << endl; // 无量纲的 边界


Info << "IOobject = " << (p.writeOpt() == IOobject::AUTO_WRITE) << nl << endl;

Info << "p.averge() = " << gAverage(p) << nl << endl;

Info << "weightedAverage(p) = " << p.weightedAverage(mesh.V()) << nl << endl;

Info << "max(p) = " << max(p).value() << ", min(p) = " << min(p) << nl << endl;

Info << "writeMinMax(p) = "; 
p.writeMinMax(Info);

p.max(20);
Info << "//----------------< p field out(with dimension): internal + boundary >----------------//" << nl 
     << p << nl << endl; // 有量纲的 内部 + 边界
