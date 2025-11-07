#pragma once
#include "Prerequisites.h"
//#include "ECS\Component.h"
class DeviceContext;

/**
 * @class MeshComponent
 * @brief Contiene los vértices e índices que forman una malla 3D.
 * Se usa dentro de un sistema ECS como componente de geometría.
 */
class MeshComponent /*: public Component*/ {
public:
  MeshComponent()
    : m_numVertex(0), m_numIndex(0) /* Inicializa contadores a cero */ {}

  virtual ~MeshComponent() = default; // Destructor simple

  /**
   * @brief Inicialización opcional de la malla.
   * (vacío porque esta clase solo almacena datos)
   */
  void init(); /*override {}*/

  /**
   * @brief Actualiza la malla (para animaciones o morphing).
   * En este motor está vacío.
   */
  void update(float deltaTime) /*override {}*/;

  /**
   * @brief Render de la malla usando buffers externos.
   * (realmente el dibujo lo hacen los Buffer + DeviceContext)
   */
  void render(DeviceContext& deviceContext) /*override {}*/;

  /**
   * @brief Libera la malla (aquí no libera nada porque no hay recursos GPU).
   */
  void destroy() /*override {}*/;

public:
  std::string m_name;                    // Nombre opcional de la malla
  std::vector<SimpleVertex> m_vertex;    // Lista de vértices (pos, uv, normal...)
  std::vector<unsigned int> m_index;     // Lista de índices (triángulos)
  int m_numVertex;                       // Total de vértices
  int m_numIndex;                        // Total de índices
};
