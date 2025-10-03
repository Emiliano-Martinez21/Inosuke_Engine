#pragma once
#include "Prerequisites.h"

class Device;
class DeviceContext;
class Texture;

/**
 * Clase que encapsula un objeto ID3D11DepthStencilView de Direct3D 11.
 *
 * Su propósito es administrar la creación, uso y destrucción de una vista
 * de profundidad/esténcil, necesaria para las operaciones de z-buffering y
 * pruebas de esténcil en el pipeline gráfico.
 */
class DepthStencilView {
public:
  /**
   * Constructor por defecto.
   * No inicializa recursos gráficos hasta que se llame a init().
   */
  DepthStencilView() = default;

  /**
   * Destructor por defecto.
   * No libera automáticamente el recurso; debe llamarse a destroy().
   */
  ~DepthStencilView() = default;

  /**
   * Inicializa la vista de profundidad/esténcil a partir de una textura.
   *
   * @param device        Dispositivo Direct3D usado para crear la vista.
   * @param depthStencil  Textura que actuará como buffer de profundidad/esténcil.
   * @param format        Formato DXGI que define cómo se interpretan los datos.
   * @return              S_OK si la creación fue exitosa; un HRESULT de error en caso contrario.
   */
  HRESULT init(Device& device, Texture& depthStencil, DXGI_FORMAT format);

  /**
   * Punto de extensión para actualizar parámetros internos en caso de necesitarse.
   * Actualmente no realiza ninguna operación.
   */
  void update() {};

  /**
   * Asigna esta vista de profundidad/esténcil al pipeline gráfico.
   *
   * @param deviceContext Contexto de dispositivo donde se aplicará la vista.
   * @pre                 Debe haberse llamado previamente a init().
   */
  void render(DeviceContext& deviceContext);

  /**
   * Libera el recurso de ID3D11DepthStencilView.
   * Puede llamarse varias veces sin causar errores.
   */
  void destroy();

public:
  /**
   * Puntero al objeto de vista de profundidad/esténcil de Direct3D 11.
   * Es válido tras una inicialización exitosa con init() y se restablece a nullptr en destroy().
   */
  ID3D11DepthStencilView* m_depthStencilView = nullptr;
};
