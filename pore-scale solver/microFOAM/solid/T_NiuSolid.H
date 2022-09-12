forAll(solidRegions[i].boundaryMesh(), patchi)
{

    forAll(solidRegions[i].boundaryMesh()[patchi], facei)
    {

     label faceid_start = solidRegions[i].boundaryMesh()[patchi].start();
     label faceID = faceid_start + facei;
     label cellID = solidRegions[i].boundaryMesh()[patchi].faceCells()[facei];
       
     D.boundaryFieldRef()[patchi][facei] = D[cellID];
    }
}  






         fvScalarMatrix TNiuEqn
        (
            fvm::ddt(cp_solid*rho_solid, TNiu)
          - fvm::laplacian(D, TNiu)
         // == 
         //    S_heat
                          
        );


        TNiuEqn.relax();

        TNiuEqn.solve(mesh.solver(TNiu.select(pimples.finalIter())));


Info<< "Min/max TNiu:" << min(TNiu) << ' '
    << max(TNiu) << endl;

 
