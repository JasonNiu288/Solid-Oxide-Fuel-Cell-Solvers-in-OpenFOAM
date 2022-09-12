scalar F (96487);          //Faraday's constant
scalar R_CONSTANT (8.314);  //universal gas constant
scalar alpha_a (0.5);     //anode transfer coefficient
scalar alpha_c (0.5);     //cathode transfer coefficient

scalar Ri_a (0); // reaction rate in the anode CL
scalar Ri_c (0); // reaction rate in the cathode CL
scalar A_act = A_ACT.value(); //cell active area
scalar term (0);
scalar pi (3.14159);

scalar Pref (101325.0);     // reference pressure;
scalar p_in=P_IN.value(); // inlet pressure;
scalar T_in=T_IN.value();

// mole fraction for inlet species
scalar mole_Fraction_H2_inlet  = MOLE_FRACTION_H2_INLET.value();   
scalar mole_Fraction_CO_inlet  = MOLE_FRACTION_CO_INLET.value();  
scalar mole_Fraction_CH4_inlet = MOLE_FRACTION_CH4_INLET.value(); 
scalar mole_Fraction_H2O_inlet = MOLE_FRACTION_H2O_INLET.value(); 

scalar mole_Fraction_O2_inlet  = MOLE_FRACTION_O2_INLET.value(); 

//volume fraction
scalar V_Ni    (0.253);
scalar V_YSZ   (0.251);
scalar V_pore  (0.496);

scalar tau_Ni  (6.91);
scalar tau_YSZ (8.85);
scalar tau_pore(1.74);


// chemical model
scalar z_temp (1.0);


scalar t = runTime.value();  //time index of the case

 if(fluidRegions[i].name() == "pore")  
{
   scalarField Ri_a_volume = fluidRegions[i].V() * J_a.internalField();

   Ri_a = gSum(Ri_a_volume);

   Info<<"Volume-averaged Reaction rate in the anode CL is "<<Ri_a<<endl;
   Info<<"anode current density is "<<Ri_a / A_act/10000.0<< " A/cm2"<<endl;

//===============================================inlet settings End====================================



        // copy boundary values to cell for Fai_ele_copy and Fai_ion_copy;
        label patchID_pore_to_Ni = fluidRegions[i].boundaryMesh().findPatchID("pore_to_Ni");
        forAll(fluidRegions[i].boundaryMesh()[patchID_pore_to_Ni],facei)
        {
            Fai_ele_copy[fluidRegions[i].boundary()[patchID_pore_to_Ni].faceCells()[facei]] = Fai_ele_copy.boundaryField()[patchID_pore_to_Ni][facei];

            //Info<<"Fai_ele_copy in pore boundaryField "<<Fai_ele_copy.boundaryField()[patchID_pore_to_Ni][facei]<<endl;
        }
        //Info<< "max Fai_ele_copy in pore:" << max(Fai_ele_copy) <<"   ********************************"<< endl;
        patchID_pore_to_Ni = fluidRegions[i].boundaryMesh().findPatchID("pore_to_YSZ");
        forAll(fluidRegions[i].boundaryMesh()[patchID_pore_to_Ni],facei)
        {
            Fai_ion_copy[fluidRegions[i].boundary()[patchID_pore_to_Ni].faceCells()[facei]] = Fai_ion_copy.boundaryField()[patchID_pore_to_Ni][facei];
        }

           forAll(Fai_ele, celli)
          {
              //J_a[celli]     = 4e8;
              JtoNi[celli]   = J_a[celli];

              JtoYSZ[celli]  = J_a[celli];

              Fai_ele[celli] = Fai_ele_copy[celli];
              Fai_ion[celli] = Fai_ion_copy[celli];
              S_m_H2[celli]  = -J_a[celli] / (2 * F) * 0.002; 
              S_m_H2O[celli] =  J_a[celli] / (2 * F) * 0.018;

          }
           Fai_ele_copy.correctBoundaryConditions();
           JtoNi.correctBoundaryConditions();
           J_a.correctBoundaryConditions();

          patchID_pore_to_Ni = fluidRegions[i].boundaryMesh().findPatchID("pore_to_Ni");
/*
          forAll(JtoNi.boundaryFieldRef()[patchID_pore_to_Ni], facei)
          {
            JtoNi.boundaryFieldRef()[patchID_pore_to_Ni][facei] = 18;
          }
*/

         //code test by Niu
         /* forAll(fluidRegions[i].boundaryMesh()[patchID_pore_to_Ni],facei)
          {
              if(facei ==20)
             {
                     const label& bCellID = fluidRegions[i].boundaryMesh()[patchID_pore_to_Ni].faceCells()[facei];
                      //Info<<"bCellID="<<bCellID<<endl;
                    
                   J_a [bCellID] =108;

             }

          }*/

 

         // copy the volScalar to the boundary by Niu
          forAll(fluidRegions[i].boundaryMesh()[patchID_pore_to_Ni],facei)
          {
              const label& bCellID = fluidRegions[i].boundaryMesh()[patchID_pore_to_Ni].faceCells()[facei];
                          
              JtoNi.boundaryFieldRef()[patchID_pore_to_Ni][facei]   = J_a [bCellID];
              Fai_ele.boundaryFieldRef()[patchID_pore_to_Ni][facei] = Fai_ele_copy [bCellID];
          }	

          patchID_pore_to_Ni = fluidRegions[i].boundaryMesh().findPatchID("pore_to_YSZ");
          forAll(fluidRegions[i].boundaryMesh()[patchID_pore_to_Ni],facei)
          {
              const label& bCellID = fluidRegions[i].boundaryMesh()[patchID_pore_to_Ni].faceCells()[facei];
                    
                           // Info<<"bCellID="<<bCellID<<endl;        
              JtoYSZ.boundaryFieldRef()[patchID_pore_to_Ni][facei]  = J_a [bCellID];
              Fai_ion.boundaryFieldRef()[patchID_pore_to_Ni][facei] = Fai_ion_copy [bCellID];
          }

           Fai_ele_copy.correctBoundaryConditions();
           JtoNi.correctBoundaryConditions();
           J_a.correctBoundaryConditions();								 
            
      Info<<"pore done !"<<endl;
}


// =============================================================================
// Ni region.  region 1!!!!!!! 


 if(fluidRegions[i].name() == "Ni")  // 
{
        label patchID_pore_to_Ni = fluidRegions[i].boundaryMesh().findPatchID("Ni_to_pore");
        forAll(fluidRegions[i].boundaryMesh()[patchID_pore_to_Ni],facei)
        {
            JtoNi[fluidRegions[i].boundary()[patchID_pore_to_Ni].faceCells()[facei]] = JtoNi.boundaryField()[patchID_pore_to_Ni][facei];
        }

        forAll(Fai_ele, celli)
        {

            //Fai_ele[celli]      = 2;
            Fai_ele_copy[celli] = Fai_ele[celli]; 
            J_a[celli]          = JtoNi[celli];

            S_ele[celli]        =  J_a[celli];
            scalar T_temp       = T[celli];
                     term       = 3.27e6-1065.3*T_temp;
            k_eff_ele[celli]    = term * V_Ni /tau_Ni;
								 
        }
         Fai_ele_copy.correctBoundaryConditions();
         J_a.correctBoundaryConditions();


        // copy the volScalar to the boundary by Niu
        patchID_pore_to_Ni = fluidRegions[i].boundaryMesh().findPatchID("Ni_to_pore");
        forAll(fluidRegions[i].boundaryMesh()[patchID_pore_to_Ni],facei)
        {
            const label& bCellID = fluidRegions[i].boundaryMesh()[patchID_pore_to_Ni].faceCells()[facei]; 
       
            Fai_ele_copy.boundaryFieldRef()[patchID_pore_to_Ni][facei] = Fai_ele [bCellID];
                     J_a.boundaryFieldRef()[patchID_pore_to_Ni][facei] = JtoNi [bCellID];

         //Info<<"Fai_ele_copy.boundaryFieldRef() = "<<Fai_ele_copy.boundaryFieldRef()[patchID_pore_to_Ni][facei]<<endl;
        }
         Fai_ele_copy.correctBoundaryConditions();
         J_a.correctBoundaryConditions();
         JtoNi.correctBoundaryConditions();


      Info<<"Ni done !"<<endl;

}

// =============================================================================
// YSZ region, region 2!!!!!!!!!!!!!!!!
 if(fluidRegions[i].name() == "YSZ")  //
{

        label patchID_pore_to_Ni = fluidRegions[i].boundaryMesh().findPatchID("YSZ_to_pore");
        forAll(fluidRegions[i].boundaryMesh()[patchID_pore_to_Ni],facei)
        {
            JtoYSZ[fluidRegions[i].boundary()[patchID_pore_to_Ni].faceCells()[facei]] = JtoYSZ.boundaryField()[patchID_pore_to_Ni][facei];
        }

        forAll(Fai_ion, celli)
        {
            //Fai_ion[celli]      =  0.5; 
            Fai_ion_copy[celli] =  Fai_ion[celli]; 
            J_a[celli]          =  JtoYSZ[celli];

            S_ion[celli]        =  J_a[celli];
            scalar T_temp       =  T[celli];
                        term    =  3.4e4*Foam::exp(-10350.0/T_temp);
            k_eff_ion[celli]    =  term * V_YSZ/tau_YSZ;
								 
        }

        // copy the volScalar to the boundary by Niu
        patchID_pore_to_Ni = fluidRegions[i].boundaryMesh().findPatchID("YSZ_to_pore");
        forAll(fluidRegions[i].boundaryMesh()[patchID_pore_to_Ni],facei)
        {
            const label& bCellID = fluidRegions[i].boundaryMesh()[patchID_pore_to_Ni].faceCells()[facei]; 
       
            Fai_ion_copy.boundaryFieldRef()[patchID_pore_to_Ni][facei] = Fai_ion [bCellID];
                     J_a.boundaryFieldRef()[patchID_pore_to_Ni][facei] = JtoYSZ  [bCellID];
        }

         Fai_ion_copy.correctBoundaryConditions();
         J_a.correctBoundaryConditions();
         JtoYSZ.correctBoundaryConditions();

      Info<<"YSZ done !"<<endl;




}







