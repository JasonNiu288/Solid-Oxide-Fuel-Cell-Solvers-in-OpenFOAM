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


forAll(fluidRegions[i].cellZones(), zoneI)
{

    const cellZone& cz = fluidRegions[i].cellZones()[zoneI];
    const labelList& cells = cz;

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

      // diffusion volume;
      forAll(cells,iCells)
      {
         const label celli  = cells[iCells];
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

//-------------------------------------------------------------------
//#2 loop, diffusion coefficient calculation;


if (cz.name() == "anodeFC" || cz.name() == "cathodeFC")
{
      Info<<"anode or cathode FC: "<<cz.name()<<endl;

    forAll(cells,iCells)
    {
        const label celli  = cells[iCells];

        for (label isp = 0; isp< sizeY; isp++)
        {

          sumD[isp][celli] = 0.0; 
          for (label nsp = 0; nsp< sizeY; nsp++)
          {
              if(nsp != isp)
              {

            mw_nsp[isp][nsp] = scalar(1.0)/(0.001*spMixture.W(isp))+scalar(1.0)/(0.001*spMixture.W(nsp));  
            scalar onethird (0.3333333333);   
            scalar DV_mean  = Foam::pow(D_V[isp],onethird) + Foam::pow(D_V[nsp],onethird);
            scalar wei_DV   = Foam::pow(mw_nsp[isp][nsp], 0.5)/ (DV_mean * DV_mean);

            scalar rpore (0.5e-6);  //pore radius, unit m;
            Dij_Knu[isp][celli]  = scalar(4.0/3.0)*rpore*Foam::pow(8.0*R_CONSTANT*T[celli]/(pi*spMixture.W(isp)*0.001), 0.5);
            Dij[isp][nsp][celli] = scalar(0.00101)*Foam::pow(T[celli], 1.75)*wei_DV/(p[celli]);
            sumD[isp][celli]=sumD[isp][celli] + moleFrac[nsp][celli]/Dij[isp][nsp][celli];
            /*if(Y[isp].name() =="H2")
            {
                Info<<"mw_nsp[0][1]="<<mw_nsp[0][1]<<",DV_mean "<<DV_mean<<",meanV="<<wei_DV<<endl;
                Info<<"D_V="<<D_V[isp]<<", "<<D_V[nsp]<<",pow="<<Foam::pow(D_V[isp],onethird)<<", "<<Foam::pow(D_V[nsp],onethird)<<endl;
                Info<<"Dij_Knu "<<Dij_Knu[isp][celli]<<endl;
            }*/
            //Info<<"Dij_Knu "<<Dij_Knu[isp][celli]<<", Dij  "<<Dij[isp][nsp][celli]<<",sumD"<<sumD[isp][celli]<<",moleFrac "<<moleFrac[isp][celli]<<"isp "<<Y[isp].name()<<endl;
              }
          }

          if (sumD[isp][celli]>0.0)
          {
               Dij_eff[isp][celli]=(scalar(1.0)-moleFrac[isp][celli])/sumD[isp][celli];
               //Info<<"sumD "<<sumD[isp][celli]<<", Dij_eff  "<<Dij_eff[isp][celli]<<endl;
               if (Y[isp].name()=="H2")
               {
                 D_eff_H2 [celli]  = Dij_eff[isp][celli]; // min(1e-4, Dij_eff[isp][celli]);
               }
              if (Y[isp].name()=="H2O")
               {
                 D_eff_H2O [celli] = Dij_eff[isp][celli]; // min(1e-4, Dij_eff[isp][celli]);
               }
               if (Y[isp].name()=="CO")
               {
                 D_eff_CO [celli]  = Dij_eff[isp][celli]; // min(1e-4, Dij_eff[isp][celli]);
               }
               if (Y[isp].name()=="CO2")
               {
                 D_eff_CO2 [celli] = Dij_eff[isp][celli]; // min(1e-4, Dij_eff[isp][celli]);
               }
               if (Y[isp].name()=="O2")
               {
                 D_eff_O2 [celli]  = Dij_eff[isp][celli]; // min(1e-4, Dij_eff[isp][celli]);
               }
               if (Y[isp].name()=="CH4")
               {
                 D_eff_CH4 [celli]  = Dij_eff[isp][celli]; // min(1e-4, Dij_eff[isp][celli]);
               }
          }
      }
    }
}   //# FC loop;

if (cz.name() == "anodeGDL" || cz.name() == "anodeCL" ||cz.name() == "cathodeGDL"|| cz.name() == "anodeCL")
{

    forAll(cells,iCells)
    {
        const label celli = cells[iCells];

        for (label isp = 0; isp< sizeY; isp++)
        {

          sumD[isp][celli] =0.0;
          for (label nsp = 0; nsp< sizeY; nsp++)
          {
              if(nsp != isp)
              {

            mw_nsp[isp][nsp] = scalar(1.0)/(0.001*spMixture.W(isp))+scalar(1.0)/(0.001*spMixture.W(nsp)); 
            scalar onethird (0.3333333333);   
            scalar meanvalue = Foam::pow(D_V[isp],onethird) + Foam::pow(D_V[nsp],onethird);
            scalar meanV = Foam::pow(mw_nsp[isp][nsp], 0.5)/ (meanvalue * meanvalue);

            scalar rpore (0.5e-6);  //pore radius, unit m;
            Dij_Knu[isp][celli] = scalar(4.0/3.0)*rpore*Foam::pow(8.0*R_CONSTANT*T[celli]/(pi*spMixture.W(isp)*0.001), 0.5);
            Dij[isp][nsp][celli] = scalar(0.00101)*Foam::pow(T[celli], 1.75)*meanV/(p[celli]);
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
                   D_eff_H2 [celli]  =  porosity[celli] / tortuosity * D_M;
                 }
               if (Y[isp].name()=="H2O")
                 {
                   D_eff_H2O [celli] =  porosity[celli] / tortuosity * D_M;
                 }
                 if (Y[isp].name()=="CO")
                 {
                   D_eff_CO [celli]  =  porosity[celli] / tortuosity * D_M;
                 }
                 if (Y[isp].name()=="CO2")
                 {
                   D_eff_CO2 [celli] =  porosity[celli] / tortuosity * D_M;
                 }
                 if (Y[isp].name()=="O2")
                 {
                   D_eff_O2 [celli]  =  porosity[celli] / tortuosity * D_M;
                 }
                // Info<<"GDL, CL down, isp= "<<isp<<", celli "<<celli<<",ncells= "<<ncells<<endl;
             }
           }  //isp = 0~nsp
        } // for All cells
  }   //#2 for GDL, CL
}   // big loop for fluid Regions


