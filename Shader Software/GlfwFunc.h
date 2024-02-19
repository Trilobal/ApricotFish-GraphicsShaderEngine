#include "apfimgui.h"
#include "stream.h"
#include "baseInit.h"

namespace apf	//Apricot Fish
{
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
	{
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
	}

	class apfeng : public apfimgui
	{
	public:
		int initialisieruns()
		{
			if (glfwInit())
			{
				glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
				glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
				glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

				init_total_erfolgreich.push_back("GLFW Initlaize: TRUE");
				init_erfolgreich = true;

				apfLog apflog;
				apflog.Init();
				init_total_erfolgreich.push_back("ApfLog Initlaize: TRUE");

				apf::apfLog::GetCoreLogger()->info("GLFW-Initialisierung erfolgreich!");
			}
			else
			{
				init_total_erfolgreich.push_back("GLFW Initlaize: FALSE");

				apf::apfLog::GetCoreLogger()->error("GLFW-Initialisierungsfehler...");
				return -1;
			}

			for (auto info : init_total_erfolgreich)
			{
				apf::apfLog::GetCoreLogger()->info("Total initialised: {}", info);
			}
			apf::apfLog::GetCoreLogger()->info("Total initialised: {}", init_total_erfolgreich.size());

			return 0;
		}


		int constructionGlfwWindow(string title, int width, int height)
		{
			if (!init_erfolgreich)
			{
				apf::apfLog::GetCoreLogger()->error("Failed to initialize GLFW!");
				return -1;
			}

			m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
			if (m_window)
			{
				apf::apfLog::GetCoreLogger()->info("The window was created successfully!");
			}
			glfwMakeContextCurrent(m_window);
			glfwSetKeyCallback(m_window, key_callback);

			if (glewInit() != GLEW_OK)
			{
				apf::apfLog::GetCoreLogger()->error("Failed to initialize GLEW!");
				return -1;
			}


			LoadShader temp;
			temp.rdStream("C:/Users/Administrator/Desktop/Learn Android Reverse/shader/vshader.txt", "C:/Users/Administrator/Desktop/Learn Android Reverse/shader/fshader.txt");

			apfimgui apfimguis;
			apfimguis.initalisierenImgui();

			while (!glfwWindowShouldClose(m_window))
			{
				processInput(m_window);
				glClearColor(155.0f, 155.0f, 155.0f, 1.0f);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


				glfwPollEvents();

				apfimguis.imguiBegin();
				apfimguis.imguiLoop();
				apfimguis.imguiRender();
				apfimguis.imguiEnd();

				glfwSwapBuffers(m_window);
			}

			return 0;
		}

		void shaderCompile()
		{

		}
	private:
		vector<string> init_total_erfolgreich;
		bool init_erfolgreich = false;

	private:
		void processInput(GLFWwindow* window)
		{
			if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
				glfwSetWindowShouldClose(window, true);
		}
	};
}
