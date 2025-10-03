#pragma once
#include "Prerequisites.h"

/**
 * Clase que encapsula una ventana de Windows para renderizado con Direct3D.
 *
 * Se encarga de crear y administrar el HWND asociado,
 * además de almacenar dimensiones y nombre de la ventana.
 */
class Window {
public:
  /// Constructor por defecto.
  Window() = default;

  /// Destructor por defecto.
  ~Window() = default;

  /**
   * Inicializa la ventana de la aplicación.
   *
   * @param hInstance Instancia de la aplicación (WinMain).
   * @param nCmdShow  Parámetro de visualización inicial (ej. SW_SHOW).
   * @param wndproc   Función de procedimiento de ventana (WinAPI).
   * @return          S_OK si fue exitoso; HRESULT en caso contrario.
   */
  HRESULT init(HINSTANCE hInstance, int nCmdShow, WNDPROC wndproc);

  /// Placeholder para lógica de actualización de la ventana.
  void update();

  /// Placeholder para operaciones de renderizado relacionadas con la ventana.
  void render();

  /// Libera los recursos asociados a la ventana (HWND, instancia, etc.).
  void destroy();

public:
  /// Handle de la ventana de Windows (HWND).
  HWND m_hWnd = nullptr;

  /// Ancho de la ventana en píxeles.
  unsigned int m_width;

  /// Alto de la ventana en píxeles.
  unsigned int m_height;

private:
  /// Instancia de la aplicación asociada a la ventana.
  HINSTANCE m_hInst = nullptr;

  /// Rectángulo que define la posición y dimensiones de la ventana.
  RECT m_rect;

  /// Nombre por defecto de la ventana (título en la barra superior).
  std::string m_windowName = "Inosuke Engine";
};
