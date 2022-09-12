/*---------------------------------------------------------------------------*\
  calculate the mole fraction of species, which is used for the calculation of partial pressure unit: mol/mol;
\*---------------------------------------------------------------------------*/
Info<<"Y.size in 2moleFraction.H= "<<Y.size()<<endl;

const label sizeY = Y.size();
const basicSpecieMixture& spMixture=dynamic_cast<const basicSpecieMixture&>(composition);

MW_mix  = 0.0;

for (int isp = 0; isp< sizeY; isp++)
{
  MW_mix = MW_mix + Y[isp]/spMixture.W(isp);

}

MW_mix=1/MW_mix;


//species mole fraction
  for (int isp = 0; isp< sizeY; isp++)
  {
    if (Y[isp].name()=="H2")
       {
       moleFrac_H2   = Y[isp] *MW_mix/spMixture.W(isp);
       }
    else if (Y[isp].name()=="H2O")
       {
       moleFrac_H2O   = Y[isp] *MW_mix/spMixture.W(isp);
       }
    else if (Y[isp].name()=="CO")
       {
       moleFrac_CO   = Y[isp] *MW_mix/spMixture.W(isp);
       }
    else if (Y[isp].name()=="CO2")
       {
       moleFrac_CO2   = Y[isp] *MW_mix/spMixture.W(isp);
       }
    else if (Y[isp].name()=="CH4")
       {
       moleFrac_CH4   = Y[isp] *MW_mix/spMixture.W(isp);
       }
    else if (Y[isp].name()=="O2")
     {
       moleFrac_O2   = Y[isp] *MW_mix/spMixture.W(isp);
     }
    else if (Y[isp].name()=="N2")
     {
       moleFrac_N2   = Y[isp] *MW_mix/spMixture.W(isp);
     }
  }




