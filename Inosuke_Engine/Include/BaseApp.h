#pragma once
#include "Prerequisites.h"
#include "Window.h"
#include "Device.h"
#include "DeviceContext.h"
#include "SwapChain.h"
#include "Texture.h"
#include "RenderTargetView.h"
#include "DepthStencilView.h"
#include "Viewport.h"
#include "ShaderProgram.h"
#include "MeshComponent.h"
#include "Buffer.h"
#include "SamplerState.h"

/**
 * @brief Clase principal que administra todo el ciclo de vida de la aplicación.
 * Se encarga de inicializar Direct3D, actualizar por cuadro y renderizar.
 */
class BaseApp {
public:
  BaseApp(HINSTANCE hInst, int nCmdShow);
  ~BaseApp() { destroy(); } // Libera recursos al cerrar

  int run(HINSTANCE hInst, int nCmdShow); // Loop principal de la aplicación

  HRESULT init(); // Inicializa todos los objetos gráficos

  void update(float deltaTime); // Actualiza lógica y matrices por cuadro

  void render(); // Dibuja el frame

  void destroy(); // Libera todos los recursos

private:
  // Procesa los mensajes de Windows (teclado, ratón, cierre, etc.)
  static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
  Window          m_window;            // Administra la ventana Win32
  Device          m_device;            // ID3D11Device (creación de recursos)
  DeviceContext   m_deviceContext;     // ID3D11DeviceContext (comandos GPU)
  SwapChain       m_swapChain;         // Intercambio de buffers (VSync)

  Texture         m_backBuffer;        // Back buffer obtenido del swap chain
  RenderTargetView m_renderTargetView; // Donde se dibuja el frame final

  Texture         m_depthStencil;      // Textura usada para pruebas de profundidad
  DepthStencilView m_depthStencilView; // Vista para habilitar depth testing

  Viewport        m_viewport;          // Región visible donde se dibuja

  ShaderProgram   m_shaderProgram;     // Vertex + Pixel Shaders + InputLayout

  MeshComponent   m_mesh;              // Geometría (vértices + índices)
  Buffer          m_vertexBuffer;      // Buffer de vértices
  Buffer          m_indexBuffer;       // Buffer de índices

  Buffer          m_cbNeverChanges;     // Constant buffer fijo
  Buffer          m_cbChangeOnResize;   // Constant buffer dependiente de ventana
  Buffer          m_cbChangesEveryFrame;// Constant buffer animado por cuadro

  Texture         m_textureCube;       // Textura aplicada al cubo
  SamplerState    m_samplerState;      // Parámetros de muestreo de textura

  // Matrices base de transformación
  XMMATRIX        m_World;       // Transformación del modelo
  XMMATRIX        m_View;        // Cámara
  XMMATRIX        m_Projection;  // Proyección en perspectiva

  XMFLOAT4        m_vMeshColor;  // Color del objeto (modificado en update)

  // Estructuras para los constant buffers
  CBChangeOnResize   cbChangesOnResize;
  CBNeverChanges     cbNeverChanges;
  CBChangesEveryFrame cb;
};
