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
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

extern SDL_Window* Window;
extern SDL_Renderer* Renderer;
extern Mix_Music* Oblivion;
extern bool b_stage0, b_mainMenu;
extern bool dia[20];
extern Uint8 darkness;
extern TTF_Font* menuFont;
extern void loadTextsStage0();
extern int Time();
extern int startTime;


enum ButtonFunction : Uint8
{
	BUTTONSTART,
};


class LImage
{
public:

	LImage();

	~LImage();

	void free();

	bool loadFromFile(std::string path);

	bool loadFromRenderedText(std::string textureText, SDL_Color textColor, TTF_Font* Font);

	void render(int x, int y, SDL_Rect* clip, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void renderAnimation(int x, int y, SDL_Rect* clip, SDL_RendererFlip flip = SDL_FLIP_NONE);

	void setAlpha(Uint8 alpha);

	int getWidth();

	int getHeight();

protected:

	SDL_Texture* mTexture;

	int mWidth;
	int mHeight;
};


///oroklodes??
class LButtonPosition : public LImage
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

LImage::LImage()
{
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LImage::~LImage()
{
	free();
}

void LImage::free()
{
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0; 
		mHeight = 0;
	}
}

bool LImage::loadFromFile(std::string path)
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

bool LImage::loadFromRenderedText(std::string textureText, SDL_Color textColor, TTF_Font* Font)
{
	//delete preexisting texture
	free();

	//SDL_Surface* textSurface = TTF_RenderUTF8_Solid(Font, textureText.c_str(), textColor);
	SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped(Font, textureText.c_str(), textColor, 1280);
	if (textSurface == NULL)
	{
		std::cout << TTF_GetError() << "\n";
		return false;
	}
	mTexture = SDL_CreateTextureFromSurface(Renderer, textSurface);
	if (mTexture == NULL)
	{
		std::cout << SDL_GetError() << "\n";
		return false;
	}

	mWidth = textSurface->w;
	mHeight = textSurface->h;

	SDL_FreeSurface(textSurface);
	
	return true;
}

void LImage::render(int x, int y, SDL_Rect* clip, SDL_RendererFlip flip)
{

	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	if (clip != NULL)
	{
		renderQuad.w = (*clip).w;
		renderQuad.h = (*clip).h;
		
	}
	SDL_RenderCopy(Renderer, mTexture, clip, &renderQuad);
}

void LImage::setAlpha(Uint8 alpha)
{
	SDL_SetTextureAlphaMod(mTexture, alpha);//set the opacity of the texture from 0 to 255
}

int LImage::getWidth()
{
	return mWidth;
}

int LImage::getHeight()
{
	return mHeight;
}

void LImage::renderAnimation(int x, int y, SDL_Rect* clip, SDL_RendererFlip flip)
{

	SDL_Rect renderQuad = { x, y, mWidth, mHeight };
	if (clip != NULL)
	{
		renderQuad.w = (*clip).w;
		renderQuad.h = (*clip).h;
	}
	int xd = Time() * 8 / SCREEN_WIDTH; //8-at modositani is lehet
	if (xd > -255)
	{
		renderQuad.x = xd;
		SDL_RenderCopy(Renderer, mTexture, clip, &renderQuad);//itt oldd meg, hogy rendereljen tovabb, csak ne mozogjon
	}
	else
	{
		renderQuad.x = SCREEN_WIDTH - mWidth;
		SDL_RenderCopy(Renderer, mTexture, clip, &renderQuad);
	}

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
			SDL_SetTextureColorMod(mTexture, 220, 190, 200);
			if (e->type == SDL_MOUSEBUTTONDOWN)
			{
				buttonEvent();
			}
		}
		else
		{
			SDL_SetTextureColorMod(mTexture, 255, 255, 255);
		}

	}
}

void LButtonPosition::buttonEvent()
{
	if (index == BUTTONSTART)
	{
		darkness = 255; //teljesen fekete lesz a kepernyo -> transition
		b_mainMenu = false;
		b_stage0 = true;
		for (int i = 0; i < 2; ++i)//ne toltse be meg a dialogokat csak az elsot
			dia[i] = false;
		dia[0] = true; //az elso dialogot mar toltheti is be
		///loading in stage0's textBoxtexts;
		loadTextsStage0();
		Mix_PlayMusic(Oblivion, -1);
		startTime = SDL_GetTicks();
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

