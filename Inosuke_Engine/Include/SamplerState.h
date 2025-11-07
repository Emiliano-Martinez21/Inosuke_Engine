#pragma once
#include "Prerequisites.h"

class Device;
class DeviceContext;

/**
 * @class SamplerState
 * @brief Maneja un ID3D11SamplerState que controla cómo se leen las texturas en los shaders.
 */
class SamplerState {
public:
  SamplerState() = default;   // Constructor simple
  ~SamplerState() = default;  // Destructor (destroy() libera el recurso)

  /**
   * @brief Crea un sampler con configuración por defecto
   * (filtrado lineal + wrap en todas las direcciones).
   */
  HRESULT init(Device& device);

  /**
   * @brief Punto de extensión para cambiar configuración del sampler.
   * Actualmente no hace nada.
   */
  void update();

  /**
   * @brief Enlaza este sampler al Pixel Shader.
   * PSSetSamplers(StartSlot, 1, &m_sampler);
   */
  void render(DeviceContext& deviceContext,
    unsigned int StartSlot,
    unsigned int NumSamplers);

  /**
   * @brief Libera el recurso COM del sampler.
   */
  void destroy();

public:
  ID3D11SamplerState* m_sampler = nullptr;  // Sampler de Direct3D (creado en init)
};
