#include<iostream>
#include<glm/vec2.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include<cmath>
#include<vector>

using namespace std;
using namespace glm;

struct Bone {
    vec2 pos, vel;
    float angle, angVel, halfLength, radius;

    Bone (vec2 pos, vec2 vel, float a, float hf, float r) : pos(pos), vel(vel), angle(a), angVel(0.0f), halfLength(hf), radius(r){}

    void draw() {
        vec2 dir(cos(angle), sin(angle));
            vec2 p1 = pos - dir * halfLength;
            vec2 p2 = pos + dir * halfLength;

            vec2 n(-dir.y, dir.x);
            glBegin(GL_QUADS);

            glVertex2f(
                p1.x + n.x * radius,
                p1.y + n.y * radius
            );

            glVertex2f(
                p2.x + n.x * radius,
                p2.y + n.y * radius
            );

            glVertex2f(
                p2.x - n.x * radius,
                p2.y - n.y * radius
            );

            glVertex2f(
                p1.x - n.x * radius,
                p1.y - n.y * radius
            );

            glEnd();

            // Circles
            const int segments = 32;

            for (vec2 center : {p1, p2}) {
                glBegin(GL_TRIANGLE_FAN);

                glVertex2f(center.x, center.y);

                for (int i = 0; i <= segments; i++) {
                    float a = 2.0f * 3.14159265359f * i / segments;

                    glVertex2f(
                        center.x + std::cos(a) * radius,
                        center.y + std::sin(a) * radius
                    );
                }
                glEnd();
            }   
    }

};

struct Joint {

};

struct Engine {
    GLFWwindow* window = nullptr;
    
    bool init() {
        if (!glfwInit()) {
            cerr << "Failed to initialize GLFW\n";
            return 1;
        }
        
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

        window = glfwCreateWindow(1280, 720, "Ragdoll", nullptr, nullptr );
        
        if(!window) {
            cerr << "Failed to create a window\n";
            glfwTerminate();
                return 1;
        }

        glfwMakeContextCurrent(window);

        if(!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
            cerr << "Failed to initialize GLAD\n";
            glfwDestroyWindow(window);
            glfwTerminate();
            return 1;
        }

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        glOrtho(0, 1280, 720, 0, -1, 1);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        cout << "OpenGL: " << glGetString(GL_VERSION) << '\n';
        
        return true;
    }

    void run(vector<Bone>& bones) {
        while(!glfwWindowShouldClose(window)) {
            glClear(GL_COLOR_BUFFER_BIT);

            for (Bone& bone : bones) {
                bone.draw();
            }

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }

    void shutdown() {
        glfwDestroyWindow(window);
        glfwTerminate(); 
    }

};

int main() {
    Engine engine;
    
    if (!engine.init())
        return 1;
    
    vector<Bone> bones = {
        Bone(vec2(450, 330), vec2(0), 0,           20, 7),  // armR
        Bone(vec2(350, 330), vec2(0), 0,           20, 7),  // armL
        Bone(vec2(500, 330), vec2(0), 0,           18, 6),  // forearmR
        Bone(vec2(300, 330), vec2(0), 0,           18, 6),  // forearmL

        Bone(vec2(300, 330), vec2(0),  3.14f/4.f,  28, 8), // legL
        Bone(vec2(300, 330), vec2(0), -3.14f/4.f,  28, 8), // legR

        Bone(vec2(300, 330), vec2(0),  3.14f/4.f,  24, 7), // calfL
        Bone(vec2(300, 330), vec2(0), -3.14f/4.f,  24, 7), // calfR

        Bone(vec2(300, 330), vec2(0), 0,           13, 3),  // hip/torso
        Bone(vec2(300, 330), vec2(0),  3.14f/2.f,  28, 15), // chest/body
        Bone(vec2(300, 330), vec2(0), 0,           12, 11)  // head
    };

    engine.run(bones);
    
    engine.shutdown();

    return 0;
}
