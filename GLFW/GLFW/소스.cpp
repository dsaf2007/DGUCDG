#include <GLFW/glfw3.h>
#include <algorithm>

const int width = 500;

const int height = 500;



float* pixels = new float[width*height * 3];



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
		drawthickLine(1, 0, 50, 50, 1.0f, 0.0f,0.0f);
		//pentagon
		drawLine(100, 100, 129, 139, 1.0f, 0.0f, 0.0f);
		drawLine(130, 140, 179, 140, 1.0f, 0.0f, 0.0f);
		drawLine(101, 99, 129, 61, 1.0f, 0.0f, 0.0f);
		drawLine(130, 60, 179, 60, 1.0f, 0.0f, 0.0f);
		drawLine(180, 61, 209, 99, 1.0f, 0.0f, 0.0f);
		drawLine(180, 139, 210, 100, 1.0f, 0.0f, 0.0f);

		//square
		drawLine(300, 100, 300, 200, 1.0f, 0.0f, 0.0f);
		drawLine(301, 200, 399, 200, 1.0f, 0.0f, 0.0f);
		drawLine(301, 100, 399, 100, 1.0f, 0.0f, 0.0f);
		drawLine(400, 100, 400, 199, 1.0f, 0.0f, 0.0f);

		//filled square
		fill(300, 300, 400, 400, 300, 400, 300, 400, 1.0f, 0.0f, 0.0f);

		//triagle
		drawLine(101, 200, 179, 200, 1.0f, 0.0f, 0.0f);
		drawLine(100, 200, 149, 230, 1.0f, 0.0f, 0.0f);
		drawLine(150, 230, 180, 200, 1.0f, 0.0f, 0.0f);





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
