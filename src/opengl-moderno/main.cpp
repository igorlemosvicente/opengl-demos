/**
 * Basic input features of GLFW, including handling of mouse and keyboard input.
 */

#include "glad.h"
#include <iostream>
#include <GLFW/glfw3.h>

#define WIDTH 500
#define HEIGHT 500

const char *vertex_shader_source = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}\0";
const char *fragment_shader_source = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                   "}\n\0";


void draw() {
  glClearColor(0.3, 0.3, 0.3, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);
}

int main() {
  // Garantir que a gente possa ter janelas, ou algo assim
  glfwInit();

  // Definindo a versão que queremos do OpenGL
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // Acho que define que vai ser o 3.3

  // Mesmo a gente tendo escolhido o modo "Compatibility", o professor disse que essa vai rodar melhor.
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Cria a tela
  GLFWwindow *window;
  window = glfwCreateWindow(WIDTH, HEIGHT, "Título da janela", NULL, NULL);

  if (window == NULL) {
    std::cout << "Deu pau para abrir a janela." << std::endl;
    exit(1);
  }

  glfwMakeContextCurrent(window); // Sempre antes de carregar as bibliotecas

  // Testar se conseguimos carregar as bibliotecas. Sempre depois de carregar o contexto
  GLADloadproc proc_address = (GLADloadproc) glfwGetProcAddress;
  char loader_loaded = gladLoadGLLoader(proc_address);
  if (!loader_loaded) {
    std::cout << "Não deu para carregar as bibliotecas." << std::endl;
    exit(2);
  }

  /**
   * Criação do Vertex Shader
   */
  // Cria um Vertex Shader na placa de vídeo.
  // A criação de shaders tem de ser sempre depois do carregamento das bibliotecas
  int vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
  // Pega o código fonte de um shader e o inicializa. Normalmente esse código estaria em um arquivo à parte, mas como estamos fazendo rápido, é uma string mesmo
  glShaderSource(vertex_shader_id, 1, &vertex_shader_source, NULL);
  glCompileShader(vertex_shader_id); // Processo assíncrono

  // Processo de compilação do vertex shader
  int success;
  char info_log[512];
  glGetShaderiv(vertex_shader_id, GL_COMPILE_STATUS, &success);

  // Checando o erro de compilação do shader
  if (!success) {
    glGetShaderInfoLog(vertex_shader_id, 512, NULL, info_log);
    std::cout << "Erro compilação shader" << std::endl << info_log << std::endl;
    return 3;
  }

  /**
   * Criação do Fragment Shader
   */
  // Cria um Fragment Shader na placa de vídeo.
  // A criação de shaders tem de ser sempre depois do carregamento das bibliotecas
  int fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
  // Pega o código fonte de um shader e o inicializa. Normalmente esse código estaria em um arquivo à parte, mas como estamos fazendo rápido, é uma string mesmo
  glShaderSource(fragment_shader_id, 1, &fragment_shader_source, NULL);
  glCompileShader(fragment_shader_id); // Processo assíncrono

  // Processo de compilação do fragment shader
  glGetShaderiv(fragment_shader_id, GL_COMPILE_STATUS, &success);

  // Checando o erro de compilação do shader
  if (!success) {
    glGetShaderInfoLog(fragment_shader_id, 512, NULL, info_log);
    std::cout << "Erro compilação shader" << std::endl << info_log << std::endl;
    return 3;
  }

  while (true) {
    if (glfwWindowShouldClose(window)) {
      break;
    }

    draw();

    // Usar buffer duplo (Foi adicionado ao código depois do PollEvents
    glfwSwapBuffers(window);

    // Alguma coisa de eventos e cliques na tela ou algo assim.
    // Quando não tem isso, dá problema até ao tentar fechar.
    glfwPollEvents();
  }

  return 0;
}
