/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2019-2021 OpenCFD Ltd.
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

Description
    Template for use with dynamic code generation of a
    fixedValue fvPatchField.

    - without state

SourceFiles
    fixedValueFvPatchFieldTemplate.C

\*---------------------------------------------------------------------------*/

#ifndef fixedValueFvPatchTemplateVectorField_H
#define fixedValueFvPatchTemplateVectorField_H

#include "fixedValueFvPatchFields.H"
#include "dictionaryContent.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                         A templated FixedValueFvPatch
\*---------------------------------------------------------------------------*/

class inletGaussianUFixedValueFvPatchVectorField
:
    public fixedValueFvPatchField<vector>,
    public dictionaryContent
{
    //- The parent boundary condition type
    typedef fixedValueFvPatchField<vector> parent_bctype;


    // Private Member Functions

        //- Report a message with the SHA1sum
        inline static void printMessage(const char* message)
        {
            Info<< message << " sha1: " << SHA1sum << '\n';
        }

public:

    //- SHA1 representation of the code content
    static constexpr const char* const SHA1sum = "d48e94c91ba2f1a5325bb07ab595b8946b7a3b6a";

    //- Runtime type information
    TypeName("inletGaussianU");


    // Constructors

        //- Construct from patch and internal field
        inletGaussianUFixedValueFvPatchVectorField
        (
            const fvPatch&,
            const DimensionedField<vector, volMesh>&
        );

        //- Construct from patch, internal field and dictionary
        inletGaussianUFixedValueFvPatchVectorField
        (
            const fvPatch&,
            const DimensionedField<vector, volMesh>&,
            const dictionary&
        );

        //- Construct by mapping a copy onto a new patch
        inletGaussianUFixedValueFvPatchVectorField
        (
            const inletGaussianUFixedValueFvPatchVectorField&,
            const fvPatch&,
            const DimensionedField<vector, volMesh>&,
            const fvPatchFieldMapper&
        );

        //- Construct as copy
        inletGaussianUFixedValueFvPatchVectorField
        (
            const inletGaussianUFixedValueFvPatchVectorField&
        );

        //- Construct as copy setting internal field reference
        inletGaussianUFixedValueFvPatchVectorField
        (
            const inletGaussianUFixedValueFvPatchVectorField&,
            const DimensionedField<vector, volMesh>&
        );

        //- Return a clone
        virtual tmp<fvPatchField<vector>> clone() const
        {
            return fvPatchField<vector>::Clone(*this);
        }

        //- Clone with an internal field reference
        virtual tmp<fvPatchField<vector>> clone
        (
            const DimensionedField<vector, volMesh>& iF
        ) const
        {
            return fvPatchField<vector>::Clone(*this, iF);
        }


    //- Destructor
    virtual ~inletGaussianUFixedValueFvPatchVectorField();


    // Member Functions

        //- Code context as a dictionary
        const dictionary& codeContext() const noexcept
        {
            return dictionaryContent::dict();
        }

        //- Update the coefficients associated with the patch field
        virtual void updateCoeffs();
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //

