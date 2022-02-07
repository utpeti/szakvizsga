#define SDL_MAIN_HANDLED
#include <iostream>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "functions.h"
#include "Classes.h"
#include <iostream>

using namespace std;


//#undef main

const int SPEED = 5;

extern SDL_Window* Window;
extern SDL_Renderer* Renderer;
extern LButtonPosition buttons[5];
extern bool b_mainMenu, b_stage0, b_stage1, b_stage2, dia[10];

int main()
{
	b_mainMenu = true;
	if (init())
	{
		if (loadMedia())
		{

			bool quit = false;
			SDL_Event e;

			while (!quit)
			{
				while (SDL_PollEvent(&e) != 0)
				{
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}

					if (b_mainMenu)
					{
						buttons[0].HandleEvent(&e);
					}
						if (b_stage1)
					{
						if (e.type == SDL_KEYDOWN)
						{
							changeDialogStage1();
						}

					}

				}

				///Cleaning
				SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
				SDL_RenderClear(Renderer);

				///Main Menu
				//To do: gomb aktivalas, hatter, szoveg
				if (b_mainMenu)
				{
					mainMenu.render(0, 0, NULL);
					buttons[0].render(buttons[0].getPosx(), buttons[0].getPosy(), NULL);
					mainMenuText.render(SCREEN_WIDTH / 2 - mainMenuText.getWidth() / 2, 0, NULL);
				}
				else if(b_stage0)
				{
					//transition
					if (darkness > 0)
					{
						darkness -= SPEED;
						blackTrans.setAlpha(darkness);
					}

					//textures
					kastely.renderAnimation(0, 0, NULL);
					blackTrans.render(0, 0, NULL);
					textBox.render(0, 0, NULL);
					
				}
				else if (b_stage1)
				{
					//transition
					if (darkness > 0)
					{
						darkness -= SPEED;
						blackTrans.setAlpha(darkness);
					}

					//textures
					kastely_belso.render(0, 0, NULL);
					textBox.render(0, 0, NULL);
					blackTrans.render(0, 0, NULL);

					//text
					//transition
					if (dia[0])
					{
						if (textTransition1.w < textBoxtext1.getWidth())
							textTransition1.w += SPEED;
						//else if() - > rendereli a kovi sort fokozatosan a masik utan
						else if (textTransition2.w < textBoxtext2.getWidth())
							textTransition2.w += SPEED;
						else if (textTransition3.w < textBoxtext3.getWidth())
							textTransition3.w += SPEED;
					}
					else if (dia[1])
					{
						if (textTransition1.w < textBoxtext1.getWidth())
							textTransition1.w += SPEED;
					}
					else if (dia[2])
					{
						if (textTransition1.w < textBoxtext1.getWidth())
							textTransition1.w += SPEED;
						else if (textTransition2.w < textBoxtext2.getWidth())
							textTransition2.w += SPEED;
					}
					else if (dia[3])
					{
						if (textTransition1.w < textBoxtext1.getWidth())
							textTransition1.w += SPEED;

					}
					else if (dia[4])
					{
						if (textTransition1.w < textBoxtext1.getWidth())
							textTransition1.w += SPEED;
						else if (textTransition2.w < textBoxtext2.getWidth())
							textTransition2.w += SPEED;
						else if (textTransition3.w < textBoxtext3.getWidth())
							textTransition3.w += SPEED;
					}

					//text rendering
					if (dia[0])
					{
						textBoxtext1.render(300, 530, &textTransition1);
						textBoxtext2.render(300, 545, &textTransition2);
						textBoxtext3.render(300, 560, &textTransition3);
					}
					else if (dia[1])
					{
						textBoxtext1.render(300, 530, &textTransition1);
					}
					else if (dia[2])
					{
						textBoxtext1.render(300, 530, &textTransition1);
						textBoxtext2.render(300, 545, &textTransition2);
					}
					else if (dia[3])
					{
						textBoxtext1.render(300, 530, &textTransition1);
					}
					else if (dia[4])
					{
						textBoxtext1.render(300, 530, &textTransition1);
						textBoxtext2.render(300, 545, &textTransition2);
						textBoxtext3.render(300, 560, &textTransition3);
					}

				}
				//else if


				SDL_RenderPresent(Renderer);




			}
		}
	}


}
