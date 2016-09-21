#include <GLFW/glfw3.h>
#include <algorithm>
#include <stdlib.h>
#include <time.h>

const int width = 500;

const int height = 500;



float* pixels = new float[width*height * 3];

bool insidecir(const double x, const double y,const int x_c,const int y_c,const int r)
{



	const double f = (x - x_c)*(x - x_c) + (y - y_c)*(y - y_c) - r*r;
	if (f>=0.0&&f<90.0)return true;
	else return false;
}

int GetRand(double min, double max)
{
	double temp = (double)rand() / (double)RAND_MAX;


	temp = min + (max - min)*temp;


	return temp;
}


void drawPixel(const int& i, const int& j, const float& red, const float& green, const float& blue)

{

	pixels[(i + width* j) * 3 + 0] = red;

	pixels[(i + width* j) * 3 + 1] = green;

	pixels[(i + width* j) * 3 + 2] = blue;

}



// scratched from https://courses.engr.illinois.edu/ece390/archive/archive-f2000/mp/mp4/anti.html

// see 'Rasterization' part.

void drawLine(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue)

{
	if (i1 == i0)
	{
		for (int j = j0; j <= j1; j++)
		{
			const int i = i1;


			drawPixel(i, j, red, green, blue);
		}
	}
	if (j1 == j0)
	{
		for (int i = i0; i <= i1; i++)
		{
			const int j = j1;


			drawPixel(i, j, red, green, blue);
		}
	}if (i0 != i1&&j0 != j1)
	{
		for (int i = i0; i <= i1; i++)

		{

			const int j = (j1 - j0)*(i - i0) / (i1 - i0) + j0;


			drawPixel(i, j, red, green, blue);
		}

	}

}
void drawthickLine(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue)
{
	for (int i = i0; i <= i1; i++)

	{

		const int j = (j1 - j0)*(i - i0) / (i1 - i0) + j0;


		drawPixel(i, j, red, green, blue);
	}
	for (int i = i0; i <= i1; i++)

	{

		const int j = (j1 - j0)*(i - i0) / (i1 - i0) + j0;


		drawPixel(i+1, j, red, green, blue);
	}
	for (int i = i0; i <= i1; i++)

	{

		const int j = (j1 - j0)*(i - i0) / (i1 - i0) + j0;


		drawPixel(i-1, j, red, green, blue);
	}
}

void fill(const int a, const int b, const int c, const int d, const int ay, const int by, const int cy, const int dy, const float& red, const float& green, const float& blue)
{
	for (int i = a; i <= c; i++)

	{

		drawLine(i, ay, i, by, 1.0f, 0.0f, 0.0f);
	}
}



int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);
		std::fill_n(pixels, width*height * 3, 1.0f);

		//draw thick
		drawthickLine(1, 100, 50, 150, 1.0f, 0.0f,0.0f);


		//square
		drawLine(100, 100, 100, 200, 1.0f, 0.0f, 0.0f);
		drawLine(101, 200, 199, 200, 1.0f, 0.0f, 0.0f);
		drawLine(101, 100, 199, 100, 1.0f, 0.0f, 0.0f);
		drawLine(200, 100, 200, 199, 1.0f, 0.0f, 0.0f);

//filled square
		fill(250, 250, 350, 350, 100, 200, 100, 200, 1.0f, 0.0f, 0.0f);



		//triagle
		drawLine(101, 300, 179, 300, 1.0f, 0.0f, 0.0f);
		drawLine(100, 300, 149, 330, 1.0f, 0.0f, 0.0f);
		drawLine(150, 330, 180, 300, 1.0f, 0.0f, 0.0f);

		//pentagon
		drawLine(200, 300, 229, 339, 1.0f, 0.0f, 0.0f);
		drawLine(230, 340, 279, 340, 1.0f, 0.0f, 0.0f);
		drawLine(201, 299, 229, 261, 1.0f, 0.0f, 0.0f);
		drawLine(230, 260, 279, 260, 1.0f, 0.0f, 0.0f);
		drawLine(280, 261, 309, 299, 1.0f, 0.0f, 0.0f);
		drawLine(280, 339, 310, 300, 1.0f, 0.0f, 0.0f);

		

		//circle
		for (int i = 0; i < 10000000; i++)
		{
			double x = GetRand(280, 480);
			double y = GetRand(200, 400);


			if (insidecir(x, y, 380, 300, 50) == true)
				drawPixel((int)x, (int)y, 1.0f, 0.0f, 0.0f);

		}









		glDrawPixels(width, height, GL_RGB, GL_FLOAT, pixels);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	delete[] pixels;
	glfwTerminate();
	return 0;
}
