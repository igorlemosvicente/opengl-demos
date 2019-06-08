/**
 * Basic input features of GLFW, including handling of mouse and keyboard input.
 */

#include "glad.h"
#include <iostream>
#include <GLFW/glfw3.h>

#define WIDTH 500
#define HEIGHT 500

int main() {
  // Garantir que a gente possa ter janelas, ou algo assim
  glfwInit();

  // Definindo a versão que queremos do OpenGL
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // Acho que define que vai ser o 3.3

  // Mesmo a gente tendo escolhido o modo "Compatibility", o professor disse que essa vai rodar melhor.
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Cria a tela
  GLFWwindow* window;
  window = glfwCreateWindow(WIDTH, HEIGHT, "Título da janela", NULL, NULL);

  if (window == NULL) {
    std::cout << "Deu pau para abrir a janela." << std::endl;
    exit(1);
  }

  glfwMakeContextCurrent(window);

  // Testar se conseguimos carregar as bibliotecas
  GLADloadproc proc_address = (GLADloadproc)glfwGetProcAddress;
  char loader_loaded = gladLoadGLLoader(proc_address);
  if (!loader_loaded) {
    std::cout << "Não deu para carregar as bibliotecas." << std::endl;
    exit(2);
  }

  while (true) {
    if (glfwWindowShouldClose(window)) {
      break;
    }

    // Usar buffer duplo (Foi adicionado ao código depois do PollEvents
    glfwSwapBuffers();

    // Alguma coisa de eventos e cliques na tela ou algo assim.
    // Quando não tem isso, dá problema até ao tentar fechar.
    glfwPollEvents();
  }

  return 0;
}
