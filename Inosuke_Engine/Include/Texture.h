#pragma once
#include "Prerequisites.h"

//--------------------------------------------------------------------------------------
// Declaraciones adelantadas
//--------------------------------------------------------------------------------------
class Device;
class DeviceContext;

/**
 * Clase que encapsula una textura 2D en Direct3D 11.
 *
 * Administra tanto el recurso de textura en GPU (ID3D11Texture2D)
 * como su vista como recurso de shader (ID3D11ShaderResourceView),
 * permitiendo cargar desde archivo, crear desde memoria o copiar
 * desde otra textura existente.
 */
class Texture {
public:
  /// Constructor por defecto: no crea recursos.
  Texture() = default;

  /// Destructor por defecto: no libera automáticamente recursos COM.
  ~Texture() = default;

  /**
   * Inicializa una textura desde archivo.
   *
   * Crea el recurso de textura y su Shader Resource View
   * para ser utilizada en los shaders.
   *
   * @param device        Dispositivo Direct3D.
   * @param textureName   Ruta o nombre de archivo de imagen.
   * @param extensionType Tipo de archivo (PNG, JPG, DDS, etc.).
   * @return              S_OK si es exitoso; HRESULT en caso de error.
   */
  HRESULT init(Device& device,
    const std::string& textureName,
    ExtensionType extensionType);

  /**
   * Inicializa una textura creada en memoria.
   *
   * Útil para render targets, depth buffers o texturas dinámicas.
   *
   * @param device        Dispositivo Direct3D.
   * @param width         Ancho en píxeles.
   * @param height        Alto en píxeles.
   * @param Format        Formato DXGI.
   * @param BindFlags     Banderas de enlace (ej. SHADER_RESOURCE, RENDER_TARGET).
   * @param sampleCount   Número de muestras MSAA (default = 1).
   * @param qualityLevels Niveles de calidad de MSAA.
   * @return              S_OK si es exitoso; HRESULT en caso de error.
   */
  HRESULT init(Device& device,
    unsigned int width,
    unsigned int height,
    DXGI_FORMAT Format,
    unsigned int BindFlags,
    unsigned int sampleCount = 1,
    unsigned int qualityLevels = 0);

  /**
   * Inicializa una textura copiando de otra existente.
   *
   * Crea una nueva textura con base en la descripción de otra,
   * pero usando un formato DXGI distinto.
   *
   * @param device     Dispositivo Direct3D.
   * @param textureRef Textura de referencia.
   * @param format     Nuevo formato DXGI.
   * @return           S_OK si es exitoso; HRESULT en caso de error.
   */
  HRESULT init(Device& device, Texture& textureRef, DXGI_FORMAT format);

  /// Placeholder para futuras actualizaciones dinámicas de la textura.
  void update();

  /**
   * Asigna la textura al pipeline gráfico como recurso de shader.
   *
   * Internamente llama a PSSetShaderResources.
   *
   * @param deviceContext Contexto donde se vincula.
   * @param StartSlot     Slot inicial en el Pixel Shader.
   * @param NumViews      Número de vistas a vincular (usualmente 1).
   */
  void render(DeviceContext& deviceContext, unsigned int StartSlot, unsigned int NumViews);

  /**
   * Libera los recursos asociados a la textura y su SRV.
   *
   * Después de esta llamada, los punteros quedan en nullptr.
   */
  void destroy();

public:
  /// Recurso base de la textura (GPU).
  ID3D11Texture2D* m_texture = nullptr;

  /// Vista de la textura como recurso de shader.
  ID3D11ShaderResourceView* m_textureFromImg = nullptr;

  /// Nombre o ruta del archivo de origen (si aplica).
  std::string m_textureName;
};
