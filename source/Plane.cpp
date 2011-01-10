#include "Plane.h"

Plane::Plane(uint width, uint height):
Surface(width, height)
{

}

Plane::~Plane()
{
   // ownership was transfered by AddToPlane
   // should delete all pointed-to objects
   for(vector<GfxObj*>::iterator it = map_gfxobj.begin(); it != map_gfxobj.end(); it++ )
   {
      delete *it;
   }
}

void Plane::AddToPlane(GfxObj* go)
{
   map_gfxobj.push_back(go);
   go->SetPlane(this);
}

void Plane::Draw()
{
   for(vector<GfxObj*>::iterator it = map_gfxobj.begin(); it != map_gfxobj.end(); it++ )
   {
      (*it)->Draw();
   }
}
