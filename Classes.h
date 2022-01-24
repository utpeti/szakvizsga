#pragma once
#include <iostream>
#include <string>
#include "../SDL2/include/SDL.h"
#include "../SDL2/SDL2_Image/include/SDL_image.h"
#include "../SDL2/SDL2_mixer/include/SDL_mixer.h"
#include "../SDL2/SDL2_ttf/include/SDL_ttf.h"
#include "functions.h"
/*#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>*/

extern const int BUTTON_WIDTH;
extern const int BUTTON_HEIGHT;

extern SDL_Window* Window;
extern SDL_Renderer* Renderer;
extern bool stage1, mainMenu;

enum ButtonFunction : Uint8
{
	BUTTONSTART,
};


class LBackground
{
public:

	LBackground();

	~LBackground();

	void free();

	bool loadFromFile(std::string path);

	void render(int x, int y, SDL_Rect* clip, SDL_RendererFlip flip = SDL_FLIP_NONE);

private:

	SDL_Texture* mTexture;

	int mWidth;
	int mHeight;
};


///oroklodes??
class LButtonPosition
{
public:
	LButtonPosition();

	void setPosition(int x, int y);

	int getPosx();

	int getPosy();

	void HandleEvent(SDL_Event* e);

	void buttonEvent();

	int index;

private:
	SDL_Point LPosition;
};

LBackground::LBackground()
{
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LBackground::~LBackground()
{
	free();
}

void LBackground::free()
{
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0; 
		mHeight = 0;
	}
}

bool LBackground::loadFromFile(std::string path)
{
	//get rid of pre existing texture
	free();

	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		
		return false;
	}

	newTexture = SDL_CreateTextureFromSurface(Renderer, loadedSurface);
	if (newTexture == NULL)
	{
		return false;
	}

	mWidth = loadedSurface->w;
	mHeight = loadedSurface->h;

	SDL_FreeSurface(loadedSurface);

	mTexture = newTexture;
	return true;
}

void LBackground::render(int x, int y, SDL_Rect* clip, SDL_RendererFlip flip)
{

	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	if (clip != NULL)
	{
		renderQuad.w = (*clip).w;
		renderQuad.h = (*clip).h;
		
	}
	SDL_RenderCopy(Renderer, mTexture, clip, &renderQuad);
}

LButtonPosition::LButtonPosition()
{
	LPosition.x = LPosition.y = 0;
	index = 0;
}

void LButtonPosition::setPosition(int x, int y)
{
	LPosition.x = x;
	LPosition.y = y;
}

void LButtonPosition::HandleEvent(SDL_Event* e)
{
	//if mouse event happened
	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
	{
		//get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);

		//check if mouse is in button//

		bool inside = true;

		//mouse is right of the button
		if (x < LPosition.x)
		{
			inside = false;
		}
		//mosue is right of the button
		else if (x > LPosition.x + BUTTON_WIDTH)
		{
			inside = false;
		}
		//mouse is above button
		else if (y < LPosition.y)
		{
			inside = false;
		}
		//mouse is below the button
		else if (y > LPosition.y + BUTTON_HEIGHT)
		{
			inside = false;
		}
		
		if (inside)
		{
			if (e->type == SDL_MOUSEBUTTONDOWN)
			{
				buttonEvent();
			}
		}

	}
}

void LButtonPosition::buttonEvent()
{
	if (index == BUTTONSTART)
	{
		mainMenu = false;
		stage1 = true;
	}
}

int LButtonPosition::getPosx()
{
	return LPosition.x;
}

int LButtonPosition::getPosy()
{
	return LPosition.y;
}
