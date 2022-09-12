  

forAll(fluidRegions[i].boundaryMesh(), patchi)
{

    forAll(fluidRegions[i].boundaryMesh()[patchi], facei)
    {

     label faceid_start = fluidRegions[i].boundaryMesh()[patchi].start();
     label faceID = faceid_start + facei;
     label cellID = fluidRegions[i].boundaryMesh()[patchi].faceCells()[facei];
       
     cp_f.boundaryFieldRef()[patchi][facei] = cp_f[cellID];
     k_f.boundaryFieldRef()[patchi][facei]  = k_f[cellID];
     k_s.boundaryFieldRef()[patchi][facei]  = k_s[cellID];

    }
}



     surfaceScalarField phi_T =     linearInterpolate(rho*cp_f*U) & mesh.Sf();
        phi_s = linearInterpolate(cp_f)*phi;
Info<<"MIN/MAX cp_f ========="<<min(cp_f).value() <<"  "<<max(cp_f).value()<<endl;

     D = porosity * k_f/cp_f + (1 - porosity) * k_s/cp_f;
//Info<<"min/max D in T_Niu"<<min(D).value()<<","<<max(D).value()<<endl;

         fvScalarMatrix TNiuEqn
        (
            fvm::ddt(rho*cp_f, TNiu)
          + fvm::div(phi*linearInterpolate(cp_f), TNiu)
        //  - fvm::SuSp(rho*cp_f*S_m_t, TNiu)
          - fvm::laplacian(D, TNiu)
        //  == 
        //     S_heat
                          
        );


        TNiuEqn.relax();

        TNiuEqn.solve(mesh.solver(TNiu.select(pimples.finalIter())));


Info<< "Min/max TNiu:" << min(TNiu) << ' '
    << max(TNiu) << endl;

 
