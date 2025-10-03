#pragma once
#include "Prerequisites.h"

//--------------------------------------------------------------------------------------
// Declaraciones adelantadas
//--------------------------------------------------------------------------------------
class Device;
class DeviceContext;
class Window;
class Texture;

/**
 * Clase que encapsula un IDXGISwapChain en Direct3D 11.
 *
 * El Swap Chain administra los buffers de renderizado (front y back buffer)
 * que se presentan en la ventana de la aplicaci�n. Permite trabajar con
 * caracter�sticas como V-Sync y MSAA (Multisample Anti-Aliasing).
 */
class SwapChain {
public:
  /// Constructor por defecto: no inicializa el swap chain a�n.
  SwapChain() = default;

  /// Destructor por defecto: no libera autom�ticamente los recursos COM.
  ~SwapChain() = default;

  /**
   * Inicializa el Swap Chain y obtiene el back buffer.
   *
   * @param device        Dispositivo Direct3D que crea el recurso.
   * @param deviceContext Contexto inmediato asociado al dispositivo.
   * @param backBuffer    Textura que contendr� el back buffer.
   * @param window        Ventana donde se mostrar� el contenido renderizado.
   * @return              S_OK si fue exitoso; HRESULT de error en caso contrario.
   *
   * Tras una inicializaci�n exitosa, m_swapChain ser� v�lido.
   */
  HRESULT init(Device& device,
    DeviceContext& deviceContext,
    Texture& backBuffer,
    Window window);

  /// Placeholder para actualizaciones din�micas (resize, MSAA, etc.).
  void update();

  /// Placeholder para operaciones de render previas a la presentaci�n.
  void render();

  /**
   * Libera los recursos asociados al swap chain y sus interfaces DXGI.
   *
   * Despu�s de esta llamada, m_swapChain ser� nullptr.
   */
  void destroy();

  /**
   * Presenta el contenido del back buffer en la ventana asociada.
   *
   * Internamente llama a IDXGISwapChain::Present.
   * Puede configurarse con o sin V-Sync en la implementaci�n.
   */
  void present();

public:
  /// Objeto COM principal que representa el swap chain.
  IDXGISwapChain* m_swapChain = nullptr;

  /// Tipo de driver utilizado (hardware, referencia, software, etc.).
  D3D_DRIVER_TYPE m_driverType = D3D_DRIVER_TYPE_NULL;

private:
  /// Nivel de caracter�sticas de Direct3D soportado (ej. 11.0, 11.1, etc.).
  D3D_FEATURE_LEVEL m_featureLevel = D3D_FEATURE_LEVEL_11_0;

  /// N�mero de muestras para MSAA (ej. 4 = 4x multisampling).
  unsigned int m_sampleCount;

  /// Cantidad de niveles de calidad soportados por MSAA.
  unsigned int m_qualityLevels;

  /// Interfaz DXGI para el dispositivo.
  IDXGIDevice* m_dxgiDevice = nullptr;

  /// Interfaz DXGI para el adaptador f�sico (GPU).
  IDXGIAdapter* m_dxgiAdapter = nullptr;

  /// Interfaz DXGI para la f�brica (creaci�n de swap chains).
  IDXGIFactory* m_dxgiFactory = nullptr;
};
