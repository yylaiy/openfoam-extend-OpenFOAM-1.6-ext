/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright held by original author
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software; you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by the
    Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM; if not, write to the Free Software Foundation,
    Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Class
    Foam::skewCorrectionVectors

Description
    Skew-correction vectors for the skewness-corrected interpolation scheme

SourceFiles
    skewCorrectionVectors.C

\*---------------------------------------------------------------------------*/

#ifndef skewCorrectionVectors_H
#define skewCorrectionVectors_H

#include "MeshObject.H"
#include "fvMesh.H"
#include "surfaceFieldsFwd.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

class fvMesh;
class mapPolyMesh;

/*---------------------------------------------------------------------------*\
                    Class skewCorrectionVectors Declaration
\*---------------------------------------------------------------------------*/

class skewCorrectionVectors
:
    public MeshObject<fvMesh, skewCorrectionVectors>
{
    // Private data

        //- Is mesh skew
        mutable bool skew_;

        //- Skew correction vectors
        mutable surfaceVectorField* skewCorrectionVectors_;

        //- Construct skewness correction vectors
        void makeSkewCorrectionVectors() const;


public:

    TypeName("skewCorrectionVectors");


    // Constructors

        explicit skewCorrectionVectors(const fvMesh& mesh);


    // Destructor

        virtual ~skewCorrectionVectors();


    // Member functions

        //- Return whether mesh is skew or not
        bool skew() const;

        //- Return reference to skew vectors array
        const surfaceVectorField& operator()() const;

        //- Delete the correction vectors when the mesh moves
        virtual bool movePoints() const;

        //- Delete the correction vectors when the mesh is updated
        virtual bool updateMesh(const mapPolyMesh&) const;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
