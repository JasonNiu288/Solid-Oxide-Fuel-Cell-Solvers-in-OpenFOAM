

label nheight = 124; //cell number along the z axis direction;
vector position(0.0,0.0,0.0);


 if(fluidRegions[i].name() == "pore")  
{
    label cellI = mesh.findCell(position);
    if (cellI != -1) //if the point is in the sub-mesh 
    {
        
       //do stuff
    }							 
            
      Info<<"pore done !"<<endl;
}


// =============================================================================
// Ni region.  region 1!!!!!!! 


 if(fluidRegions[i].name() == "Ni")  // 
{



      Info<<"Ni done !"<<endl;

}

// =============================================================================
// YSZ region, region 2!!!!!!!!!!!!!!!!
 if(fluidRegions[i].name() == "YSZ")  //
{


}







