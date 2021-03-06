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

\*---------------------------------------------------------------------------*/

#include "nearestToPoint.H"
#include "polyMesh.H"
#include "meshSearch.H"

#include "addToRunTimeSelectionTable.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{

defineTypeNameAndDebug(nearestToPoint, 0);

addToRunTimeSelectionTable(topoSetSource, nearestToPoint, word);

addToRunTimeSelectionTable(topoSetSource, nearestToPoint, istream);

}


Foam::topoSetSource::addToUsageTable Foam::nearestToPoint::usage_
(
    nearestToPoint::typeName,
    "\n    Usage: nearestToPoint (pt0 .. ptn)\n\n"
    "    Select the nearest point for each of the points pt0 ..ptn\n\n"
);


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void Foam::nearestToPoint::combine(topoSet& set, const bool add) const
{
    // Do linear search since usually just a few points.

    forAll(points_, pointI)
    {
        const pointField& pts = mesh_.points();

        if (pts.size())
        {
            label minPointI = 0;
            scalar minDistSqr = magSqr(pts[minPointI] - points_[pointI]);

            for (label i = 1; i < pts.size(); i++)
            {
                scalar distSqr = magSqr(pts[i] - points_[pointI]);

                if (distSqr < minDistSqr)
                {
                    minDistSqr = distSqr;
                    minPointI = i;
                }
            }

            addOrDelete(set, minPointI, add);
        }
    }
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

// Construct from components
Foam::nearestToPoint::nearestToPoint
(
    const polyMesh& mesh,
    const pointField& points
)
:
    topoSetSource(mesh),
    points_(points)
{}


// Construct from dictionary
Foam::nearestToPoint::nearestToPoint
(
    const polyMesh& mesh,
    const dictionary& dict
)
:
    topoSetSource(mesh),
    points_(dict.lookup("points"))
{}


// Construct from Istream
Foam::nearestToPoint::nearestToPoint
(
    const polyMesh& mesh,
    Istream& is
)
:
    topoSetSource(mesh),
    points_(checkIs(is))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

Foam::nearestToPoint::~nearestToPoint()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void Foam::nearestToPoint::applyToSet
(
    const topoSetSource::setAction action,
    topoSet& set
) const
{
    if ((action == topoSetSource::NEW) || (action == topoSetSource::ADD))
    {
        Info<< "    Adding points nearest to " << points_ << endl;

        combine(set, true);
    }
    else if (action == topoSetSource::DELETE)
    {
        Info<< "    Removing points nearest to " << points_ << endl;

        combine(set, false);
    }
}


// ************************************************************************* //
