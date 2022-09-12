//scalar Av (1.025e5);     //reactive surface area per unit volume, from Nerat et al.  Int J Hydrogen Energy 2016;41(5):3613e27;
//scalar Av (1.5e5); 
scalar Av (1.5e3);
mole_Fraction_H2_inlet = MOLE_FRACTION_H2_INLET.value();  //inlet mole fraction for H2; 
mole_Fraction_CO_inlet = MOLE_FRACTION_CO_INLET.value();  //inlet mole fraction for CO;
mole_Fraction_O2_inlet = MOLE_FRACTION_O2_INLET.value();  //inlet mole fraction for O2;


scalar p_H2_in=p_in*mole_Fraction_H2_inlet;  //H2 partial pressure;
scalar p_CO_in=p_in*mole_Fraction_CO_inlet;  //CO partial pressure;
scalar p_O2_in=p_in*mole_Fraction_O2_inlet;  //O2 partial pressure;

//adjustable experiment fitting parameters for BV Eqn;
scalar gamma_a_H2=1.35e9;
scalar gamma_a_CO=6.14e8;
scalar gamma_c_O2=9.0e7;
scalar para_m (0.5);
scalar para_n (0.5);
//scalar para_k (0.25);
scalar para_k (0.25);
// end
scalar Eact_a (1.1e5);
scalar Eact_c (1.3e5);
scalar j0_a (0);
scalar j0_c (0);

scalar E_a (12000);
 


if(fluidRegions[i].name() =="pore")
{
    TPB = 0;
    label patchID_pore_to_Ni = fluidRegions[i].boundaryMesh().findPatchID("pore_to_Ni");
    forAll(TPB.boundaryFieldRef()[patchID_pore_to_Ni],facei)
    {
        label cellID = fluidRegions[i].boundaryMesh()[patchID_pore_to_Ni].faceCells()[facei];
        TPB[cellID]  = 1;
    }

    label nTPB = 0;
    patchID_pore_to_Ni = fluidRegions[i].boundaryMesh().findPatchID("pore_to_YSZ");
    forAll(TPB.boundaryFieldRef()[patchID_pore_to_Ni],facei)
    {
        label cellID = fluidRegions[i].boundaryMesh()[patchID_pore_to_Ni].faceCells()[facei];
        if(TPB[cellID] == 1)
        {
            TPB[cellID]  = 2;
            nTPB += 1;
        }
    }

    Info<<"number of TPB cell in pore region " <<nTPB<<endl;

    forAll(Fai_ele, celli)
    {
/*        if(TPB[celli] == 2)
        { 
             yita_act[celli] = Fai_ele[celli] - Fai_ion[celli];
             scalar T_temp = T_in;//T[celli];
             scalar XH2    = moleFrac_H2[celli];
             scalar XCO    = moleFrac_CO[celli];
             scalar j0_a_H2=gamma_a_H2*Foam::sqrt(XH2)*Foam::exp(-Eact_a/(R_CONSTANT*T_temp));
             scalar j0_a_CO=gamma_a_CO*Foam::sqrt(XCO)*Foam::exp(-Eact_a/(R_CONSTANT*T_temp));
                      j0_a = j0_a_H2 + j0_a_CO;

             scalar term1=Foam::exp(     alpha_a*2*F*yita_act[celli]/(R_CONSTANT*T_temp));
             scalar term2=Foam::exp(-(1-alpha_a)*2*F*yita_act[celli]/(R_CONSTANT*T_temp));       
             scalar J_t=j0_a*Av*(term1-term2);
             J_a[celli]=J_t;

       //Info<<"j0_a ="<<j0_a<<",j0_H2="<<j0_a_H2<<",j0_CO="<<j0_a_CO<<endl;
       //Info<<"term= "<<term1<<",  "<<term2<<";moleFrac="<<mole_Fraction_H2_inlet<<",  "<<mole_Fraction_H2_inlet<<endl;
             if(J_a[celli] < 0 )
            {
               Info<<"J_a is negative! Force to zero"<<endl;
               J_a[celli] = 0;
            }
        }*/

        if(TPB[celli] == 2)
        { 

         yita_act[celli] = Fai_ele[celli] - Fai_ion[celli];
         scalar T_temp = T_in;//T[celli];
         scalar XH2    = moleFrac_H2[celli];
         scalar XH2O   = moleFrac_H2O[celli];

         //BV Equation from Li Qiangqiang, Energy & Fuels 2021, 35, 12495-12506;
         scalar TPBl   = 2.49e12;   // three-phase density length, unit m*m-3;
         scalar j0     = 0.0013 * Foam::pow(XH2 *p[celli], 0.04) 
                                * Foam::pow(XH2O*p[celli], 0.67)
                                * Foam::exp(-84900/(R_CONSTANT*T[celli]));
         scalar term   = Foam::exp(2*F*yita_act[celli]/(R_CONSTANT*T[celli])); 
         scalar term1  = Foam::exp( -F*yita_act[celli]/(R_CONSTANT*T[celli]));    
         scalar J_t    = j0*(term-term1) /(65e-9*65e-9);       

         scalar i0     = 31.4 * Foam::pow(XH2 *p[celli], -0.03) 
                              * Foam::pow(XH2O*p[celli], 0.4)
                              * Foam::exp(-1.52e5/(R_CONSTANT*T[celli]));  

          J_t    = i0*(term-term1) /(65e-9*65e-9);  //65e-9 is the mesh resolution
         J_a[celli]    = J_t;    
         



         //BV equation from Wang Yang applications in Energy and Combustion Science 2021
/*         scalar yita = 5.5e9;
         scalar TPBl = 100;
         scalar term = Foam::sqrt(XH2*p_in/Pref) * Foam::exp(-E_a/(R_CONSTANT*T_temp));
         scalar j0   = yita*R_CONSTANT*T_temp/(2*F)*TPBl/1.455 * term;       

                term   = Foam::exp(alpha_a*2*F*yita_act[celli]/(R_CONSTANT*T_temp)); 
         scalar term1  = Foam::exp(-(1-alpha_a)*2*F*yita_act[celli]/(R_CONSTANT*T_temp)); 
         scalar J_t    = j0 * (term - term1); 
         J_a[celli]    = J_t;*/
         }
    }

    //   Info<<"Max over potential yita_act is"<<max(yita_act)<<endl;
    //   Info<<"Min over potential yita_act is"<<min(yita_act)<<endl;
       Info<<"J_a is calculated in the pore"<<endl;
       Info<<"max(J_a)"<<max(J_a)<<"     "<<"min(J_a)"<<min(J_a)<<endl;
       Info<<"j0_a in the pore "<<j0_a<<endl;

    Info<<"BVEqn done in the pore"<<endl;
}


