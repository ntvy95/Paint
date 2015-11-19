#include "MenuList.h"
#include "Procedure.h"
#include "Global.h"
#include "Event.h"
#include "graphics.h"
#pragma comment(lib, "graphics.lib")

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* NAME: MenuBar.
* INPUT: Menu** menu.
* OUTPUT: Menu* MenuBar.
* DESCRIPTION: Include: File, Edit. Please view the MenuList.h file for more
information. I will have a detailed explanation on this menu, the other ones
are alike.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
Menu* MenuBar(Menu** menu) {
	//We initialize MenuBar with some initial arguments (their meaning can be found at Menu.h file).
	Menu* MenuBar = new Menu(20, 0, 75, 30, MAXX - 60, 30, false);
	
	//We initialize the FileMenu - which is the child menu of File item. It is convenient to do
	//the FileMenu initialization before File initialization.
	Menu* FileMenu = new Menu;
	Menu* EditMenu = new Menu;

	//We initialize the File item and the Edit item, the meaning of initialized arguments can be found
	//at Item.h file.
	Item *File = new Item(FileMenu, "File", NULL, 0, &Style::normal_outtext, &Style::active_outtext),
		*Edit = new Item(EditMenu, "Edit", NULL, 0, &Style::normal_outtext, &Style::active_outtext);

	//We add the File item into the MenuBar menu. This action will coordinate the File item automatically.
	MenuBar->add(File);
	//We specify some possible mouse events of the File item.
	File->mouse_event->hover = &ItemEvent::hover_menu;
	File->mouse_event->hover_inactive = &ItemEvent::hover_inactive_menu;

	//Same action to the Edit item.
	MenuBar->add(Edit);
	Edit->mouse_event->hover = &ItemEvent::hover_menu;
	Edit->mouse_event->hover_inactive = &ItemEvent::hover_inactive_menu;

	//Now it is the time for us to set up the FileMenu menu that we have leaved it "blank" above.
	::FileMenu(FileMenu, File);
	::EditMenu(EditMenu, Edit);

	return MenuBar;
}

void EditMenu(Menu* EditMenu, Item* Edit) {
	EditMenu->set(Edit->layer->startx, Edit->layer->endy, (int)(Edit->parent->itemw * 1.5), Edit->parent->itemh, (int)(Edit->parent->itemw * 1.5), 0, true);
	EditMenu->max_active = -1;

	Item *Undo = new Item(NULL, "Undo", NULL, 0, &Style::normal_outtext, &Style::active_outtext),
		//*Crop = new Item(NULL, "Crop", NULL, 0, &Style::normal_outtext, &Style::active_outtext),
		*Shear = new Item(NULL, "Shear", NULL, NULL, &Style::normal_outtext, &Style::active_outtext),
		*Rotate = new Item(NULL, "Rotate", NULL, NULL, &Style::normal_outtext, &Style::active_outtext),
		*Stretch = new Item(NULL, "Stretch", NULL, NULL, &Style::normal_outtext, &Style::active_outtext),
		*Move = new Item(NULL, "Move", NULL, NULL, &Style::normal_outtext, &Style::active_outtext);

	EditMenu->add(Undo);
	Undo->mouse_event->hover = &ItemEvent::hover_menu;
	Undo->mouse_event->hover_inactive = &ItemEvent::hover_inactive_menu;
	Undo->mouse_event->leftdown = &ItemEvent::leftdown_undo;

	/*EditMenu->add(Crop);
	Crop->mouse_event->hover = &ItemEvent::hover_menu;
	Crop->mouse_event->hover_inactive = &ItemEvent::hover_inactive_menu;
	Crop->mouse_event->leftdown = &ItemEvent::leftdown_crop;*/

	EditMenu->add(Shear);
	Shear->mouse_event->hover = &ItemEvent::hover_menu;
	Shear->mouse_event->hover_inactive = &ItemEvent::hover_inactive_menu;
	Shear->mouse_event->leftdown = &ItemEvent::leftdown_keyboard_shear;

	EditMenu->add(Rotate);
	Rotate->mouse_event->hover = &ItemEvent::hover_menu;
	Rotate->mouse_event->hover_inactive = &ItemEvent::hover_inactive_menu;
	Rotate->mouse_event->leftdown = &ItemEvent::leftdown_keyboard_rotate;

	EditMenu->add(Stretch);
	Stretch->mouse_event->hover = &ItemEvent::hover_menu;
	Stretch->mouse_event->hover_inactive = &ItemEvent::hover_inactive_menu;
	Stretch->mouse_event->leftdown = &ItemEvent::leftdown_keyboard_stretch;

	EditMenu->add(Move);
	Move->mouse_event->hover = &ItemEvent::hover_menu;
	Move->mouse_event->hover_inactive = &ItemEvent::hover_inactive_menu;
	Move->mouse_event->leftdown = &ItemEvent::leftdown_move;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* NAME: FileMenu.
* INPUT: Menu* FileMenu, Item* File.
* OUTPUT: void.
* DESCRIPTION: Where we set up the FileMenu mentioned above. Include: Load Bitmap,
Save Bitmap.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void FileMenu(Menu* FileMenu, Item* File) {
	//We set some arguments of the FileMenu that depending on some File item arguments.
	//Including: coordination, its item width, its item height, etc.
	FileMenu->set(File->layer->startx, File->layer->endy, (int)(File->parent->itemw * 1.5), File->parent->itemh, (int)(File->parent->itemw * 1.5), 0, true);
	//We set the FileMenu menu to be a hover-dropdown menu. For more information on this,
	//please check the Menu.h file.
	FileMenu->max_active = -1;

	//FileMenu has Load and Savve as child items.
	Item *New = new Item(NULL, "New", NULL, 0, &Style::normal_outtext, &Style::active_outtext),
		*Load = new Item(NULL, "Load Bitmap", NULL, 0, &Style::normal_outtext, &Style::active_outtext),
		*Save = new Item(NULL, "Save Bitmap", NULL, 0, &Style::normal_outtext, &Style::active_outtext);

	//If you forgot what these mean, please take a look back to the MenuBar procedure above.
	FileMenu->add(New);
	New->mouse_event->hover = &ItemEvent::hover_menu;
	New->mouse_event->hover_inactive = &ItemEvent::hover_inactive_menu;
	New->mouse_event->leftdown = &ItemEvent::leftdown_new;

	FileMenu->add(Load);
	Load->mouse_event->hover = &ItemEvent::hover_menu;
	Load->mouse_event->hover_inactive = &ItemEvent::hover_inactive_menu;

	FileMenu->add(Save);
	Save->mouse_event->hover = &ItemEvent::hover_menu;
	Save->mouse_event->hover_inactive = &ItemEvent::hover_inactive_menu;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* NAME: ToolPanel.
* INPUT: Menu* FileMenu, Item* File.
* OUTPUT: void.
* DESCRIPTION: Include: Drawing options: Line, Circle, Square, Fill, ABC.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
Menu* ToolPanel(Menu** menu) {
	Menu* ToolPanel = new Menu(menu[0]->layer->startx, menu[0]->layer->endy, 30, 30, 30, 0, true);
	ToolPanel->max_active = 1;

	Menu *CircleMenu = new Menu,
		 *SquareMenu = new Menu,
		 *ABCMenu = new Menu;

	int* arr3 = new int[3];
	arr3[0] = ToolPanel->itemw / 2;
	arr3[1] = ToolPanel->itemh / 2;
	arr3[2] = Min(ToolPanel->itemw, ToolPanel->itemh) / 4;

	Item *Select = new Item(NULL, "Select", arr3, 3, &Style::normal_select, &Style::active_select),
		*Line = new Item(NULL, "Line", arr3, 3, &Style::normal_line, &Style::active_line),
		*Bezier = new Item(NULL, "Bezier", arr3, 3, &Style::normal_bezier, &Style::active_bezier),
		*Parabol = new Item(NULL, "Parabol", arr3, 3, &Style::normal_parabol, &Style::active_parabol),
		*Circle = new Item(CircleMenu, "Circle", arr3, 3, &Style::normal_circle, &Style::active_circle),
		*Ellipse = new Item(NULL, "Ellipse", arr3, 3, &Style::normal_ellipse, &Style::active_ellipse),
		*Square = new Item(SquareMenu, "Square", arr3, 3, &Style::normal_square, &Style::active_square),
		*Fill = new Item(NULL, "Fill", arr3, 3, &Style::normal_fill, &Style::active_fill),
		*ABC = new Item(ABCMenu, "ABC", NULL, 0, &Style::normal_outtext, &Style::active_outtext);

	ToolPanel->add(Select);
	Select->mouse_event->hover = &ItemEvent::hover_menu;
	Select->mouse_event->hover_inactive = &ItemEvent::hover_inactive_menu;
	Select->mouse_event->leftdown = &ItemEvent::leftdown_select;

	ToolPanel->add(Line);
	Line->mouse_event->hover = &ItemEvent::hover_menu;
	Line->mouse_event->hover_inactive = &ItemEvent::hover_inactive_menu;
	Line->mouse_event->leftdown = &ItemEvent::leftdown_line;

	ToolPanel->add(Bezier);
	Bezier->mouse_event->hover = &ItemEvent::hover_menu;
	Bezier->mouse_event->hover_inactive = &ItemEvent::hover_inactive_menu;
	Bezier->mouse_event->leftdown = &ItemEvent::leftdown_bezier;

	ToolPanel->add(Parabol);
	Parabol->mouse_event->hover = &ItemEvent::hover_menu;
	Parabol->mouse_event->hover_inactive = &ItemEvent::hover_inactive_menu;
	Parabol->mouse_event->leftdown = &ItemEvent::leftdown_parabol;

	ToolPanel->add(Ellipse);
	Ellipse->mouse_event->hover = &ItemEvent::hover_menu;
	Ellipse->mouse_event->hover_inactive = &ItemEvent::hover_inactive_menu;
	Ellipse->mouse_event->leftdown = &ItemEvent::leftdown_ellipse;

	ToolPanel->add(Circle);
	Circle->mouse_event->hover = &ItemEvent::hover_menu;
	Circle->mouse_event->hover_inactive = &ItemEvent::hover_inactive_menu;

	ToolPanel->add(Square);
	Square->mouse_event->hover = &ItemEvent::hover_menu;
	Square->mouse_event->hover_inactive = &ItemEvent::hover_inactive_menu;

	ToolPanel->add(Fill);
	Fill->mouse_event->hover = &ItemEvent::hover_menu;
	Fill->mouse_event->hover_inactive = &ItemEvent::hover_inactive_menu;
	Fill->mouse_event->leftdown = &ItemEvent::leftdown_fillcolor;

	ToolPanel->add(ABC);
	ABC->mouse_event->hover = &ItemEvent::hover_menu;
	ABC->mouse_event->hover_inactive = &ItemEvent::hover_inactive_menu;

	::CircleMenu(CircleMenu, Circle);
	::SquareMenu(SquareMenu, Square);
	::ABCMenu(ABCMenu, ABC);

	return ToolPanel;
}

void CircleMenu(Menu* CircleMenu, Item* Circle) {
	CircleMenu->set((int)(Circle->layer->startx - Circle->parent->itemw / 2), Circle->layer->endy, (int)(Circle->parent->itemw * 1.2), (int)(Circle->parent->itemh), (int)(Circle->parent->itemw * 2.4), 0, true);
	CircleMenu->max_active = -1;


	Item *KEY = new Item(NULL, "KEY", NULL, 0, &Style::normal_outtext, &Style::active_outtext),
		*MOU = new Item(NULL, "MOU", NULL, 0, &Style::normal_outtext, &Style::active_outtext);

	CircleMenu->add(KEY);
	KEY->mouse_event->hover = &ItemEvent::hover_menu;
	KEY->mouse_event->leftdown = &ItemEvent::leftdown_keyboard_circle;

	CircleMenu->add(MOU);
	MOU->mouse_event->hover = &ItemEvent::hover_menu;
	MOU->mouse_event->leftdown = &ItemEvent::leftdown_circle;
}

void SquareMenu(Menu* SquareMenu, Item* Square) {
	SquareMenu->set((int)(Square->layer->startx - Square->parent->itemw / 2), Square->layer->endy, (int)(Square->parent->itemw * 1.2), Square->parent->itemh, (int)(Square->parent->itemw * 2.4), 0, true);
	SquareMenu->max_active = -1;

	Item *KEY = new Item(NULL, "KEY", NULL, 0, &Style::normal_outtext, &Style::active_outtext),
		*MOU = new Item(NULL, "MOU", NULL, 0, &Style::normal_outtext, &Style::active_outtext);

	SquareMenu->add(KEY);
	KEY->mouse_event->hover = &ItemEvent::hover_menu;
	KEY->mouse_event->leftdown = &ItemEvent::leftdown_keyboard_square;

	SquareMenu->add(MOU);
	MOU->mouse_event->hover = &ItemEvent::hover_menu;
	MOU->mouse_event->leftdown = &ItemEvent::leftdown_square;
}

void ABCMenu(Menu* ABCMenu, Item* ABC) {
	ABCMenu->set(ABC->layer->endx, ABC->layer->starty, ABC->parent->itemw, ABC->parent->itemh, 0, ABC->parent->itemh, false);
	ABCMenu->max_active = -1;

	Item *A = new Item(NULL, "A", NULL, 0, &Style::normal_outtext, &Style::active_outtext),
		 *B = new Item(NULL, "B", NULL, 0, &Style::normal_outtext, &Style::active_outtext),
		 *C = new Item(NULL, "C", NULL, 0, &Style::normal_outtext, &Style::active_outtext);

	ABCMenu->add(A);
	A->mouse_event->hover = &ItemEvent::hover_menu;
	A->mouse_event->leftdown = &ItemEvent::leftdown_character;

	ABCMenu->add(B);
	B->mouse_event->hover = &ItemEvent::hover_menu;
	B->mouse_event->leftdown = &ItemEvent::leftdown_character;

	ABCMenu->add(C);
	C->mouse_event->hover = &ItemEvent::hover_menu;
	C->mouse_event->leftdown = &ItemEvent::leftdown_character;
}

Menu* DrawingArea(Menu** menu) {
	Menu* DrawingArea = new Menu(menu[1]->layer->endx, menu[1]->layer->starty, menu[0]->layer->endx - menu[1]->layer->endx, MAXY - 195, menu[0]->layer->endx - menu[1]->layer->endx, 0, true);
	DrawingArea->max_active = 0;

	Item* DrawingAreaItem = new Item(NULL, "Drawing Area Item", NULL, 0, NULL, NULL);

	DrawingArea->add(DrawingAreaItem);
	DrawingAreaItem->mouse_event->hover = &ItemEvent::hover_drawing_area;
	DrawingAreaItem->mouse_event->hover_inactive = &ItemEvent::hover_inactive_drawing_area;
	DrawingAreaItem->mouse_event->leftdown = &ItemEvent::leftdown_draw;
	DrawingAreaItem->mouse_event->leftdrag = &ItemEvent::leftdrag_draw;
	DrawingAreaItem->mouse_event->leftup = &ItemEvent::leftup_draw;

	DrawingAreaItem->scrollbar = new Scrollbar(DrawingAreaItem);
	DrawingAreaItem->layers = new Layers();

	Event::item_drawing_area = DrawingAreaItem;

	return DrawingArea;
}

Menu* StyleMenu(Menu** menu) {
	Menu* StyleMenu = new Menu(menu[2]->layer->startx, menu[2]->layer->endy, (int)(MAXX * 0.1), 30, 0, 30, false);
	StyleMenu->max_active = 1;

	int *thickp = new int[1],
		*dottedp = new int[1];
	thickp[0] = SOLID_LINE;
	dottedp[0] = DOTTED_LINE;

	Item *Thick = new Item(NULL, "Thick Line", thickp, 1, &Style::normal_line_style, &Style::active_line_style),
		 *Dotted = new Item(NULL, "Dotted Line", dottedp, 1, &Style::normal_line_style, &Style::active_line_style);
	
	StyleMenu->add(Thick);
	Thick->mouse_event->hover = &ItemEvent::hover_menu;
	Thick->mouse_event->hover_inactive = &ItemEvent::hover_inactive_menu;

	StyleMenu->add(Dotted);
	Dotted->mouse_event->hover = &ItemEvent::hover_menu;
	Dotted->mouse_event->hover_inactive = &ItemEvent::hover_inactive_menu;

	return StyleMenu;
}

Menu* ColorMenu(Menu** menu) {
	Menu* ColorMenu = new Menu(menu[3]->layer->startx, menu[3]->layer->endy, (int)(MAXX * 0.05), 30, 0, 30, false);
	ColorMenu->max_active = 1;

	int *blackp = new int[1],
		*bluep = new int[1],
		*greenp = new int[1],
		*cyanp = new int[1],
		*redp = new int[1],
		*magentap = new int[1],
		*brownp = new int[1],
		*lightgrayp = new int[1],
		*darkgrayp = new int[1],
		*lightbluep = new int[1],
		*lightgreenp = new int[1], 
		*lightcyanp = new int[1], 
		*lightredp = new int[1],
		*lightmagentap = new int[1],
		*yellowp = new int[1],
		*whitep = new int[1];
	blackp[0] = BLACK;
	bluep[0] = BLUE;
	greenp[0] = GREEN;
	cyanp[0] = CYAN;
	redp[0] = RED;
	magentap[0] = MAGENTA;
	brownp[0] = BROWN;
	lightgrayp[0] = LIGHTGRAY;
	darkgrayp[0] = DARKGRAY;
	lightbluep[0] = LIGHTBLUE;
	lightgreenp[0] = LIGHTGREEN;
	lightcyanp[0] = LIGHTCYAN;
	lightredp[0] = LIGHTRED;
	lightmagentap[0] = LIGHTMAGENTA;
	yellowp[0] = YELLOW;
	whitep[0] = WHITE;

	Item *Black = new Item(NULL, "Black Color", blackp, 1, &Style::normal_color, &Style::active_color),
		 *Blue = new Item(NULL, "Blue Color", bluep, 1, &Style::normal_color, &Style::active_color),
		 *Green = new Item(NULL, "Green Color", greenp, 1, &Style::normal_color, &Style::active_color),
		 *Cyan = new Item(NULL, "Cyan Color", cyanp, 1, &Style::normal_color, &Style::active_color),
		 *Red = new Item(NULL, "Red Color", redp, 1, &Style::normal_color, &Style::active_color),
		 *Magenta = new Item(NULL, "Magenta Color", magentap, 1, &Style::normal_color, &Style::active_color),
		 *Brown = new Item(NULL, "Brown Color", brownp, 1, &Style::normal_color, &Style::active_color),
		 *Lightgray = new Item(NULL, "Lightgray Color", lightgrayp, 1, &Style::normal_color, &Style::active_color),
		 *Darkgray = new Item(NULL, "Darkgray Color", darkgrayp, 1, &Style::normal_color, &Style::active_color),
		 *Lightblue = new Item(NULL, "Lightblue Color", lightbluep, 1, &Style::normal_color, &Style::active_color),
		 *Lightgreen = new Item(NULL, "Lightgreen Color", lightgreenp, 1, &Style::normal_color, &Style::active_color),
		 *Lightcyan = new Item(NULL, "Lightcyan Color", lightcyanp, 1, &Style::normal_color, &Style::active_color),
		 *Lightred = new Item(NULL, "Lightgray Color", lightredp, 1, &Style::normal_color, &Style::active_color),
		 *Lightmagenta = new Item(NULL, "Lightgray Color", lightmagentap, 1, &Style::normal_color, &Style::active_color),
		 *Yellow = new Item(NULL, "Yellow Color", yellowp, 1, &Style::normal_color, &Style::active_color),
		 *White = new Item(NULL, "White Color", whitep, 1, &Style::normal_color, &Style::active_color);

	ColorMenu->add(Black);
	Black->mouse_event->hover = &ItemEvent::hover_menu;
	Black->mouse_event->hover_inactive = &ItemEvent::hover_inactive_menu;
	Black->mouse_event->leftup = &ItemEvent::leftup_color;

	ColorMenu->add(Blue);
	Blue->mouse_event->hover = &ItemEvent::hover_menu;
	Blue->mouse_event->hover_inactive = &ItemEvent::hover_inactive_menu;
	Blue->mouse_event->leftup = &ItemEvent::leftup_color;

	ColorMenu->add(Green);
	Green->mouse_event->hover = &ItemEvent::hover_menu;
	Green->mouse_event->hover_inactive = &ItemEvent::hover_inactive_menu;
	Green->mouse_event->leftup = &ItemEvent::leftup_color;

	ColorMenu->add(Cyan);
	Cyan->mouse_event->hover = &ItemEvent::hover_menu;
	Cyan->mouse_event->hover_inactive = &ItemEvent::hover_inactive_menu;
	Cyan->mouse_event->leftup = &ItemEvent::leftup_color;

	ColorMenu->add(Red);
	Red->mouse_event->hover = &ItemEvent::hover_menu;
	Red->mouse_event->hover_inactive = &ItemEvent::hover_inactive_menu;
	Red->mouse_event->leftup = &ItemEvent::leftup_color;

	ColorMenu->add(Magenta);
	Magenta->mouse_event->hover = &ItemEvent::hover_menu;
	Magenta->mouse_event->hover_inactive = &ItemEvent::hover_inactive_menu;
	Magenta->mouse_event->leftup = &ItemEvent::leftup_color;

	ColorMenu->add(Brown);
	Brown->mouse_event->hover = &ItemEvent::hover_menu;
	Brown->mouse_event->hover_inactive = &ItemEvent::hover_inactive_menu;
	Brown->mouse_event->leftup = &ItemEvent::leftup_color;

	ColorMenu->add(Lightgray);
	Lightgray->mouse_event->hover = &ItemEvent::hover_menu;
	Lightgray->mouse_event->hover_inactive = &ItemEvent::hover_inactive_menu;
	Lightgray->mouse_event->leftup = &ItemEvent::leftup_color;

	ColorMenu->add(Darkgray);
	Darkgray->mouse_event->hover = &ItemEvent::hover_menu;
	Darkgray->mouse_event->hover_inactive = &ItemEvent::hover_inactive_menu;
	Darkgray->mouse_event->leftup = &ItemEvent::leftup_color;

	ColorMenu->add(Lightblue);
	Lightblue->mouse_event->hover = &ItemEvent::hover_menu;
	Lightblue->mouse_event->hover_inactive = &ItemEvent::hover_inactive_menu;
	Lightblue->mouse_event->leftup = &ItemEvent::leftup_color;

	ColorMenu->add(Lightgreen);
	Lightgreen->mouse_event->hover = &ItemEvent::hover_menu;
	Lightgreen->mouse_event->hover_inactive = &ItemEvent::hover_inactive_menu;
	Lightgreen->mouse_event->leftup = &ItemEvent::leftup_color;

	ColorMenu->add(Lightcyan);
	Lightcyan->mouse_event->hover = &ItemEvent::hover_menu;
	Lightcyan->mouse_event->hover_inactive = &ItemEvent::hover_inactive_menu;
	Lightcyan->mouse_event->leftup = &ItemEvent::leftup_color;

	ColorMenu->add(Lightred);
	Lightred->mouse_event->hover = &ItemEvent::hover_menu;
	Lightred->mouse_event->hover_inactive = &ItemEvent::hover_inactive_menu;
	Lightred->mouse_event->leftup = &ItemEvent::leftup_color;

	ColorMenu->add(Lightmagenta);
	Lightmagenta->mouse_event->hover = &ItemEvent::hover_menu;
	Lightmagenta->mouse_event->hover_inactive = &ItemEvent::hover_inactive_menu;
	Lightmagenta->mouse_event->leftup = &ItemEvent::leftup_color;

	ColorMenu->add(Yellow);
	Yellow->mouse_event->hover = &ItemEvent::hover_menu;
	Yellow->mouse_event->hover_inactive = &ItemEvent::hover_inactive_menu;
	Yellow->mouse_event->leftup = &ItemEvent::leftup_color;

	ColorMenu->add(White);
	White->mouse_event->hover = &ItemEvent::hover_menu;
	White->mouse_event->hover_inactive = &ItemEvent::hover_inactive_menu;
	White->mouse_event->leftup = &ItemEvent::leftup_color;
	
	return ColorMenu;
}