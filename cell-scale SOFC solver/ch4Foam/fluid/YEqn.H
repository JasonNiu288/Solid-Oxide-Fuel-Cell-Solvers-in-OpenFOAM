tmp<fv::convectionScheme<scalar>> mvConvection(nullptr);

if (Y.size())
{
    mvConvection = tmp<fv::convectionScheme<scalar>>
    (
        fv::convectionScheme<scalar>::New
        (
            mesh,
            fields,
            phi,
            mesh.divScheme("div(phi,Yi_h)")
        )
    );
}


if(fluidRegions[i].name() == "anodePart")
{
    reaction.correct();
    Qdot = reaction.Qdot();
    volScalarField Yt
    (
        IOobject("Yt", runTime.timeName(), mesh),
        mesh,
        dimensionedScalar("Yt", dimless, 0)
    );

    forAll(Y, i)
    {
        if (i != inertIndex && composition.active(i))
        {
            volScalarField& Yi = Y[i];

            if (Yi.name()=="H2")
           {
              fvScalarMatrix YiEqn
              (
                  fvm::ddt(rho, Yi)
                + mvConvection->fvmDiv(phi, Yi)
                - fvm::laplacian(D_eff_H2, Yi)  
               ==
                  S_m_H2
              );

              YiEqn.relax();
              YiEqn.solve(mesh.solver("Yi"));
              Yi.max(0.0);
              Yt += Yi;

           }
 //           if(Yi.name()=="H2O")
 //          {
 //             fvScalarMatrix YiEqn
 //             (
 //                 fvm::ddt(rho, Yi)
 //               + mvConvection->fvmDiv(phi, Yi)
 //               - fvm::laplacian(D_eff_H2O, Yi)
 //              ==
 //                 S_m_H2O
 //             );

//              YiEqn.relax();
//              YiEqn.solve(mesh.solver("Yi"));
//              Yi.max(0.0);
//              Yt += Yi;
//           }

            if(Yi.name()=="CO")
           {
              fvScalarMatrix YiEqn
              (
                  fvm::ddt(rho, Yi)
                + mvConvection->fvmDiv(phi, Yi)
                - fvm::laplacian(D_eff_CO, Yi)
               ==
                  S_m_CO
              );

              YiEqn.relax();
              YiEqn.solve(mesh.solver("Yi"));
              Yi.max(0.0);
              Yt += Yi;
           }
            if(Yi.name()=="CO2")
           {
              fvScalarMatrix YiEqn
              (
                  fvm::ddt(rho, Yi)
                + mvConvection->fvmDiv(phi, Yi)
                - fvm::laplacian(D_eff_CO2, Yi)
               ==
                  S_m_CO2
              );	

              YiEqn.relax();
              YiEqn.solve(mesh.solver("Yi"));
              Yi.max(0.0);
              Yt += Yi;
           }

            if(Yi.name()=="CH4")
           {
              fvScalarMatrix YiEqn
              (
                  fvm::ddt(rho, Yi)
                + mvConvection->fvmDiv(phi, Yi)
                - fvm::laplacian(D_eff_CH4, Yi)
               ==
                  S_m_CH4
              );

              YiEqn.relax();
              YiEqn.solve(mesh.solver("Yi"));
              Yi.max(0.0);
              Yt += Yi;
           }

        
        }


   }

    if (Y.size())
    {
        Y[inertIndex] = scalar(1) - Yt;
        Y[inertIndex].max(0.0);
    }
}


if(fluidRegions[i].name() == "cathodePart")
{
    reaction.correct();
    Qdot = reaction.Qdot();
    volScalarField Yt
    (
        IOobject("Yt", runTime.timeName(), mesh),
        mesh,
        dimensionedScalar("Yt", dimless, 0)
    );

    forAll(Y, i)
    {
        if (i != inertIndex && composition.active(i))
        {
            volScalarField& Yi = Y[i];
           if(Yi.name()=="O2")
           {
              fvScalarMatrix YiEqn
              (
                  fvm::ddt(rho, Yi)
                + mvConvection->fvmDiv(phi, Yi)
                - fvm::laplacian(D_eff_O2, Yi) 
               ==
                  S_m_O2
              );
              YiEqn.relax();
              YiEqn.solve(mesh.solver("Yi"));
        
        Info<< "Min/max Y_O2:" << min(Yi) << ' '
             << max(Yi) << endl;

            Yi.max(1e-12);
            Yt += Yi;
 
  
           }
           if(Yi.name()=="H2O")
           {
              fvScalarMatrix YiEqn
              (
                  fvm::ddt(rho, Yi)
                + mvConvection->fvmDiv(phi, Yi)
                - fvm::laplacian(D_eff_H2O, Yi) 
               ==
                  S_m_H2O
              );

              YiEqn.relax();
              YiEqn.solve(mesh.solver("Yi"));
              Yi.max(0.0);
              Yt += Yi;
           }

        
        }
    }

    if (Y.size())
    {
        Y[inertIndex] = scalar(1) - Yt;
        Y[inertIndex].max(0.0);
    }
}

