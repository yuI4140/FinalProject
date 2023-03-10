#include <fmt/core.h>
#include <string.h>
#include <string>
#include "raylib.h"
#include "colors.h"
#include <random>
#include <fstream>
#include<iostream>
#include <cstdlib>
bool _menu=false;
int getRandom(int min, int max)
{
	std::random_device rd;
	std::uniform_int_distribution<int> uni(min, max);
	return uni(rd);
}
int points = 0;
static constexpr int ee_BadFoods = 3;
static constexpr int ne_BadFoods = 5;
static constexpr int hrde_BadFoods = 7;
int fdWidth=20, fdheight=20;
int attempts = 3;
const char* cmd = "D:\\Greyber\\GameDEV\\repositories\\FinalProject";
float playerSpeed = 1550.0f;
float hardPlayerSpeed = playerSpeed*1.50f;
float easyPlayerSpeed = playerSpeed/2;
Color to_hex(const char* hex)
{
	int hexValue = (int)strtol(&hex[1], NULL, 16);

	int red = (hexValue >> 16) & 0xFF;
	int green = (hexValue >> 8) & 0xFF;
	int blue = hexValue & 0xFF;

	Color _color_={ red, green, blue, 255 };
	return _color_;
}
auto bgPlay = to_hex(Setcolor::mh_blueGrey[9].c_str());
/*
	void template()
	{
	while (!WindowShouldClose())
	{
	BeginDrawing();
	EndDrawing();
	}
	}
	*/
constexpr int numSlots = 9; 
constexpr int slotSize = 50;
constexpr int inventoryWidth = numSlots * slotSize;
struct Item 
{ 	Texture tex; 
const char* nNName{};
Item() = default;
Item(const char* name)
{
	Image image = LoadImage(name);
	tex = LoadTextureFromImage(image);
	nNName = name;
	UnloadImage(image); // free loaded image data
}
Item(const char* name, Texture Tex)
{
	nNName = name;
	tex = Tex;
}
~Item()
{
	UnloadTexture(tex);
}
};
void Twrite(const std::string& filename, const std::string& content) {
	std::ofstream file(filename);
	if (file.is_open()) {
		file << content;
		file.close();
		std::cout << "File saved successfully!\n";
	}
	else {
		std::cerr << "Unable to open file!\n";
	}
}
void Tread(const std::string& filename) {
	std::ifstream file(filename);
	if (file.is_open()) {
		std::string content;
		while (std::getline(file, content)) {
			std::cout << content << '\n';
		}
		file.close();
	}
	else {
		std::cerr << "Unable to open file!\n";
	}
}
void rankingTable()
{ 	Twrite(".//scores.txt",std::string(TextFormat("%i\n",points)));
while (!WindowShouldClose())
{
	BeginDrawing();

	EndDrawing();
}
}
void GameOver()
{ Rectangle _continue_ = {GetScreenWidth()/2,
GetScreenHeight() / 2,500,50};
bool continueHover = CheckCollisionPointRec(GetMousePosition(),_continue_);
while (!WindowShouldClose())
{ if (IsKeyDown(KEY_R))
{
	CloseWindow();
	system("start .//bin//Release//fp.exe");
}
BeginDrawing();
ClearBackground(to_hex("#1b1b1b"));
DrawText("GAME OVER",GetScreenWidth()/2-200,
         GetScreenHeight() / 2-200,60,RED);
DrawText(TextFormat("SCORE: %i", points),GetScreenWidth()/2-100,
         GetScreenHeight() / 2-100, 50, ORANGE);
DrawRectangleRec(_continue_, BLUE);
DrawText("PRESS <R> TO HOME", _continue_.x + 30,_continue_.y + 15, 20, BLACK);
EndDrawing();
}
}
void nplay()
{ 	auto deltaTime = GetFrameTime();
Rectangle food = {(float)getRandom(0,GetScreenWidth()),0.0f,20.0f,20.0f};
Rectangle badFood = {(float)getRandom(0,GetScreenWidth()),0.0f,20.0f,20.0f};
Rectangle player = {(float)GetScreenWidth()/2.0f,(float)GetScreenHeight()/2.0f,
50.0f,50.0f};
Item bgTex=".//src//KCave.png";
//InitAudioDevice();
//Music music = LoadMusicStream("D://Greyber//Downloads//sht_sell_classic.mp3");
//PlayMusicStream(music);
std::array<Rectangle, ne_BadFoods>badFoods;
for (int i = 0; i < ne_BadFoods; ++i)
{
	badFoods[i] = badFood;
}
DrawTexture(bgTex.tex, 0, 0, WHITE);
	
while (!WindowShouldClose())
{ if (points<0)
{
	points = 0;
}
if (attempts<=0)
{
	GameOver();
}
//UpdateMusicStream(music);
BeginDrawing();
DrawTexture(bgTex.tex, 0, 0, WHITE);
DrawText(TextFormat("SCORE: %i",points),GetScreenWidth()/2,GetScreenHeight()/2+200,
         40, RAYWHITE);
DrawText(TextFormat("attempt: %i",attempts),GetScreenWidth()/2,GetScreenHeight()/2-200,
         40, RAYWHITE);
DrawRectangle(food.x, food.y, food.widths, food.height, BLUE);
for (int i = 0; i < ne_BadFoods; ++i)
{
	DrawRectangle(badFoods[i].x, badFoods[i].y, badFoods[i].widths, badFoods[i].height, RED);
}
to_hex(Setcolor::mh_Red[12].c_str());
ClearBackground(bgPlay);
DrawRectangle(player.x,player.y,player.widths,player.height,RED);
food.y += 300.0f*deltaTime;
for (int i = 0; i < ne_BadFoods; ++i)
{
	badFoods[i].y+=300.0f*deltaTime;
}
EndDrawing();
if (IsKeyDown(KEY_A)) { player.x -= playerSpeed*deltaTime; }
if (IsKeyDown(KEY_D)) { player.x += playerSpeed*deltaTime; }
if (IsKeyDown(KEY_LEFT)) { player.x -= playerSpeed*deltaTime; }
if (IsKeyDown(KEY_RIGHT)) { player.x += playerSpeed*deltaTime; }
if (player.x + player.widths > GetScreenWidth())
{
	player.x = GetScreenWidth() - player.widths;
}
if (player.x < 0)
{
	player.x = 0;
}
if (CheckCollisionRecs(player,food))
{
	Rectangle another = {(float)getRandom(0,GetScreenWidth()),0.0f,20.0f,20.0f};
	food = another;
	++points;
}
for (int i = 0; i < ne_BadFoods; ++i)
{
	if (CheckCollisionRecs(player,badFoods[i]))
	{
		Rectangle another = {(float)getRandom(0,GetScreenWidth()),0.0f,20.0f,20.0f};
		badFoods[i] = another;
		--attempts;
	}
}
if (food.y>=GetScreenHeight())
{
	Rectangle another = {(float)getRandom(0,GetScreenWidth()),0.0f,20.0f,20.0f};
	food = another;
	--attempts;
}
for (int i = 0; i < ne_BadFoods; ++i)
{
	if (badFoods[i].y >= GetScreenHeight())
	{
		Rectangle another = { (float)getRandom(0, GetScreenWidth()), 0.0f, 20.0f, 20.0f };
		badFoods[i] = another;
	} 
}
}
//StopMusicStream(music);
//UnloadMusicStream(music);
//CloseAudioDevice();
}
void hardPlay()
{ 	auto deltaTime = GetFrameTime();
Rectangle food = {(float)getRandom(0,GetScreenWidth()),0.0f,20.0f,20.0f};
Rectangle badFood = {(float)getRandom(0,GetScreenWidth()),0.0f,20.0f,20.0f};
Rectangle player = {(float)GetScreenWidth()/2.0f,(float)GetScreenHeight()/2.0f,
50.0f,50.0f};
std::array<Rectangle, hrde_BadFoods>badFoods;
for (int i = 0; i < hrde_BadFoods; ++i)
{
	badFoods[i] = badFood;
}
while (!WindowShouldClose())
{ if (points<0)
{
	points = 0;
}
if (attempts<=0)
{
	GameOver();
}
BeginDrawing();
DrawText(TextFormat("SCORE: %i",points),GetScreenWidth()/2,GetScreenHeight()/2+200,
         40, RAYWHITE);
DrawText(TextFormat("attempt: %i",attempts),GetScreenWidth()/2,GetScreenHeight()/2-200,
         40, RAYWHITE);
DrawRectangle(food.x, food.y, food.widths, food.height, BLUE);
for (int i = 0; i < hrde_BadFoods; ++i)
{
	DrawRectangle(badFoods[i].x, badFoods[i].y, badFoods[i].widths, badFoods[i].height, RED);
}
to_hex(Setcolor::mh_Red[12].c_str());
ClearBackground(bgPlay);
DrawRectangle(player.x,player.y,player.widths,player.height, RED);
food.y += (300.0f*deltaTime)*2;
for (int i = 0; i < hrde_BadFoods; ++i)
{
	badFoods[i].y += (300.0f*deltaTime)*2;
}
EndDrawing();
if (IsKeyDown(KEY_D)) { player.x += hardPlayerSpeed*deltaTime; }
if (IsKeyDown(KEY_A)) { player.x -= hardPlayerSpeed*deltaTime; }
if (IsKeyDown(KEY_LEFT)) { player.x -= hardPlayerSpeed*deltaTime; }
if (IsKeyDown(KEY_RIGHT)) { player.x += hardPlayerSpeed*deltaTime; }
if (player.x + player.widths > GetScreenWidth())
{
	player.x = GetScreenWidth() - player.widths;
}
if (player.x < 0)
{
	player.x = 0;
}
if (CheckCollisionRecs(player,food))
{
	Rectangle another = {(float)getRandom(0,GetScreenWidth()),0.0f,20.0f,20.0f};
	food = another;
	++points;
}
for (int i = 0; i < hrde_BadFoods; ++i)
{
	if (CheckCollisionRecs(player,badFoods[i]))
	{
		Rectangle another = {(float)getRandom(0,GetScreenWidth()),0.0f,20.0f,20.0f};
		badFoods[i] = another;
		--attempts;
	}
}
if (food.y>=GetScreenHeight())
{
	Rectangle another = {(float)getRandom(0,GetScreenWidth()),0.0f,20.0f,20.0f};
	food = another;
	--attempts;
}
for (int i = 0; i < hrde_BadFoods; ++i)
{
	if (badFoods[i].y >= GetScreenHeight())
	{
		Rectangle another = { (float)getRandom(0, GetScreenWidth()), 0.0f, 20.0f, 20.0f };
		badFoods[i] = another;
	} 
}
}
}
void easyPlay()
{ 	auto deltaTime = GetFrameTime();
Rectangle food = {(float)getRandom(0,GetScreenWidth()),0.0f,20.0f,20.0f};
Rectangle badFood = {(float)getRandom(0,GetScreenWidth()),0.0f,20.0f,20.0f};
Rectangle player = {(float)GetScreenWidth()/2.0f,(float)GetScreenHeight()/2.0f,
50.0f,50.0f};
std::array<Rectangle, ee_BadFoods>badFoods;
for (int i = 0; i < ee_BadFoods; ++i)
{
	badFoods[i] = badFood;
}
while (!WindowShouldClose())
{ if (points<0)
{
	points = 0;
}
if (attempts<=0)
{
	GameOver();
}
BeginDrawing();
DrawText(TextFormat("SCORE: %i",points),GetScreenWidth()/2,GetScreenHeight()/2+200,
         40, RAYWHITE);
DrawText(TextFormat("attempt: %i",attempts),GetScreenWidth()/2,GetScreenHeight()/2-200,
         40, RAYWHITE);
DrawRectangle(food.x, food.y, food.widths, food.height, BLUE);
for (int i = 0; i < ee_BadFoods; ++i)
{
	DrawRectangle(badFoods[i].x, badFoods[i].y, badFoods[i].widths, badFoods[i].height, RED);
}
to_hex(Setcolor::mh_Red[12].c_str());
ClearBackground(bgPlay);
DrawRectangle(player.x,player.y,player.widths,player.height, RED);
food.y += 300.0f*deltaTime;
for (int i = 0; i < ee_BadFoods; ++i)
{
	badFoods[i].y+=300.0f*deltaTime;
}
EndDrawing();
if (IsKeyDown(KEY_A)) { player.x -= playerSpeed*deltaTime; }
if (IsKeyDown(KEY_D)) { player.x += playerSpeed*deltaTime; }
if (IsKeyDown(KEY_LEFT)) { player.x -= playerSpeed*deltaTime; }
if (IsKeyDown(KEY_RIGHT)) { player.x += playerSpeed*deltaTime; }
if (player.x + player.widths > GetScreenWidth())
{
	player.x = GetScreenWidth() - player.widths;
}
if (player.x < 0)
{
	player.x = 0;
}
if (CheckCollisionRecs(player,food))
{
	Rectangle another = {(float)getRandom(0,GetScreenWidth()),0.0f,20.0f,20.0f};
	food = another;
	++points;
}
for (int i = 0; i < ee_BadFoods; ++i)
{
	if (CheckCollisionRecs(player,badFoods[i]))
	{
		Rectangle another = {(float)getRandom(0,GetScreenWidth()),0.0f,20.0f,20.0f};
		badFoods[i] = another;
		--attempts;
	}
}
if (food.y>=GetScreenHeight())
{
	Rectangle another = {(float)getRandom(0,GetScreenWidth()),0.0f,20.0f,20.0f};
	food = another;
	--attempts;
}
for (int i = 0; i < ee_BadFoods; ++i)
{
	if (badFoods[i].y >= GetScreenHeight())
	{
		Rectangle another = { (float)getRandom(0, GetScreenWidth()), 0.0f, 20.0f, 20.0f };
		badFoods[i] = another;
	} 
}
}
}
void chooseMode()
{	Rectangle easyButton = { 0,0, 200.0f*2.0f/3, 50.0f*2.0f };
Rectangle normalButton = { 0,100, 200.0f*2.0f/3, 50.0f*2.0f };
Rectangle hardButton = {0,200, 200.0f*2.0f/3, 50.0f*2.0f };
while (!WindowShouldClose())
{
	DrawFPS(0, 0);
	// Check if the mouse is hovering over a button
	bool easyHover = CheckCollisionPointRec(GetMousePosition(), easyButton);
	bool normalHover = CheckCollisionPointRec(GetMousePosition(), normalButton);
	bool hardHover = CheckCollisionPointRec(GetMousePosition(), hardButton);

	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		if (easyHover)
		{
			easyPlay();
		}
		else if (normalHover)
		{
			nplay();
		}
		else if (hardHover)
		{
			hardPlay();
		}
	}

	// Begin drawing the scene
	BeginDrawing();

	// Clear the screen with a color
	ClearBackground(to_hex(Setcolor::mh_blueGrey[8].c_str()));

	// Draw the menu buttons
	DrawRectangleRec(easyButton, easyHover ?  to_hex(Setcolor::mh_Red[8].c_str()): RED);
	DrawText("easy", easyButton.x + 30, easyButton.y + 15, 20, BLACK);

	DrawRectangleRec(normalButton, normalHover ? DARKBLUE: BLUE);
	DrawText("normal", normalButton.x + 10, normalButton.y + 15, 20, BLACK);

	DrawRectangleRec(hardButton, hardHover ? DARKGREEN : GREEN);
	DrawText("hard", hardButton.x + 40, hardButton.y + 15, 20, BLACK);

	EndDrawing();
}
}
void menu()
{ if (_menu != false)
	{
		menu();
	}
	Color bgBt = to_hex(Setcolor::mh_Red[5].c_str());
	Rectangle playButton = { 200.0f, 120.0f, 200.0f*2.0f, 50.0f*2.0f };
	Rectangle settingsButton = { 200.0f, 180.0f+50, 200.0f*2.0f, 50.0f*2.0f };
	Rectangle exitButton = { 200.0f, 400.0f-50, 200.0f*2.0f, 50.0f*2.0f };
	while (!WindowShouldClose())
	{	 
		DrawFPS(0, 0);
		bool playHover = CheckCollisionPointRec(GetMousePosition(), playButton);
		bool settingsHover = CheckCollisionPointRec(GetMousePosition(), settingsButton);
		bool exitHover = CheckCollisionPointRec(GetMousePosition(), exitButton);
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			if (playHover)
			{
				chooseMode();
			}
			else if (settingsHover)
			{
			}
			else if (exitHover)
			{
				break;
			}
		}
		BeginDrawing();
		ClearBackground(to_hex("#121212"));
		DrawRectangleRec(playButton, playHover ?  to_hex(Setcolor::mh_Red[11].c_str()): bgBt);
		DrawText("Play", playButton.x + 30, playButton.y + 15, 20, BLACK);
		DrawRectangleRec(settingsButton, settingsHover ? DARKGRAY : GRAY);
		DrawText("Settings", settingsButton.x + 10, settingsButton.y + 15, 20, BLACK);
		DrawRectangleRec(exitButton, exitHover ? DARKGRAY : GRAY);
		DrawText("Exit", exitButton.x + 40, exitButton.y + 15, 20, BLACK);
		EndDrawing();
	}
}
int main()
{ 	Color bgBt = to_hex(Setcolor::mh_Red[5].c_str());
const int screenWidth = 800;
const int screenHeight = 600;
const char* windowTitle = "Kyuxa";
InitWindow(screenWidth, screenHeight, windowTitle);
SetTargetFPS(60);
const int fontSize = 50;
const char* prompt = "Enter your name:";
std::string name;
while (!WindowShouldClose())
{	 
	if (IsKeyPressed(KEY_ENTER))
	{
		std::cout << "Entered text: " << name << std::endl;
		menu();
	}
	else if (IsKeyPressed(KEY_BACKSPACE) && name.length() > 0)
	{
		// Remove the last character from the entered text
		name.pop_back();
	}
	else
	{
		// Check for text input
		int key = GetCharPressed();
		if (key > 0 && key < 256)
		{
			name += static_cast<char>(key);
		}
	}
	DrawFPS(0, 0);
	BeginDrawing();
	DrawText(prompt,GetScreenWidth()/2-60,GetScreenHeight()/2-70, fontSize, RED);
	DrawText(name.c_str(),GetScreenWidth()/2-20, screenHeight / 2-30, fontSize, WHITE);
	ClearBackground(to_hex("#121212"));
	EndDrawing();
}
CloseWindow();
return 0;
}