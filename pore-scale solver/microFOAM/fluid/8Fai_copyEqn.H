// pore region shares the Fai_ion, Fai_ele, and J_a with Ni and YSZ region

        //transfer Fai_ele from Ni region to pore region
        fvScalarMatrix Fai_ele_copyEqn
        (
            fvm::ddt(tau_potential, Fai_ele_copy)
                 
        );

        Fai_ele_copyEqn.relax();


//==============================================================================     
        // transfer Fai_ion from YSZ region to pore region;
        fvScalarMatrix Fai_ion_copyEqn
        (
            fvm::ddt(tau_potential, Fai_ion_copy)
                  
        );


        Fai_ion_copyEqn.relax();



//==============================================================================     
        // transfer J from pore region to Ni region;
        fvScalarMatrix JtoNiEqn
        (
            fvm::ddt(tau_potential, JtoNi)
                  
        );


        JtoNiEqn.relax();

//==============================================================================     
        // transfer J from pore region to YSZ region;
        fvScalarMatrix JtoYSZEqn
        (
            fvm::ddt(tau_potential, JtoYSZ)
                  
        );


        JtoYSZEqn.relax();

Info<< "Min/max JtoYSZ:" << min(JtoYSZ) << ' '<< max(JtoYSZ) << endl;

