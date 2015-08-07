
#include <glut.h>

#include <iostream>
#include <windows.h>
#include <list>

#pragma comment(lib, "applicationGlut")


class Class_Glut {

private:
	GLfloat light_ambient[4], light_diffuse[4], light_specular[4], light_position[4];

	double mouse_sensitivity;						// general settings
	int active_light;

	typedef void(*pointFunc)();
	std::list<pointFunc> myFunc_2d;
	std::list<pointFunc> myFunc_3d;
	std::list<pointFunc> myFunc_3d_static;

	typedef void(*pointKey)(unsigned char, int, int);
	std::list<pointKey> myFunc_keyboard;

	typedef void(*pointMouse)(int, int, int, int);
	std::list<pointMouse> myFunc_mouse;

	typedef void(*pointMotion)(int, int);
	std::list<pointMotion> myFunc_motion;
	std::list<pointMotion> myFunc_mouse_passive;

	double camera_x, camera_y, camera_z;


	double red_3d, green_3d, blue_3d, alpha_3d;		// 3d setings


	double red_2d, green_2d, blue_2d, alpha_2d;	// 2d setings


public:
	int active_3d;
	int update_ms;

	int kn;
	int          width, height;
	int          button;
	float        angleX, angleY;
	float        mouseX, mouseY;
	float        distZ;


	Class_Glut();

	void size(int w, int h);

	void keyboard(unsigned char key, int x, int y);

	void mouse(int _button, int state, int x, int y);

	void motion(int x, int y);

	void mouse_passive(int x, int y);



	void add_to_2d(void(*func)());

	void add_to_3d(void(*func)());

	void add_to_3d_static(void(*func)());

	void add_to_keyboard(void(*func)(unsigned char, int, int));

	void add_to_mouse(void(*func)(int, int, int, int));

	void add_to_motion(void(*func)(int, int));

	void add_to_mouse_passive(void(*func)(int, int));



	void resizeWindow();

	void resizeWindow(int width, int height);

	void resizeWindow(int width, int height, int position_x, int position_y);

	void change_2d_3d();


	void change_back_color_2d(double red, double green, double blue, double alpha);

	void change_back_color_3d(double red, double green, double blue, double alpha);

	void on_off_light();

	void refresh_frame(int frequency);

	void change_mouse_sensivity(double sensivity);

	void paint();

};
