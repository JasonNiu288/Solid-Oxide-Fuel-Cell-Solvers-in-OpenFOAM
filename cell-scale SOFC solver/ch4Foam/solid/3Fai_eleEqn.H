if (solidRegions[i].name() == "anodeBP" || solidRegions[i].name() == "cathodeBP")
{

label anode_topPatch (0);   // the fixed value is set in this patch, the bottom in the cathode is zero
scalar T_0=T_IN.value();  //inlet temperature
scalar p_0=P_IN.value(); //inlet pressure;

//species mole fraction for H2, CO, H2O
scalar chi_H2  = MOLE_FRACTION_H2_INLET.value(); 
scalar chi_CO  = MOLE_FRACTION_CO_INLET.value();
// species partial pressure, scaled by reference pressure
scalar p_H2  = 0.4;//H2_I; 
scalar p_CO  = 0.4;//CO_I;
scalar p_O2  = 0.2;//O2_I;
scalar p_H2O = 0.2;//H2O_I;
scalar p_CO2 = 0.1;//CO2_I;

scalar t = runTime.value();
//Info<<",Time "<<t<<endl;
if (t>2*0.01)
{
    p_H2  = H2_I; 
    p_CO  = CO_I;
    p_O2  = O2_I;
    p_H2O = H2O_I;
    p_CO2 = CO2_I;
}

//Info<<"H2 Interface = " <<H2_I<<", and O2  "<<O2_I<<endl;
Info<<"CO Interface = " <<CO_I<<", and H2O "<<H2O_I<<", CO2 "<<CO2_I<<endl;

scalar para_H2 (2.4516e-4);//from Ni Meng, ECM 70(2013);
scalar para_CO (4.527e-4); //from Ni Meng, ECM 70(2013);


//scalar term1=Foam::log(p0_H2*Foam::pow(p0_O2,0.5)/p0_H2O);
scalar E0 (1.0);
scalar E_H2;
       E_H2 = E0;
scalar E_CO;
       E_CO = 0;
if(t>4 && p_H2O > 0) E_H2 = 1.253   - para_H2 * T_0 + 8.314 * T_0/2/96487 * Foam::log(p_H2 * Foam::sqrt (p_O2)/p_H2O);
if(t>4 && p_CO > 0) E_CO = 1.46713 - para_CO * T_0 + 8.314 * T_0/2/96487 * Foam::log(p_CO * Foam::sqrt (p_O2)/p_CO2);


//scalar Eocv=E_H2*chi_H2/(chi_H2+chi_CO)+E_CO*chi_CO/(chi_H2+chi_CO);
scalar Eocv =E0;
if (t > 4)   Eocv=E_H2*chi_H2/(chi_H2+chi_CO)+E_CO*chi_CO/(chi_H2+chi_CO);
if (t <= 4)  Eocv = 1.0;

Eocv =0.95;

Info<<"open circuit voltage is "<<Eocv<<endl;


 if(solidRegions[i].name() =="anodeBP")
{
   anode_topPatch = solidRegions[0].boundaryMesh().findPatchID("top");
   Info<<"anode_topPatch ID is "<<anode_topPatch<<endl;
    
         forAll(Fai_ele.boundaryFieldRef()[anode_topPatch],facei)
        {
         
               Fai_ele.boundaryFieldRef()[anode_topPatch][facei] = Eocv - V_out.value();         

        }

}



       fvScalarMatrix Fai_eleEqn
        (
            fvm::ddt(tau_potential, Fai_ele)
          - fvm::laplacian(k_eff_ele, Fai_ele)
            
        );

        Fai_eleEqn.relax();

        Fai_eleEqn.solve(mesh.solver(Fai_ele.select(pimples.finalIter())));

Info<< "Min/max Fai_ele:" << min(Fai_ele) << ' '
    << max(Fai_ele) << endl;

}
