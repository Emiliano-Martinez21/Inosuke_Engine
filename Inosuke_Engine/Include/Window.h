#pragma once
#include "Prerequisites.h"

/**
 * Clase que encapsula una ventana de Windows para renderizado con Direct3D.
 *
 * Se encarga de crear y administrar el HWND asociado,
 * adem�s de almacenar dimensiones y nombre de la ventana.
 */
class Window {
public:
  /// Constructor por defecto.
  Window() = default;

  /// Destructor por defecto.
  ~Window() = default;

  /**
   * Inicializa la ventana de la aplicaci�n.
   *
   * @param hInstance Instancia de la aplicaci�n (WinMain).
   * @param nCmdShow  Par�metro de visualizaci�n inicial (ej. SW_SHOW).
   * @param wndproc   Funci�n de procedimiento de ventana (WinAPI).
   * @return          S_OK si fue exitoso; HRESULT en caso contrario.
   */
  HRESULT init(HINSTANCE hInstance, int nCmdShow, WNDPROC wndproc);

  /// Placeholder para l�gica de actualizaci�n de la ventana.
  void update();

  /// Placeholder para operaciones de renderizado relacionadas con la ventana.
  void render();

  /// Libera los recursos asociados a la ventana (HWND, instancia, etc.).
  void destroy();

public:
  /// Handle de la ventana de Windows (HWND).
  HWND m_hWnd = nullptr;

  /// Ancho de la ventana en p�xeles.
  unsigned int m_width;

  /// Alto de la ventana en p�xeles.
  unsigned int m_height;

private:
  /// Instancia de la aplicaci�n asociada a la ventana.
  HINSTANCE m_hInst = nullptr;

  /// Rect�ngulo que define la posici�n y dimensiones de la ventana.
  RECT m_rect;

  /// Nombre por defecto de la ventana (t�tulo en la barra superior).
  std::string m_windowName = "Inosuke Engine";
};
