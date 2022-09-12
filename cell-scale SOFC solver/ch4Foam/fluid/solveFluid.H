if (pimple.frozenFlow())
{
//    #include "EEqn.H"
}
else
{
    #include "1fluidZoneSet.H"
    #include "2moleFraction.H"
   // #include "6diffusionCoeff.H"
    #include "7WangdiffusionCoeff.H"
    if (!mesh.steady() && pimples.nCorrPimple() <= 1)
    {
        //#include "rhoEqn.H"
        #include "sofc_rhoEqn.H"
    }

    #include "UEqn.H"
    #include "YEqn.H"
//    #include "EEqn.H"
     #include "3BVEqn.H"
     #include "4Fai_ionEqn.H"
     #include "5Fai_eleEqn.H"

    // --- PISO loop
    while (pimple.correct())
    {
        #include "pEqn.H"
    }

    if (pimples.pimpleTurbCorr(i))
    {
        turbulence.correct();
    }

    if (!mesh.steady() && pimples.finalIter())
    {
        rho = thermo.rho();
    }
}
