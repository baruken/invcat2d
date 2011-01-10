#include "GEImage.hpp"

GEImage::GEImage(const char *file):m_pSurface(NULL), m_pFlipSurface(NULL)
{
	std::cout << "GEImage constructor from file = " << file << " this = " << this << '\n';
	SDL_Surface	*temp_surface;
	temp_surface = IMG_Load(file);
	m_pSurface = SDL_DisplayFormat(temp_surface);
	SDL_FreeSurface(temp_surface);

	// Create alternate flipped frame
	m_pFlipSurface = FlipSurface(m_pSurface);

	m_nWidth = m_pSurface->w;
	m_nHeight = m_pSurface->h;
}

GEImage::GEImage(GEImage* p_image, int width, int height, int nFrame):m_pSurface(NULL), m_pFlipSurface(NULL)
{
	std::cout << "GEImage constructor from image pointer = " << p_image << " frame = " << nFrame << " this = " << this << '\n';
	
	// Get atributes from current video surface to initialize internal parameters
	SDL_Surface* video = NULL;
	video = SDL_GetVideoSurface();
	
	m_pSurface = SDL_CreateRGBSurface(video->flags, width, height,
									video->format->BitsPerPixel, 
									video->format->Rmask, 
									video->format->Gmask, 
									video->format->Bmask, 
									video->format->Amask);
	if( m_pSurface )
	{
		std::cout << "Image surface allocated correctly.\n";
		// We don't need free the surface from SDL_GetVideoSurface() -> This will free the screen: big mistake!
		
		SDL_Rect position;
		
		/* Understanding the position
		 * 
		 * The one-file/one-surface sprite map is a linear constant height/variable width image file, with all images copied side by side.
		 * Frame 0 is on 0 x 0 (col X row)
		 * Frame 1 is on width*1 x 0
		 * Frame 2 is on width*2 x 0
		 * ...
		 * Frame n is on width*n x 0
		 * 
		 */
		  
		position.x = nFrame * width;
		position.y = 0;

		// Create frame
		SDL_BlitSurface(p_image->GetSurface(), &position, m_pSurface, NULL);
		
		// Create alternate flipped frame
		m_pFlipSurface = FlipSurface(m_pSurface);

		m_nWidth = width;
		m_nHeight = height;
	}
	else
	{
		std::cout << "Failed to allocated image surface.\n";
	}
}

GEImage::~GEImage()
{
	std::cout << "GEImage destructor. this = " << this << '\n';
	SDL_FreeSurface(m_pSurface);
	SDL_FreeSurface(m_pFlipSurface);
}

SDL_Surface* GEImage::GetSurface()
{
	return m_pSurface;
}

SDL_Surface* GEImage::GetFlipSurface()
{
	return m_pFlipSurface;
}

void GEImage::SetColorKey(int R, int G, int B)
{
	Uint32 colorkey = SDL_MapRGB(m_pSurface->format, R, G, B); // transforms RGB values into a valid color
	SDL_SetColorKey(m_pSurface, SDL_SRCCOLORKEY, colorkey); 
	SDL_SetColorKey(m_pFlipSurface, SDL_SRCCOLORKEY, colorkey);
}

int GEImage::GetWidth()
{
	return m_nWidth;
}

int GEImage::GetHeight()
{
	return m_nHeight;
}

void GEImage::Scale2x()
{
	SDL_Surface* temp_surface = NULL;
	
	temp_surface = SurfaceScale2x(m_pSurface);
	SDL_FreeSurface(m_pSurface);
	m_pSurface = temp_surface;
	
	temp_surface = SurfaceScale2x(m_pFlipSurface);
	SDL_FreeSurface(m_pFlipSurface);
	m_pFlipSurface = temp_surface;
	
	m_nWidth *= 2;
	m_nHeight *= 2;
}


SDL_Surface* FlipSurface(SDL_Surface* flip_surface)
{
	SDL_Surface* copy_surface = NULL;

	if( flip_surface )
	{
		// This only works for 32 bit pixel format
		if( flip_surface->format->BitsPerPixel == 32 )
		{
			// This surface must be freed by the caller.
			copy_surface = SDL_CreateRGBSurface(flip_surface->flags, flip_surface->w, flip_surface->h,
											flip_surface->format->BitsPerPixel, 
											flip_surface->format->Rmask, 
											flip_surface->format->Gmask, 
											flip_surface->format->Bmask, 
											flip_surface->format->Amask);
											
			Uint32 *source = static_cast<Uint32*>(flip_surface->pixels);
			Uint32 *dest = static_cast<Uint32*>(copy_surface->pixels);

			for(int i = 0; i < flip_surface->h; i++)
			{
				for(int j = 0; j < flip_surface->w; j++)
				{
					dest[ i * flip_surface->w + j ] = source[ (i + 1) * flip_surface->w - j];
				}
			}
		}
	}
		
	return copy_surface;
}

SDL_Surface* SurfaceScale2x(SDL_Surface* surface)
{
	if( surface )
	{
		SDL_Surface* copy_surface = NULL;
				
		// This surface must be freed by the caller.
		copy_surface = SDL_CreateRGBSurface(surface->flags, surface->w * 2, surface->h * 2,
										surface->format->BitsPerPixel, 
										surface->format->Rmask, 
										surface->format->Gmask, 
										surface->format->Bmask, 
										surface->format->Amask);
										
		Uint32 *source = static_cast<Uint32*>(surface->pixels);
		Uint32 *dest = static_cast<Uint32*>(copy_surface->pixels);
		
		int index;
		int A, B, C, D, E, F, G, H, I;
		int E0, E1, E2, E3;
		
		for(int i = 0; i < surface->h; i++)
		{
			for(int j = 0; j < surface->w; j++)
			{
				index = i * surface->w + j;
				
				/*
				 * ABC
				 * DEF
				 * GHI				
				 */
				
				E = index;
				B = (i == 0) ? E : E - surface->w;
				D = (j == 0) ? E : E - 1 ;
				F = (j == surface->w - 1) ? E : E + 1;
				H = (i == surface->h - 1) ? E : E + surface->w;
				A = (i == 0 && j == 0) ? E : (i == 0 && j != 0) ? B : ( i != 0 && j == 0) ? D : E - 1 - surface->w;
				C = (i == 0 && j == surface->w - 1) ? E : (i != 0 && j == surface->w - 1 ) ? B : (i == 0 && j != surface->w - 1) ? F : E + 1 - surface->w;
				G = (i == surface->h - 1 && j == 0) ? E : (i != surface->h - 1 && j == 0 ) ? H : (i == surface->h - 1 && j != 0) ? D : E - 1 + surface->w;
				I = (i == surface->h - 1 && j == surface->w - 1) ? E : (i != surface->h - 1 && j == surface->w - 1) ? H : (i == surface->h - 1 && j != surface->w - 1) ? F : E + 1 + surface->w;
				
				E0 = (i * 2) * copy_surface->w + (j * 2);
				E1 = E0 + 1;
				E2 = (1 + i * 2) * copy_surface->w + (j * 2);
				E3 = E2 + 1;
			
				if (source[B] != source[H] && source[D] != source[F])
				{
					dest[E0] = source[D] == source[B] ? source[D] : source[E];
					dest[E1] = source[B] == source[F] ? source[F] : source[E];
					dest[E2] = source[D] == source[H] ? source[D] : source[E];
					dest[E3] = source[H] == source[F] ? source[F] : source[E];
				}
				else
				{
					dest[E0] = source[E];
					dest[E1] = source[E];
					dest[E2] = source[E];
					dest[E3] = source[E];
				}	
			}
		}
		
		return copy_surface;
	}
}
