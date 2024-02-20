#pragma once
#include "ModelLoader.h"

#include "baseInit.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "TimerClass.h"

// ��ҪIMGUI������
class apfimgui
{
public:
	//��ʼ��IMGUI
	virtual void initalisierenImgui()
	{
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		(void)io;

		ImGui::StyleColorsClassic();

		io.Fonts->AddFontFromFileTTF("c:/windows/fonts/simhei.ttf", 13.0f, NULL, io.Fonts->GetGlyphRangesChineseSimplifiedCommon());

		ImGui_ImplGlfw_InitForOpenGL(m_window, true);
		ImGui_ImplOpenGL3_Init("#version 330");
	}

	//IMGUIҳ��ͷ
	virtual void imguiBegin()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();

		ImGui::NewFrame();
	}

	//IMGUI����ѭ�� ��Ҫ���ڻ��ƽ����Լ����
	virtual void imguiLoop()
	{
		//����Ǳ�����Ҫ�ۼ���
		static ImGuiStyle& style = ImGui::GetStyle();

		//�����ж�IMGUI�����С�Ķ�
		static bool styleNumVar = 1;
		static bool styleNumVar2 = 1;
		static bool styleNumVar3 = 1;

		//Imgui::checkbox�еı����ۼ���
		static bool demoWindow = false;
		static bool WindowLeftTop = false;
		static bool shaderCodeWindow = false;
		static bool apricotFishSettingsSw = false;
		static bool imguistyleSw = false;

		//�жϴ���λ�ã�Ȼ�����´��ڵ�λ��λ�ڼ���λ��
		static float tempWindowHeight = 0;
		static bool tempWindowPosSw = 1;

		//�ֱ����ڴ���ѧ��̫�ֱ��ˣ�̫Ӳ�ˣ��ֱ�����ֱҪshi����
		static char shaderSourceCode[99999] = "";

		//GLSL���빹��Ļ�������
		static string shaderSourceCodeZero = "";
		static string shaderBaseSourceCode =
			"#version 330 core\n\n"
			"void main()\n"
			"{\n"
			"\040\040\040\040\n"
			"}\0";

		//��ʼ�����ļ�·��
		static char FilePath[50] = "C:/Apricot Fish Engine/vShader.vs";

		//�ж�Ctrl+S���������ÿ�ݼ��洢GLSL����
		if (glfwGetKey(m_window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS && glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
		{
			ofstream SourceTxt;

			SourceTxt.open(FilePath, ios::out | ios::trunc);
			if (!SourceTxt.is_open())
				apf::apfLog::GetClientLogger()->error("Failed to save file...Please read files!");
			else
				apf::apfLog::GetClientLogger()->info("Save to file successfully!");
			SourceTxt << shaderSourceCode << endl;

			SourceTxt.close();

			Sleep(250);
			//MessageBoxA(nullptr, "Save to Shader Source Code Successfully!", "Apricot Fish", MB_OK);
		}

		ImGui::Begin("Apricot Fish ImGui");

		ImGui::Text("Welcome to the Apricot Fish");

		if (styleNumVar)
		{
			imguiStyleVarInit();
			styleNumVar = 0;
		}

		ImGui::Checkbox("Demo Window",&demoWindow);
		if (demoWindow)
			ImGui::ShowDemoWindow();

		ImGui::SameLine();

		//���õ�IMGUI����
		ImGui::Checkbox("Apricot Fish Settings", &apricotFishSettingsSw);
		if (apricotFishSettingsSw)
		{
			ImGui::Begin("Apricot Fish Settings Window");

			ImGui::Text(u8"��Setting component rounded corners");
			if (ImGui::SliderFloat(" ", &style.FrameRounding, 0.0f, 15.0f))
				style.GrabRounding = style.FrameRounding;
			
			const char* styleList[] = { "Dark","Light","Classic" };
			static int item_current = 2;
			ImGui::Combo("Style Colors", &item_current, styleList, IM_ARRAYSIZE(styleList));
			if (item_current == 0)
				ImGui::StyleColorsDark();
			if (item_current == 1)
				ImGui::StyleColorsLight();
			if (item_current == 2)
				ImGui::StyleColorsClassic();

			static bool autoSaveSpdlogInformation = false;
			ImGui::Checkbox("Open Auto Save Spdlog Information",&autoSaveSpdlogInformation);
			static bool autoSaveSpdlogInformationValue = true;
			static int a = 1;
			if (autoSaveSpdlogInformation)
			{
				if (autoSaveSpdlogInformationValue)
				{
					//�������������д�뵽��־�ļ���·����C:\Apricot Fish Engine\Spdlog_Information
					//�޸�һ���߼��Ϳ��ԣ���Ӹ��ж�checkbox�Ŀ��أ�Ȼ����spdlog.cpp�Լ�spdlog.h�ļ����ҵ��������һ�¿����ж�.
					apf::apfLog::GetCoreLogger()->info("Autosave logging is turned on!");
					
					autoSaveSpdlogInformationValue = false;
				}
			}
			else autoSaveSpdlogInformationValue = true;

			ImGui::End();
		}

		// �ô���һֱλ�����Ͻ�
		ImGui::Checkbox("Window Left Top", &WindowLeftTop);
		if (WindowLeftTop)
			ImGui::SetWindowPos(ImVec2(0, 0), 1);

		ImGui::SameLine();

		// �༭GLSL����Ĵ���
		ImGui::Checkbox("Shader Code", &shaderCodeWindow);
		if (shaderCodeWindow)
		{
			tempWindowHeight = ImGui::GetWindowHeight();

			ImGui::Begin("Shader Code Window");

			if (tempWindowPosSw)
			{
				ImGui::SetWindowPos(ImVec2(0, tempWindowHeight + 5));
				tempWindowPosSw = 0;
			}

			if (styleNumVar2)
			{
				ImGui::SetWindowSize("Shader Code Window", ImVec2(560, 415));
				styleNumVar2 = 0;
			}

			if (ImGui::Button("Construction Base Code"))
			{
				strcpy_s(shaderSourceCode,shaderBaseSourceCode.c_str());
			}
			ImGui::SameLine();
			if (ImGui::Button("Clear Code"))
			{
				strcpy_s(shaderSourceCode, shaderSourceCodeZero.c_str());
			}
			
			ImGui::SameLine();

			ImGui::Text("Infomation: You can use Ctrl+S Save to Files.");

			const char* items[] = { "" };

			//��ȡVertex��ɫ���Ĵ���
			if (ImGui::Button("Read Vertex Code"))
			{
				ofstream SourceTxt;

				strcpy_s(FilePath, "C:/Apricot Fish Engine/");
				strcat_s(FilePath, "vShader.vs");

				SourceTxt.open(FilePath,ios::in);
				if (!SourceTxt.is_open())
				{
					apf::apfLog::GetClientLogger()->error("Failed to open Vertex code files...");
				}
				else
				{
					apf::apfLog::GetClientLogger()->info("Open Vertex code files successfully!"); 
					strcpy_s(shaderSourceCode, readStreamtxt(FilePath).c_str());
				}
			}
			ImGui::SameLine();
			//��ȡFragment��ɫ���Ĵ���
			if (ImGui::Button("Read Fragment Code"))
			{
				ofstream SourceTxt;

				strcpy_s(FilePath, "C:/Apricot Fish Engine/");
				strcat_s(FilePath, "fShader.vs");

				SourceTxt.open(FilePath, ios::in);
				if (!SourceTxt.is_open())
				{
					apf::apfLog::GetClientLogger()->error("Failed to open Fragment code files...");
				}
				else
				{
					apf::apfLog::GetClientLogger()->info("Open Fragment code files successfully!");
					strcpy_s(shaderSourceCode, readStreamtxt(FilePath).c_str());
				}
			}

			ImGui::SameLine();
			//�ļ��洢·��
			ImGui::InputText("FilePath", FilePath, IM_ARRAYSIZE(FilePath));
			
			//������ɫ�����밴ť
			if (ImGui::Button("Save Shader Source Code"))
			{
				ofstream SourceTxt;

				if(_access("C:/Apricot Fish Engine",0) == -1)
					CreateDirectoryA("C:/Apricot Fish Engine", NULL);
				SourceTxt.open(FilePath, ios::out | ios::trunc);
				if (!SourceTxt.is_open())
				{
					apf::apfLog::GetClientLogger()->error("Failed to save file...Please read files!");
				}
				else
				{
					apf::apfLog::GetClientLogger()->info("Save to file successfully!");
				}
				SourceTxt << shaderSourceCode << endl;

				SourceTxt.close();
			}

			ImGui::SameLine();

			//�Զ�������룬��û��д�ã�����Ա�дһ����ʱ��Ȼ�����뵽���Ｔ�ɡ�
			static bool auto_saveSourceCode = false;
			if (ImGui::Checkbox("Auto Save Code", &auto_saveSourceCode))
			{
				
			}
			else
			{
				
			}

			static int apfColorR = 0;
			static int apfColorB = 255;
			static int apfColorG = 0;
			static int apfColorA = 255;

			//InputText��������ɫ�ı�
			ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(apfColorR, apfColorB, apfColorG, apfColorA));
			ImGui::InputTextMultiline("##input text", shaderSourceCode, IM_ARRAYSIZE(shaderSourceCode), ImVec2(-FLT_MIN, ImGui::GetWindowHeight() + 100));
			ImGui::PopStyleColor();


			ImGui::End();
		}
		else if(!styleNumVar2)
		{
			styleNumVar2 = 1;
		}

		static bool ModelFunctionsSw = false;
		//ģ�����봰�ڣ���û��д���
		ImGui::Checkbox("Model Functions", &ModelFunctionsSw);
		if (ModelFunctionsSw)
		{
			ImGui::Begin("Model Menu");

			if (styleNumVar3)
			{
				ImGui::SetWindowSize("Model Menu", ImVec2(465, 170));
				styleNumVar3 = 0;
			}

			if (ImGui::TreeNode("Loading Model"))
			{
				if (ImGui::Button("Load"))
				{

				}
				ImGui::SameLine();
				static char tempSave[100];
				
				ImGui::InputText("Modules Path", tempSave, IM_ARRAYSIZE(tempSave));

				ImGui::TreePop();
			}

			ImGui::End();
		}
		else if(!styleNumVar3)
		{
			styleNumVar3 = 1;
		}

		ImGui::End();
	}

	//IMGUI����Ⱦ
	virtual void imguiRender()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	//IMGUI�Ľ���
	virtual void imguiEnd()
	{
		ImGui::EndFrame();
	}
private:
	int VertexReadState = 0;
	int FragmentReadState = 0;

	string shaderCodetxt;

	ifstream Shadertxt;
private:
	bool isFileExe(string name)
	{
		FILE* file;
		if (fopen_s(&file, name.c_str(), "r"))
		{
			fclose(file);
			return true;
		}
		else
		{
			return false;
		}
	}

	void imguiStyleVarInit()
	{
		ImGuiStyle& temp = ImGui::GetStyle();
		temp.FrameRounding = 4.5f;
		temp.GrabRounding = temp.FrameRounding;
	}

	//�������뷽ʽ��ָ��λ�ö�ȡ�ı�
	string readStreamtxt(const char* vPath)
	{
		string StreamCode;

		ifstream Shader;

		Shader.exceptions(ifstream::failbit | ifstream::badbit);
		try
		{
			stringstream ShaderStream;

			Shader.open(vPath);

			ShaderStream << Shader.rdbuf();

			Shader.close();

			StreamCode = ShaderStream.str();
		}
		catch (ifstream::failure& e)
		{
			cout << "ERROR::Shader::File_not_successfully_read: " << e.what() << endl;
		}

		return StreamCode;
	}

	bool takeBook(bool bools)
	{
		return bools == true ? false : true;
	}
};
