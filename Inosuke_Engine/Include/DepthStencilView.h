#pragma once
#include "Prerequisites.h"

class Device;
class DeviceContext;
class Texture;

/**
 * Clase que encapsula un objeto ID3D11DepthStencilView de Direct3D 11.
 *
 * Su prop�sito es administrar la creaci�n, uso y destrucci�n de una vista
 * de profundidad/est�ncil, necesaria para las operaciones de z-buffering y
 * pruebas de est�ncil en el pipeline gr�fico.
 */
class DepthStencilView {
public:
  /**
   * Constructor por defecto.
   * No inicializa recursos gr�ficos hasta que se llame a init().
   */
  DepthStencilView() = default;

  /**
   * Destructor por defecto.
   * No libera autom�ticamente el recurso; debe llamarse a destroy().
   */
  ~DepthStencilView() = default;

  /**
   * Inicializa la vista de profundidad/est�ncil a partir de una textura.
   *
   * @param device        Dispositivo Direct3D usado para crear la vista.
   * @param depthStencil  Textura que actuar� como buffer de profundidad/est�ncil.
   * @param format        Formato DXGI que define c�mo se interpretan los datos.
   * @return              S_OK si la creaci�n fue exitosa; un HRESULT de error en caso contrario.
   */
  HRESULT init(Device& device, Texture& depthStencil, DXGI_FORMAT format);

  /**
   * Punto de extensi�n para actualizar par�metros internos en caso de necesitarse.
   * Actualmente no realiza ninguna operaci�n.
   */
  void update() {};

  /**
   * Asigna esta vista de profundidad/est�ncil al pipeline gr�fico.
   *
   * @param deviceContext Contexto de dispositivo donde se aplicar� la vista.
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
   * Puntero al objeto de vista de profundidad/est�ncil de Direct3D 11.
   * Es v�lido tras una inicializaci�n exitosa con init() y se restablece a nullptr en destroy().
   */
  ID3D11DepthStencilView* m_depthStencilView = nullptr;
};
