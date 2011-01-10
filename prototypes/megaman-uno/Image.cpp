#include "Image.hpp"

SDL_Surface*	SDL_CreateSurface(int width, int height)
{
	SDL_Surface* result = NULL;
	SDL_Surface* video = SDL_GetVideoSurface();
	
	result = SDL_CreateRGBSurface(	video->flags, width, height,
									video->format->BitsPerPixel, 
									video->format->Rmask, 
									video->format->Gmask, 
									video->format->Bmask, 
									video->format->Amask);
									
	return result;
}

SDL_Surface*	SDL_SurfaceFlip(SDL_Surface* pSurface)
{
	SDL_Surface* flip = NULL;

	if( pSurface )
	{
		// This only works for 32 bit pixel format
		if( pSurface->format->BitsPerPixel == 32 )
		{
			// This surface must be freed by the caller.
			flip = SDL_CreateRGBSurface(pSurface->flags, pSurface->w, pSurface->h,
										pSurface->format->BitsPerPixel, 
										pSurface->format->Rmask, 
										pSurface->format->Gmask, 
										pSurface->format->Bmask, 
										pSurface->format->Amask);
											
			assert( flip != NULL );
											
			Uint32 *source = static_cast<Uint32*>(pSurface->pixels);
			Uint32 *dest = static_cast<Uint32*>(flip->pixels);

			for(int i = 0; i < pSurface->h; i++)
			{
				for(int j = 0; j < pSurface->w; j++)
				{
					dest[ i * pSurface->w + j ] = source[ (i + 1) * pSurface->w - j];
				}
			}
		}
	}
		
	return flip;
}

SDL_Surface*	SDL_SurfaceScale2x(SDL_Surface* pSurface)
{
	SDL_Surface* scale2x = NULL;	
	
	if( pSurface )
	{				
		// This surface must be freed by the caller.
		scale2x = SDL_CreateRGBSurface( pSurface->flags, pSurface->w * 2, pSurface->h * 2,
										pSurface->format->BitsPerPixel, 
										pSurface->format->Rmask, 
										pSurface->format->Gmask, 
										pSurface->format->Bmask, 
										pSurface->format->Amask);
										
		assert( scale2x != NULL );
										
		Uint32 *source = static_cast<Uint32*>(pSurface->pixels);
		Uint32 *dest = static_cast<Uint32*>(scale2x->pixels);
		
		int index;
		int A, B, C, D, E, F, G, H, I;
		int E0, E1, E2, E3;
		
		for(int i = 0; i < pSurface->h; i++)
		{
			for(int j = 0; j < pSurface->w; j++)
			{
				index = i * pSurface->w + j;
				
				/*
				 * ABC
				 * DEF
				 * GHI				
				 */
				
				E = index;
				B = (i == 0) ? E : E - pSurface->w;
				D = (j == 0) ? E : E - 1 ;
				F = (j == pSurface->w - 1) ? E : E + 1;
				H = (i == pSurface->h - 1) ? E : E + pSurface->w;
				A = (i == 0 && j == 0) ? E : (i == 0 && j != 0) ? B : ( i != 0 && j == 0) ? D : E - 1 - pSurface->w;
				C = (i == 0 && j == pSurface->w - 1) ? E : (i != 0 && j == pSurface->w - 1 ) ? B : (i == 0 && j != pSurface->w - 1) ? F : E + 1 - pSurface->w;
				G = (i == pSurface->h - 1 && j == 0) ? E : (i != pSurface->h - 1 && j == 0 ) ? H : (i == pSurface->h - 1 && j != 0) ? D : E - 1 + pSurface->w;
				I = (i == pSurface->h - 1 && j == pSurface->w - 1) ? E : (i != pSurface->h - 1 && j == pSurface->w - 1) ? H : (i == pSurface->h - 1 && j != pSurface->w - 1) ? F : E + 1 + pSurface->w;
				
				E0 = (i * 2) * scale2x->w + (j * 2);
				E1 = E0 + 1;
				E2 = (1 + i * 2) * scale2x->w + (j * 2);
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
	}
	
	return scale2x;
}


Image::Image():
m_pImage(NULL), m_pImageFlip(NULL)
{
	#ifdef DEBUG
	std::cout << "Image() constructor: " << this << std::endl;
	#endif
	
	SetPosition(0, 0);
}

Image::Image(const char* file):
m_pImage(NULL), m_pImageFlip(NULL)
{
	#ifdef DEBUG
	std::cout << "Image(file) constructor: " << this << std::endl;
	#endif
	
	SetPosition(0, 0);
	Load(file);
}

Image::Image(const Image& rhs):
m_pImage(NULL), m_pImageFlip(NULL)
{
	#ifdef DEBUG
	std::cout << "Image copy constructor: " << this << std::endl;
	#endif
	
	if( rhs.m_pImage != NULL ) m_pImage = SDL_DisplayFormat(rhs.m_pImage);
	if( rhs.m_pImageFlip != NULL ) m_pImageFlip = SDL_DisplayFormat(rhs.m_pImageFlip);
	m_sPosition.x = rhs.m_sPosition.x;
	m_sPosition.y = rhs.m_sPosition.y;
}

Image::Image(Image* pImage, SDL_Rect& clip_rect):
m_pImage(NULL), m_pImageFlip(NULL)
{
	#ifdef DEBUG
	std::cout << "Image(Image*) constructor: " << this << std::endl;
	#endif
	
	m_pImage = SDL_CreateSurface(clip_rect.w, clip_rect.h);
										
	assert( m_pImage != NULL );
		
	SDL_BlitSurface(pImage->GetSurface(), &clip_rect, m_pImage, NULL);
	SetPosition(0, 0);
}

Image::~Image()
{
	#ifdef DEBUG
	std::cout << "Image destructor: " << this << std::endl;
	#endif
	
	FreeMemory();
}

Image& Image::operator =(const Image& rhs)
{
	if( &rhs != this )
	{
		FreeMemory(); // to avoid memory leak
				
		if( rhs.m_pImage != NULL ) m_pImage = SDL_DisplayFormat(rhs.m_pImage);
		if( rhs.m_pImageFlip != NULL ) m_pImageFlip = SDL_DisplayFormat(rhs.m_pImageFlip);
		m_sPosition.x = rhs.m_sPosition.x;
		m_sPosition.y = rhs.m_sPosition.y;
	}
	return *this;
}

Image& Image::operator +=(const Image& rhs)
{
	// This operator composes one image based on the sum of two images
	if( &rhs != this )
	{
		SDL_Rect rhs_position; // this->(x,y) is used as reference
		rhs_position.x = rhs.m_sPosition.x - this->GetPosition()->x;
		rhs_position.y = rhs.m_sPosition.y - this->GetPosition()->y;
		rhs_position.w = rhs.m_pImage->w;
		rhs_position.h = rhs.m_pImage->h;
		
		SDL_Surface* lhs_copy = SDL_DisplayFormat(m_pImage);
				
		int nWidth, nHeight;		
				
		if( rhs_position.x < 0 )
		{
			if( rhs_position.x + rhs_position.w > this->GetWidth() )
			{
				nWidth = -rhs_position.x + rhs_position.w;
			}
			else
			{
				nWidth = -rhs_position.x + this->GetWidth();
			}
		}
		else
		{
			if( rhs_position.x + rhs_position.w > this->GetWidth() )
			{
				nWidth = rhs_position.x + rhs_position.w;
			}
			else
			{
				nWidth = this->GetWidth();
			}
		}

		if( rhs_position.y < 0 )
		{
			if( rhs_position.y + rhs_position.h > this->GetHeight() )
			{
				nHeight = -rhs_position.y + rhs_position.h;
			}
			else
			{
				nHeight = -rhs_position.y + this->GetHeight();
			}
		}
		else
		{
			if( rhs_position.y + rhs_position.h > this->GetHeight() )
			{
				nHeight = rhs_position.y + rhs_position.h;
			}
			else
			{
				nHeight = this->GetHeight();
			}
		}		
		
		SDL_FreeSurface(m_pImage);
		m_pImage = SDL_CreateSurface(nWidth, nHeight);
		
		SDL_Rect lhs_position;
		lhs_position.x = 0;
		lhs_position.y = 0;
		lhs_position.w = nWidth;
		lhs_position.h = nHeight;
		
		if( rhs_position.x < 0 )
		{
			lhs_position.x = -rhs_position.x;
			rhs_position.x = 0;
		}
		
		if( rhs_position.y < 0 )
		{
			lhs_position.y = -rhs_position.y;
			rhs_position.y = 0;
		}
		
		SDL_BlitSurface(lhs_copy, NULL, m_pImage, &lhs_position);
		SDL_BlitSurface(rhs.m_pImage, NULL, m_pImage, &rhs_position);
		
		SDL_FreeSurface(lhs_copy);
	}
	return *this;
}

const Image& Image::operator +(const Image& rhs)
{
	return Image(*this) += rhs;
}

bool Image::operator ==(const Image& rhs)
{
	bool bResult = true;
	if( &rhs != this )
	{
		if( (m_pImage->w == rhs.m_pImage->w) && (m_pImage->h == rhs.m_pImage->h) )
		{
			Uint32* source = static_cast<Uint32*>(m_pImage->pixels);
			Uint32* dest = static_cast<Uint32*>(rhs.m_pImage->pixels);
			
			for(int i = 0; i < m_pImage->h; i++)
			{
				for(int j = 0; j < m_pImage->w; j++)
				{
					bResult = (source[i*m_pImage->w + j] == dest[i*m_pImage->w + j]);
					if( !bResult ) break;
				}
				
				if( !bResult ) break;
			}
		}
		else
		{
			bResult = false;
		}
	}
	
	return bResult;
}

void Image::Load(const char* file)
{
	FreeMemory();

	SDL_Surface* image = IMG_Load(file);
	assert( image != NULL );
	
	m_pImage = SDL_DisplayFormat(image);
	SDL_FreeSurface(image);
	
	assert( m_pImage != NULL );
}

void Image::FreeMemory()
{
	if( m_pImage ) SDL_FreeSurface(m_pImage);
	if( m_pImageFlip ) SDL_FreeSurface(m_pImageFlip);	
	
	m_pImage = NULL;
	m_pImageFlip = NULL;
}

int Image::GetHeight()
{
	return m_pImage->h;
}

int Image::GetWidth()
{
	return m_pImage->w;
}

SDL_Rect* Image::GetPosition()
{
	return &m_sPosition;
}

void Image::SetPosition(int x, int y)
{
	m_sPosition.x = x;
	m_sPosition.y = y;
}

SDL_Surface* Image::GetSurface()
{
	return m_pImage;
}

SDL_Surface* Image::GetSurfaceFlip()
{
	if( m_pImageFlip == NULL ) FlipImage();
	return m_pImageFlip;
}

void Image::FlipImage()
{
	if( (m_pImageFlip == NULL) && (m_pImage != NULL) )
	{
		m_pImageFlip = SDL_SurfaceFlip(m_pImage);
	}
}

void Image::Scale2x()
{
	SDL_Surface* scale2x = NULL;
	
	if( m_pImage != NULL )
	{
		scale2x = SDL_SurfaceScale2x(m_pImage);
		SDL_FreeSurface(m_pImage);
		m_pImage = scale2x;
	}
	
	if( m_pImageFlip != NULL )
	{
		scale2x = SDL_SurfaceScale2x(m_pImageFlip);
		SDL_FreeSurface(m_pImageFlip);
		m_pImageFlip = scale2x;
	}
}
