if (fluidRegions[i].name() == "Ni")
{

label anode_topPatch (0);   // the fixed value is set in this patch, the bottom in the cathode is zero
scalar T_0=T_IN.value();  //inlet temperature
scalar p_0=P_IN.value(); //inlet pressure;

//species mole fraction for H2, CO, H2O
scalar chi_H2  = MOLE_FRACTION_H2_INLET.value(); 
scalar chi_CO  = MOLE_FRACTION_CO_INLET.value();

scalar para_H2 (2.4516e-4);//from Ni Meng, ECM 70(2013);
scalar para_CO (4.527e-4); //from Ni Meng, ECM 70(2013);


//scalar term1=Foam::log(p0_H2*Foam::pow(p0_O2,0.5)/p0_H2O);
scalar E0 (1.12128);
scalar E_H2;
       E_H2 = E0;
//if(t>4 && p_H2O > 0) E_H2 = 1.253   - para_H2 * T_0 + 8.314 * T_0/2/96487 * Foam::log(p_H2 * Foam::sqrt (p_O2)/p_H2O);

scalar Eocv = 1.253   - para_H2 * T_0;


Info<<"open circuit voltage is "<<Eocv<<endl;


 if(fluidRegions[i].name() =="Ni")
{
   anode_topPatch = fluidRegions[i].boundaryMesh().findPatchID("bottom");
   Info<<"NiRegion_Patch ID is "<<anode_topPatch<<endl;
    
         forAll(Fai_ele.boundaryFieldRef()[anode_topPatch],facei)
        {
         
               Fai_ele.boundaryFieldRef()[anode_topPatch][facei] = V_out.value();         

        }

}

  //      k_eff_ele = alpha_Fai_ele * (1-grad_alpha_Fai_ele) * k_eff_ele;
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


}
