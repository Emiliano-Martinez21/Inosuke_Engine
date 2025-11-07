# Inosuke_Engine
Repositorio para las clases de graficas computacionales 3D 
Es un motor de render 3D desarrollado en C++ y en DirectX 11.El motor implementa un pipeline de renderizado en tiempo real capaz de mostrar un cubo texturizado girando.
El motor implementa un pipeline de renderizado en tiempo real capaz de:

Pipeline renderizado

Crear ventana Win32

Inicializar DirectX 11 (Device, DeviceContext, SwapChain)

Configurar RenderTarget, DepthStencil y Viewport

Compilar y aplicar Vertex/Pixel Shaders

Cargar modelos OBJ básicos

Crear y administrar buffers: Vertex / Index / Constant

Aplicar texturas y Sampler State

Renderizar un cubo texturizado en rotación

          🔹 Arquitectura del proyecto
| Módulo / Clase             | Función en el motor                                     |
| -------------------------- | ------------------------------------------------------- |
| **Window**                 | Gestión de la ventana Win32                             |
| **Device & DeviceContext** | Creación de recursos GPU y emisión de comandos          |
| **SwapChain**              | Presentación del frame al monitor                       |
| **Texture**                | Manejo de texturas 2D y depth-stencil                   |
| **RenderTargetView**       | Buffer donde se dibuja cada cuadro                      |
| **DepthStencilView**       | Control de pruebas de profundidad y stencil             |
| **Viewport**               | Define el área visible de renderizado                   |
| **ShaderProgram**          | Compilación y uso de Vertex/Pixel Shaders + InputLayout |
| **Buffer**                 | Vertex / Index / Constant Buffers                       |
| **SamplerState**           | Filtrado y direccionamiento de texturas                 |
| **MeshComponent**          | Almacena vértices e índices de una malla                |
| **ModelLoader**            | Lector manual de modelos OBJ                            |
| **BaseApp**                | Loop principal, lógica de actualización y renderizado   |

