#include "GEPlaneMap.hpp"

GEPlaneMap::GEPlaneMap():
m_nWidth(0), m_nHeight(0), m_nTileSize(0), m_nTiles(0), m_nTotalPlaneTiles(0), m_pSurface(NULL), m_nPixelHeight(0), m_nPixelWidth(0)
{
	std::cout << "GEPlaneMap constructor.\n";
}

GEPlaneMap::~GEPlaneMap()
{
	std::cout << "GEPlaneMap destructor.\n";
	
	ClearTileSet();
	
	if( m_pSurface )
	{
		SDL_FreeSurface(m_pSurface);
	}
}

void GEPlaneMap::BuildPlane()
{
	std::cout << "Building Plane:\n";
	
	// TODO: enable partial map building to enable less memory usage
	if( m_pSurface )
	{
		SDL_FreeSurface(m_pSurface);
	}
	
	SDL_Surface* video = SDL_GetVideoSurface();
	m_nPixelHeight = m_nHeight * m_nTileSize;
	m_nPixelWidth = m_nWidth * m_nTileSize;
	
	std::cout << "Plane pixel width = " << m_nPixelWidth << " (in tiles = " << m_nWidth << ")\n";
	std::cout << "Plane pixel height = " << m_nPixelHeight << " (in tiles = " << m_nHeight << ")\n";
	
	m_pSurface = SDL_CreateRGBSurface(video->flags, m_nPixelWidth, m_nPixelHeight, video->format->BitsPerPixel, 
									video->format->Rmask, 
									video->format->Gmask, 
									video->format->Bmask, 
									video->format->Amask);
	if( m_pSurface )
	{
		std::cout << "Plane surface allocated.\n";
	}
	else
	{
		std::cout << "Failed allocating plane surface.\n";
	}

	SDL_Rect	cursor;
	cursor.x = 0;
	cursor.y = 0;
	
	for(int i = 0; i < m_nHeight; i++)
	{
		for(int j = 0; j < m_nWidth; j++)
		{
			SDL_BlitSurface(m_pTiles[m_pPlaneMap[i][j]]->GetSurface(), NULL, m_pSurface, &cursor);
			cursor.x += m_nTileSize;
		}
		cursor.x = 0;
		cursor.y += m_nTileSize;
	}
	
	// debug only:
	//SDL_SaveBMP(m_pSurface, "planebuild.bmp");
}

void GEPlaneMap::LoadPlaneMap(const char* file)
{
	std::ifstream 	planemap_file(file);
	std::string		input;

	planemap_file >> input;
	m_nWidth = atoi(input.c_str());
	
	if( m_nWidth > GE_PLANEMAP_MAX_WIDTH ) m_nWidth = GE_PLANEMAP_MAX_WIDTH;

	planemap_file >> input;
	m_nHeight = atoi(input.c_str());
	
	if( m_nHeight > GE_PLANEMAP_MAX_HEIGHT ) m_nHeight = GE_PLANEMAP_MAX_HEIGHT;
		
	m_nTotalPlaneTiles = m_nHeight * m_nWidth;
	
	for(int i = 0; i < m_nHeight; i++)
	{
		for(int j = 0; j < m_nWidth; j++)
		{
			planemap_file >> input;
			m_pPlaneMap[i][j] = atoi(input.c_str());
		}
	}
}

void GEPlaneMap::ClearPlaneMap()
{
	for(int i = 0; i < m_nHeight; i++)
	{
		for(int j = 0; j < m_nWidth; j++)
		{
			m_pPlaneMap[i][j] = 0;
		}
	}
	m_nHeight = 0;
	m_nWidth = 0;
	m_nTotalPlaneTiles = 0;
}

void GEPlaneMap::LoadTileSet(const char* file)
{
	std::cout << "Loading Tile Set from " << file << "...\n";
	// There is a map already loaded, clear it.
	ClearTileSet();
	
	GEImage* tile_map = new GEImage(file);
	m_nTileSize = tile_map->GetHeight();
	
	m_nTiles = tile_map->GetWidth() / m_nTileSize;
	
	// Limit tile loading
	if( m_nTiles > GE_PLANEMAP_MAX_TILES ) m_nTiles = GE_PLANEMAP_MAX_TILES;
	
	std::cout << "Tiles to be loaded: " << m_nTiles << "\n";
	
	for(int i = 0; i < m_nTiles; i++ )
	{
//		std::stringstream file;
//		file << "tile";
		m_pTiles[i] = new GEImage(tile_map, m_nTileSize, m_nTileSize, i);
//		file << i << ".bmp";
//		SDL_SaveBMP(m_pTiles[i]->GetSurface(), file.str().c_str());
	}
	
	delete tile_map;
}

void GEPlaneMap::ClearTileSet()
{
	if( m_nTiles )
	{
		for(int i = 0; i < m_nTiles; i++)
		{
			delete m_pTiles[i];
		}
		m_nTiles = 0;
	}	
}

void GEPlaneMap::Scale2x()
{
	// Scale2x only work before building the plane
	if( m_nTiles && !m_pSurface)
	{
		m_nTileSize *= 2;
		
		// TODO: check size limits!
				
		for(int i = 0; i < m_nTiles; i++)
		{
			m_pTiles[i]->Scale2x();
		}
	}
}

SDL_Surface* GEPlaneMap::GetSurface()
{
	return m_pSurface;
}

int GEPlaneMap::GetPixelHeight()
{
	return m_nPixelHeight;
}

int GEPlaneMap::GetPixelWidth()
{
	return m_nPixelWidth;
}

int GEPlaneMap::GetTileSize()
{
	return m_nTileSize;
}
