#pragma once

#include "components/simple_scene.h"

#define MOVE_RATIO			(.25f)
#define LIMIT				(.5f)
#define SCALE_FACTOR_X		(1.5f)
#define SCALE_FACTOR_Y		(2.f)

namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
    public:
        Tema1();
        ~Tema1();

        void Init() override;

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

    protected:
        float cx, cy;
        float translateX, translateY;
        float centerX, centerY;
        float rad;
        float scaleX, scaleY;
        float angularStep;
        float current_angle;
        float wing_angle, angle_add;
        float direction;
        int side;

        int dx, dy;
        int reverse_duck;

        int life_count;
        int bullet_count;
        int score;
        
        int duck, duck_count;
        int hit;

        float speed_inc;
        float timer;

        float edge_hitbox;
        glm::vec3 center_hitbox;
        glm::vec3 new_center_hitbox;

        // TODO(student): If you need any other class variables, define them here.

        glm::vec3 center_head;
        glm::vec3 center_head_now;
        glm::ivec2 resolution;

        glm::mat3 modelMatrix;
        glm::mat3 modelMatrix_grass;
        glm::mat3 modelMatrix_score_bar;
        glm::mat3 modelMatrix_score;
        glm::mat3 modelMatrix_life;
        glm::mat3 modelMatrix_bullet;
        glm::mat3 modelMatrix_hitbox;

        glm::mat3 modelMatrix_body;
        glm::mat3 modelMatrix_right_wing;
        glm::mat3 modelMatrix_left_wing;
        glm::mat3 modelMatrix_head;
        glm::mat3 modelMatrix_beak;
        glm::mat3 modelMatrix_right_eye;
        glm::mat3 modelMatrix_left_eye;
        glm::mat3 modelMatrix_right_eye_sparkle;
        glm::mat3 modelMatrix_left_eye_sparkle;

        // special eyes

        glm::mat3 modelMatrix_dead_eye_1;
        glm::mat3 modelMatrix_dead_eye_2;
        glm::mat3 modelMatrix_dead_eye_3;
        glm::mat3 modelMatrix_dead_eye_4;

        glm::mat3 modelMatrix_happy_eye_1;
        glm::mat3 modelMatrix_happy_eye_2;
        glm::mat3 modelMatrix_happy_eye_3;
        glm::mat3 modelMatrix_happy_eye_4;
    };
}   // namespace m1
