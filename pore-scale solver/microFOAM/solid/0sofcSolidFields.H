PtrList<volScalarField> Fai_ionSolid(solidRegions.size());
PtrList<volScalarField> Fai_eleSolid(solidRegions.size());
PtrList<volScalarField> k_eff_ionSolid(solidRegions.size());
PtrList<volScalarField> k_eff_eleSolid(solidRegions.size());

PtrList<volScalarField> TSolid(solidRegions.size());

//transient term in ionic/electronic potential
PtrList<dimensionedScalar> tau_potentialSolid(solidRegions.size());
PtrList<dimensionedScalar> V_outSolid(solidRegions.size());

PtrList<dimensionedScalar> P_INSolid(solidRegions.size());
PtrList<dimensionedScalar> T_INSolid(solidRegions.size());

PtrList<dimensionedScalar> MOLE_FRACTION_H2_INLETSolid(solidRegions.size()); 
PtrList<dimensionedScalar> MOLE_FRACTION_CO_INLETSolid(solidRegions.size()); 

PtrList<volScalarField> DSolid(solidRegions.size());

//thermal conductivity
PtrList<dimensionedScalar> k_BP_aSolid(solidRegions.size());
PtrList<dimensionedScalar> k_BP_cSolid(solidRegions.size());
PtrList<dimensionedScalar> k_memSolid(solidRegions.size());

forAll(solidRegions, i)
{
//V 1
Info<< " Adding to Fai_ionSolid\n" << endl;
   Fai_ionSolid.set
   (
        i,
        new volScalarField
       (
            IOobject
           (
             "Fai_ion",
             runTime.timeName(),
             solidRegions[i],
             IOobject::MUST_READ,
             IOobject::AUTO_WRITE
            ),
            solidRegions[i]
        )
    );

//V 2
Info<< " Adding to Fai_eleSolid\n" << endl;
   Fai_eleSolid.set
   (
        i,
        new volScalarField
       (
            IOobject
           (
             "Fai_ele",
             runTime.timeName(),
             solidRegions[i],
             IOobject::MUST_READ,
             IOobject::AUTO_WRITE
            ),
            solidRegions[i]
        )
    );

//V 3
Info<< " Adding to k_eff_ionSolid\n" << endl;
   k_eff_ionSolid.set
   (
        i,
        new volScalarField
       (
            IOobject
           (
             "k_eff_ion",
             runTime.timeName(),
             solidRegions[i],
             IOobject::READ_IF_PRESENT,
             IOobject::AUTO_WRITE
            ),
            solidRegions[i],
            dimensionedScalar("k_eff_ion", dimless, 10),
            zeroGradientFvPatchScalarField::typeName
        )
    );

//V 4
Info<< " Adding to k_eff_eleSolid\n" << endl;
   k_eff_eleSolid.set
   (
        i,
        new volScalarField
       (
            IOobject
           (
             "k_eff_ele",
             runTime.timeName(),
             solidRegions[i],
             IOobject::READ_IF_PRESENT,
             IOobject::AUTO_WRITE
            ),
            solidRegions[i],
            dimensionedScalar("k_eff_ele", dimless, 2e4),
            zeroGradientFvPatchScalarField::typeName
        )
    );

Info<< " Adding to TSolid\n" << endl;
   TSolid.set
   (
        i,
        new volScalarField
       (
            IOobject
           (
             "T",
             runTime.timeName(),
             solidRegions[i],
             IOobject::MUST_READ,
             IOobject::AUTO_WRITE
            ),
            solidRegions[i]
        )
    );

Info<< " Adding to DSolid\n" << endl;
   DSolid.set
   (
        i,
        new volScalarField
       (
            IOobject
           (
             "D",
             runTime.timeName(),
             solidRegions[i],
             IOobject::MUST_READ,
             IOobject::AUTO_WRITE
            ),
            solidRegions[i],
        dimensionedScalar
       (
         "D",
         dimensionSet(0, 2, -1, 0, 0, 0, 0),
         11
       )

        )
    );

Info<< "    Adding transport properties to  Solid field\n" << endl;   
Info<< "Reading transportProperties\n" << endl;

         IOdictionary sofcsolidProperties
        (
             IOobject
           (
              "sofcsolidProperties",
              runTime.constant(),
              solidRegions[i],
              IOobject::MUST_READ_IF_MODIFIED,
              IOobject::NO_WRITE
           )
         );

Info<< " Reading tau_potential\n" << endl;
        tau_potentialSolid.set (i, new dimensionedScalar (sofcsolidProperties.lookup("tau_potential")));

Info<< " Reading output voltage v_out\n" << endl;
         V_outSolid.set (i, new dimensionedScalar (sofcsolidProperties.lookup("V_out")));



Info<< " Reading inlet pressure!!!! If boost pressure is used, remerber adjusting the P_IN!!!!!!!\n" << endl;
         P_INSolid.set (i, new dimensionedScalar (sofcsolidProperties.lookup("P_IN")));

Info<< " Reading inlet temperature!!!! Remerber adjusting the T_0!!!!!!!\n" << endl;
         T_INSolid.set (i, new dimensionedScalar (sofcsolidProperties.lookup("T_IN")));


Info<< " Reading mole_Fraction_H2 at the inlet\n" << endl;
        MOLE_FRACTION_H2_INLETSolid.set (i, new dimensionedScalar (sofcsolidProperties.lookup("MOLE_FRACTION_H2_INLET")));

Info<< " Reading mole_Fraction_CO at the inlet\n" << endl;
        MOLE_FRACTION_CO_INLETSolid.set (i, new dimensionedScalar (sofcsolidProperties.lookup("MOLE_FRACTION_CO_INLET")));


Info<< " Reading solid thermal conductivity\n" << endl;
         k_BP_aSolid.set (i, new dimensionedScalar (sofcsolidProperties.lookup("k_BP_a")));
         k_BP_cSolid.set (i, new dimensionedScalar (sofcsolidProperties.lookup("k_BP_c")));
         k_memSolid.set (i, new dimensionedScalar (sofcsolidProperties.lookup("k_mem")));



















}
