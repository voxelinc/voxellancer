#include "colorcoder.h"

#include "voxel/specialvoxels/enginevoxel.h"
#include "voxel/specialvoxels/hardpointvoxel.h"
#include "voxel/specialvoxels/cockpitvoxel.h"
#include "voxel/specialvoxels/fuelvoxel.h"
#include "voxel/specialvoxels/crucialvoxel.h"


ColorCoder::ColorCoder() :
    prop_engineKey("colorcode.EngineKey"),
    prop_engineColor("colorcode.EngineColor"),
    prop_engineMass("colorcode.EngineMass"),
    prop_engineHP("colorcode.EngineHP"),
    prop_hardpointKey("colorcode.HardpointKey"),
    prop_hardpointColor("colorcode.HardpointColor"),
    prop_hardpointMass("colorcode.HardpointMass"),
    prop_hardpointHP("colorcode.HardpointHP"),
    prop_cockpitKey("colorcode.CockpitKey"),
    prop_cockpitColor("colorcode.CockpitColor"),
    prop_cockpitMass("colorcode.CockpitMass"),
    prop_cockpitHP("colorcode.CockpitHP"),
    prop_fuelKey("colorcode.FuelKey"),
    prop_fuelColor("colorcode.FuelColor"),
    prop_fuelMass("colorcode.FuelMass"),
    prop_fuelHP("colorcode.FuelHP"),
    prop_crucialKey("colorcode.CrucialKey"),
    prop_crucialColor("colorcode.CrucialColor"),
    prop_crucialMass("colorcode.CrucialMass"),
    prop_crucialHP("colorcode.CrucialHP")
{
    
}

ColorCoder::~ColorCoder(){

}


Voxel* ColorCoder::newCodedVoxel(Voxel& voxel){

    if (voxel.color() == prop_engineKey){
        return new EngineVoxel(voxel.gridCell(), prop_engineColor, prop_engineMass, prop_engineHP);
    } else if (voxel.color() == prop_hardpointKey){
        return new HardpointVoxel(voxel.gridCell(), prop_hardpointColor, prop_hardpointMass, prop_hardpointHP);
    } else if (voxel.color() == prop_cockpitKey){
        return new CockpitVoxel(voxel.gridCell(), prop_cockpitColor, prop_cockpitMass, prop_cockpitHP);
    } else if (voxel.color() == prop_fuelKey){
        return new FuelVoxel(voxel.gridCell(), prop_fuelColor, prop_fuelMass, prop_fuelHP);
    } else if (voxel.color() == prop_crucialKey){
        return new CrucialVoxel(voxel.gridCell(), prop_crucialColor, prop_crucialMass, prop_crucialHP);
    } else {
        return new Voxel(voxel);
    }

}