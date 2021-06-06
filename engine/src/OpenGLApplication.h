#pragma once
#include <string>
#include <GL/glew.h>

namespace engine {
	class OpenGLApplication
	{
	public:
		OpenGLApplication(const std::string title, int width, int height);
		~OpenGLApplication();

		void Create(int argc, char* argv[]);

		void SetTitle(const std::string title);
		const std::string GetTitle();

		void SetWindowSize(int width, int height);
		int GetWidth();
		int GetHeight();

		int GetFrameCount();
		void SetFrameCount(int count);

		void SetWindowHandle(int handle);
		int GetWindowHandle();

		virtual void Init() = 0;
		virtual void Update(const GLfloat deltaTime) = 0;
		virtual void Draw() = 0;
		virtual void Destroy() = 0;

	protected:
		std::string title;
		int width;
		int height;
		int windowHandle;
		int frameCount;
	private:
		void SetupGLUT(int argc, char* argv[]);
		void SetupGLEW();
		void SetupOpenGL();
		void CheckOpenGLInfo();
		void SetupCallbacks();
	};
}
