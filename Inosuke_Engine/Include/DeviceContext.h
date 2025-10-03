#pragma once
#include "Prerequisites.h"

/**
 * Clase que encapsula un ID3D11DeviceContext de Direct3D 11.
 *
 * Su función principal es administrar las operaciones del pipeline gráfico,
 * como asignación de recursos, estados, shaders y envío de comandos de dibujo.
 *
 * Nota: representa el contexto inmediato; no maneja múltiples contextos en paralelo.
 */
class DeviceContext {
public:
  /// Constructor por defecto: no asocia ningún contexto aún.
  DeviceContext() = default;

  /// Destructor por defecto: no libera automáticamente el contexto.
  ~DeviceContext() = default;

  /// Inicializa el contexto de dispositivo.
  void init();

  /// Método placeholder para actualizaciones internas (sin lógica por ahora).
  void update();

  /// Método placeholder para render (puede usarse para pruebas o debug).
  void render();

  /// Libera el recurso de contexto de dispositivo.
  void destroy();

  /**
   * Configura los viewports activos en el rasterizador.
   * @param NumViewports Número de viewports.
   * @param pViewports   Arreglo de descriptores de viewport.
   */
  void RSSetViewports(unsigned int NumViewports, const D3D11_VIEWPORT* pViewports);

  /**
   * Asigna recursos de shader a la etapa de Pixel Shader.
   */
  void PSSetShaderResources(unsigned int StartSlot,
                            unsigned int NumViews,
                            ID3D11ShaderResourceView* const* ppShaderResourceViews);

  /**
   * Define el Input Layout usado por el ensamblador de entrada.
   */
  void IASetInputLayout(ID3D11InputLayout* pInputLayout);

  /**
   * Asigna un Vertex Shader al pipeline.
   */
  void VSSetShader(ID3D11VertexShader* pVertexShader,
                    ID3D11ClassInstance* const* ppClassInstances,
                    unsigned int NumClassInstances);

  /**
   * Asigna un Pixel Shader al pipeline.
   */
  void PSSetShader(ID3D11PixelShader* pPixelShader,
                    ID3D11ClassInstance* const* ppClassInstances,
                    unsigned int NumClassInstances);

  /**
   * Copia datos desde CPU hacia un recurso en GPU.
   */
  void UpdateSubresource(ID3D11Resource* pDstResource,
                          unsigned int DstSubresource,
                          const D3D11_BOX* pDstBox,
                          const void* pSrcData,
                          unsigned int SrcRowPitch,
                          unsigned int SrcDepthPitch);

  /**
   * Asigna buffers de vértices al ensamblador de entrada.
   */
  void IASetVertexBuffers(unsigned int StartSlot,
                          unsigned int NumBuffers,
                          ID3D11Buffer* const* ppVertexBuffers,
                          const unsigned int* pStrides,
                          const unsigned int* pOffsets);

  /**
   * Asigna un Index Buffer al ensamblador de entrada.
   */
  void IASetIndexBuffer(ID3D11Buffer* pIndexBuffer,
                        DXGI_FORMAT Format,
                        unsigned int Offset);

  /**
   * Asigna estados de muestreo al Pixel Shader.
   */
  void PSSetSamplers(unsigned int StartSlot,
                      unsigned int NumSamplers,
                      ID3D11SamplerState* const* ppSamplers);

  /**
   * Configura el estado de rasterización.
   */
  void RSSetState(ID3D11RasterizerState* pRasterizerState);

  /**
   * Configura un Blend State en la etapa Output Merger.
   */
  void OMSetBlendState(ID3D11BlendState* pBlendState,
                        const float BlendFactor[4],
                        unsigned int SampleMask);

  /**
   * Asigna render targets y depth stencil al Output Merger.
   */
  void OMSetRenderTargets(unsigned int NumViews,
                          ID3D11RenderTargetView* const* ppRenderTargetViews,
                          ID3D11DepthStencilView* pDepthStencilView);

  /**
   * Define la topología de primitivas a dibujar.
   */
  void IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY Topology);

  /**
   * Limpia un Render Target con un color dado.
   */
  void ClearRenderTargetView(ID3D11RenderTargetView* pRenderTargetView,
                              const float ColorRGBA[4]);

  /**
   * Limpia un Depth Stencil View con valores de profundidad/esténcil.
   */
  void ClearDepthStencilView(ID3D11DepthStencilView* pDepthStencilView,
                              unsigned int ClearFlags,
                              float Depth,
                              UINT8 Stencil);

  /**
   * Asigna constant buffers al Vertex Shader.
   */
  void VSSetConstantBuffers(unsigned int StartSlot,
                            unsigned int NumBuffers,
                            ID3D11Buffer* const* ppConstantBuffers);

  /**
   * Asigna constant buffers al Pixel Shader.
   */
  void PSSetConstantBuffers(unsigned int StartSlot,
                            unsigned int NumBuffers,
                            ID3D11Buffer* const* ppConstantBuffers);

  /**
   * Envía un comando para dibujar primitivas indexadas.
   */
  void DrawIndexed(unsigned int IndexCount,
                    unsigned int StartIndexLocation,
                    int BaseVertexLocation);

public:
  /// Puntero al contexto inmediato de Direct3D 11 (válido tras init()).
  ID3D11DeviceContext* m_deviceContext = nullptr;
};
