#pragma once
#include "Item.h"
#include "Scrollbar.h"

struct Menu;
struct Scrollbar;
typedef struct Style {
	/*ARTRIBUTE*/
	//There may be various data types here: Item, Menu, etc. Though, please make sure that there is only one non-NULL data type.
	Item* item;
	Menu* menu;
	Scrollbar* scrollbar;
	//The other attributes.
	char* text;
	int ntext;
	int* parameters;
	int npara;
	void(Style::*normal)();
	void(Style::*active)();
	/*METHOD*/
	//Constructors and Destructors
	Style();
	Style(Item* i);
	Style(Menu* m);
	Style(Scrollbar* s);
	~Style();
	void set(Item* i, Menu* m, Scrollbar* s, char* t, int* p, int N, void(Style::*no)(), void(Style::*ac)());
	//normal & active style options.
	//Even though we can make all the style procedure applicable to all the data types listed above,
	//due to the limit of the time being, I have decided not to build the style procedure fully.
	//So there are some only works with Item data type, some works with all other data types.
	void graybg();
	void normal_outtext();
	void active_outtext();
	void normal_line();
	void active_line();
	void normal_circle();
	void active_circle();
	void normal_ellipse();
	void active_ellipse();
	void normal_square();
	void active_square();
	void normal_fill();
	void active_fill();
	void normal_line_style();
	void active_line_style();
	void normal_color();
	void active_color();
	void normal_rectangle_border();
	void active_rectangle_border();
	void normal_select();
	void active_select();
	void normal_parabol();
	void active_parabol();
	void normal_bezier();
	void active_bezier();
	/*STATIC MEMBER*/
	static const int nInputText = 255;
	static char* InputText;
	static int POS;
	static void hide_KEY();
	static void normal_KEY_Circle();
	static void normal_KEY_Square();
	static void normal_KEY_Stretch();
	static void normal_KEY_Rotation();
	static void normal_KEY_Shear();
} Style;