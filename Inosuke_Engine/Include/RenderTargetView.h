#pragma once
#include "Prerequisites.h"

//--------------------------------------------------------------------------------------
// Declaraciones adelantadas para reducir dependencias cruzadas
//--------------------------------------------------------------------------------------
class Device;
class DeviceContext;
class Texture;
class DepthStencilView;

/**
 * Clase que encapsula un ID3D11RenderTargetView en Direct3D 11.
 *
 * Su propósito es representar un destino de renderizado, ya sea el back buffer
 * de la swap chain o una textura usada para render targets auxiliares
 * (ej. G-Buffer, mapas de sombra, postprocesado).
 */
class RenderTargetView {
public:
  /// Constructor por defecto: no inicializa ningún recurso.
  RenderTargetView() = default;

  /// Destructor por defecto: no libera automáticamente el recurso.
  ~RenderTargetView() = default;

  /**
   * Inicializa el Render Target View a partir del back buffer.
   *
   * @param device     Dispositivo Direct3D que crea el RTV.
   * @param backBuffer Textura asociada al back buffer de la swap chain.
   * @param Format     Formato DXGI del RTV (ej. DXGI_FORMAT_R8G8B8A8_UNORM).
   * @return           S_OK si fue exitoso; un código HRESULT en caso de error.
   */
  HRESULT init(Device& device, Texture& backBuffer, DXGI_FORMAT Format);

  /**
   * Inicializa el Render Target View desde una textura genérica.
   *
   * @param device        Dispositivo Direct3D que crea el RTV.
   * @param inTex         Textura que actuará como destino de renderizado.
   * @param ViewDimension Dimensión de la vista (ej. D3D11_RTV_DIMENSION_TEXTURE2D).
   * @param Format        Formato DXGI del RTV.
   * @return              S_OK si fue exitoso; un código HRESULT en caso de error.
   *
   * Útil cuando se requieren render targets adicionales (ej. G-Buffer o shadow maps).
   */
  HRESULT init(Device& device,
                Texture& inTex,
                D3D11_RTV_DIMENSION ViewDimension,
                DXGI_FORMAT Format);

  /// Placeholder para futuras actualizaciones dinámicas del RTV.
  void update();

  /**
   * Asigna el RTV y un Depth Stencil View al pipeline.
   *
   * Además, limpia el RTV con el color especificado.
   *
   * @param deviceContext    Contexto donde se aplica.
   * @param depthStencilView Vista de profundidad/esténcil asociada.
   * @param numViews         Número de RTVs (típicamente 1).
   * @param ClearColor       Color de limpieza en formato RGBA.
   */
  void render(DeviceContext& deviceContext,
              DepthStencilView& depthStencilView,
              unsigned int numViews,
              const float ClearColor[4]);

  /**
   * Asigna el RTV al pipeline sin limpiar ni asociar Depth Stencil.
   *
   * @param deviceContext Contexto donde se aplica.
   * @param numViews      Número de RTVs (típicamente 1).
   */
  void render(DeviceContext& deviceContext,
              unsigned int numViews);

  /**
   * Libera el recurso COM asociado al RTV.
   *
   * Puede llamarse múltiples veces sin riesgo (idempotente).
   */
  void destroy();

private:
  /// Puntero COM al recurso Render Target View de Direct3D 11.
  ID3D11RenderTargetView* m_renderTargetView = nullptr;
};
