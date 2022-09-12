scalar F (96487);          //Faraday's constant
scalar R_CONSTANT (8.314);  //universal gas constant
scalar alpha_a (0.5);     //anode transfer coefficient
scalar alpha_c (0.5);     //cathode transfer coefficient

scalar Ri_a (0); // reaction rate in the anode CL
scalar Ri_c (0); // reaction rate in the cathode CL
scalar A_act = A_ACT.value(); //cell active area
scalar omega (0.5);
scalar term (0);
scalar pi (3.14159);
scalar tortuosity (6.0);

scalar Pref (101325);     // reference pressure;
scalar p_in=P_IN.value(); // inlet pressure;
scalar T_in=T_IN.value();

scalar N_0_fuel (0);      // mole flow rate for fuel
scalar N_0_air (0);       // mole flow rate for air
// mole fraction for inlet species
scalar mole_Fraction_H2_inlet  = MOLE_FRACTION_H2_INLET.value();   
scalar mole_Fraction_CO_inlet  = MOLE_FRACTION_CO_INLET.value();  
scalar mole_Fraction_CH4_inlet = MOLE_FRACTION_CH4_INLET.value(); 
scalar mole_Fraction_H2O_inlet = MOLE_FRACTION_H2O_INLET.value(); 

scalar mole_Fraction_O2_inlet  = MOLE_FRACTION_O2_INLET.value(); 


scalar U_f =U_F.value();  // fuel utilization


scalar I_ref = I_REF.value(); //A m-2  obtain the reference current ensity

scalar FC_cross_section  = FC_CROSS_SECTION.value(); //FC cross-section area: flow channel width*height;
scalar lamda_air = lamda_AIR.value();  //air ratio

// chemical model
scalar z_temp (1.0);


scalar t = runTime.value();  //time index of the case

nuEff=turbulence.nuEff();

 if(fluidRegions[i].name() == "anodePart")
{
   scalarField Ri_a_volume = fluidRegions[i].V() * J_a.internalField();

   Ri_a = gSum(Ri_a_volume);

   Info<<"Volume-averaged Reaction rate in the anode CL is "<<Ri_a<<endl;
   Info<<"anode current density is "<<Ri_a / A_act/10000<< " A/cm2"<<endl;

// set the species inlet in the anode
    label inletPatch = fluidRegions[i].boundaryMesh().findPatchID("outlet_anode");
    scalar u_x (0);
    forAll(U.boundaryFieldRef()[inletPatch],facei)
    {

      if(t > 4)
      {
        I_ref = Ri_a / A_act;

      }

        // N_fuel_0: mole flow rate for fuel
        term=8*F*mole_Fraction_CH4_inlet+2*F*mole_Fraction_H2_inlet+2*F*mole_Fraction_CO_inlet;
        N_0_fuel=I_ref*A_act / (term*U_f);
        u_x =  N_0_fuel*R_CONSTANT*T_in / (FC_cross_section*p_in);
        U.boundaryFieldRef()[inletPatch][facei] = vector (-u_x, 0, 0);
    }
    Info<<"H2 velocity at anode inlet is "<<u_x<<" m/s"<<endl;
//===============================================inlet settings End====================================



    forAll(fluidRegions[i].cellZones(), zoneI)
    {
        const cellZone& cz = fluidRegions[i].cellZones()[zoneI];
        const labelList& cells = cz;

        label cellZoneID  = fluidRegions[i].cellZones().findZoneID("anodeCL");
        label anodeCLSize = fluidRegions[i].cellZones()[cellZoneID].size();


 /*a1*/  if (cz.name() == "anodeFC")
        {

            forAll(cells,iCells)
            {
               const label celli = cells[iCells];

               porosity[celli]=1;
            }
      Info<<"anodeFC done !"<<endl;
         }
 /*a2*/ else if (cz.name() == "anodeGDL")
        {

            forAll(cells,iCells)
           {
              const label celli = cells[iCells];
             //effective conductivity
              porosity[celli]=0.3;
              K_permea[celli] = K_p_GDL.value();
              AC[celli] = nuEff[celli] * rho[celli]/ K_permea[celli]* Foam::pow(porosity[celli],2);

              scalar T_temp = T[celli];
              term=9.5e7/T_temp*Foam::exp(-1150/T_temp);
              k_eff_ele[celli]=omega*(1-porosity[celli])/tortuosity*term;
              
              // chemical model  water gas shift reaction;

              z_temp= 1000/T_temp-1;
              term=-0.2935*Foam::pow(z_temp,3)+0.6351*Foam::pow(z_temp,2)+4.1788*z_temp+0.3169;

              scalar pH2O = moleFrac_H2O[celli] *p_in;
              scalar pCO  = moleFrac_CO[celli]  *p_in;
              scalar pH2  = moleFrac_H2[celli]  *p_in;
              scalar pCO2 = moleFrac_CO2[celli] *p_in;
              scalar pCH4 = moleFrac_CH4[celli] *p_in;

              if (mole_Fraction_CO_inlet > 0)
              {
              Kps[celli]=Foam::exp(term);
              Ksf[celli]=0.0171*Foam::exp(-103191/(R_CONSTANT*T_temp));
              term=Kps[celli];


//              R_WGSR[celli]   = Ksf[celli]*(pH2O*pCO-pH2*pCO2/term);
              heatWGSR[celli] = 45063-10.28*T_temp;
              }

              // chemical model  methane steam reforming reaction;
              if (mole_Fraction_CH4_inlet > 0)
              {
              term=-0.2513*Foam::pow(z_temp,4)+0.3665*Foam::pow(z_temp,3)+0.5810*Foam::pow(z_temp,2)-27.134*z_temp+3.277;
              Kpr[celli]=1.0267e10*Foam::exp(term);
              Krf[celli]=2395*Foam::exp(-231266/(R_CONSTANT*T_temp));
              term=Kpr[celli];
//              R_MSR[celli] = Krf[celli]*(pCH4*pH2O-pCO*Foam::pow(pH2,3)/term);
              heatMSR[celli] = -(206205.5+19.5175*T_temp);
              }
              //species source term;
              S_m_CH4[celli] = -R_MSR[celli]*0.016; //R_MSR*MH2;
              S_m_H2[celli]  = (3*R_MSR[celli]+R_WGSR[celli]) * 0.002; 
              S_m_CO[celli]  = (R_MSR[celli]-R_WGSR[celli])   * 0.028;   
              S_m_H2O[celli] = (-R_MSR[celli]-R_WGSR[celli])  * 0.018;  
              S_m_CO2[celli] = R_WGSR[celli] * 0.044;
              S_m_t[celli]   = S_m_CH4[celli] + S_m_H2[celli] + S_m_CO[celli] + S_m_H2O[celli] + S_m_CO2[celli];
             }
      Info<<"anodeGDL done !"<<endl;
          }       
 /*a3*/ else if (cz.name() == "anodeCL")
        {

            forAll(cells,iCells)
            {
              const label celli = cells[iCells];
              S_ion[celli] = J_a[celli];
              S_ele[celli] = -J_a[celli];
              yita_act[celli] = Fai_ele[celli] -Fai_ion[celli];
             //effective conductivity
              porosity[celli]=0.3;
              K_permea[celli] = K_p_CL.value();
              AC[celli] = nuEff[celli] * rho[celli]/ K_permea[celli]* Foam::pow(porosity[celli],2);

              scalar T_temp = T[celli];
              term=9.5e7/T_temp*Foam::exp(-1150/T_temp);
              k_eff_ele[celli]=omega*(1-porosity[celli])/tortuosity*term;
              k_eff_ion[celli]=(1-omega)*(1-porosity[celli])/tortuosity*33.4e3*Foam::exp(-10300/T_temp);

              //k_eff_ion[celli] = 0.5;
              scalar pH2O = moleFrac_H2O[celli] *p_in;
              scalar pCO  = moleFrac_CO[celli]  *p_in;
              scalar pH2  = moleFrac_H2[celli]  *p_in;
              scalar pCO2 = moleFrac_CO2[celli] *p_in;
              scalar pCH4 = moleFrac_CH4[celli] *p_in;

              // chemical model  water gas shift reaction;
              if (mole_Fraction_CO_inlet > 0)
              {

              z_temp= 1000/T_temp-1;
              term=-0.2935*Foam::pow(z_temp,3)+0.6351*Foam::pow(z_temp,2)+4.1788*z_temp+0.3169;
              Kps[celli]=Foam::exp(term);
              Ksf[celli]=0.0171*Foam::exp(-103191/(R_CONSTANT*T_temp));
              term=Kps[celli];
//              R_WGSR[celli]   = Ksf[celli]*(pH2O*pCO-pH2*pCO2/term);
              heatWGSR[celli] = 45063-10.28*T_temp;
              }
              // chemical model  methane steam reforming reaction;
              if (mole_Fraction_CH4_inlet > 0)
              {
              term=-0.2513*Foam::pow(z_temp,4)+0.3665*Foam::pow(z_temp,3)+0.5810*Foam::pow(z_temp,2)-27.134*z_temp+3.277;

              Kpr[celli]=1.0267e10*Foam::exp(term);
              Krf[celli]=2395*Foam::exp(-231266/(R_CONSTANT*T_temp));
              term=Kpr[celli];
//              R_MSR[celli] = Krf[celli]*(pCH4*pH2O-pCO*Foam::pow(pH2,3)/term);
              heatMSR[celli] = -(206205.5+19.5175*T_temp);
              }
              //source term for species
              S_m_CH4[celli] = -R_MSR[celli]*0.016; //R_MSR*MH2;
              S_m_H2[celli]  = (3*R_MSR[celli]+R_WGSR[celli]) * 0.002-J_a[celli] / (2 * F) * 0.002; 
              S_m_CO[celli]  = (R_MSR[celli]-R_WGSR[celli])   * 0.028-J_a[celli] / (2 * F) * 0.028;
              S_m_H2O[celli] = (-R_MSR[celli]-R_WGSR[celli])  * 0.018+J_a[celli] / (2 * F) * 0.018;
              S_m_CO2[celli] = R_WGSR[celli] * 0.044 + J_a[celli] / (2 * F) * 0.044;

              S_m_t[celli]   = S_m_CH4[celli] + S_m_H2[celli] + S_m_CO[celli] + S_m_H2O[celli] + S_m_CO2[celli];
                    
             }
      Info<<"anodeCL done !"<<endl;

          }
     }

}


 if(fluidRegions[i].name() == "cathodePart")
{

// set the species inlet in the cathode

   scalarField Ri_c_volume = fluidRegions[i].V() * J_c.internalField();

   Ri_c = gSum(Ri_c_volume);

   Info<<"Volume-averaged Reaction rate in the cathode CL is "<<Ri_c<<endl;
   Info<<"cathode current density is "<<Ri_c / A_act/10000<< " A/cm2"<<endl;


    label inletPatch = fluidRegions[i].boundaryMesh().findPatchID("inlet_cathode");
    scalar u_x (0);

       if(t > 4)
      {
        I_ref = Ri_c / A_act;
      }
    
    N_0_air=lamda_air*I_ref*A_act/(4*F*mole_Fraction_O2_inlet);

    forAll(U.boundaryFieldRef()[inletPatch],facei)
    {
      u_x = N_0_air * R_CONSTANT*T_in / (FC_cross_section*p_in);
      U.boundaryFieldRef()[inletPatch][facei] = vector (u_x, 0, 0);

    }
    Info<<"Air velocity at cathode inlet is "<<u_x<<" m/s"<<endl;



    label cellZoneID  = fluidRegions[i].cellZones().findZoneID("cathodeCL");
    label cathodeCLSize = fluidRegions[i].cellZones()[cellZoneID].size();

    forAll(fluidRegions[i].cellZones(), zoneI)
    {
        const cellZone& cz = fluidRegions[i].cellZones()[zoneI];
        const labelList& cells = cz;

    /*c1*/if (cz.name() == "cathodeFC")
        {

            forAll(cells,iCells)
            {
               const label celli = cells[iCells];
               porosity[celli]=1;
             }
      Info<<"cathodeFC done !"<<endl;
           }
    /*c2*/else if (cz.name() == "cathodeGDL")
         {

            forAll(cells,iCells)
            {
                const label celli = cells[iCells];
             //effective conductivity
              porosity[celli]=0.3;
              K_permea[celli] = K_p_GDL.value();
              AC[celli] = nuEff[celli] * rho[celli]/ K_permea[celli]* Foam::pow(porosity[celli],2);

              scalar T_temp = T[celli];
              term=4.2e7/T_temp*Foam::exp(-1200/T_temp);
              k_eff_ele[celli]=omega*(1-porosity[celli])/tortuosity*term;
             }
      Info<<"cathodeGDL done !"<<endl;
          }
    /*c3*/else if (cz.name() == "cathodeCL")
        {

            forAll(cells,iCells)
            {
              const label celli = cells[iCells];
              S_ion[celli] = -J_c[celli];
              S_ele[celli] =  J_c[celli];
              yita_act[celli] = Fai_ele[celli] -Fai_ion[celli];

             //effective conductivity
              porosity[celli]=0.3;
              K_permea[celli] = K_p_CL.value();
              AC[celli] = nuEff[celli] * rho[celli]/ K_permea[celli]* Foam::pow(porosity[celli],2);

              scalar T_temp = T[celli];
              term=4.2e7/T_temp*Foam::exp(-1200/T_temp);
              k_eff_ele[celli]=omega*(1-porosity[celli])/tortuosity*term;

              term=33.4e3*Foam::exp(-10300/T_temp);
              k_eff_ion[celli]=(1-omega)*(1-porosity[celli])/tortuosity*term;

              //k_eff_ion[celli] = 0.5;

              S_m_O2[celli] = -J_c[celli] / (4 * F) * 0.032;

              S_m_t[celli]  = S_m_O2[celli];

             }
      Info<<"cathodeCL done !"<<endl;
         }
      }
}
