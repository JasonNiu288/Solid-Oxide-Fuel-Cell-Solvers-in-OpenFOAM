/*---------------------------------------------------------------------------*\
  calculate effective diffusion coefficients 
\*---------------------------------------------------------------------------*/



//const label sizeY = Y.size();
//const basicSpecieMixture& spMixture=dynamic_cast<const basicSpecieMixture&>(composition);
// for effective diffusion coefficients
     List<scalar> D_V;  //diffusion volume;

     List<List<scalar>>  mw_nsp;   // mole weight Mij
     List<List<scalar>>  moleFrac; // mole fraction, size: nsp*ncells
List<List<List<scalar>>> Dij;      //binary diffusion coeficients for species i and j;
     List<List<scalar>>  Dij_Knu;  //Knudsen diffusion coefficient
     List<List<scalar>>  Dij_eff;  //effective diffusion coefficient Deff_i,j

     D_V.resize(sizeY);
  mw_nsp.resize(sizeY);
     Dij.resize(sizeY);
 Dij_Knu.resize(sizeY);
 Dij_eff.resize(sizeY);
moleFrac.resize(sizeY);

     List<List<scalar>> sumD;  //sum mole fraction/Dij;
     sumD.resize(sizeY);


//forAll(fluidRegions[i].cellZones(), zoneI)
//{
 if(fluidRegions[i].name() == "pore")  
{

    label ncells = mesh.nCells();

//===========================================================
// #1 loop, array initilization;
//===========================================================
    //resize the array
    for (label isp = 0; isp < sizeY; isp++)
    {
        mw_nsp[isp].resize (sizeY);
           Dij[isp].resize (sizeY);
       Dij_Knu[isp].resize (ncells);
       Dij_eff[isp].resize (ncells);
      moleFrac[isp].resize (ncells);
          sumD[isp].resize (ncells);

      moleFrac[isp]    = 0.0;
      Dij_Knu[isp]     = 0.0;
         sumD[isp]     = 0.0;

        for (label jsp = 0; jsp < sizeY; jsp++)
        {
              Dij[isp][jsp].resize(ncells);
           mw_nsp[isp][jsp] = 0.0;
              Dij[isp][jsp] = 0.0;
        }

      // diffusion volume and moleFraction initialization;
      forAll(T,celli)
      {
         if (Y[isp].name()=="H2")
         {
         D_V[isp]  =  6.12;
         moleFrac[isp][celli]  = moleFrac_H2[celli];
         }
         else if (Y[isp].name()=="H2O")
         {
         D_V[isp]  =  13.1;
         moleFrac[isp][celli]  = moleFrac_H2O[celli];
         }
         else if (Y[isp].name()=="CO")
         {
         D_V[isp]  =  18.0;
         moleFrac[isp][celli]  = moleFrac_CO[celli];
         }
         else if (Y[isp].name()=="CO2")
         {
         D_V[isp]  =  26.9;
         moleFrac[isp][celli]  = moleFrac_CO2[celli];
         }
         else if (Y[isp].name()=="CH4")
         {
         D_V[isp]  =  25;
         moleFrac[isp][celli]  = moleFrac_CH4[celli];
         }
         else if (Y[isp].name()=="O2")
         {
         D_V[isp]  =  16.3;
         moleFrac[isp][celli]  = moleFrac_O2[celli];
         }
         else if (Y[isp].name()=="N2")
         {
         D_V[isp]  =  18.5;
         moleFrac[isp][celli]  = moleFrac_N2[celli];
         }

     }
   }

    //calculation the sum of (Xj/Dij);----------------------------  
    forAll(T,celli)
    {
        for (label isp = 0; isp< sizeY; isp++)
        {

          sumD[isp][celli] =0.0;
          for (label nsp = 0; nsp< sizeY; nsp++)
          {
              //if(nsp != isp && composition.active(isp))
              if(nsp != isp)
              {

            mw_nsp[isp][nsp] =scalar(0.002)/ (scalar(1.0)/spMixture.W(isp)+scalar(1.0)/spMixture.W(nsp));
            scalar onethird (0.3333333333); 
  
            scalar meanvalue = Foam::pow(D_V[isp],onethird) + Foam::pow(D_V[nsp],onethird);
            scalar meanV     = Foam::pow(mw_nsp[isp][nsp], 0.5)* (meanvalue * meanvalue);

            scalar rpore (0.5e-6);  //pore radius, unit m;
            Dij_Knu[isp][celli] = scalar(4.0/3.0)*rpore*Foam::pow(8.0*R_CONSTANT*T[celli]/(pi*spMixture.W(isp)*0.001), 0.5);
            Dij[isp][nsp][celli] = scalar(0.00101)*Foam::pow(T[celli], 1.75)/(p[celli]*meanV);
            sumD[isp][celli]=sumD[isp][celli] + moleFrac[nsp][celli]/Dij[isp][nsp][celli];
          //Info<<"Dij_Knu "<<Dij_Knu[isp][celli]<<", Dij  "<<Dij[isp][nsp][celli]<<endl;
              }
          }

           if (sumD[isp][celli]>0.0 && Dij_eff[isp][celli]>0.0 && Dij_Knu[isp][celli]>0.0)
           { 
             Dij_eff[isp][celli]=(scalar(1.0)-moleFrac[isp][celli])/sumD[isp][celli];
             scalar D_M = scalar (1.0)/(scalar(1.0)/Dij_eff[isp][celli]+scalar (1.0)/Dij_Knu[isp][celli]);
             //Info<<"D_M="<<D_M<<",Dij_eff="<<Dij_eff[isp][celli]<<",Dij_Knu="<<Dij_Knu[isp][celli]<<endl;

                 if (Y[isp].name()=="H2")
                 {
                   D_eff_H2 [celli]  =  D_M;//V_pore / tau_pore * D_M;
                   D_eff_H2 [celli]  =  V_pore / tau_pore * D_M;
                 }
                 if (Y[isp].name()=="H2O")
                 {
                   D_eff_H2O [celli] =  D_M;//V_pore / tau_pore * D_M;
                   D_eff_H2O [celli] =  V_pore / tau_pore * D_M;
                 }
                 if (Y[isp].name()=="CO")
                 {
                   D_eff_CO [celli]  =  D_M;//V_pore / tau_pore * D_M;
                   D_eff_CO [celli]  =  V_pore / tau_pore * D_M;
                 }
                 if (Y[isp].name()=="CO2")
                 {
                   D_eff_CO2 [celli] =  D_M;//V_pore / tau_pore * D_M;
                   D_eff_CO2 [celli] =  V_pore / tau_pore * D_M;
                 }
                 if (Y[isp].name()=="O2")
                 {
                   D_eff_O2 [celli]  =  D_M;//V_pore / tau_pore * D_M;
                   D_eff_O2 [celli]  =  V_pore / tau_pore * D_M;
                 }
                // Info<<"GDL, CL down, isp= "<<isp<<", celli "<<celli<<",ncells= "<<ncells<<endl;
             }
         }  //isp = 0~nsp
   }
}   // big loop for fluid Regions


