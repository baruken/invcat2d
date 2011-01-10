/*
 * Tile Extractor:
 * 
 * Extracts tiles from image.
 * 
 */

#include <iostream>
#include <fstream>

#include "SDL/SDL.h"
#include "GEImage.hpp"
#include "../GEConstants.hpp"
//#include "../GEScreen.hpp"

#define	TE_DEFAULT_TILE_SIZE	16
#define TE_TILE_MEM_SIZE		TE_DEFAULT_TILE_SIZE * TE_DEFAULT_TILE_SIZE
#define	TE_MAX_TILES			512
//#define TE_TOTAL_MEMORY_USAGE	TE_TILE_MEM_SIZE * TE_MAX_TILES * sizeof(int)

int 	raw_tile_map[TE_MAX_TILES][TE_TILE_MEM_SIZE];
int		unique_tile_counter = 0;
int		source_image_width = 0;

void AddToTileMap(int* tile);
bool CompareTile(int* tile1, int* tile2);
void CopyTile(int* source, int* dest);
void ExtractTile(int* source, int* dest, int tile_row, int tile_col);
void InsertTile(int* source, int* dest, int tile_index, int dest_image_width);

using namespace std;

ostream* plane_map = NULL;

int main(int argc, char** argv)
{
	if( argc < 2)
	{
		cout << "Not enough params. Use: \"te_extractor source [dest]\"\n";
		return 1;
	}
	
	SDL_Init( SDL_INIT_EVERYTHING );
	SDL_Surface* video = SDL_SetVideoMode(GE_SCREEN_WIDTH, GE_SCREEN_HEIGHT, GE_SCREEN_BPP, GE_SCREEN_FLAGS);
	
	GEImage* tile_source = new GEImage(argv[1]);
	
	if( (tile_source->GetWidth() % TE_DEFAULT_TILE_SIZE) || (tile_source->GetHeight() % TE_DEFAULT_TILE_SIZE) )
	{
		cout << "Image size not divisible by " << TE_DEFAULT_TILE_SIZE << ".\n";
		return 2;
	}
	
	int h_tiles = tile_source->GetWidth() / TE_DEFAULT_TILE_SIZE;
	int v_tiles = tile_source->GetHeight() / TE_DEFAULT_TILE_SIZE;
	int total_tiles = h_tiles * v_tiles;
	
	cout << "Image size: " << tile_source->GetHeight() << " x " << tile_source->GetWidth() << "\n";
	cout << "Using tile size " << TE_DEFAULT_TILE_SIZE << " x " << TE_DEFAULT_TILE_SIZE << "\n";
	cout << "Total blocks to be processed: " << total_tiles << "\n";
	cout << "Maximum unique blocks extracted: " << TE_MAX_TILES << "\n";
	
	plane_map = new ofstream("plane_map.txt", ios::out);
	*plane_map << h_tiles << ", " << v_tiles << "\n";
	
	int* source = static_cast<int*>(tile_source->GetSurface()->pixels);
	int temp[TE_TILE_MEM_SIZE];
	source_image_width = tile_source->GetWidth();
	
	for(int i = 0; i < v_tiles; i++)
	{
		for(int j = 0; j < h_tiles; j++)
		{
			ExtractTile(source, temp, i, j);
			AddToTileMap(temp);
		}
	}
	
	cout << "Unique blocks extracted: " << unique_tile_counter << "\n";
	
	SDL_Surface* tile_map = SDL_CreateRGBSurface(video->flags, unique_tile_counter * TE_DEFAULT_TILE_SIZE, TE_DEFAULT_TILE_SIZE,
											video->format->BitsPerPixel, 
											video->format->Rmask, 
											video->format->Gmask, 
											video->format->Bmask, 
											video->format->Amask);
	int *tile_map_pixels = static_cast<int*>(tile_map->pixels);

	for(int i = 0; i < unique_tile_counter; i++)
	{
		InsertTile(raw_tile_map[i], tile_map_pixels, i, unique_tile_counter * TE_DEFAULT_TILE_SIZE);
	}
	
	if( argc > 2 )
	{
		cout << "Saving tile map to file: " << argv[2] << "\n";
		SDL_SaveBMP(tile_map, argv[2]);
	}
	else
	{
		cout << "Saving tile map to file: tilemap.bmp\n";
		SDL_SaveBMP(tile_map, "tilemap.bmp");
	}
	SDL_FreeSurface(tile_map);
	
	delete plane_map;
}

void ExtractTile(int* source, int* dest, int tile_row, int tile_col)
{
	// tile size = 16, width = 1792
	int base = TE_DEFAULT_TILE_SIZE * ( source_image_width * tile_row + tile_col);
	
	for(int i = 0; i < TE_DEFAULT_TILE_SIZE; i++)
	{
		for(int j = 0; j < TE_DEFAULT_TILE_SIZE; j++)
		{
			int dest_index = i * TE_DEFAULT_TILE_SIZE + j;
			int source_index = base + i * source_image_width + j;
			dest[dest_index] = source[source_index];
		}
	}
}

void InsertTile(int* source, int* dest, int tile_index, int dest_image_width)
{
	int base = TE_DEFAULT_TILE_SIZE * tile_index;
	
	for(int i = 0; i < TE_DEFAULT_TILE_SIZE; i++)
	{
		for(int j = 0; j < TE_DEFAULT_TILE_SIZE; j++)
		{
			int source_index = i * TE_DEFAULT_TILE_SIZE + j;
			int dest_index = base + i * dest_image_width + j;
			dest[dest_index] = source[source_index];
		}
	}	
}

bool CompareTile(int* tile1, int* tile2)
{
	bool identic = true;
	
	for(int i = 0; i < TE_DEFAULT_TILE_SIZE; i++)
	{
		for(int j = 0; j < TE_DEFAULT_TILE_SIZE; j++)
		{
			identic &= (tile1[i*TE_DEFAULT_TILE_SIZE + j] == tile2[i*TE_DEFAULT_TILE_SIZE + j]);
		}
		if( !identic ) break;
	}
	
	return identic;
}

void AddToTileMap(int* tile)
{
	if( unique_tile_counter == 0 )
	{
		CopyTile(tile, raw_tile_map[unique_tile_counter]);
		unique_tile_counter++;
	}
	else if( unique_tile_counter == TE_MAX_TILES )
	{
		// do nothing
	}
	else
	{
		int i;
		bool match = false;
		for(i = 0; i < unique_tile_counter; i++)
		{
			match = CompareTile(tile, raw_tile_map[i]);
			if( match )	break;
		}
		
		if( !match )
		{
			CopyTile(tile, raw_tile_map[unique_tile_counter]);
			unique_tile_counter++;
		}
		
		(*plane_map) << i << ", ";
	}
}

void CopyTile(int* source, int* dest)
{
	for(int i = 0; i < TE_DEFAULT_TILE_SIZE; i++)
	{
		for(int j = 0; j < TE_DEFAULT_TILE_SIZE; j++)
		{
			dest[i*TE_DEFAULT_TILE_SIZE + j] = source[i*TE_DEFAULT_TILE_SIZE + j];
		}
	}
}

