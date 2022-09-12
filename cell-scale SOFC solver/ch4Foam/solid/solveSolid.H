{
    #include "1solidZoneSet.H"
    while (pimple.correctNonOrthogonal())
    {
/*        fvScalarMatrix hEqn
        (
            fvm::ddt(betav*rho, h)
          - (
                thermo.isotropic()
              ? fvm::laplacian(betav*thermo.alpha(), h, "laplacian(alpha,h)")
              : fvm::laplacian(betav*taniAlpha(), h, "laplacian(alpha,h)")
            )
          ==
            fvOptions(rho, h)
        );

        hEqn.relax();

        fvOptions.constrain(hEqn);

        hEqn.solve(mesh.solver(h.select(pimples.finalIter())));

        fvOptions.correct(h);
*/
         #include "2Fai_ionEqn.H"
         #include "3Fai_eleEqn.H"
    }
}

thermo.correct();

Info<< "Min/max T:" << min(thermo.T()).value() << ' '
    << max(thermo.T()).value() << endl;
