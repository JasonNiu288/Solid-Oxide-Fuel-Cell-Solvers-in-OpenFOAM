
     if (solidRegions[i].name() == "membrane")
     {
        fvScalarMatrix Fai_ionEqn
        (
            fvm::ddt(tau_potential, Fai_ion)
          - fvm::laplacian(k_eff_ion, Fai_ion)
                          
        );

        Fai_ionEqn.relax();

        Fai_ionEqn.solve(mesh.solver(Fai_ion.select(pimples.finalIter())));


       Info<< "Min/max Fai_ion:" << min(Fai_ion) << ' '
          << max(Fai_ion) << endl;
      }
