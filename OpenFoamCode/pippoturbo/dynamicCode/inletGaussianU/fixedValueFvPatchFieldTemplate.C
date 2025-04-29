/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2019-2021 OpenCFD Ltd.
    Copyright (C) YEAR AUTHOR, AFFILIATION
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

#include "fixedValueFvPatchFieldTemplate.H"
#include "addToRunTimeSelectionTable.H"
#include "fvPatchFieldMapper.H"
#include "volFields.H"
#include "surfaceFields.H"
#include "unitConversion.H"
#include "PatchFunction1.H"

//{{{ begin codeInclude
#line 30 "/home/richard/OpenFOAM/richard-v2412/run/tutorials/incompressible/simpleFoam/pippoturbo/0/U/boundaryField/inlet"
#include "fvCFD.H"
//}}} end codeInclude


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// * * * * * * * * * * * * * * * Local Functions * * * * * * * * * * * * * * //

//{{{ begin localCode

//}}} end localCode


// * * * * * * * * * * * * * * * Global Functions  * * * * * * * * * * * * * //

// dynamicCode:
// SHA1 = d48e94c91ba2f1a5325bb07ab595b8946b7a3b6a
//
// unique function name that can be checked if the correct library version
// has been loaded
extern "C" void inletGaussianU_d48e94c91ba2f1a5325bb07ab595b8946b7a3b6a(bool load)
{
    if (load)
    {
        // Code that can be explicitly executed after loading
    }
    else
    {
        // Code that can be explicitly executed before unloading
    }
}

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

makeRemovablePatchTypeField
(
    fvPatchVectorField,
    inletGaussianUFixedValueFvPatchVectorField
);

} // End namespace Foam


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::
inletGaussianUFixedValueFvPatchVectorField::
inletGaussianUFixedValueFvPatchVectorField
(
    const fvPatch& p,
    const DimensionedField<vector, volMesh>& iF
)
:
    parent_bctype(p, iF)
{
    if (false)
    {
        printMessage("Construct inletGaussianU : patch/DimensionedField");
    }
}


Foam::
inletGaussianUFixedValueFvPatchVectorField::
inletGaussianUFixedValueFvPatchVectorField
(
    const inletGaussianUFixedValueFvPatchVectorField& rhs,
    const fvPatch& p,
    const DimensionedField<vector, volMesh>& iF,
    const fvPatchFieldMapper& mapper
)
:
    parent_bctype(rhs, p, iF, mapper)
{
    if (false)
    {
        printMessage("Construct inletGaussianU : patch/DimensionedField/mapper");
    }
}


Foam::
inletGaussianUFixedValueFvPatchVectorField::
inletGaussianUFixedValueFvPatchVectorField
(
    const fvPatch& p,
    const DimensionedField<vector, volMesh>& iF,
    const dictionary& dict
)
:
    parent_bctype(p, iF, dict)
{
    if (false)
    {
        printMessage("Construct inletGaussianU : patch/dictionary");
    }
}


Foam::
inletGaussianUFixedValueFvPatchVectorField::
inletGaussianUFixedValueFvPatchVectorField
(
    const inletGaussianUFixedValueFvPatchVectorField& rhs
)
:
    parent_bctype(rhs),
    dictionaryContent(rhs)
{
    if (false)
    {
        printMessage("Copy construct inletGaussianU");
    }
}


Foam::
inletGaussianUFixedValueFvPatchVectorField::
inletGaussianUFixedValueFvPatchVectorField
(
    const inletGaussianUFixedValueFvPatchVectorField& rhs,
    const DimensionedField<vector, volMesh>& iF
)
:
    parent_bctype(rhs, iF)
{
    if (false)
    {
        printMessage("Construct inletGaussianU : copy/DimensionedField");
    }
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

Foam::
inletGaussianUFixedValueFvPatchVectorField::
~inletGaussianUFixedValueFvPatchVectorField()
{
    if (false)
    {
        printMessage("Destroy inletGaussianU");
    }
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void
Foam::
inletGaussianUFixedValueFvPatchVectorField::updateCoeffs()
{
    if (this->updated())
    {
        return;
    }

    if (false)
    {
        printMessage("updateCoeffs inletGaussianU");
    }

//{{{ begin code
    #line 35 "/home/richard/OpenFOAM/richard-v2412/run/tutorials/incompressible/simpleFoam/pippoturbo/0/U/boundaryField/inlet"
// Face centres on this inlet patch
            const vectorField& Cf = patch().Cf();

            // Gaussian parameters
            const scalar x0     = 3;   // centre in x [m]
            const scalar z0     = 0.0;   // centre in z [m]
            const scalar sigma  = 3;   // width [m]
            const scalar Umax   = 3.0;   // peak velocity [m/s]
            const scalar x1 = 2.0;
            const scalar z1 = 6.0;
            const scalar sigma1 = 1.0;


            // Loop over each face, compute radius and assign U vector
        forAll(Cf, faceI)
            {
            scalar x = Cf[faceI].x();
            scalar z = Cf[faceI].z();

            scalar dx = (x - x0) / sigma;
            scalar dz = (z - z0) / sigma;
            scalar mag = exp(-(dx * dx + dz * dz));

            scalar dx1 = (x - x1) / sigma;
            scalar dz1 = (z - z1) / sigma;
            scalar mag1 = exp(-(dx1 * dx1 + dz1 * dz1));

    // sommo le due Gaussiane e moltiplico per il picco
            //mag1 ok, è al centro del patch
            // scalar speed = Umax * (mag1);
            scalar speed = Umax * (mag+mag1);

            // assegno in una volta
    (*this)[faceI] = vector(speed, 0.0, 0.0);
        }
//}}} end code

    this->parent_bctype::updateCoeffs();
}


// ************************************************************************* //

