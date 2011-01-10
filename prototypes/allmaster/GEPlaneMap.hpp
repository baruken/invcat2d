#ifndef _GE_PLANEMAP_HEADER_
#define	_GE_PLANEMAP_HEADER_

#include <iostream>
#include <fstream>
#include <sstream>
#include "GEImage.hpp"
#include "GEConstants.hpp"

class GEPlaneMap
{
	public:
		GEPlaneMap();
		~GEPlaneMap();
		
		void			LoadPlaneMap(const char* file);
		void			ClearPlaneMap();
		void			LoadTileSet(const char* file);
		void			ClearTileSet();
		
		void			BuildPlane();
		
		SDL_Surface*	GetSurface();
		int				GetPixelHeight();
		int				GetPixelWidth();
		int				GetTileSize();
		
		void			Scale2x();
		
	private:
		GEImage*		m_pTiles[GE_PLANEMAP_MAX_TILES];
		int				m_pPlaneMap[GE_PLANEMAP_MAX_HEIGHT][GE_PLANEMAP_MAX_WIDTH];
		SDL_Surface*	m_pSurface;
		
		int				m_nHeight;
		int				m_nWidth;
		int				m_nTileSize;
		int				m_nTiles;
		int				m_nTotalPlaneTiles;
		
		int				m_nPixelHeight;
		int				m_nPixelWidth;
};

#endif // _GE_PLANEMAP_HEADER_
