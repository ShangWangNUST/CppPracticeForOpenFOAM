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

\*---------------------------------------------------------------------------*/

#include "parabolicVelocityFvPatchVectorField.H"
#include "addToRunTimeSelectionTable.H"
#include "fvPatchFieldMapper.H"
#include "volFields.H"
#include "surfaceFields.H"

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

// Foam::scalar Foam::parabolicVelocityFvPatchVectorField::t() const
// {
//     return db().time().userTimeValue();
// }


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::parabolicVelocityFvPatchVectorField::
parabolicVelocityFvPatchVectorField
(
    const fvPatch& p,
    const DimensionedField<vector, volMesh>& iF
)
:
    fixedValueFvPatchVectorField(p, iF),
    maxvalue_(0),
    n_(1, 0, 0),
    y_(0, 1, 0)
{
}


Foam::parabolicVelocityFvPatchVectorField::
parabolicVelocityFvPatchVectorField
(
    const fvPatch& p,
    const DimensionedField<vector, volMesh>& iF,
    const dictionary& dict
)
:
    fixedValueFvPatchVectorField(p, iF),
    maxvalue_(readScalar(dict.lookup("maxvalue"))),
    n_(dict.lookup("n")),
    y_(dict.lookup("y"))
{
    Info << "Using the parabolicVelocity boundary condition" << endl;
     if (mag(n_) < SMALL || mag(y_) < SMALL)
    {
        FatalErrorIn("parabolicVelocityFvPatchVectorField(dict)")
        << "n or y given with zero size not correct"
        << abort(FatalError);
    }
    n_ /= mag(n_);
    y_ /= mag(y_);


    fixedValueFvPatchVectorField::evaluate();

    /*
    // Initialise with the value entry if evaluation is not possible
    fvPatchVectorField::operator=
    (
        vectorField("value", dict, p.size())
    );
    */
}


Foam::parabolicVelocityFvPatchVectorField::
parabolicVelocityFvPatchVectorField
(
    const parabolicVelocityFvPatchVectorField& ptf,
    const fvPatch& p,
    const DimensionedField<vector, volMesh>& iF,
    const fvPatchFieldMapper& mapper
)
:
    fixedValueFvPatchVectorField(ptf, p, iF, mapper),
    maxvalue_(ptf.maxvalue_),
    n_(ptf.n_),
    y_(ptf.y_)
{}


Foam::parabolicVelocityFvPatchVectorField::
parabolicVelocityFvPatchVectorField
(
    const parabolicVelocityFvPatchVectorField& ptf,
    const DimensionedField<vector, volMesh>& iF
)
:
    fixedValueFvPatchVectorField(ptf, iF),
    maxvalue_(ptf.maxvalue_),
    n_(ptf.n_),
    y_(ptf.y_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void Foam::parabolicVelocityFvPatchVectorField::updateCoeffs()
{
    if (updated())
    {
        return;
    }
    // 得到边界坐标
    boundBox bb(patch().patch().localPoints(),true);
    // 得到边界的中点，因为并非所有时候中点都是零
    vector ctr = 0.5*(bb.max()+bb.min());
    // 得到面向量
    const vectorField &c = patch().Cf();
    // 这里的&符号表示向量点积
    scalarField coord = 2*((c-ctr)&y_)/((bb.max()-bb.min())&y_);
    // 给边界赋值
    vectorField :: operator =(n_*maxvalue_ * (1.0-sqr(coord)));

    fixedValueFvPatchVectorField::updateCoeffs();
}


void Foam::parabolicVelocityFvPatchVectorField::write
(
    Ostream& os
) const
{
    fvPatchVectorField::write(os);
    writeEntry(os, "n", n_);
    writeEntry(os, "y", y_);
    writeEntry(os, "maxvalue", maxvalue_);
    writeEntry(os, "value", *this);
}


// * * * * * * * * * * * * * * Build Macro Function  * * * * * * * * * * * * //

namespace Foam
{
    makePatchTypeField
    (
        fvPatchVectorField,
        parabolicVelocityFvPatchVectorField
    );
}

// ************************************************************************* //
