#pragma once
#include "Prerequisites.h"
#include <unordered_map>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>

class MeshComponent;

/**
 * Loader manual de OBJ (v, vt, vn, f).
 * - Soporta índices positivos y negativos.
 * - Soporta "v", "v/vt", "v//vn", "v/vt/vn".
 * - Triangulación por fan para n-gons (tri/quad/...).
 * - Genera SimpleVertex { Pos, Tex } para tu layout actual.
 */
class ModelLoader {
public:
  struct Options {
    bool flipV = true;         
    bool allowNegative = true; 
  };

  static bool loadFromFile(const std::string& filename,
    MeshComponent& outMesh,
    const Options& opts = {});

private:
  static void processFace(const std::vector<std::string>& faceTokens,
    std::unordered_map<std::string, unsigned>& uniqueMap,
    std::vector<SimpleVertex>& outVertices,
    std::vector<unsigned>& outIndices,
    const std::vector<XMFLOAT3>& pos,
    const std::vector<XMFLOAT2>& uvs,
    const std::vector<XMFLOAT3>& norms,
    const Options& opts);

  static int  resolveIndex(int idx, int count, bool allowNegative);
  static void split(const std::string& s, char delim, std::vector<std::string>& out);
  static std::string trim(const std::string& s);
};
