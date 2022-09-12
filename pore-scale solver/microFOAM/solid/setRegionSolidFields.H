fvMesh& mesh = solidRegions[i];
solidThermo& thermo = thermos[i];

tmp<volScalarField> trho = thermo.rho();
const volScalarField& rho = trho();

tmp<volScalarField> tcp = thermo.Cp();
const volScalarField& cp = tcp();

tmp<volSymmTensorField> taniAlpha;
if (!thermo.isotropic())
{
    volSymmTensorField& aniAlpha = aniAlphas[i];
    tmp<volVectorField> tkappaByCp = thermo.Kappa()/cp;
    const coordinateSystem& coodSys = coordinates[i];

    aniAlpha.primitiveFieldRef() =
        coodSys.R().transformVector(tkappaByCp());
    aniAlpha.correctBoundaryConditions();

    taniAlpha = tmp<volSymmTensorField>
    (
        new volSymmTensorField(aniAlpha)
    );
}


volScalarField& h = thermo.he();

const volScalarField& betav = betavSolid[i];

fv::options& fvOptions = solidHeatSources[i];

solidNoLoopControl& pimple = pimples.solid(i);



//sofc

volScalarField& Fai_ion = Fai_ionSolid[i];
volScalarField& Fai_ele = Fai_eleSolid[i];
volScalarField& k_eff_ele = k_eff_eleSolid[i];
volScalarField& k_eff_ion = k_eff_ionSolid[i];
volScalarField& T = TSolid[i];

volScalarField& D = DSolid[i];
//volScalarField& S_heat = S_heatSolid[i];

const dimensionedScalar& tau_potential = tau_potentialSolid[i];
const dimensionedScalar& V_out = V_outSolid[i];

const dimensionedScalar& P_IN = P_INSolid[i];
const dimensionedScalar& T_IN = T_INSolid[i];

const dimensionedScalar& MOLE_FRACTION_H2_INLET   =  MOLE_FRACTION_H2_INLETSolid[i];
const dimensionedScalar& MOLE_FRACTION_CO_INLET   =  MOLE_FRACTION_CO_INLETSolid[i];

const dimensionedScalar& k_BP_a = k_BP_aSolid[i];
const dimensionedScalar& k_BP_c = k_BP_cSolid[i];
const dimensionedScalar& k_mem  = k_memSolid[i];



