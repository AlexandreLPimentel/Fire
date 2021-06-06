#pragma once
#include <map>
#include "vector.h"

namespace engine {
	class Input
	{
		static Input* instance;

		static Input& getInstance();

		std::map<unsigned char, bool> keysDown;
		std::map<unsigned char, bool> lastFrame;
		std::map<int, bool> mouseButton;
		std::map<int, bool> mouseButtonLastFrame;

		vec2 mouseMovement;
		vec2 prevMousePosition;
		vec2 mousePosition;

		Input();
		~Input();
	public:
		Input(Input const&) = delete;
		void operator=(Input const&) = delete;


		static void Update();

		static bool GetKey(const unsigned char key);
		static bool GetKeyDown(const unsigned char key);
		static bool GetKeyUp(const unsigned char key);

		static bool GetMouseButton(const int button);
		static bool GetMouseButtonDown(const int button);
		static bool GetMouseButtonUp(const int button);

		static vec2 GetMouseMovement();
		static vec2 GetMousePosition();

		static void KeyboardDown(unsigned char key, int x, int y);
		static void KeyboardUp(unsigned char key, int x, int y);
		
		static void MouseButtonCallback(int button, int state, int x, int y);
		
		static void MouseMovement(int x, int y);
	};
}
