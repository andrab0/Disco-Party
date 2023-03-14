#pragma once

#include "components/simple_scene.h"

namespace m1
{
	class Tema1 : public gfxc::SimpleScene
	{

	 public:
		 struct ViewportSpace
		 {
			 ViewportSpace() : x(0), y(0), width(1), height(1) {}
			 ViewportSpace(int x, int y, int width, int height)
				 : x(x), y(y), width(width), height(height) {}
			 int x;
			 int y;
			 int width;
			 int height;
		 };

		 struct LogicSpace
		 {
			 LogicSpace() : x(0), y(0), width(1), height(1) {}
			 LogicSpace(float x, float y, float width, float height)
				 : x(x), y(y), width(width), height(height) {}
			 float x;
			 float y;
			 float width;
			 float height;
		 };

		 struct Inamic {
			 Inamic(): transX(0), transY(0) {}
			 Inamic(float transX, float transY)
				 : transX(transX), transY(transY) {}
			 float transX;
			 float transY;
		 };

		 struct Glont {
			 Glont() : transX(0), transY(0), lifeStart(0), transXDist(0), transYDist(0) {}
			 Glont(float transX, float transY, time_t lifeStart, float transXDist, float transYDist)
				 : transX(transX), transY(transY), lifeStart(lifeStart), transXDist(transXDist), transYDist(transYDist) {}
			 float transX;
			 float transY;
			 float transXDist;
			 float transYDist;
			 //float distParc;
			 time_t lifeStart;
		 };

		 struct Bullet
		 {
			 Bullet(float x, float y, float angle, time_t lifeSpan)
				 : x(x), y(y), angle(angle), lifeSpan(lifeSpan) {}

			 float x, y, angle;
			 time_t lifeSpan;
		 };

	 public:
		 Tema1();
		 ~Tema1();

		 void Init() override;
	
	 private:
		 void FrameStart() override;
		 void Update(float deltaTimeSeconds) override;
		 void FrameEnd() override;

		 void DrawScene(glm::mat3 visMatrix, float deltaTime);
		 void DrawPlayer(glm::mat3 visMatrix, float deltaTime);
		 void DrawEnemyA(glm::mat3 visMatrix, float deltaTime);
		 void DrawEnemyB(glm::mat3 visMatrix, float deltaTime, float translateXEnemy, float translateYEnemy);
		 void DrawObstacles(glm::mat3 visMatrix, float deltaTime);
		 void DrawProiectil(glm::mat3 visMatrix, float deltaTime);
		 void GenerareEnemy(glm::mat3 visMatrix, float deltaTime);
		 //void AparitieInamiciMari(glm::mat3 visMatrix, float deltaTime);


		 void OnInputUpdate(float deltaTime, int mods) override;
		 void OnKeyPress(int key, int mods) override;
		 void OnKeyRelease(int key, int mods) override;
		 void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		 void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		 void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		 void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		 void OnWindowResize(int width, int height) override;

		 glm::mat3 VisualizationTransf2D(const LogicSpace& logicSpace, const ViewportSpace& viewSpace);
		 glm::mat3 VisualizationTransf2DUnif(const LogicSpace& logicSpace, const ViewportSpace& viewSpace);

		 void SetViewportArea(const ViewportSpace& viewSpace, glm::vec3 colorColor = glm::vec3(0), bool clear = true);
		 void CrearePlayer();
		 void CreareObst();
		 void CreareInamic();
		 void CreareProiectil();
		 void FollowPlayer1(float deltaTime);
		 void FollowPlayer2(float deltaTime);
		 void FollowPlayer3(float deltaTime);
		 void FollowPlayer4(float deltaTime);

		 void ColiziuneHartaJucator(float deltaTime);
		 void ColiziuneHartaInamicA(float deltaTime);
		 void ColiziuneHartaInamicB(float deltaTime);




	 protected:
		 float cx, cy,
			 cxEnm, cyEnm,
			 cxPro, cyPro;
		 glm::mat3 modelMatrix, visMatrix;
		 float translateX, translateY;
		 float angularStep;
		 float angularStepInamic;
		 float angularStepProiectil;
		 float playerRadius, mapSide, eyeSide, nasSide;
		 glm::vec3 nasCorner, enemyCorner, proiectilCorner;
		 float enemySide, proiectilSide;

		 float translateXEnemy1, translateYEnemy1;
		 float translateXEnemy2, translateYEnemy2;
		 float translateXEnemy3, translateYEnemy3;
		 float translateXEnemy4, translateYEnemy4;
		 float translateXEnemyMic, translateYEnemyMic;
		 float translateXProiectil, translateYProiectil;

		 float scaleX1, scaleY1;
		 float scaleX2, scaleY2;
		 float scaleX3, scaleY3;
		 float scaleX4, scaleY4;

		 int count;
		 bool atac1;
		 bool atac2;
		 bool atac3;
		 bool atac4;
		 ViewportSpace viewSpace;
		 LogicSpace logicSpace;

		 std::vector<Glont> proiectile;
		 std::vector<Inamic> inamiciMari;
		 //std::vector<Glont> proiectileInamic;

		 time_t inamicStart;
		 time_t fireRateBegin, fireRateEnd, enemyBegin;

		 glm::ivec2 resolution = window->GetResolution();
	};
}