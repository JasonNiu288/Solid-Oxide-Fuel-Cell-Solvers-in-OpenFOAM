//BVEqn
PtrList<volScalarField> yita_actFluid(fluidRegions.size());    //over potential in the anode/cathode CLs = Fai_ele - Fai_ion
PtrList<volScalarField> J_aFluid(fluidRegions.size());    //electrochemical reaction rate in the anode (A/m3)
PtrList<volScalarField> J_cFluid(fluidRegions.size());    //electrochemical reaction rate in the cathode (A/m3)

PtrList<volScalarField> TFluid(fluidRegions.size());    //temperature field readed from the folder

//mole fraction for inlet species, different from Niu's code, where mole concentration was used
PtrList<dimensionedScalar> MOLE_FRACTION_H2_INLETFluid(fluidRegions.size()); 

PtrList<dimensionedScalar> MOLE_FRACTION_CO_INLETFluid(fluidRegions.size()); 
PtrList<dimensionedScalar> MOLE_FRACTION_CH4_INLETFluid(fluidRegions.size()); //mole contentration CH4 at inlet
PtrList<dimensionedScalar> MOLE_FRACTION_H2O_INLETFluid(fluidRegions.size()); //anode side

PtrList<dimensionedScalar> MOLE_FRACTION_O2_INLETFluid(fluidRegions.size()); 

PtrList<dimensionedScalar> P_INFluid(fluidRegions.size()); //inlet pressure;
PtrList<dimensionedScalar> T_INFluid(fluidRegions.size()); //inlet temperature;
PtrList<dimensionedScalar> A_ACTFluid(fluidRegions.size());

//Fai_ele vs Fai_ion Eqn
PtrList<volScalarField> Fai_ionFluid(fluidRegions.size());   //ionin potential
PtrList<volScalarField> Fai_eleFluid(fluidRegions.size()); //electronic potential
PtrList<volScalarField> k_eff_ionFluid(fluidRegions.size());    //ion conductivity
PtrList<volScalarField> k_eff_eleFluid(fluidRegions.size());    //electron conductivity

PtrList<dimensionedScalar> tau_potentialFluid(fluidRegions.size());

PtrList<volScalarField> S_ionFluid(fluidRegions.size());    //source term of Fai_ion
PtrList<volScalarField> S_eleFluid(fluidRegions.size());    //source term of Fai_ele

PtrList<volScalarField> porosityFluid(fluidRegions.size()); //porosity of entire domain
PtrList<dimensionedScalar> I_REFFluid(fluidRegions.size());
PtrList<dimensionedScalar> FC_CROSS_SECTIONFluid(fluidRegions.size());

PtrList<dimensionedScalar> lamda_AIRFluid(fluidRegions.size());//air ratio;
PtrList<dimensionedScalar> U_FFluid(fluidRegions.size());  //fuel utilization;

//isolate the Fai_ele and Fai_ion in the FC
/*PtrList<volScalarField> alpha_Fai_eleFluid(fluidRegions.size());
PtrList<volScalarField> grad_alpha_Fai_eleFluid(fluidRegions.size()); 
PtrList<volScalarField> alpha_Fai_ionFluid(fluidRegions.size());
PtrList<volScalarField> grad_alpha_Fai_ionFluid(fluidRegions.size()); */

//chemical model
PtrList<volScalarField> KpsFluid(fluidRegions.size());
PtrList<volScalarField> KsfFluid(fluidRegions.size()); 
PtrList<volScalarField> R_WGSRFluid(fluidRegions.size());
PtrList<volScalarField> KrfFluid(fluidRegions.size());
PtrList<volScalarField> KprFluid(fluidRegions.size()); 
PtrList<volScalarField> R_MSRFluid(fluidRegions.size());   //reaction rate, mol/(m3*s)
PtrList<volScalarField> heatWGSRFluid(fluidRegions.size());//reaction heat
PtrList<volScalarField> heatMSRFluid(fluidRegions.size()); //reaction heat, J/mol

// species source term
PtrList<volScalarField> S_m_H2Fluid(fluidRegions.size());    //source term of Y[H2]
PtrList<volScalarField> S_m_O2Fluid(fluidRegions.size());    //source term of Y[O2]
PtrList<volScalarField> S_m_H2OFluid(fluidRegions.size());   //source term of Y[H2O]
PtrList<volScalarField> S_m_COFluid(fluidRegions.size());    //source term of Y[CO]
PtrList<volScalarField> S_m_CO2Fluid(fluidRegions.size());   //source term of Y[CO2]
PtrList<volScalarField> S_m_CH4Fluid(fluidRegions.size());
// diffusion coefficient
/*PtrList<volScalarField> D_H2Fluid(fluidRegions.size()); 
PtrList<volScalarField> D_O2Fluid(fluidRegions.size()); 
PtrList<volScalarField> D_H2OFluid(fluidRegions.size()); 
PtrList<volScalarField> D_COFluid(fluidRegions.size()); 
PtrList<volScalarField> D_CO2Fluid(fluidRegions.size()); 
PtrList<volScalarField> D_CH4Fluid(fluidRegions.size()); */
// effective diffusion coeficient
PtrList<volScalarField> D_eff_H2Fluid(fluidRegions.size()); 
PtrList<volScalarField> D_eff_O2Fluid(fluidRegions.size()); 
PtrList<volScalarField> D_eff_H2OFluid(fluidRegions.size()); 
PtrList<volScalarField> D_eff_COFluid(fluidRegions.size()); 
PtrList<volScalarField> D_eff_CO2Fluid(fluidRegions.size()); 
PtrList<volScalarField> D_eff_CH4Fluid(fluidRegions.size()); 

//species mole fraction
PtrList<volScalarField> moleFrac_H2OFluid(fluidRegions.size());
PtrList<volScalarField> moleFrac_H2Fluid(fluidRegions.size()); 
PtrList<volScalarField> moleFrac_N2Fluid(fluidRegions.size()); 
PtrList<volScalarField> moleFrac_O2Fluid(fluidRegions.size()); 
PtrList<volScalarField> moleFrac_COFluid(fluidRegions.size()); 
PtrList<volScalarField> moleFrac_CO2Fluid(fluidRegions.size()); 
PtrList<volScalarField> moleFrac_CH4Fluid(fluidRegions.size());

PtrList<volScalarField> MW_mixFluid(fluidRegions.size()); //mixture molecular weight; unit kg/mol

PtrList<volScalarField> S_m_tFluid(fluidRegions.size());    //total mass source term for pEqn;

//source term for temperature;
PtrList<volScalarField> S_heatFluid(fluidRegions.size());
PtrList<volScalarField> S_revFluid(fluidRegions.size());    //heat source due to reversible loss
PtrList<volScalarField> S_actFluid(fluidRegions.size());    //heat source due to activation loss
PtrList<volScalarField> S_ohmFluid(fluidRegions.size());    //heat source due to ohmic loss   
PtrList<volVectorField> grad_Fai_ionFluid(fluidRegions.size());
PtrList<volVectorField> grad_Fai_eleFluid(fluidRegions.size());

//intrinsic permeability
PtrList<volScalarField> K_permeaFluid(fluidRegions.size());

PtrList<dimensionedScalar> K_p_GDLFluid(fluidRegions.size());
PtrList<dimensionedScalar> K_p_CLFluid(fluidRegions.size());

PtrList<volScalarField> ACFluid(fluidRegions.size());   //set the porous media by add fvm::Sp(AC,U) in the UEqn.H

PtrList<volScalarField> nuEffFluid(fluidRegions.size());    //store kinetic viscosity of mixture

PtrList<volScalarField> thermo_cpFluid(fluidRegions.size());    //middle variable for heat capacity of fluid 
//For heat transfer in porous media
PtrList<volScalarField> rho_sFluid(fluidRegions.size());    //density of solid (electrode)
PtrList<volScalarField> rho_fFluid(fluidRegions.size());    //density of mixture (reactant)
PtrList<volScalarField> cp_sFluid(fluidRegions.size());     //heat capacity of solid (electrode)
PtrList<volScalarField> cp_fFluid(fluidRegions.size());     //heat capacity of mixture (reactant)
PtrList<volScalarField> k_sFluid(fluidRegions.size());     //thermal conductivity of solid (electrode)
PtrList<volScalarField> k_fFluid(fluidRegions.size());     //thermal conductivity of fluid (reactant)
PtrList<volScalarField> alphaEffFluid(fluidRegions.size());    //store kinetic viscosity of mixture

PtrList<dimensionedScalar> rho_GDLFluid(fluidRegions.size()); //density of GDL
PtrList<dimensionedScalar> cp_GDLFluid(fluidRegions.size()); //heat capacity of GDL
PtrList<dimensionedScalar> ks_GDLFluid(fluidRegions.size()); //density of GDL

PtrList<dimensionedScalar> rho_CLFluid(fluidRegions.size()); //density of GDL
PtrList<dimensionedScalar> cp_CLFluid(fluidRegions.size()); //heat capacity of GDL
PtrList<dimensionedScalar> ks_CLFluid(fluidRegions.size()); //density of GDL

PtrList<surfaceScalarField> phi_sFluid(fluidRegions.size());  //phi for s_FC
PtrList<volScalarField> DFluid(fluidRegions.size());

PtrList<dimensionedScalar> V_outFluid(fluidRegions.size());



//PtrList<volScalarField> A_ID_OUTFluid(fluidRegions.size());

forAll(fluidRegions, i)
{

/*Info<< " Adding to A_ID_OUTFluid\n" << endl;
   A_ID_OUTFluid.set
   (
        i,
        new volScalarField
       (
            IOobject
           (
             "A_ID_OUT",
             runTime.timeName(),
             fluidRegions[i],
             IOobject::READ_IF_PRESENT,
             IOobject::AUTO_WRITE
            ),
            fluidRegions[i],
            dimensionedScalar("A_ID_OUT", dimless, 0),
            zeroGradientFvPatchScalarField::typeName
        )
    );*/


// V1
Info<< " Adding to yita_actFluid\n" << endl;
   yita_actFluid.set
   (
        i,
        new volScalarField
       (
            IOobject
           (
             "yita_act",
             runTime.timeName(),
             fluidRegions[i],
             IOobject::READ_IF_PRESENT,
             IOobject::AUTO_WRITE
            ),
            fluidRegions[i],
            dimensionedScalar("yita_act", dimless, 0),
            zeroGradientFvPatchScalarField::typeName
        )
    );

//V 2
Info<< " Adding to J_aFluid\n" << endl;
   J_aFluid.set
   (
        i,
        new volScalarField
       (
            IOobject
           (
             "J_a",
             runTime.timeName(),
             fluidRegions[i],
             IOobject::READ_IF_PRESENT,
             IOobject::AUTO_WRITE
            ),
            fluidRegions[i],
            dimensionedScalar("J_a", dimless, 0),
            zeroGradientFvPatchScalarField::typeName
        )
    );

//V 3
Info<< " Adding to J_cFluid\n" << endl;
   J_cFluid.set
   (
        i,
        new volScalarField
       (
            IOobject
           (
             "J_c",
             runTime.timeName(),
             fluidRegions[i],
             IOobject::READ_IF_PRESENT,
             IOobject::AUTO_WRITE
            ),
            fluidRegions[i],
            dimensionedScalar("J_c", dimless, 0),
            zeroGradientFvPatchScalarField::typeName
        )
    );


//V 4
Info<< " Adding to TFluid\n" << endl;
   TFluid.set
   (
        i,
        new volScalarField
       (
            IOobject
           (
             "T",
             runTime.timeName(),
             fluidRegions[i],
             IOobject::MUST_READ,
             IOobject::AUTO_WRITE
            ),
            fluidRegions[i]
        )
    );



Info<< "    Adding transport properties to  fluid field\n" << endl;
Info<< "Reading transportProperties\n" << endl;

         IOdictionary sofcProperties
        (
             IOobject
           (
              "sofcProperties",
              runTime.constant(),
              fluidRegions[i],
              IOobject::MUST_READ_IF_MODIFIED,
              IOobject::NO_WRITE
           )
         );
// V 5
Info<< " Adding to Fai_ionFluid\n" << endl;
   Fai_ionFluid.set
   (
        i,
        new volScalarField
       (
            IOobject
           (
             "Fai_ion",
             runTime.timeName(),
             fluidRegions[i],
             IOobject::MUST_READ,
             IOobject::AUTO_WRITE
            ),
            fluidRegions[i]
        )
    );

//V 6
Info<< " Adding to Fai_eleFluid\n" << endl;
   Fai_eleFluid.set
   (
        i,
        new volScalarField
       (
            IOobject
           (
             "Fai_ele",
             runTime.timeName(),
             fluidRegions[i],
             IOobject::MUST_READ,
             IOobject::AUTO_WRITE
            ),
            fluidRegions[i]
        )
    );
// V 7
Info<< " Adding to effective ion conductivity\n" << endl;
   k_eff_ionFluid.set
   (
        i,
        new volScalarField
       (
            IOobject
           (
             "k_eff_ion",
             runTime.timeName(),
             fluidRegions[i],
             IOobject::READ_IF_PRESENT,
             IOobject::AUTO_WRITE
            ),
            fluidRegions[i],
            dimensionedScalar("k_eff_ion", dimless, 1),
            zeroGradientFvPatchScalarField::typeName
        )
    );

//V 8
Info<< " Adding to effective electron conductivity\n" << endl;
   k_eff_eleFluid.set
   (
        i,
        new volScalarField
       (
            IOobject
           (
             "k_eff_ele",
             runTime.timeName(),
             fluidRegions[i],
             IOobject::READ_IF_PRESENT,
             IOobject::AUTO_WRITE
            ),
            fluidRegions[i],
            dimensionedScalar("k_eff_ele", dimless, 5000),
            zeroGradientFvPatchScalarField::typeName
        )
    );
// V 9
Info<< " Adding to Source term of S_ion\n" << endl;
   S_ionFluid.set
   (
        i,
        new volScalarField
       (
            IOobject
           (
             "S_ion",
             runTime.timeName(),
             fluidRegions[i],
             IOobject::READ_IF_PRESENT,
             IOobject::AUTO_WRITE
            ),
            fluidRegions[i],
            dimensionedScalar("S_ion", dimless, 0),
            zeroGradientFvPatchScalarField::typeName
        )
    );

//V 10
Info<< " Adding to Source term of S_ele\n" << endl;
   S_eleFluid.set
   (
        i,
        new volScalarField
       (
            IOobject
           (
             "S_ele",
             runTime.timeName(),
             fluidRegions[i],
             IOobject::READ_IF_PRESENT,
             IOobject::AUTO_WRITE
            ),
            fluidRegions[i],
            dimensionedScalar("S_ele", dimless, 0),
            zeroGradientFvPatchScalarField::typeName
        )
    );
// V 11
Info<< " Adding to porosity\n" << endl;
   porosityFluid.set
   (
        i,
        new volScalarField
       (
            IOobject
           (
             "porosity",
             runTime.timeName(),
             fluidRegions[i],
             IOobject::READ_IF_PRESENT,
             IOobject::AUTO_WRITE
            ),
            fluidRegions[i],
            dimensionedScalar("porosity", dimless, 0),
            zeroGradientFvPatchScalarField::typeName
       )
    );
/*// V 12
Info<< " Adding to alpha_Fai_ele\n" << endl;
   alpha_Fai_eleFluid.set
   (
        i,
        new volScalarField
       (
            IOobject
           (
             "alpha_Fai_ele",
             runTime.timeName(),
             fluidRegions[i],
             IOobject::READ_IF_PRESENT,
             IOobject::AUTO_WRITE
            ),
            fluidRegions[i]//,
         //   dimensionedScalar("alpha_Fai_ele", dimless, 1),  //must to set this default value as 1, in this way, the boundary field is not zero and variable can diffuse
         //   zeroGradientFvPatchScalarField::typeName

        )
    );
// V 13
Info<< " Adding to grad_alpha_Fai_ele\n" << endl;
   grad_alpha_Fai_eleFluid.set
   (
        i,
        new volScalarField
       (
            IOobject
           (
             "grad_alpha_Fai_ele",
             runTime.timeName(),
             fluidRegions[i],
             IOobject::MUST_READ,
             IOobject::AUTO_WRITE
            ),
            fluidRegions[i]//,
          //  dimensionedScalar("grad_alpha_Fai_ele", dimless, 0),
           // zeroGradientFvPatchScalarField::typeName

        )
    );
// V 14
Info<< " Adding to alpha_Fai_ion\n" << endl;
   alpha_Fai_ionFluid.set
   (
        i,
        new volScalarField
       (
            IOobject
           (
             "alpha_Fai_ion",
             runTime.timeName(),
             fluidRegions[i],
             IOobject::READ_IF_PRESENT,
             IOobject::AUTO_WRITE
            ),
            fluidRegions[i]

        )
    );
// V 15
Info<< " Adding to grad_alpha_Fai_ion\n" << endl;
   grad_alpha_Fai_ionFluid.set
   (
        i,
        new volScalarField
       (
            IOobject
           (
             "grad_alpha_Fai_ion",
             runTime.timeName(),
             fluidRegions[i],
             IOobject::MUST_READ,
             IOobject::AUTO_WRITE
            ),
            fluidRegions[i]
        )
    );*/
// V 16-18
Info<< " Adding to WGSR\n" << endl;
   KsfFluid.set
   (
        i,
        new volScalarField
       (
            IOobject
           (
             "Ksf",
             runTime.timeName(),
             fluidRegions[i],
             IOobject::READ_IF_PRESENT,
             IOobject::AUTO_WRITE
            ),
            fluidRegions[i],
            dimensionedScalar("Ksf", dimless, 0),
            zeroGradientFvPatchScalarField::typeName
        )
    );
   KpsFluid.set
   (
        i,
        new volScalarField
       (
            IOobject
           (
             "Kps",
             runTime.timeName(),
             fluidRegions[i],
             IOobject::READ_IF_PRESENT,
             IOobject::AUTO_WRITE
            ),
            fluidRegions[i],
            dimensionedScalar("Kps", dimless, 0),
            zeroGradientFvPatchScalarField::typeName
        )
    );

   R_WGSRFluid.set
   (
        i,
        new volScalarField
       (
            IOobject
           (
             "R_WGSR",
             runTime.timeName(),
             fluidRegions[i],
             IOobject::READ_IF_PRESENT,
             IOobject::AUTO_WRITE
            ),
            fluidRegions[i],
            dimensionedScalar("R_WGSR", dimless, 0),
            zeroGradientFvPatchScalarField::typeName
        )
    );
// V 19-21
Info<< " Adding to MSR\n" << endl;
   KrfFluid.set
   (
        i,
        new volScalarField
       (
            IOobject
           (
             "Krf",
             runTime.timeName(),
             fluidRegions[i],
             IOobject::READ_IF_PRESENT,
             IOobject::AUTO_WRITE
            ),
            fluidRegions[i],
            dimensionedScalar("Krf", dimless, 0),
            zeroGradientFvPatchScalarField::typeName
        )
    );
   KprFluid.set
   (
        i,
        new volScalarField
       (
            IOobject
           (
             "Kpr",
             runTime.timeName(),
             fluidRegions[i],
             IOobject::READ_IF_PRESENT,
             IOobject::AUTO_WRITE
            ),
            fluidRegions[i],
            dimensionedScalar("Kpr", dimless, 0),
            zeroGradientFvPatchScalarField::typeName
        )
    );

   R_MSRFluid.set
   (
        i,
        new volScalarField
       (
            IOobject
           (
             "R_MSR",
             runTime.timeName(),
             fluidRegions[i],
             IOobject::READ_IF_PRESENT,
             IOobject::AUTO_WRITE
            ),
            fluidRegions[i],
            dimensionedScalar("R_MSR", dimless, 0),
            zeroGradientFvPatchScalarField::typeName
        )
    );
// V 22
Info<< " Adding to reaction heatWGSR\n" << endl;
   heatWGSRFluid.set
   (
        i,
        new volScalarField
       (
            IOobject
           (
             "heatWGSR",
             runTime.timeName(),
             fluidRegions[i],
             IOobject::READ_IF_PRESENT,
             IOobject::AUTO_WRITE
            ),
            fluidRegions[i],
            dimensionedScalar("heatWGSR", dimless, 0),
            zeroGradientFvPatchScalarField::typeName
        )
    );
// V 23
Info<< " Adding to reaction heatMSR\n" << endl;
   heatMSRFluid.set
   (
        i,
        new volScalarField
       (
            IOobject
           (
             "heatMSR",
             runTime.timeName(),
             fluidRegions[i],
             IOobject::READ_IF_PRESENT,
             IOobject::AUTO_WRITE
            ),
            fluidRegions[i],
            dimensionedScalar("heatMSR", dimless, 0),
            zeroGradientFvPatchScalarField::typeName
        )
    );

Info<< " Adding to S_m_H2\n" << endl;
   S_m_H2Fluid.set
   (
        i,
        new volScalarField
       (
            IOobject
           (
             "S_m_H2",
             runTime.timeName(),
             fluidRegions[i],
             IOobject::READ_IF_PRESENT,
             IOobject::AUTO_WRITE
            ),
            fluidRegions[i],
            dimensionedScalar("S_m_H2", dimless, 0),
            zeroGradientFvPatchScalarField::typeName
       )
    );
Info<< " Adding to S_m_O2\n" << endl;
   S_m_O2Fluid.set
   (
        i,
        new volScalarField
       (
            IOobject
           (
             "S_m_O2",
             runTime.timeName(),
             fluidRegions[i],
             IOobject::READ_IF_PRESENT,
             IOobject::AUTO_WRITE
            ),
            fluidRegions[i],
            dimensionedScalar("S_m_O2", dimless, 0),
            zeroGradientFvPatchScalarField::typeName
       )
    );
Info<< " Adding to S_m_H2O\n" << endl;
   S_m_H2OFluid.set
   (
        i,
        new volScalarField
       (
            IOobject
           (
             "S_m_H2O",
             runTime.timeName(),
             fluidRegions[i],
             IOobject::READ_IF_PRESENT,
             IOobject::AUTO_WRITE
            ),
            fluidRegions[i],
            dimensionedScalar("S_m_H2O", dimless, 0),
            zeroGradientFvPatchScalarField::typeName
       )
    );
Info<< " Adding to S_m_CO\n" << endl;
   S_m_COFluid.set
   (
        i,
        new volScalarField
       (
            IOobject
           (
             "S_m_CO",
             runTime.timeName(),
             fluidRegions[i],
             IOobject::READ_IF_PRESENT,
             IOobject::AUTO_WRITE
            ),
            fluidRegions[i],
            dimensionedScalar("S_m_CO", dimless, 0),
            zeroGradientFvPatchScalarField::typeName
       )
    );

Info<< " Adding to S_m_CO2\n" << endl;
   S_m_CO2Fluid.set
   (
        i,
        new volScalarField
       (
            IOobject
           (
             "S_m_CO2",
             runTime.timeName(),
             fluidRegions[i],
             IOobject::READ_IF_PRESENT,
             IOobject::AUTO_WRITE
            ),
            fluidRegions[i],
            dimensionedScalar("S_m_CO2", dimless, 0),
            zeroGradientFvPatchScalarField::typeName
       )
    );

Info<< " Adding to S_m_CH4\n" << endl;
   S_m_CH4Fluid.set
   (
        i,
        new volScalarField
       (
            IOobject
           (
             "S_m_CH4",
             runTime.timeName(),
             fluidRegions[i],
             IOobject::READ_IF_PRESENT,
             IOobject::AUTO_WRITE
            ),
            fluidRegions[i],
            dimensionedScalar("S_m_CH4", dimless, 0),
            zeroGradientFvPatchScalarField::typeName
       )
    );

/*Info<< " Adding to D_H2\n" << endl;
   D_H2Fluid.set
   (
        i,
        new volScalarField
       (
            IOobject
           (
             "D_H2",
             runTime.timeName(),
             fluidRegions[i],
             IOobject::READ_IF_PRESENT,
             IOobject::AUTO_WRITE
            ),
            fluidRegions[i],
            dimensionedScalar("D_H2", dimless, 1e-5),
            zeroGradientFvPatchScalarField::typeName
       )
    );

Info<< " Adding to D_O2\n" << endl;
   D_O2Fluid.set
   (
        i,
        new volScalarField
       (
            IOobject
           (
             "D_O2",
             runTime.timeName(),
             fluidRegions[i],
             IOobject::READ_IF_PRESENT,
             IOobject::AUTO_WRITE
            ),
            fluidRegions[i],
            dimensionedScalar("D_O2", dimless, 1e-5),
            zeroGradientFvPatchScalarField::typeName
       )
    );

Info<< " Adding to D_H2O\n" << endl;
   D_H2OFluid.set
   (
        i,
        new volScalarField
       (
            IOobject
           (
             "D_H2O",
             runTime.timeName(),
             fluidRegions[i],
             IOobject::READ_IF_PRESENT,
             IOobject::AUTO_WRITE
            ),
            fluidRegions[i],
            dimensionedScalar("D_H2O", dimless, 1e-5),
            zeroGradientFvPatchScalarField::typeName
       )
    );

Info<< " Adding to D_CO2\n" << endl;
   D_CO2Fluid.set
   (
        i,
        new volScalarField
       (
            IOobject
           (
             "D_CO2",
             runTime.timeName(),
             fluidRegions[i],
             IOobject::READ_IF_PRESENT,
             IOobject::AUTO_WRITE
            ),
            fluidRegions[i],
            dimensionedScalar("D_CO2", dimless, 1e-5),
            zeroGradientFvPatchScalarField::typeName
       )
    );

Info<< " Adding to D_CO\n" << endl;
   D_COFluid.set
   (
        i,
        new volScalarField
       (
            IOobject
           (
             "D_CO",
             runTime.timeName(),
             fluidRegions[i],
             IOobject::READ_IF_PRESENT,
             IOobject::AUTO_WRITE
            ),
            fluidRegions[i],
            dimensionedScalar("D_CO", dimless, 1e-5),
            zeroGradientFvPatchScalarField::typeName
       )
    );

Info<< " Adding to D_CH4\n" << endl;
   D_CH4Fluid.set
   (
        i,
        new volScalarField
       (
            IOobject
           (
             "D_CH4",
             runTime.timeName(),
             fluidRegions[i],
             IOobject::READ_IF_PRESENT,
             IOobject::AUTO_WRITE
            ),
            fluidRegions[i],
            dimensionedScalar("D_CH4", dimless, 1e-5),
            zeroGradientFvPatchScalarField::typeName
       )
    );*/

Info<< " Adding to D_eff_H2\n" << endl;
   D_eff_H2Fluid.set
   (
        i,
        new volScalarField
       (
            IOobject
           (
             "D_eff_H2",
             runTime.timeName(),
             fluidRegions[i],
             IOobject::READ_IF_PRESENT,
             IOobject::AUTO_WRITE
            ),
            fluidRegions[i],
            dimensionedScalar("D_eff_H2", dimless, 1e-5),
            zeroGradientFvPatchScalarField::typeName
       )
    );

//V 48
Info<< " Adding to D_eff_O2\n" << endl;
   D_eff_O2Fluid.set
   (
        i,
        new volScalarField
       (
            IOobject
           (
             "D_eff_O2",
             runTime.timeName(),
             fluidRegions[i],
             IOobject::READ_IF_PRESENT,
             IOobject::AUTO_WRITE
            ),
            fluidRegions[i],
            dimensionedScalar("D_eff_O2", dimless, 1e-5),
            zeroGradientFvPatchScalarField::typeName
       )
    );

Info<< " Adding to D_eff_H2O\n" << endl;
   D_eff_H2OFluid.set
   (
        i,
        new volScalarField
       (
            IOobject
           (
             "D_eff_H2O",
             runTime.timeName(),
             fluidRegions[i],
             IOobject::READ_IF_PRESENT,
             IOobject::AUTO_WRITE
            ),
            fluidRegions[i],
            dimensionedScalar("D_eff_H2O", dimless, 1e-5),
            zeroGradientFvPatchScalarField::typeName
       )
    );

//V 48
Info<< " Adding to D_eff_CO2\n" << endl;
   D_eff_CO2Fluid.set
   (
        i,
        new volScalarField
       (
            IOobject
           (
             "D_eff_CO2",
             runTime.timeName(),
             fluidRegions[i],
             IOobject::READ_IF_PRESENT,
             IOobject::AUTO_WRITE
            ),
            fluidRegions[i],
            dimensionedScalar("D_eff_CO2", dimless, 1e-5),
            zeroGradientFvPatchScalarField::typeName
       )
    );

Info<< " Adding to D_eff_CH4\n" << endl;
   D_eff_CH4Fluid.set
   (
        i,
        new volScalarField
       (
            IOobject
           (
             "D_eff_CH4",
             runTime.timeName(),
             fluidRegions[i],
             IOobject::READ_IF_PRESENT,
             IOobject::AUTO_WRITE
            ),
            fluidRegions[i],
            dimensionedScalar("D_eff_CH4", dimless, 1e-5),
            zeroGradientFvPatchScalarField::typeName
       )
    );

//V 48
Info<< " Adding to D_eff_CO\n" << endl;
   D_eff_COFluid.set
   (
        i,
        new volScalarField
       (
            IOobject
           (
             "D_eff_CO",
             runTime.timeName(),
             fluidRegions[i],
             IOobject::READ_IF_PRESENT,
             IOobject::AUTO_WRITE
            ),
            fluidRegions[i],
            dimensionedScalar("D_eff_CO", dimless, 1e-5),
            zeroGradientFvPatchScalarField::typeName
       )
    );

Info<< " Adding to moleFrac_H2OFluid\n" << endl;
   moleFrac_H2OFluid.set
   (
        i,
        new volScalarField
       (
            IOobject
           (
             "moleFrac_H2O",
             runTime.timeName(),
             fluidRegions[i],
             IOobject::READ_IF_PRESENT,
             IOobject::AUTO_WRITE
            ),
            fluidRegions[i],
            dimensionedScalar("moleFrac_H2O", dimless, 0),
            zeroGradientFvPatchScalarField::typeName
        )
    );
Info<< " Adding to moleFrac_H2Fluid\n" << endl;
   moleFrac_H2Fluid.set
   (
        i,
        new volScalarField
       (
            IOobject
           (
             "moleFrac_H2",
             runTime.timeName(),
             fluidRegions[i],
             IOobject::READ_IF_PRESENT,
             IOobject::AUTO_WRITE
            ),
            fluidRegions[i],
            dimensionedScalar("moleFrac_H2", dimless, 0),
            zeroGradientFvPatchScalarField::typeName
        )
    );

//V 7
Info<< " Adding to moleFrac_N2Fluid\n" << endl;
   moleFrac_N2Fluid.set
   (
        i,
        new volScalarField
       (
            IOobject
           (
             "moleFrac_N2",
             runTime.timeName(),
             fluidRegions[i],
             IOobject::READ_IF_PRESENT,
             IOobject::AUTO_WRITE
            ),
            fluidRegions[i],
            dimensionedScalar("moleFrac_N2", dimless, 0),
            zeroGradientFvPatchScalarField::typeName
        )
    );

//V 8
Info<< " Adding to moleFrac_O2Fluid\n" << endl;
   moleFrac_O2Fluid.set
   (
        i,
        new volScalarField
       (
            IOobject
           (
             "moleFrac_O2",
             runTime.timeName(),
             fluidRegions[i],
             IOobject::READ_IF_PRESENT,
             IOobject::AUTO_WRITE
            ),
            fluidRegions[i],
            dimensionedScalar("moleFrac_O2", dimless, 0),
            zeroGradientFvPatchScalarField::typeName
        )
    );

Info<< " Adding to moleFrac_COFluid\n" << endl;
   moleFrac_COFluid.set
   (
        i,
        new volScalarField
       (
            IOobject
           (
             "moleFrac_CO",
             runTime.timeName(),
             fluidRegions[i],
             IOobject::READ_IF_PRESENT,
             IOobject::AUTO_WRITE
            ),
            fluidRegions[i],
            dimensionedScalar("moleFrac_CO", dimless, 0),
            zeroGradientFvPatchScalarField::typeName
        )
    );

Info<< " Adding to moleFrac_CO2Fluid\n" << endl;
   moleFrac_CO2Fluid.set
   (
        i,
        new volScalarField
       (
            IOobject
           (
             "moleFrac_CO2",
             runTime.timeName(),
             fluidRegions[i],
             IOobject::READ_IF_PRESENT,
             IOobject::AUTO_WRITE
            ),
            fluidRegions[i],
            dimensionedScalar("moleFrac_CO2", dimless, 0),
            zeroGradientFvPatchScalarField::typeName
        )
    );
Info<< " Adding to moleFrac_CH4Fluid\n" << endl;
   moleFrac_CH4Fluid.set
   (
        i,
        new volScalarField
       (
            IOobject
           (
             "moleFrac_CH4",
             runTime.timeName(),
             fluidRegions[i],
             IOobject::READ_IF_PRESENT,
             IOobject::AUTO_WRITE
            ),
            fluidRegions[i],
            dimensionedScalar("moleFrac_CH4", dimless, 0),
            zeroGradientFvPatchScalarField::typeName
        )
    );

Info<< " Adding to mixture molecular weight Fluid\n" << endl;
   MW_mixFluid.set
   (
        i,
        new volScalarField
       (
            IOobject
           (
             "MW_mix",
             runTime.timeName(),
             fluidRegions[i],
             IOobject::READ_IF_PRESENT,
             IOobject::NO_WRITE
            ),
            fluidRegions[i],
            dimensionedScalar("MW_mix", dimless, 0),
            zeroGradientFvPatchScalarField::typeName
        )
    );

Info<< " Adding to S_m_t\n" << endl;
   S_m_tFluid.set
   (
        i,
        new volScalarField
       (
            IOobject
           (
             "S_m_t",
             runTime.timeName(),
             fluidRegions[i],
             IOobject::READ_IF_PRESENT,
             IOobject::AUTO_WRITE
            ),
            fluidRegions[i],
            dimensionedScalar("S_m_t", dimless, 0),
            zeroGradientFvPatchScalarField::typeName
       )
    );

//permeability
Info<< " Adding to K_permea\n" << endl;
   K_permeaFluid.set
   (
        i,
        new volScalarField
       (
            IOobject
           (
             "K_permea",
             runTime.timeName(),
             fluidRegions[i],
             IOobject::READ_IF_PRESENT,
             IOobject::NO_WRITE
            ),
            fluidRegions[i],
            dimensionedScalar("K_permea", dimless, 0),
            zeroGradientFvPatchScalarField::typeName
       )
    );

Info<< " Adding to AC\n" << endl;
   ACFluid.set
   (
        i,
        new volScalarField
       (
            IOobject
           (
             "AC",
             runTime.timeName(),
             fluidRegions[i],
             IOobject::READ_IF_PRESENT,
             IOobject::AUTO_WRITE
            ),
            fluidRegions[i],
            dimensionedScalar("AC", dimless, 0),
            zeroGradientFvPatchScalarField::typeName

        )
    );

Info<< " Adding to nuEff\n" << endl;
   nuEffFluid.set
   (
        i,
        new volScalarField
       (
            IOobject
           (
             "nuEff",
             runTime.timeName(),
             fluidRegions[i],
             IOobject::READ_IF_PRESENT,
             IOobject::AUTO_WRITE
            ),
            fluidRegions[i],
            dimensionedScalar("nuEff", dimless, 0),
            zeroGradientFvPatchScalarField::typeName
       )
    );

Info<< " Adding to S_heat\n" << endl;
   S_heatFluid.set
   (
        i,
        new volScalarField
       (
            IOobject
           (
             "S_heat",
             runTime.timeName(),
             fluidRegions[i],
             IOobject::READ_IF_PRESENT,
             IOobject::AUTO_WRITE
            ),
            fluidRegions[i],
            dimensionedScalar("S_heat", dimless, 0),
            zeroGradientFvPatchScalarField::typeName
       )
    );

Info<< " Adding to grad_Fai_ion\n" << endl;
   grad_Fai_ionFluid.set
   (
        i,
        new volVectorField
       (
            IOobject
           (
             "grad_Fai_ion",
             runTime.timeName(),
             fluidRegions[i],
             IOobject::READ_IF_PRESENT,
             IOobject::NO_WRITE
            ),
            fluidRegions[i],
            dimensionedVector("grad_Fai_ion", dimless, vector(0, 0, 0)),
            fixedValueFvPatchScalarField::typeName

        )
    );

//UDS 78
Info<< " Adding to grad_Fai_ele\n" << endl;
   grad_Fai_eleFluid.set
   (
        i,
        new volVectorField
       (
            IOobject
           (
             "grad_Fai_ele",
             runTime.timeName(),
             fluidRegions[i],
             IOobject::READ_IF_PRESENT,
             IOobject::NO_WRITE
            ),
            fluidRegions[i],
            dimensionedVector("grad_Fai_ele", dimless, vector(0, 0, 0)),
            fixedValueFvPatchScalarField::typeName

        )
    );


Info<< " Adding to heat capacity of fluid thermo_cp\n" << endl;
   thermo_cpFluid.set
   (
        i,
        new volScalarField
       (
            IOobject
           (
             "thermo_cp",
             runTime.timeName(),
             fluidRegions[i],
             IOobject::READ_IF_PRESENT,
             IOobject::AUTO_WRITE
            ),
            fluidRegions[i],
            dimensionedScalar("thermo_cp", dimless, 0),
            zeroGradientFvPatchScalarField::typeName
        )
    );

Info<< " Adding to density of solid rho_s\n" << endl;
   rho_sFluid.set
   (
        i,
        new volScalarField
       (
            IOobject
           (
             "rho_s",
             runTime.timeName(),
             fluidRegions[i],
             IOobject::READ_IF_PRESENT,
             IOobject::NO_WRITE
            ),
            fluidRegions[i],
            dimensionedScalar("rho_s", dimless, 0),
            zeroGradientFvPatchScalarField::typeName
        )
    );

//84
Info<< " Adding to density of fluid rho_f\n" << endl;
   rho_fFluid.set
   (
        i,
        new volScalarField
       (
            IOobject
           (
             "rho_f",
             runTime.timeName(),
             fluidRegions[i],
             IOobject::READ_IF_PRESENT,
             IOobject::NO_WRITE
            ),
            fluidRegions[i],
            dimensionedScalar("rho_f", dimless, 0),
            zeroGradientFvPatchScalarField::typeName
        )
    );

//85
Info<< " Adding to heat capacity of fluid cp_f\n" << endl;
   cp_fFluid.set
   (
        i,
        new volScalarField
       (
            IOobject
           (
             "cp_f",
             runTime.timeName(),
             fluidRegions[i],
             IOobject::READ_IF_PRESENT,
             IOobject::NO_WRITE
            ),
            fluidRegions[i],
            dimensionedScalar("cp_f", dimless, 0),
            zeroGradientFvPatchScalarField::typeName
        )
    );

//86
Info<< " Adding to heat capacity of solid cp_s\n" << endl;
   cp_sFluid.set
   (
        i,
        new volScalarField
       (
            IOobject
           (
             "cp_s",
             runTime.timeName(),
             fluidRegions[i],
             IOobject::READ_IF_PRESENT,
             IOobject::NO_WRITE
            ),
            fluidRegions[i],
            dimensionedScalar("cp_s", dimless, 0),
            zeroGradientFvPatchScalarField::typeName
        )
    );

//87
Info<< " Adding to thermal conductivity of fluid k_f\n" << endl;
   k_fFluid.set
   (
        i,
        new volScalarField
       (
            IOobject
           (
             "k_f",
             runTime.timeName(),
             fluidRegions[i],
             IOobject::READ_IF_PRESENT,
             IOobject::NO_WRITE
            ),
            fluidRegions[i],
            dimensionedScalar("k_f", dimless, 0),
            zeroGradientFvPatchScalarField::typeName
        )
    );

//88
Info<< " Adding to thermal conductivity of solid k_s\n" << endl;
   k_sFluid.set
   (
        i,
        new volScalarField
       (
            IOobject
           (
             "k_s",
             runTime.timeName(),
             fluidRegions[i],
             IOobject::READ_IF_PRESENT,
             IOobject::NO_WRITE
            ),
            fluidRegions[i],
            dimensionedScalar("k_s", dimless, 0),
            zeroGradientFvPatchScalarField::typeName
        )
    );

Info<< " Adding to alphaEff\n" << endl;
   alphaEffFluid.set
   (
        i,
        new volScalarField
       (
            IOobject
           (
             "alphaEff",
             runTime.timeName(),
             fluidRegions[i],
             IOobject::READ_IF_PRESENT,
             IOobject::AUTO_WRITE
            ),
            fluidRegions[i],
            dimensionedScalar("alphaEff", dimless, 0),
            zeroGradientFvPatchScalarField::typeName
       )
    );

Info<< " Adding to phi_s\n" << endl;
   phi_sFluid.set
   (
        i,
        new surfaceScalarField
       (
            IOobject
           (
             "phi_s",
             runTime.timeName(),
             fluidRegions[i],
             IOobject::MUST_READ,
             IOobject::AUTO_WRITE
            ),
            fluidRegions[i]

        )
    );

Info<< " Adding to DFluid\n" << endl;
   DFluid.set
   (
        i,
        new volScalarField
       (
            IOobject
           (
             "D",
             runTime.timeName(),
             fluidRegions[i],
             IOobject::MUST_READ,
             IOobject::AUTO_WRITE
            ),
            fluidRegions[i],
        dimensionedScalar
       (
         "D",
         dimensionSet(0, 2, -1, 0, 0, 0, 0),
         0.2
       )

        )
    );

Info<< " Adding to S_rev\n" << endl;
   S_revFluid.set
   (
        i,
        new volScalarField
       (
            IOobject
           (
             "S_rev",
             runTime.timeName(),
             fluidRegions[i],
             IOobject::READ_IF_PRESENT,
             IOobject::AUTO_WRITE
            ),
            fluidRegions[i],
            dimensionedScalar("S_rev", dimless, 0),
            zeroGradientFvPatchScalarField::typeName
       )
    );

//V 81
Info<< " Adding to S_act\n" << endl;
   S_actFluid.set
   (
        i,
        new volScalarField
       (
            IOobject
           (
             "S_act",
             runTime.timeName(),
             fluidRegions[i],
             IOobject::READ_IF_PRESENT,
             IOobject::AUTO_WRITE
            ),
            fluidRegions[i],
            dimensionedScalar("S_act", dimless, 0),
            zeroGradientFvPatchScalarField::typeName
       )
    );

//V 81
Info<< " Adding to S_ohm\n" << endl;
   S_ohmFluid.set
   (
        i,
        new volScalarField
       (
            IOobject
           (
             "S_ohm",
             runTime.timeName(),
             fluidRegions[i],
             IOobject::READ_IF_PRESENT,
             IOobject::AUTO_WRITE
            ),
            fluidRegions[i],
            dimensionedScalar("S_ohm", dimless, 0),
            zeroGradientFvPatchScalarField::typeName
       )
    );




Info<< " Reading mole_Fraction_H2 at the inlet\n" << endl;
        MOLE_FRACTION_H2_INLETFluid.set (i, new dimensionedScalar (sofcProperties.lookup("MOLE_FRACTION_H2_INLET")));

Info<< " Reading mole_Fraction_CO at the inlet\n" << endl;
        MOLE_FRACTION_CO_INLETFluid.set (i, new dimensionedScalar (sofcProperties.lookup("MOLE_FRACTION_CO_INLET")));

Info<< " Reading mole_Fraction_CH4 at the inlet\n" << endl;
        MOLE_FRACTION_CH4_INLETFluid.set (i, new dimensionedScalar (sofcProperties.lookup("MOLE_FRACTION_CH4_INLET")));

Info<< " Reading mole_Fraction_O2 at the inlet\n" << endl;
        MOLE_FRACTION_O2_INLETFluid.set (i, new dimensionedScalar (sofcProperties.lookup("MOLE_FRACTION_O2_INLET")));

Info<< " Reading mole_Fraction_H2O at the inlet\n" << endl;
        MOLE_FRACTION_H2O_INLETFluid.set (i, new dimensionedScalar (sofcProperties.lookup("MOLE_FRACTION_H2O_INLET")));

Info<< " Reading inlet pressure!!!! If boost pressure is used, remerber adjusting the P_IN!!!!!!!\n" << endl;
        P_INFluid.set  (i, new dimensionedScalar (sofcProperties.lookup("P_IN")));

Info<< " Reading inlet temperature!!!! \n" << endl;
        T_INFluid.set  (i, new dimensionedScalar (sofcProperties.lookup("T_IN")));

Info<< " Reading refrence current density A_ACT\n" << endl;
        A_ACTFluid.set (i, new dimensionedScalar (sofcProperties.lookup("A_ACT")));

Info<< " Reading refrence current density FC_CROSS_SECTION\n" << endl;
        FC_CROSS_SECTIONFluid.set (i, new dimensionedScalar (sofcProperties.lookup("FC_CROSS_SECTION")));

Info<< " Reading tau_potential\n" << endl;
        tau_potentialFluid.set (i, new dimensionedScalar (sofcProperties.lookup("tau_potential")));

Info<< " Reading refrence current density I_REF\n" << endl;
        I_REFFluid.set (i, new dimensionedScalar (sofcProperties.lookup("I_REF")));

Info<< " Reading air ratio\n" << endl;
        lamda_AIRFluid.set (i, new dimensionedScalar (sofcProperties.lookup("lamda_AIR")));

Info<< " Reading fuel utilization\n" << endl;
        U_FFluid.set (i, new dimensionedScalar (sofcProperties.lookup("U_F")));

Info<< " Reading intrinsic permeability GDL\n" << endl;
        K_p_GDLFluid.set  (i, new dimensionedScalar (sofcProperties.lookup("K_p_GDL")));

Info<< " Reading intrinsic permeability CL\n" << endl;
        K_p_CLFluid.set  (i, new dimensionedScalar (sofcProperties.lookup("K_p_CL")));
//

Info<< " Reading density of GDL rho_GDL\n" << endl;
        rho_GDLFluid.set (i, new dimensionedScalar (sofcProperties.lookup("rho_GDL")));

Info<< " Reading heat capacity of GDL cp_GDL\n" << endl;
        cp_GDLFluid.set (i, new dimensionedScalar (sofcProperties.lookup("cp_GDL")));

Info<< " Reading thermal conductivity of GDL ks_GDL\n" << endl;
        ks_GDLFluid.set (i, new dimensionedScalar (sofcProperties.lookup("ks_GDL")));

Info<< " Reading density of CL rho_CL\n" << endl;
        rho_CLFluid.set (i, new dimensionedScalar (sofcProperties.lookup("rho_CL")));

Info<< " Reading heat capacity of CL cp_CL\n" << endl;
        cp_CLFluid.set (i, new dimensionedScalar (sofcProperties.lookup("cp_CL")));

Info<< " Reading thermal conductivity of CL ks_CL\n" << endl;
        ks_CLFluid.set (i, new dimensionedScalar (sofcProperties.lookup("ks_CL")));


// 2021.12.20
Info<< " Reading output voltage v_out\n" << endl;
         V_outFluid.set (i, new dimensionedScalar (sofcProperties.lookup("V_out")));





}

 #include "9copyFluidFields.H" 
