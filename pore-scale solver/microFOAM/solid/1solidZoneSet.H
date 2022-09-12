scalar F (96487);          //Faraday's constant
scalar R_CONSTANT (8.314);  //universal gas constant

scalar cp_solid   = 470; 
scalar rho_solid  = 5160; 




forAll(solidRegions[i].cellZones(), zoneI)
{
     const cellZone& cz = solidRegions[i].cellZones()[zoneI];
     const labelList& cells = cz;
     if (solidRegions[i].name() == "membrane")
    {

        forAll(cells,iCells)
        {
            const label celli = cells[iCells];
             //effective conductivity
              scalar T_temp = T[celli];

              k_eff_ion[celli] = 33.4e3*Foam::exp(-10300/T_temp);
              D[celli] = k_mem.value();
         }
      }


     if (solidRegions[i].name() == "anodeBP")
    {

        forAll(cells,iCells)
        {
            const label celli = cells[iCells];
              D[celli] = k_BP_a.value();
         }
      }

     if (solidRegions[i].name() == "cathodeBP")
    {

        forAll(cells,iCells)
        {
            const label celli = cells[iCells];
              D[celli] = k_BP_c.value();
         }
      }
}







  if (runTime.outputTime())
  {
    k_eff_ele.write();
    k_eff_ion.write();
  }
