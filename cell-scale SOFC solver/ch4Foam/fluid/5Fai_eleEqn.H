
        k_eff_ele = alpha_Fai_ele * (1-grad_alpha_Fai_ele) * k_eff_ele;
  //      k_eff_ele_tensor = alpha_Fai_ele * (1-grad_alpha_Fai_ele) * k_eff_ele_tensor;
        fvScalarMatrix Fai_eleEqn
        (
            fvm::ddt(tau_potential, Fai_ele)
          - fvm::laplacian(k_eff_ele, Fai_ele)
          == S_ele
                          
        );


        Fai_eleEqn.relax();

        Fai_eleEqn.solve(mesh.solver(Fai_ele.select(pimples.finalIter())));


Info<< "Min/max Fai_ele:" << min(Fai_ele) << ' '
    << max(Fai_ele) << endl;
