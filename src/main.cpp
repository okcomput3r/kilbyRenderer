#define COMMI_IMPLEMENTATION
#include <coMMI.h>

#include <tgaimage.h>
#include <window.h>
#include <iostream>

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);
struct A{
	int a;
	int b;
};
int main(int argc, char** argv) {
	/*TGAImage image(100, 100, TGAImage::RGB);
	image.set(52, 41, red);
	image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	image.write_tga_file("out/output.tga");
	*/
	/*
	std::cout << "Creating window \n";
	Window* pWindow = new Window();

	bool running = true;
	while(running)
	{	
		if(pWindow->proccesMessages())
		{
			std::cout << "Clossing window \n";
			running = false;
		}

		Sleep(100);
	}

	delete pWindow;
	*/

	int x;
	coMMIWindowContext window_context;
	coMMI_create_context(&window_context,0);
	coMMI_destroy_context(&window_context);
	std::cin >> x;
	return 0;
}
