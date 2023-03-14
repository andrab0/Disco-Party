#pragma once

#include <string>
#include <unordered_map>

#include "components/simple_scene.h"
#include "components/transform.h"


namespace m1
{
	class Tema3 : public gfxc::SimpleScene
	{
	public:
		Tema3();
		~Tema3();

		void Init() override;

		// de adaugat alte functii necesare;		

	private:
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;


		void RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3 color, int luminaGlob, Texture2D* texture1);
		void RenderSimpleMeshPerete(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3 color, int i, int j, int luminaPodea, int luminaSpot, int luminaGlob , Texture2D* texture1);
		void RenderSimpleMeshDansator(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3 color, glm::vec3 pozitie, int luminaPodea, int luminaSpot, int luminaGlob, Texture2D* texture1);
		void RenderCon(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3 color);
		void RenderGlob(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, Texture2D* texture1);

		glm::vec3 MiscareDansator(float deltaTime, float translateX, float translateZ);
		glm::vec3 MiscareDansatorOrizontal(float deltaTime, glm::vec3 posAct, float pas);
		glm::vec3 MiscareDansatorVertical(float deltaTime, glm::vec3 posAct, float pas);
		
		Texture2D* CreateRandomTexture(unsigned int width, unsigned int height);

		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;


		glm::vec3 lightPosition;
		glm::vec3 lightDirection;
		unsigned int materialShininess;
		float materialKd;
		float materialKs;
		glm::vec3 ringDans[8][8];
		glm::vec3 matriceCulori[8][8];
		float randR;
		float randG;
		float randB;

		bool flag;

		glm::vec3 posD1, pos1end;
		glm::vec3 posD2, pos2end;
		glm::vec3 posD3, pos3end;
		glm::vec3 posD4, pos4end;
		glm::vec3 posD5, pos5end;

		glm::vec3 delta1;
		glm::vec3 delta2;
		glm::vec3 delta3;
		glm::vec3 delta4;
		glm::vec3 delta5;
		float xPas, zPas;

		float translateX1, translateZ1;
		float translateX2, translateZ2;
		float translateX3, translateZ3;
		float translateX4, translateZ4;
		float translateX5, translateZ5;

		glm::vec3 pozitieSpot[4];
		glm::vec3 culoareSpot[4];
		glm::vec3 directieSpot[4];

		float n = 1001;
		float nr_grade_intre = 360.0 / (n - 1.0) * 0.0174532925;
		int dirAct[4];
		float unghiStDr[4];
		float unghiSusJos[4];
		float directii[4];
		
		int luminaPodea;
		int luminaSpotlight;
		int luminaGlob;

		std::unordered_map<std::string, Texture2D*> mapTextures;
	};

	// namespace m1
}