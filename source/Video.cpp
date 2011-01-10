#include "Video.h"
#include "Config.h"
#include "Exception.h"
#include "SDL/SDL_image.h"
#include "Player.h"
#include "KbInput.h"

Video::Video():
mp_plane(0)
{
   IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

   Prepare(0);
}

Video::~Video()
{
   Finalize();

   IMG_Quit();
}

void Video::Update()
{
   if( mp_plane )
   {
      mp_plane->Draw(); // update plane
      m_screen = *mp_plane;
   }
}

void Video::Prepare(const char* stage)
{
   mp_plane = new Plane(m_screen.Width(), m_screen.Height());

/*   Surface* s = new Surface("background.bmp");
   mp_plane->AddToPlane(s); // ownership transfer

   Surface* s2 = new Surface("hello.bmp");
   s2->SetPosition(150,150);
   mp_plane->AddToPlane(s2);
*/
   Player* s3 = new Player("c:\\sprite1.ini");
   KbInput* kb = new KbInput();
   s3->SetInput(kb);
//   s3->Scale2x();
   mp_plane->AddToPlane(s3);
}

void Video::Finalize()
{
   delete mp_plane;
}
