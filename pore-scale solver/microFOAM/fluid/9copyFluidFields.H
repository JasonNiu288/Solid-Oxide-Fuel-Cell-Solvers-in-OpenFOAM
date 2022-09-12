//copy Fai_ele, Fai_ion, and J_a to pore region to calculate the BVEqn

//PtrList<volScalarField> J_a_copyFluid(fluidRegions.size());    //electrochemical reaction rate in the anode (A/m3)

PtrList<volScalarField> Fai_ion_copyFluid(fluidRegions.size());      //ionin potential
PtrList<volScalarField> Fai_ele_copyFluid(fluidRegions.size());      //electronic potential
PtrList<volScalarField> k_copyFluid(fluidRegions.size());    //electron conductivity
PtrList<volScalarField> JtoNiFluid(fluidRegions.size());    // exchange current density to NiRegion
PtrList<volScalarField> JtoYSZFluid(fluidRegions.size());

PtrList<volScalarField> TPBFluid(fluidRegions.size());

forAll(fluidRegions, i)
{


Info<< " Adding to JtoNiFluid\n" << endl;
   JtoNiFluid.set
   (
        i,
        new volScalarField
       (
            IOobject
           (
             "JtoNi",
             runTime.timeName(),
             fluidRegions[i],
             IOobject::MUST_READ,
             IOobject::AUTO_WRITE
            ),
            fluidRegions[i]

            /*IOobject
           (
             "JtoNi",
             runTime.timeName(),
             fluidRegions[i],
             IOobject::READ_IF_PRESENT,
             IOobject::AUTO_WRITE
            ),
            fluidRegions[i],
            dimensionedScalar("JtoNi", dimless, 0),
            zeroGradientFvPatchScalarField::typeName*/
        )
    );

Info<< " Adding to JtoYSZFluid\n" << endl;
   JtoYSZFluid.set
   (
        i,
        new volScalarField
       (
            IOobject
           (
             "JtoYSZ",
             runTime.timeName(),
             fluidRegions[i],
             IOobject::MUST_READ,
             IOobject::AUTO_WRITE
            ),
            fluidRegions[i]
        )
    );

Info<< " Adding to Fai_ion_copy\n" << endl;
   Fai_ion_copyFluid.set
   (
        i,
        new volScalarField
       (
            IOobject
           (
             "Fai_ion_copy",
             runTime.timeName(),
             fluidRegions[i],
             IOobject::MUST_READ,
             IOobject::AUTO_WRITE
            ),
            fluidRegions[i]
        )
    );
//V 6
Info<< " Adding to Fai_ele_copy\n" << endl;
   Fai_ele_copyFluid.set
   (
        i,
        new volScalarField
       (
            IOobject
           (
             "Fai_ele_copy",
             runTime.timeName(),
             fluidRegions[i],
             IOobject::MUST_READ,
             IOobject::AUTO_WRITE
            ),
            fluidRegions[i]
        )
    );

//V 8
Info<< " Adding to effective electron conductivity\n" << endl;
   k_copyFluid.set
   (
        i,
        new volScalarField
       (
            IOobject
           (
             "k_copy",
             runTime.timeName(),
             fluidRegions[i],
             IOobject::READ_IF_PRESENT,
             IOobject::AUTO_WRITE
            ),
            fluidRegions[i],
            dimensionedScalar("k_copy", dimless, 1),
            zeroGradientFvPatchScalarField::typeName
        )
    );

Info<< " Adding to TPBFluid\n" << endl;
   TPBFluid.set
   (
        i,
        new volScalarField
       (
            IOobject
           (
             "TPB",
             runTime.timeName(),
             fluidRegions[i],
             IOobject::READ_IF_PRESENT,
             IOobject::AUTO_WRITE
            ),
            fluidRegions[i],
            dimensionedScalar("TPB", dimless, 0),
            zeroGradientFvPatchScalarField::typeName
        )
    );


}

