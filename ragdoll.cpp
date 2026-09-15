#include<iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace std;

struct Engine {
    GLFWwindow* window = nullptr;
    
    bool init() {
        if (!glfwInit()) {
            cerr << "Failed to initialize GLFW\n";
            return 1;
        }
        
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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

        cout << "OpenGL: " << glGetString(GL_VERSION) << '\n';
        
        return true;
    }

    void run() {
        while(!glfwWindowShouldClose(window)) {
            glClear(GL_COLOR_BUFFER_BIT);

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

    engine.run();
    engine.shutdown();

    return 0;
}
