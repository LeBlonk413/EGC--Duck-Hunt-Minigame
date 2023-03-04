#include "lab_m1/Tema1/Tema1.h"

#include <vector>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <time.h>


#include "lab_m1/lab3/transform2D.h"
#include "lab_m1/lab3/object2D.h"

using namespace std;
using namespace m1;

m1::Tema1::Tema1()
{
}

m1::Tema1::~Tema1()
{
}

void Tema1::Init()
{
    resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    // duck mesh rendering
    {
        // body
        float edge_body = 50;
        glm::vec3 corner_body = glm::vec3(0, 0, 0);

        Mesh* triangle_body = object2D::CreateTriangle("triangle_body", corner_body, edge_body, glm::vec3(0.41f, 0.38f, 0.07f), true);
        AddMeshToList(triangle_body);

        // wing
        float edge_wing = 30;
        glm::vec3 corner_wing = glm::vec3(50, 80, 0);

        Mesh* triangle_wing = object2D::CreateTriangle("triangle_wing", corner_wing, edge_wing, glm::vec3(0.41f, 0.38f, 0.07f), true);
        AddMeshToList(triangle_wing);

        // head
        float edge_head = 32;
        center_head = glm::vec3(50, 150, 0);

        Mesh* circle_head = object2D::CreateCircle("circle_head", center_head, edge_head, glm::vec3(0.13f, 0.63f, 0.43f), true);
        AddMeshToList(circle_head);

        // beak
        float edge_beak = 12;
        glm::vec3 corner_beak = glm::vec3(38, 170, 0);

        Mesh* triangle_beak = object2D::CreateTriangle("triangle_beak", corner_beak, edge_beak, glm::vec3(0.78f, 0.62f, 0.20f), true);
        AddMeshToList(triangle_beak);

        // dead eye
        float dead_eye_length = 18;
        float dead_eye_width = 3.5;
        glm::vec3 corner_dead_eye = glm::vec3(50, 160, 0);

        Mesh* rectangle_dead_eye = object2D::CreateRectangle("rectangle_dead_eye", corner_dead_eye, dead_eye_length, dead_eye_width, glm::vec3(0, 0, 0), true);
        AddMeshToList(rectangle_dead_eye);

        // happy eye
        float happy_eye_length = 13;
        float happy_eye_width = 3;
        glm::vec3 corner_happy_eye = glm::vec3(50, 160, 0);

        Mesh* rectangle_happy_eye = object2D::CreateRectangle("rectangle_happy_eye", corner_happy_eye, happy_eye_length, happy_eye_width, glm::vec3(0, 0, 0), true);
        AddMeshToList(rectangle_happy_eye);

        // eye
        float edge_eye = 5;
        glm::vec3 center_eye = glm::vec3(50, 160, 0);
        // initialise collision point in the middle of the head
        centerX = 50;
        centerY = 50;

        Mesh* circle_eye = object2D::CreateCircle("circle_eye", center_eye, edge_eye, glm::vec3(0, 0, 0), true);
        AddMeshToList(circle_eye);

        // eye sparkle
        float edge_eye_sparkle = 2;
        glm::vec3 center_eye_sparkle = glm::vec3(50, 160, 0);

        Mesh* circle_eye_sparkle = object2D::CreateCircle("circle_eye_sparkle", center_eye_sparkle, edge_eye_sparkle, glm::vec3(1, 1, 1), true);
        AddMeshToList(circle_eye_sparkle);

        // hitbox center
        edge_hitbox = 70;
        center_hitbox = glm::vec3(50, 70, 1);
    }

    // other asset rendering
    {
        // grass
        float width_grass = 120;
        float length_grass = resolution.x;
        glm::vec3 corner_grass = glm::vec3(0, 0, 0);

        Mesh* rectangle_grass = object2D::CreateRectangle("rectangle_grass", corner_grass, length_grass, width_grass, glm::vec3(0.20f, 0.76f, 0.48f), true);
        AddMeshToList(rectangle_grass);

        // score
        float width_score = 40;
        float length_score = 10;
        glm::vec3 corner_score = glm::vec3(resolution.x - 205, resolution.y - 175, 0);

        Mesh* rectangle_score = object2D::CreateRectangle("rectangle_score", corner_score, length_score, width_score, glm::vec3(0.13f, 0.53f, 0.82f), true);
        AddMeshToList(rectangle_score);

        // score bar
        float width_score_bar = 50;
        float length_score_bar = 160;
        glm::vec3 corner_score_bar = glm::vec3(resolution.x - 200, resolution.y - 180, 0);

        Mesh* rectangle_score_bar = object2D::CreateRectangle("rectangle_score_bar", corner_score_bar, length_score_bar, width_score_bar, glm::vec3(0.23f, 0.13f, 0.82f), true);
        AddMeshToList(rectangle_score_bar);

        // lives
        float edge_life = 25;
        glm::vec3 center_life = glm::vec3(resolution.x - 12, resolution.y - 40, 0);

        Mesh* circle_life = object2D::CreateCircle("circle_life", center_life, edge_life, glm::vec3(0.82f, 0.31f, 0.3f), true);
        AddMeshToList(circle_life);

        // bullets
        float width_bullet = 40;
        float length_bullet = 20;
        glm::vec3 corner_bullet = glm::vec3(resolution.x - 15, resolution.y - 120, 0);

        Mesh* rectangle_bullet = object2D::CreateRectangle("rectangle_bullet", corner_bullet, length_bullet, width_bullet, glm::vec3(0.63f, 0.46f, 0.29f), true);
        AddMeshToList(rectangle_bullet);
    }

    // inits
    {

        translateX = 0;
        translateY = 0;

        // Initialize sx and sy (the scale factors)
        scaleX = 1;
        scaleY = 1;

        dx = 1;
        dy = 1;

        // initialise frying angle
        current_angle = -45.f;
        reverse_duck = 0;

        angularStep = 0.25f;
        angle_add = 1;

        // initialise starting point
        modelMatrix *= transform2D::Translate(-100, -100);

        // initialise player info
        life_count = 3;
        bullet_count = 3;
        score = 0;

        // initialise duck alive status
        duck = 1;
        hit = 0;

        duck_count = 0;
        speed_inc = 1;

        // timer
        timer = 0;
    }
}

void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0.35f, 0.85f, 0.82f, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema1::Update(float deltaTimeSeconds)
{
    // timer
    timer += deltaTimeSeconds;

    // GUI
    {
        // render the grass
        modelMatrix_grass = glm::mat3(1);
        RenderMesh2D(meshes["rectangle_grass"], shaders["VertexColor"], modelMatrix_grass);

        // check score
        modelMatrix_score = glm::mat3(1);

        for (int i = 1; i <= score; i++) {
            modelMatrix_score *= transform2D::Translate(10, 0);
            RenderMesh2D(meshes["rectangle_score"], shaders["VertexColor"], modelMatrix_score);
        }

        // render the score bar
        modelMatrix_score_bar = glm::mat3(1);

        RenderMesh2D(meshes["rectangle_score_bar"], shaders["VertexColor"], modelMatrix_score_bar);

        // check life
        modelMatrix_life = glm::mat3(1);

        for (int i = 1; i <= life_count; i++) {
            modelMatrix_life *= transform2D::Translate(-55, 0);
            RenderMesh2D(meshes["circle_life"], shaders["VertexColor"], modelMatrix_life);
        }

        // check bullets
        modelMatrix_bullet = glm::mat3(1);

        for (int i = 1; i <= bullet_count; i++) {
            modelMatrix_bullet *= transform2D::Translate(-58, 0);
            RenderMesh2D(meshes["rectangle_bullet"], shaders["VertexColor"], modelMatrix_bullet);
        }
    }

    // check frame collision
    {
        if (translateX + (center_head.x / 2) > resolution.x && duck == 1) {

            dx = -1;
            reverse_duck = 0;
        }
        if (translateY + (center_head.y / 2) > resolution.y && duck == 1) {

            dy = -1;
            reverse_duck = 1;
        }
        if (translateX - (center_head.x) < 0 && duck == 1) {

            dx = 1;
            reverse_duck = 1;
        }
        if (translateY - (center_head.y) < 0 && duck == 1) {

            dy = 1;
            reverse_duck = 0;
        }
    }

    // duck status + transformations
    {
        modelMatrix = glm::mat3(1);

        if (duck_count == 5) {
            speed_inc += 0.4f;
            duck_count = 0;
        }

        if (timer > 5)
            duck = 0;

        if (duck == 1) {                                                            // while the duck is alive
            translateX += dx * deltaTimeSeconds * 200 * speed_inc;
            translateY += dy * deltaTimeSeconds * 200 * speed_inc;

            modelMatrix *= transform2D::Translate(translateX, translateY);

        } else if (hit == 0) {                                                      // the duck escaped / time ran out
            dy = 1;

            if (dy == -1)
                translateY -= dy * deltaTimeSeconds * 200;
            else
                translateY += dy * deltaTimeSeconds * 200;

            if (translateY > resolution.y) {

                duck = 1;
                duck_count++;
                life_count--;

                if (life_count == 0)
                    exit(0);

                bullet_count = 3;

                // render new duck
                {
                    translateX = rand() % resolution.x;

                    side = rand() % 2;
                    if (side == 0)
                        dx = -1;
                    else
                        dx = 1;

                    translateY = 0;

                    duck = 1;

                    // reset timer
                    timer = 0;
                }
            }

            modelMatrix *= transform2D::Translate(translateX, translateY);

        } else if (hit == 1) {                                                      // the duck was killed

            if (dy == -1)
                translateY += dy * deltaTimeSeconds * 200;
            else 
                translateY -= dy * deltaTimeSeconds * 200;

            if (translateY < -100) {

                hit = 0;
                duck_count++;

                if (score < 15)
                    score++;

                bullet_count = 3;

                // render new duck
                {
                    translateX = rand() % resolution.x;

                    side = rand() % 2;
                    if (side == 0)
                        dx = -1;
                    else
                        dx = 1;

                    translateY = 0;

                    duck = 1;

                    // reset timer
                    timer = 0;
                }
            }

            modelMatrix *= transform2D::Translate(translateX, translateY);
        }

        modelMatrix *= transform2D::Rotate(atan2(dy,dx) - M_PI_2);

        //modelMatrix_hitbox = glm::mat3(1);
        new_center_hitbox = modelMatrix * center_hitbox;
    }

    // wing animations
    {
        angularStep += angle_add * deltaTimeSeconds;

        if (angularStep < -0.25f)
            angle_add = 1;
        if (angularStep > 0.25f)
            angle_add = -1;
    }

    // duck mesh render
    {

        // duck eyes - alive
        if (duck == 1)
        {
            // render right eye sparkle
            modelMatrix_right_eye_sparkle = glm::mat3(1);
            modelMatrix_right_eye_sparkle *= modelMatrix;
            modelMatrix_right_eye_sparkle *= transform2D::Translate(17, 1);

            RenderMesh2D(meshes["circle_eye_sparkle"], shaders["VertexColor"], modelMatrix_right_eye_sparkle);

            // render left eye sparkle
            modelMatrix_left_eye_sparkle = glm::mat3(1);
            modelMatrix_left_eye_sparkle *= modelMatrix;
            modelMatrix_left_eye_sparkle *= transform2D::Translate(-17, 1);

            RenderMesh2D(meshes["circle_eye_sparkle"], shaders["VertexColor"], modelMatrix_left_eye_sparkle);

            // render right eye
            modelMatrix_right_eye = glm::mat3(1);
            modelMatrix_right_eye *= modelMatrix;
            modelMatrix_right_eye *= transform2D::Translate(17, 0);

            RenderMesh2D(meshes["circle_eye"], shaders["VertexColor"], modelMatrix_right_eye);

            // render left eye
            modelMatrix_left_eye = glm::mat3(1);
            modelMatrix_left_eye *= modelMatrix;
            modelMatrix_left_eye *= transform2D::Translate(-17, 0);

            RenderMesh2D(meshes["circle_eye"], shaders["VertexColor"], modelMatrix_left_eye);
        }

        // duck eyes - dead
        if (duck == 0 && hit == 1) {
            //
            modelMatrix_dead_eye_1 = glm::mat3(1);
            modelMatrix_dead_eye_1 *= modelMatrix;

            modelMatrix_dead_eye_1 *= transform2D::Translate(55.5f, 163.5f);
            modelMatrix_dead_eye_1 *= transform2D::Rotate(glm::radians(-45.f));
            modelMatrix_dead_eye_1 *= transform2D::Translate(-50, -160);

            RenderMesh2D(meshes["rectangle_dead_eye"], shaders["VertexColor"], modelMatrix_dead_eye_1);

            //
            modelMatrix_dead_eye_2 = glm::mat3(1);
            modelMatrix_dead_eye_2 *= modelMatrix;

            modelMatrix_dead_eye_2 *= transform2D::Translate(43.5f, 163.5f);
            modelMatrix_dead_eye_2 *= transform2D::Scale(-1, 1);
            modelMatrix_dead_eye_2 *= transform2D::Rotate(glm::radians(-45.f));
            modelMatrix_dead_eye_2 *= transform2D::Translate(-50, -160);

            RenderMesh2D(meshes["rectangle_dead_eye"], shaders["VertexColor"], modelMatrix_dead_eye_2);

            //
            modelMatrix_dead_eye_3 = glm::mat3(1);
            modelMatrix_dead_eye_3 *= modelMatrix;

            modelMatrix_dead_eye_3 *= transform2D::Translate(55.5f, 151);
            modelMatrix_dead_eye_3 *= transform2D::Rotate(glm::radians(45.f));
            modelMatrix_dead_eye_3 *= transform2D::Translate(-50, -160);

            RenderMesh2D(meshes["rectangle_dead_eye"], shaders["VertexColor"], modelMatrix_dead_eye_3);

            //
            modelMatrix_dead_eye_4 = glm::mat3(1);
            modelMatrix_dead_eye_4 *= modelMatrix;

            modelMatrix_dead_eye_4 *= transform2D::Translate(43.5f, 151);
            modelMatrix_dead_eye_4 *= transform2D::Scale(-1, 1);
            modelMatrix_dead_eye_4 *= transform2D::Rotate(glm::radians(45.f));
            modelMatrix_dead_eye_4 *= transform2D::Translate(-50, -160);

            RenderMesh2D(meshes["rectangle_dead_eye"], shaders["VertexColor"], modelMatrix_dead_eye_4);
        }

        // duck eyes - escaped
        if (duck == 0 && hit == 0) {
            //
            modelMatrix_happy_eye_1 = glm::mat3(1);
            modelMatrix_happy_eye_1 *= modelMatrix;

            modelMatrix_happy_eye_1 *= transform2D::Translate(54.5f, 158.5f);
            modelMatrix_happy_eye_1 *= transform2D::Rotate(glm::radians(45.f));
            modelMatrix_happy_eye_1 *= transform2D::Translate(-50, -160);

            RenderMesh2D(meshes["rectangle_happy_eye"], shaders["VertexColor"], modelMatrix_happy_eye_1);

            //
            modelMatrix_happy_eye_2 = glm::mat3(1);
            modelMatrix_happy_eye_2 *= modelMatrix;

            modelMatrix_happy_eye_2 *= transform2D::Translate(72.5f, 159.5f);
            modelMatrix_happy_eye_2 *= transform2D::Rotate(glm::radians(135.f));
            modelMatrix_happy_eye_2 *= transform2D::Translate(-50, -160);

            RenderMesh2D(meshes["rectangle_happy_eye"], shaders["VertexColor"], modelMatrix_happy_eye_2);

            //
            modelMatrix_happy_eye_3 = glm::mat3(1);
            modelMatrix_happy_eye_3 *= modelMatrix;

            modelMatrix_happy_eye_3 *= transform2D::Translate(26.5f, 161.5f);
            modelMatrix_happy_eye_3 *= transform2D::Scale(-1, 1);
            modelMatrix_happy_eye_3 *= transform2D::Rotate(glm::radians(135.f));
            modelMatrix_happy_eye_3 *= transform2D::Translate(-50, -160);

            RenderMesh2D(meshes["rectangle_happy_eye"], shaders["VertexColor"], modelMatrix_happy_eye_3);

            //
            modelMatrix_happy_eye_4 = glm::mat3(1);
            modelMatrix_happy_eye_4 *= modelMatrix;

            modelMatrix_happy_eye_4 *= transform2D::Translate(42.5f, 159.5f);
            modelMatrix_happy_eye_4 *= transform2D::Scale(-1, 1);
            modelMatrix_happy_eye_4 *= transform2D::Rotate(glm::radians(45.f));
            modelMatrix_happy_eye_4 *= transform2D::Translate(-50, -160);

            RenderMesh2D(meshes["rectangle_happy_eye"], shaders["VertexColor"], modelMatrix_happy_eye_4);
        }

        // rest of the body
        {
            // render head
            modelMatrix_head = glm::mat3(1);
            modelMatrix_head *= modelMatrix;

            RenderMesh2D(meshes["circle_head"], shaders["VertexColor"], modelMatrix_head);

            // render beak
            modelMatrix_beak = glm::mat3(1);
            modelMatrix_beak *= modelMatrix;

            RenderMesh2D(meshes["triangle_beak"], shaders["VertexColor"], modelMatrix_beak);

            // render body
            modelMatrix_body = glm::mat3(1);
            modelMatrix_body *= modelMatrix;

            RenderMesh2D(meshes["triangle_body"], shaders["VertexColor"], modelMatrix_body);

            // render right wing + animation
            modelMatrix_right_wing = glm::mat3(1);
            modelMatrix_right_wing *= modelMatrix;

            modelMatrix_right_wing *= transform2D::Translate(50, 80);
            modelMatrix_right_wing *= transform2D::Rotate(glm::radians(-60.f));
            modelMatrix_right_wing *= transform2D::Rotate(angularStep); // wing animation
            modelMatrix_right_wing *= transform2D::Translate(-50, -80);

            RenderMesh2D(meshes["triangle_wing"], shaders["VertexColor"], modelMatrix_right_wing);

            // render left wing + animation
            modelMatrix_left_wing = glm::mat3(1);
            modelMatrix_left_wing *= modelMatrix;

            modelMatrix_left_wing *= transform2D::Translate(50, 80);
            modelMatrix_left_wing *= transform2D::Scale(-1, 1);
            modelMatrix_left_wing *= transform2D::Rotate(glm::radians(-60.f));
            modelMatrix_left_wing *= transform2D::Rotate(angularStep);  // wing animation
            modelMatrix_left_wing *= transform2D::Translate(-50, -80);

            RenderMesh2D(meshes["triangle_wing"], shaders["VertexColor"], modelMatrix_left_wing);
        }
    }
}


void Tema1::FrameEnd()
{
    //DrawCoordinateSystem();
}


void Tema1::OnInputUpdate(float deltaTime, int mods)
{
}


void Tema1::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
    glm::vec3 mouse_click = glm::vec3(mouseX, resolution.y - mouseY, 0);

    if (duck == 1) {
        if (glm::distance(mouse_click, new_center_hitbox) < edge_hitbox) {
            duck = 0;
            hit = 1;
            bullet_count--;
        }
        else {
            bullet_count--;
        }
    }

    if (bullet_count < 1 && hit == 0) {
        duck = 0;
    }
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}