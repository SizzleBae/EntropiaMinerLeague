#include <ScreenCapture/ScreenCapture.h>

#include <SFML/Graphics.hpp>

#include <algorithm>
#include <atomic>
#include <chrono>
#include <climits>
#include <iostream>
#include <locale>
#include <string>
#include <thread>
#include <vector>

using namespace std::chrono_literals;
std::shared_ptr<SL::Screen_Capture::IScreenCaptureManager> framgrabber;
std::atomic<int> realcounter;
std::atomic<int> onNewFramecounter;
auto onNewFramestart = std::chrono::high_resolution_clock::now();

inline std::ostream &operator<<(std::ostream &os, const SL::Screen_Capture::Monitor &p)
{
	return os << "Id=" << p.Id << " Index=" << p.Index << " Height=" << p.Height << " Width=" << p.Width << " OffsetX=" << p.OffsetX
		<< " OffsetY=" << p.OffsetY << " Name=" << p.Name;
}

void createwindowgrabber()
{
	realcounter = 0;
	onNewFramecounter = 0;
	framgrabber = nullptr;
	framgrabber =
		SL::Screen_Capture::CreateCaptureConfiguration([]() {
		auto windows = SL::Screen_Capture::GetWindows();
		std::string srchterm = "Blitz";
		// convert to lower case for easier comparisons
		std::transform(srchterm.begin(), srchterm.end(), srchterm.begin(), [](char c) { return std::tolower(c, std::locale()); });
		decltype(windows) filtereditems;
		for(auto &a : windows) {
			std::string name = a.Name;
			std::transform(name.begin(), name.end(), name.begin(), [](char c) { return std::tolower(c, std::locale()); });
			if(name.find(srchterm) != std::string::npos) {
				filtereditems.push_back(a);
				std::cout << "ADDING WINDOW  Height " << a.Size.y << "  Width  " << a.Size.x << "   " << a.Name << std::endl;
			}
		}
		return filtereditems;
	})

		->onFrameChanged([&](const SL::Screen_Capture::Image &img, const SL::Screen_Capture::Window &window) {
		// std::cout << "Difference detected!  " << img.Bounds << std::endl;
		auto r = realcounter.fetch_add(1);
		auto s = std::to_string(r) + std::string("WINDIF_") + std::string(".jpg");
		auto size = Width(img) * Height(img) * sizeof(SL::Screen_Capture::ImageBGRA);

		/* auto imgbuffer(std::make_unique<unsigned char[]>(size));
		ExtractAndConvertToRGBA(img, imgbuffer.get(), size);
		tje_encode_to_file(s.c_str(), Width(img), Height(img), 4, (const unsigned char*)imgbuffer.get());
		*/
	})
		->onNewFrame([&](const SL::Screen_Capture::Image &img, const SL::Screen_Capture::Window &window) {
		auto r = realcounter.fetch_add(1);
		auto s = std::to_string(r) + std::string("WINNEW_") + std::string(".jpg");
		auto size = Width(img) * Height(img) * sizeof(SL::Screen_Capture::ImageBGRA);

		// auto imgbuffer(std::make_unique<unsigned char[]>(size));
		// ExtractAndConvertToRGBA(img, imgbuffer.get(), size);
		// tje_encode_to_file(s.c_str(), Width(img), Height(img), 4, (const unsigned char*)imgbuffer.get());

		if(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - onNewFramestart).count() >=
			1000) {
			std::cout << "onNewFrame fps" << onNewFramecounter << std::endl;
			onNewFramecounter = 0;
			onNewFramestart = std::chrono::high_resolution_clock::now();
		}
		onNewFramecounter += 1;
	})
		->onMouseChanged([&](const SL::Screen_Capture::Image *img, const SL::Screen_Capture::MousePoint &mousepoint) {
		auto r = realcounter.fetch_add(1);
		auto s = std::to_string(r) + std::string(" M") + std::string(".png");
		if(img) {
			// std::cout << "New mouse coordinates  AND NEW Image received." << " x= " << point.x << " y= " <<
			// point.y << std::endl;
			// lodepng::encode(s,StartSrc(*img), Width(*img), Height(*img));
		}
		else {
			// std::cout << "New mouse coordinates received." << " x= " << point.x << " y= " << point.y << " The
			// mouse image is still the same
			// as the last" << std::endl;
		}
	})
		->start_capturing();

	framgrabber->setFrameChangeInterval(std::chrono::milliseconds(100));
	framgrabber->setMouseChangeInterval(std::chrono::milliseconds(100));
}

int main()
{

	
	std::srand(std::time(nullptr));
	std::cout << "Starting Capture Demo/Test" << std::endl;
	std::cout << "Testing captured monitor bounds check" << std::endl;

	auto goodmonitors = SL::Screen_Capture::GetMonitors();
	for(auto &m : goodmonitors) {
		std::cout << m << std::endl;
	}
	auto badmonitors = SL::Screen_Capture::GetMonitors();

	for(auto m : badmonitors) {
		m.Height += 1;
		std::cout << m << std::endl;
	}
	for(auto m : badmonitors) {
		m.Width += 1;
		std::cout << m << std::endl;
	}

	createwindowgrabber();

	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	while(window.isOpen())
	{
		sf::Event event;
		while(window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;
}