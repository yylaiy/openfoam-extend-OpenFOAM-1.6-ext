IOdictionary propsDict
(
    IOobject
    (
        "particleTrackProperties",
        runTime.constant(),
        mesh,
        IOobject::MUST_READ
    )
);

word cloudName(propsDict.lookup("cloudName"));

label sampleFrequency(readLabel(propsDict.lookup("sampleFrequency")));

// outputMode: compositeFile, filePerTrack
//word outputmode(propsDict.lookup("outputMode"))

label maxPositions(readLabel(propsDict.lookup("maxPositions")));

// outputFormat: raw, vtk
//word outputFormat(propsDict.lookup("outputFormat"));
