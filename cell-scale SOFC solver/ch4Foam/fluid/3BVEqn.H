//scalar Av (1.025e5);     //reactive surface area per unit volume, from Nerat et al.  Int J Hydrogen Energy 2016;41(5):3613e27;
scalar Av (1.5e5); 
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

 


if(fluidRegions[i].name() =="anodePart")
{
   label cellZoneID = fluidRegions[i].cellZones().findZoneID("anodeCL");
    const cellZone& cz = fluidRegions[i].cellZones()[cellZoneID];
    const labelList& cells = cz;

        forAll(cells, iCells)
        {
         const label celli = cells[iCells];
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

       }
    //   Info<<"Max over potential yita_act is"<<max(yita_act)<<endl;
    //   Info<<"Min over potential yita_act is"<<min(yita_act)<<endl;
       Info<<"J_a is calculated in the anodeCL"<<endl;
       Info<<"max(J_a)"<<max(J_a)<<"     "<<"min(J_a)"<<min(J_a)<<endl;
       Info<<"j0_a in the anodeCL "<<j0_a<<endl;
}





if(fluidRegions[i].name() =="cathodePart")
{
   label cellZoneID = fluidRegions[i].cellZones().findZoneID("cathodeCL");
    const cellZone& cz = fluidRegions[i].cellZones()[cellZoneID];
    const labelList& cells = cz;


        forAll(cells, iCells)
        {
         const label celli = cells[iCells];
          yita_act[celli] = Fai_ele[celli] - Fai_ion[celli];

         scalar T_temp = T_in;//T[celli];
         scalar XO2    = moleFrac_O2[celli];
                j0_c=gamma_c_O2*Foam::pow(XO2,0.25)*Foam::exp(-Eact_c/(R_CONSTANT*T_temp));

    //   Info<<"j0_c in the cathodeCL "<<j0_c<<endl;
         scalar term1=Foam::exp(     alpha_c*4*F*yita_act[celli]/(R_CONSTANT*T_temp));
         scalar term2=Foam::exp(-(1-alpha_c)*4*F*yita_act[celli]/(R_CONSTANT*T_temp));       
         scalar J_t=j0_c*Av*(-term1+term2);
         J_c[celli]=J_t;
          if(J_c[celli] < 0 )
          {
             Info<<"J_c is negative! Force to zero"<<endl;
             J_c[celli] = 0;
          }
        }
      // Info<<"Max over potential yita_act is"<<max(yita_act)<<endl;
      // Info<<"Min over potential yita_act is"<<min(yita_act)<<endl;
       Info<<"J_c is calculated in the cathodeCL"<<endl;
       Info<<"max(J_c)"<<max(J_c)<<"     "<<"min(J_c)"<<min(J_c)<<endl;
       Info<<"j0_c in the cathodeCL "<<j0_c<<endl;
}

















