/*********** Field Data Out To Screen ***********/
Info << "/****************** < Data Out > **************************/" << nl;
// volume field data in files
Info << "[1-1]. Single scalar field result\n" << nl;
Info << phi << nl << nl;

Info << "[1-2]. Single vector field result\n" << nl;
Info << E << nl << nl;

Info << nl << "[1-3]. Many scalar fields result\n" << nl;
forAll(phiMany, iField)
{
    Info << "scalar field data --- [" << iField << "] ---" << nl;
    volScalarField& tmpS = phiMany[iField]();
    Info << tmpS << nl;    
}

Info << nl << "[1-4]. Many vector fields result\n" << nl;
forAll(EMany, jField)
{
    Info << "vector field data --- [" << jField << "]" << nl;
    volVectorField& tmpV = EMany[jField]();
    Info << tmpV << nl;
}

// volume field data in code
Info << nl << "[2-1]. Single scalar field result\n" << nl;
Info << phiNew << nl << nl;

Info << "[2-2]. Single vector field result\n" << nl;
Info << ENew << nl << nl;

/*************** Points Data ***************/
Info << "[3-1] Points scalar field result\n" << nl;
Info << pointScalar << nl;
Info << nl << "--------- points in index format ---------\n" << nl;
forAll(pointScalar, ix)
{
    Info << "p[" << ix << "] = " << pointScalar[ix] << nl;
}
// point.write();

Info << nl << "[3-2] Points vector field result\n" << nl;
Info << pointVector << nl;
Info << nl << "--------- points in index format ---------\n" << nl;
forAll(pointVector, ix)
{
    Info << "p[" << ix << "] = " << pointVector[ix] << nl;
}

/************* Interpolate Point To Cell *************/
// using the field data initialized in code
// 4-1. interpolate scalar field data
forAll(phiNew, ix)
{
    phiNew[ix] = interpolatePointToCell(pointScalar, ix);
}
Info << nl << "[4-1] Interpolate Point To Cell scalar field result\n" << nl;
Info << phiNew << nl;

// 4-2. interpolate vector field data
forAll(ENew, ix)
{
    ENew[ix] = interpolatePointToCell(pointVector, ix);
}
Info << nl << "[4-2] Interpolate Point To Cell vector field result\n" << nl;
Info << ENew << nl;


/*********** Field Data Out To Screen ***********/
Info << "Write field data to time folder !!!!!" << nl;
while (runTime.loop())
{
    Info<< "Time = " << runTime.timeName() << nl << endl;
    // if (runTime.time().value() >= 1)
    // {
    //     runTime.write();
    // }
    runTime.write();
}

Info << "Write data done !!" << nl;