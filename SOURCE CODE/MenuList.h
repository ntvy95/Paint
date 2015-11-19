/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* COLLECTION: MenuList.
* DESCRIPTION: This is where we construct the visuality of the menus of Paint
program. The Menu** menu array input here is quite specific: This is the place
to store all the ancestor menu of the program.
Here is the partial direct parent-child relationship tree:
---Menu** menu array.
------MenuBar.
---------FileMenu.
------ToolPanel.
---------CircleMenu.
---------SquareMenu.
---------ABCMenu.
------DrawingArea.
------StyleMenu.
------ColorMenu.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#pragma once
#include "Menu.h"

Menu* MenuBar(Menu** menu);
void FileMenu(Menu* FileMenu, Item* File);
void EditMenu(Menu* EditMenu, Item* Edit);
Menu* ToolPanel(Menu** menu);
void CircleMenu(Menu* CircleMenu, Item* Circle);
void SquareMenu(Menu* SquareMenu, Item* Square);
void ABCMenu(Menu* ABCMenu, Item* ABC);
Menu* DrawingArea(Menu** menu);
Menu* StyleMenu(Menu** menu);
Menu* ColorMenu(Menu** menu);