#pragma once

//--------------------------------------------------------------------------------------
// Librer�as est�ndar de C++
//--------------------------------------------------------------------------------------
#include <string>
#include <sstream>
#include <vector>
#include <Windows.h>
#include <xnamath.h>
#include <thread>

//--------------------------------------------------------------------------------------
// Librer�as de DirectX necesarias para renderizado y compilaci�n de shaders
//--------------------------------------------------------------------------------------
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include "Resource.h"
#include "resource.h"

//--------------------------------------------------------------------------------------
// Librer�as externas (placeholder para dependencias de terceros)
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
// Macros de utilidad
//--------------------------------------------------------------------------------------

/// Libera de forma segura un recurso COM y lo establece en nullptr.
#define SAFE_RELEASE(x) if(x != nullptr) x->Release(); x = nullptr;

/// Macro para mostrar un mensaje informativo en la salida de depuraci�n.
#define MESSAGE(classObj, method, state)                       \
{                                                              \
   std::wostringstream os_;                                    \
   os_ << classObj << "::" << method                           \
       << " : " << "[CREATION OF RESOURCE : " << state << "]\n"; \
   OutputDebugStringW(os_.str().c_str());                      \
}

/// Macro para mostrar un mensaje de error en la salida de depuraci�n.
/// Captura excepciones para evitar fallos al formatear el log.
#define ERROR(classObj, method, errorMSG)                        \
{                                                                \
    try {                                                        \
        std::wostringstream os_;                                 \
        os_ << L"ERROR : " << classObj << L"::" << method        \
            << L" : " << errorMSG << L"\n";                      \
        OutputDebugStringW(os_.str().c_str());                   \
    } catch (...) {                                              \
        OutputDebugStringW(L"Failed to log error message.\n");   \
    }                                                            \
}

//--------------------------------------------------------------------------------------
// Estructuras auxiliares para shaders y constantes
//--------------------------------------------------------------------------------------

/// Estructura b�sica de un v�rtice: posici�n y coordenadas de textura.
struct SimpleVertex {
  XMFLOAT3 Pos;  ///< Posici�n en espacio 3D
  XMFLOAT2 Tex;  ///< Coordenadas UV de la textura
};

/// Buffer constante: datos de vista (no cambian durante la ejecuci�n).
struct CBNeverChanges {
  XMMATRIX mView;  ///< Matriz de vista (c�mara)
};

/// Buffer constante: datos que cambian al redimensionar la ventana.
struct CBChangeOnResize {
  XMMATRIX mProjection;  ///< Matriz de proyecci�n
};

/// Buffer constante: datos que cambian cada frame.
struct CBChangesEveryFrame {
  XMMATRIX mWorld;       ///< Matriz de transformaci�n del mundo
  XMFLOAT4 vMeshColor;   ///< Color del mesh
};

//--------------------------------------------------------------------------------------
// Enumeraciones
//--------------------------------------------------------------------------------------

/// Tipos de extensi�n de archivo de textura soportados.
enum ExtensionType {
  DDS = 0,  ///< Textura en formato DDS
  PNG = 1,  ///< Textura en formato PNG
  JPG = 2   ///< Textura en formato JPG
};

enum ShaderType {
  VERTEX_SHADER = 0,
  PIXEL_SHADER = 1
};