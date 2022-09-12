    const fvMesh& mesh = fluidRegions[i];

    CombustionModel<rhoReactionThermo>& reaction = reactionFluid[i];

    rhoReactionThermo& thermo = thermoFluid[i];
    thermo.validate(args.executable(), "h", "e");

    basicMultiComponentMixture& composition = thermo.composition();
    PtrList<volScalarField>& Y = composition.Y();

    label inertIndex = -1;
    if (Y.size())
    {
        const word inertSpecie(thermo.lookup("inertSpecie"));
        if (!composition.species().found(inertSpecie))
        {
            FatalIOErrorIn(args.executable().c_str(), thermo)
                << "Inert specie " << inertSpecie
                << " not found in available species "
                << composition.species()
                << exit(FatalIOError);
        }
        inertIndex = composition.species()[inertSpecie];
    }

    volScalarField& rho = rhoFluid[i];
    volVectorField& U = UFluid[i];
    surfaceScalarField& phi = phiFluid[i];

    compressible::turbulenceModel& turbulence = turbulenceFluid[i];
    volScalarField& K = KFluid[i];
    volScalarField& dpdt = dpdtFluid[i];

    volScalarField& p = thermo.p();
    const volScalarField& psi = thermo.psi();

    volScalarField& p_rgh = p_rghFluid[i];

    const dimensionedVector& g = gFluid[i];
    const volScalarField& gh = ghFluid[i];
    const surfaceScalarField& ghf = ghfFluid[i];

    multivariateSurfaceInterpolationScheme<scalar>::fieldTable& fields =
        fieldsFluid[i];

    volScalarField& Qdot = QdotFluid[i];

    radiation::radiationModel& rad = radiation[i];

    IOMRFZoneList& MRF = MRFfluid[i];
    fv::options& fvOptions = fluidFvOptions[i];

    const dimensionedScalar initialMass
    (
        "initialMass",
        dimMass,
        initialMassFluid[i]
    );

    pimpleNoLoopControl& pimple = pimples.pimple(i);

    pressureControl& pressureControl = pressureControlFluid[i];

    scalar cumulativeContErr = cumulativeContErrs[i];



//added by whzhao, 2021.9

// BV Eqn
volScalarField& yita_act   = yita_actFluid[i];
volScalarField& J_a        = J_aFluid[i];
volScalarField& J_c        = J_cFluid[i];

volScalarField& T          = TFluid[i];

//
volScalarField& Fai_ion      = Fai_ionFluid[i];
volScalarField& Fai_ele      = Fai_eleFluid[i];
volScalarField& k_eff_ion    = k_eff_ionFluid[i];
volScalarField& k_eff_ele    = k_eff_eleFluid[i];

volScalarField& S_ion    = S_ionFluid[i];
volScalarField& S_ele    = S_eleFluid[i];

volScalarField& porosity = porosityFluid[i];

/*volScalarField& alpha_Fai_ele = alpha_Fai_eleFluid[i];
volScalarField& grad_alpha_Fai_ele = grad_alpha_Fai_eleFluid[i];
volScalarField& alpha_Fai_ion = alpha_Fai_ionFluid[i];
volScalarField& grad_alpha_Fai_ion = grad_alpha_Fai_ionFluid[i];*/

//chemical model
volScalarField& Kps    = KpsFluid[i];
volScalarField& Ksf    = KsfFluid[i];
volScalarField& R_WGSR = R_WGSRFluid[i];    //reaction rate
volScalarField& Krf    = KrfFluid[i];
volScalarField& Kpr    = KprFluid[i];
volScalarField& R_MSR  = R_MSRFluid[i];     //reaction rate
volScalarField& heatMSR  = heatMSRFluid[i]; //reaction heat
volScalarField& heatWGSR = heatWGSRFluid[i];//reaction heat

//  source term for species
volScalarField& S_m_H2    = S_m_H2Fluid[i];
volScalarField& S_m_O2    = S_m_O2Fluid[i];
volScalarField& S_m_H2O   = S_m_H2OFluid[i];
volScalarField& S_m_CO    = S_m_COFluid[i];
volScalarField& S_m_CO2   = S_m_CO2Fluid[i];
volScalarField& S_m_CH4   = S_m_CH4Fluid[i];
//diffusion coeficient
/*
volScalarField& D_H2  = D_H2Fluid[i];
volScalarField& D_O2  = D_O2Fluid[i];
volScalarField& D_H2O = D_H2OFluid[i];
volScalarField& D_CO2 = D_CO2Fluid[i];
volScalarField& D_CO  = D_COFluid[i];
volScalarField& D_CH4 = D_CH4Fluid[i];*/

volScalarField& D_eff_H2  = D_eff_H2Fluid[i];
volScalarField& D_eff_O2  = D_eff_O2Fluid[i];
volScalarField& D_eff_H2O = D_eff_H2OFluid[i];
volScalarField& D_eff_CO  = D_eff_COFluid[i];
volScalarField& D_eff_CO2 = D_eff_CO2Fluid[i];
volScalarField& D_eff_CH4 = D_eff_CH4Fluid[i];

//species mole fraction
volScalarField& moleFrac_H2O = moleFrac_H2OFluid[i];
volScalarField& moleFrac_H2  = moleFrac_H2Fluid[i];
volScalarField& moleFrac_N2  = moleFrac_N2Fluid[i];
volScalarField& moleFrac_O2  = moleFrac_O2Fluid[i];
volScalarField& moleFrac_CO  = moleFrac_COFluid[i];
volScalarField& moleFrac_CO2 = moleFrac_CO2Fluid[i];
volScalarField& moleFrac_CH4 = moleFrac_CH4Fluid[i];
volScalarField& MW_mix   = MW_mixFluid[i];

volScalarField& S_m_t  = S_m_tFluid[i];
volScalarField& S_heat = S_heatFluid[i];
volVectorField& grad_Fai_ion = grad_Fai_ionFluid[i];
volVectorField& grad_Fai_ele = grad_Fai_eleFluid[i];

volScalarField& S_rev       = S_revFluid[i];
volScalarField& S_act       = S_actFluid[i];
volScalarField& S_ohm       = S_ohmFluid[i];

volScalarField& K_permea = K_permeaFluid[i];

volScalarField& AC = ACFluid[i]; //UEqn.H
volScalarField& nuEff = nuEffFluid[i];
volScalarField& alphaEff = alphaEffFluid[i];

volScalarField& thermo_cp     = thermo_cpFluid[i];

volScalarField& rho_f  = rho_fFluid[i];
volScalarField& rho_s  = rho_sFluid[i];
volScalarField& cp_f   = cp_fFluid[i];
volScalarField& cp_s   = cp_sFluid[i];
volScalarField& k_f    = k_fFluid[i];
volScalarField& k_s    = k_sFluid[i];

volScalarField& D = DFluid[i];

//volScalarField& A_ID_OUT = A_ID_OUTFluid[i];


surfaceScalarField& phi_s = phi_sFluid[i];

const dimensionedScalar& MOLE_FRACTION_H2_INLET   =  MOLE_FRACTION_H2_INLETFluid[i]; //partial pressure
const dimensionedScalar& MOLE_FRACTION_O2_INLET   =  MOLE_FRACTION_O2_INLETFluid[i];
const dimensionedScalar& MOLE_FRACTION_CO_INLET   =  MOLE_FRACTION_CO_INLETFluid[i];
const dimensionedScalar& MOLE_FRACTION_CH4_INLET  =  MOLE_FRACTION_CH4_INLETFluid[i];
const dimensionedScalar& MOLE_FRACTION_H2O_INLET  =  MOLE_FRACTION_H2O_INLETFluid[i];
const dimensionedScalar& P_IN                     =  P_INFluid[i];  //inlet pressure;
const dimensionedScalar& T_IN                     =  T_INFluid[i];  //inlet temperature;
const dimensionedScalar& A_ACT                    =  A_ACTFluid[i];


const dimensionedScalar& tau_potential = tau_potentialFluid[i];

const dimensionedScalar& I_REF   =  I_REFFluid[i];  //reference current density;

const dimensionedScalar& FC_CROSS_SECTION   =  FC_CROSS_SECTIONFluid[i];

const dimensionedScalar& lamda_AIR   =  lamda_AIRFluid[i]; //air ratio

const dimensionedScalar& U_F   =  U_FFluid[i];  // fuel utilization;

//permeability
const dimensionedScalar& K_p_GDL = K_p_GDLFluid[i];
const dimensionedScalar& K_p_CL = K_p_CLFluid[i];


const dimensionedScalar& rho_GDL   =  rho_GDLFluid[i];
const dimensionedScalar& cp_GDL    =  cp_GDLFluid[i];
const dimensionedScalar& ks_GDL    =  ks_GDLFluid[i];

const dimensionedScalar& rho_CL   =  rho_CLFluid[i];
const dimensionedScalar& cp_CL    =  cp_CLFluid[i];
const dimensionedScalar& ks_CL    =  ks_CLFluid[i];

const dimensionedScalar& V_out = V_outFluid[i];



// share Fai_ele, Fai_ion, J_a through Ni, YSZ and pore regions
volScalarField& Fai_ion_copy      = Fai_ion_copyFluid[i];
volScalarField& Fai_ele_copy      = Fai_ele_copyFluid[i];
volScalarField& JtoNi   = JtoNiFluid[i];
volScalarField& JtoYSZ  = JtoYSZFluid[i];

volScalarField& TPB  = TPBFluid[i];




