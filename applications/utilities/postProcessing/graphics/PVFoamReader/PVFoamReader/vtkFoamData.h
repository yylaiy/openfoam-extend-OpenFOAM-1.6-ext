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
    vtkFoamData

Description

SourceFiles
    vtkFoamData.cxx

\*---------------------------------------------------------------------------*/

#ifndef vtkFoamData_h
#define vtkFoamData_h

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include "vtkDataSetSource.h"

/*---------------------------------------------------------------------------*\
                         Class vtkFoamData Declaration
\*---------------------------------------------------------------------------*/

class VTK_IO_EXPORT vtkFoamData
: 
    public vtkDataSetSource
{

public:

    static vtkFoamData *New();
    vtkTypeRevisionMacro(vtkFoamData,vtkDataSetSource);

    vtkFoamData();
    ~vtkFoamData();

    void SetNthOutput(int num, vtkDataObject *output)
    {
        vtkDataSetSource::SetNthOutput(num, output);
    }
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
