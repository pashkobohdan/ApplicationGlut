
#include "applicationGlut.h" 

Class_Glut::Class_Glut() {
	light_ambient[0] = 0.0f;
	light_ambient[1] = 0.0f;
	light_ambient[2] = 0.0f;
	light_ambient[3] = 1.0f;

	light_diffuse[0] = 1.0f;
	light_diffuse[1] = 1.0f;
	light_diffuse[2] = 1.0f;
	light_diffuse[3] = 1.0f;

	light_specular[0] = 0.6;
	light_specular[1] = 0.6f;
	light_specular[2] = 0.6;
	light_specular[3] = 1.0f;

	light_position[0] = 0.6f;
	light_position[1] = 0.6f;
	light_position[2] = 1.2f;
	light_position[3] = 0.0f;


	active_3d = 1;

	kn = 0;
	button = -1;
	angleX = 0, angleY = -30;
	mouseX, mouseY;
	distZ = -15;

	update_ms = 10;

	mouse_sensitivity = 0.05;

	red_2d = 0.5;
	green_2d = 0;
	blue_2d = 0;
	alpha_2d = 0;

	red_3d = 0.5;
	green_3d = 0.5;
	blue_3d = 0;
	alpha_3d = 0;

	camera_x = 0;
	camera_y = 0;
	camera_z = -15;

	active_light = 1;

}

void Class_Glut::size(int w, int h)
{
	width = w;
	height = h;
	if (height == 0) height = 1;
}

void Class_Glut::keyboard(unsigned char key, int x, int y) {
	for (std::list<pointKey>::iterator i = myFunc_keyboard.begin(); i != myFunc_keyboard.end(); ++i) {
		(*i)(key, x, y);
	}
}

void Class_Glut::mouse(int _button, int state, int x, int y) {
	for (std::list<pointMouse>::iterator i = myFunc_mouse.begin(); i != myFunc_mouse.end(); ++i) {
		(*i)(_button, state, x, y);
	}

}

void Class_Glut::motion(int x, int y)
{
	for (std::list<pointMotion>::iterator i = myFunc_motion.begin(); i != myFunc_motion.end(); ++i) {
		(*i)(x, y);
	}

}

void Class_Glut::mouse_passive(int x, int y) {
	for (std::list<pointMotion>::iterator i = myFunc_mouse_passive.begin(); i != myFunc_mouse_passive.end(); ++i) {
		(*i)(x, y);
	}
}



void Class_Glut::add_to_2d(void(*func)()) {
	myFunc_2d.push_back(func);
}

void Class_Glut::add_to_3d(void(*func)()) {
	myFunc_3d.push_back(func);
}

void Class_Glut::add_to_3d_static(void(*func)()) {
	myFunc_3d_static.push_back(func);
}

void Class_Glut::add_to_keyboard(void(*func)(unsigned char, int, int)) {
	myFunc_keyboard.push_back(func);
}

void Class_Glut::add_to_mouse(void(*func)(int, int, int, int)) {
	myFunc_mouse.push_back(func);
}

void Class_Glut::add_to_motion(void(*func)(int, int)) {
	myFunc_motion.push_back(func);
}

void Class_Glut::add_to_mouse_passive(void(*func)(int, int)) {
	myFunc_mouse_passive.push_back(func);
}



void Class_Glut::resizeWindow() {
	glutFullScreen();
}

void Class_Glut::resizeWindow(int width, int height) {
	glutReshapeWindow(width, height);
}

void Class_Glut::resizeWindow(int width, int height, int position_x, int position_y) {
	glutReshapeWindow(width, height);
	glutPositionWindow(position_x, position_y);
}

void Class_Glut::change_2d_3d() {
	if (active_3d == 0) { active_3d = 1; }
	else { active_3d = 0; }
}


void Class_Glut::change_back_color_2d(double red, double green, double blue, double alpha = 0.0) {
	red_2d = red;
	green_2d = green;
	blue_3d = blue;
	alpha_2d = alpha;
}

void Class_Glut::change_back_color_3d(double red, double green, double blue, double alpha = 0.0) {
	red_3d = red;
	green_3d = green;
	blue_3d = blue;
	alpha_3d = alpha;
}

void Class_Glut::on_off_light() {
	active_light == 1 ? active_light = 0 : active_light = 1;
}

void Class_Glut::refresh_frame(int frequency) {
	update_ms = 995 / frequency;
}

void Class_Glut::change_mouse_sensivity(double sensivity) {
	mouse_sensitivity = sensivity / 20;
}

void Class_Glut::paint() {

	if (active_3d == 0) {

		glViewport(width / 2, height / 2, width, height);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0, width, 0, height);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(red_2d, green_2d, blue_2d, alpha_2d);

		for (std::list<pointFunc>::iterator i = myFunc_2d.begin(); i != myFunc_2d.end(); ++i) {
			(*i)();
		}

		glutSwapBuffers();

	}
	else {

		glViewport(0, 0, width, height);

		glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		gluPerspective(60, (GLfloat)width / height, 1, 100);// задаємо усічений конус видимості

		glMatrixMode(GL_MODELVIEW);// включаємо режим роботи з видовою матрицею
		glLoadIdentity();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(red_3d, green_3d, blue_3d, alpha_3d);

		glRotatef(angleX*mouse_sensitivity, 0.0f, 1.0f, 0.0f);  // потім повертається по осі Oy
		glRotatef(angleY*mouse_sensitivity, 1.0f, 0.0f, 0.0f);  // потім повертається по осі Ox

		glTranslatef(camera_x, camera_y, camera_z);  // камера з початку координат зсувається на distZ, 

		glEnable(GL_DEPTH_TEST);  // включаємо буфер глибини
		glPushMatrix();

		if (active_light == 1) {
			glEnable(GL_LIGHTING);
			glEnable(GL_LIGHT0);
		}

		for (std::list<pointFunc>::iterator j = myFunc_3d.begin(); j != myFunc_3d.end(); ++j) {	// after turning the camera
			(*j)();
		}

		if (active_light == 1) {
			glDisable(GL_LIGHT0);
			glDisable(GL_LIGHTING);
		}



		glPopMatrix();
		glDisable(GL_DEPTH_TEST);


		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		gluPerspective(60, (GLfloat)width / height, 1, 100);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glTranslatef(camera_x, camera_y, camera_z);
		glPushMatrix();

		for (std::list<pointFunc>::iterator i = myFunc_3d_static.begin(); i != myFunc_3d_static.end(); ++i) {
			(*i)();													// before turning the camera
		}
		glPopMatrix();

		glFlush();
		glutSwapBuffers(); // перемикання буферів
	}
}

