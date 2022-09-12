scalar F (96487);          //Faraday's constant
scalar R_CONSTANT (8.314);  //universal gas constant




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

              k_eff_ion[celli]=33.4e3*Foam::exp(-10300/T_temp);
         }
      }
}







  if (runTime.outputTime())
  {
    k_eff_ele.write();
    k_eff_ion.write();
  }
