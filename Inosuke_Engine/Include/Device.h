#pragma once
#include "Prerequisites.h"

/**
 * Clase que encapsula un ID3D11Device de Direct3D 11.
 *
 * Su función es centralizar la creación de recursos gráficos
 * como vistas, texturas, shaders, buffers y estados de muestreo.
 *
 * Nota: esta clase solo gestiona el dispositivo, no el contexto.
 */
class Device {
public:
  /// Constructor por defecto: no crea el dispositivo aún.
  Device() = default;

  /// Destructor por defecto: no libera automáticamente el recurso.
  ~Device() = default;

  /// Inicializa el dispositivo gráfico.
  void init();

  /// Método de actualización general (actualmente sin lógica).
  void update();

  /// Método de renderizado (actualmente sin lógica).
  void render();

  /// Libera los recursos del dispositivo.
  void destroy();

  /**
   * Crea una Render Target View (RTV).
   *
   * @param pResource Recurso base, normalmente una textura.
   * @param pDesc     Descriptor opcional de la RTV.
   * @param ppRTView  Puntero de salida con la RTV creada.
   */
  HRESULT CreateRenderTargetView(ID3D11Resource* pResource,
                                  const D3D11_RENDER_TARGET_VIEW_DESC* pDesc,
                                  ID3D11RenderTargetView** ppRTView);

  /**
   * Crea una textura 2D.
   *
   * @param pDesc        Descriptor que define la textura.
   * @param pInitialData Datos iniciales opcionales.
   * @param ppTexture2D  Puntero de salida con la textura creada.
   */
  HRESULT CreateTexture2D(const D3D11_TEXTURE2D_DESC* pDesc,
                          const D3D11_SUBRESOURCE_DATA* pInitialData,
                          ID3D11Texture2D** ppTexture2D);

  /**
   * Crea una Depth Stencil View (DSV).
   *
   * @param pResource Recurso base, debe ser una textura de profundidad.
   * @param pDesc     Descriptor opcional de la DSV.
   * @param ppDepthStencilView Puntero de salida con la DSV creada.
   */
  HRESULT CreateDepthStencilView(ID3D11Resource* pResource,
                                  const D3D11_DEPTH_STENCIL_VIEW_DESC* pDesc,
                                  ID3D11DepthStencilView** ppDepthStencilView);

  /**
   * Crea un Vertex Shader.
   *
   * @param pShaderBytecode Bytecode compilado.
   * @param BytecodeLength  Tamaño del bytecode.
   * @param pClassLinkage   Enlace de clases (opcional).
   * @param ppVertexShader  Puntero de salida con el shader creado.
   */
  HRESULT CreateVertexShader(const void* pShaderBytecode,
                              unsigned int BytecodeLength,
                              ID3D11ClassLinkage* pClassLinkage,
                              ID3D11VertexShader** ppVertexShader);

  /**
   * Crea un Input Layout.
   *
   * @param pInputElementDescs Lista de elementos de entrada.
   * @param NumElements        Número de elementos.
   * @param pShaderBytecodeWithInputSignature Bytecode que contiene la firma de entrada.
   * @param BytecodeLength     Tamaño del bytecode.
   * @param ppInputLayout      Puntero de salida con el layout creado.
   */
  HRESULT CreateInputLayout(const D3D11_INPUT_ELEMENT_DESC* pInputElementDescs,
                            unsigned int NumElements,
                            const void* pShaderBytecodeWithInputSignature,
                            unsigned int BytecodeLength,
                            ID3D11InputLayout** ppInputLayout);

  /**
   * Crea un Pixel Shader.
   *
   * @param pShaderBytecode Bytecode compilado.
   * @param BytecodeLength  Tamaño del bytecode.
   * @param pClassLinkage   Enlace de clases (opcional).
   * @param ppPixelShader   Puntero de salida con el shader creado.
   */
  HRESULT CreatePixelShader(const void* pShaderBytecode,
                            unsigned int BytecodeLength,
                            ID3D11ClassLinkage* pClassLinkage,
                            ID3D11PixelShader** ppPixelShader);

  /**
   * Crea un buffer genérico (vertex, index, constant, etc.).
   *
   * @param pDesc        Descriptor del buffer.
   * @param pInitialData Datos iniciales opcionales.
   * @param ppBuffer     Puntero de salida con el buffer creado.
   */
  HRESULT CreateBuffer(const D3D11_BUFFER_DESC* pDesc,
                        const D3D11_SUBRESOURCE_DATA* pInitialData,
                        ID3D11Buffer** ppBuffer);

  /**
   * Crea un Sampler State.
   *
   * @param pSamplerDesc   Descriptor del muestreador.
   * @param ppSamplerState Puntero de salida con el estado creado.
   */
  HRESULT CreateSamplerState(const D3D11_SAMPLER_DESC* pSamplerDesc,
                              ID3D11SamplerState** ppSamplerState);

public:
  /// Puntero al dispositivo Direct3D 11. Se crea en init() y se libera en destroy().
  ID3D11Device* m_device = nullptr;
};
