#include "ModelLoader.h"
#include "MeshComponent.h"


void ModelLoader::split(const std::string& s, char d, std::vector<std::string>& out) {
  out.clear();
  std::string tok;
  std::istringstream ss(s);
  while (std::getline(ss, tok, d)) out.push_back(tok);
}

std::string ModelLoader::trim(const std::string& s) {
  const char* ws = " \t\r\n";
  size_t b = s.find_first_not_of(ws);
  if (b == std::string::npos) return "";
  size_t e = s.find_last_not_of(ws);
  return s.substr(b, e - b + 1);
}


int ModelLoader::resolveIndex(int idx, int count, bool allowNegative) {
  if (idx == 0) return -1;
  if (idx < 0 && allowNegative) return count + idx;  
  return idx - 1;                                     
}

void ModelLoader::processFace(
  const std::vector<std::string>& face,
  std::unordered_map<std::string, unsigned>& uniqueMap,
  std::vector<SimpleVertex>& outVertices,
  std::vector<unsigned>& outIndices,
  const std::vector<XMFLOAT3>& pos,
  const std::vector<XMFLOAT2>& uvs,
  const std::vector<XMFLOAT3>& norms,
  const Options& opts)
{
  
  std::vector<unsigned> vidx; vidx.reserve(face.size());

  for (const std::string& vtokenRaw : face) {
    std::string vtoken = trim(vtokenRaw);
    if (vtoken.empty()) continue;

    auto it = uniqueMap.find(vtoken);
    if (it != uniqueMap.end()) {
      vidx.push_back(it->second);
      continue;
    }

    // Parse "v[/vt][/vn]"
    std::vector<std::string> parts;
    split(vtoken, '/', parts);
    int v = 0, vt = 0, vn = 0;

    try {
      if (parts.size() >= 1 && !parts[0].empty()) v = std::stoi(parts[0]);
      if (parts.size() >= 2 && !parts[1].empty()) vt = std::stoi(parts[1]);
      if (parts.size() >= 3 && !parts[2].empty()) vn = std::stoi(parts[2]);
    }
    catch (...) {
      
      continue;
    }

    int pv = resolveIndex(v, (int)pos.size(), opts.allowNegative);
    int pt = resolveIndex(vt, (int)uvs.size(), opts.allowNegative);
    

    if (pv < 0 || pv >= (int)pos.size()) continue;

    SimpleVertex sv{};
    sv.Pos = pos[pv];

    if (pt >= 0 && pt < (int)uvs.size()) {
      sv.Tex = uvs[pt];
      if (opts.flipV) sv.Tex.y = 1.0f - sv.Tex.y;
    }
    else {
      sv.Tex = XMFLOAT2(0.0f, 0.0f);
    }

    unsigned newIndex = (unsigned)outVertices.size();
    outVertices.push_back(sv);
    uniqueMap[vtoken] = newIndex;
    vidx.push_back(newIndex);
  }

  if (vidx.size() < 3) return;

  
  const unsigned i0 = vidx[0];
  for (size_t i = 1; i + 1 < vidx.size(); ++i) {
    outIndices.push_back(i0);
    outIndices.push_back(vidx[i]);
    outIndices.push_back(vidx[i + 1]);
  }
}

bool ModelLoader::loadFromFile(const std::string& filename,
  MeshComponent& outMesh,
  const Options& opts)
{
  std::ifstream f(filename);
  if (!f.is_open()) {
    std::wstring wfn(filename.begin(), filename.end());
    ERROR(L"ModelLoader", L"loadFromFile", (L"No se pudo abrir: " + wfn).c_str());
    return false;
  }

  std::vector<XMFLOAT3> positions;
  std::vector<XMFLOAT2> texcoords;
  std::vector<XMFLOAT3> normals;

  std::vector<SimpleVertex> outVertices;
  std::vector<unsigned> outIndices;
  std::unordered_map<std::string, unsigned> unique;

  std::string line;
  while (std::getline(f, line)) {
    line = trim(line);
    if (line.empty() || line[0] == '#') continue;

    std::istringstream ss(line);
    std::string tag;
    ss >> tag;

    if (tag == "v") {
      XMFLOAT3 p{};
      if (ss >> p.x >> p.y >> p.z) positions.push_back(p);
    }
    else if (tag == "vt") {
      XMFLOAT2 t{};
      if (ss >> t.x >> t.y) texcoords.push_back(t); 
    }
    else if (tag == "vn") {
      XMFLOAT3 n{};
      if (ss >> n.x >> n.y >> n.z) normals.push_back(n);
    }
    else if (tag == "f") {
      std::vector<std::string> tokens;
      std::string vtok;
      while (ss >> vtok) tokens.push_back(vtok);
      if (tokens.size() >= 3) {
        processFace(tokens, unique, outVertices, outIndices,
          positions, texcoords, normals, opts);
      }
    }
    
  }
  f.close();

  outMesh.m_name = filename;
  outMesh.m_vertex = std::move(outVertices);
  outMesh.m_index = std::move(outIndices);
  outMesh.m_numVertex = (int)outMesh.m_vertex.size();
  outMesh.m_numIndex = (int)outMesh.m_index.size();

  if (outMesh.m_numVertex == 0 || outMesh.m_numIndex == 0) {
    std::wstring wfn(filename.begin(), filename.end());
    ERROR(L"ModelLoader", L"loadFromFile", (L"Modelo vacío o malformado: " + wfn).c_str());
    return false;
  }

  std::wostringstream wss;
  std::wstring wfn(filename.begin(), filename.end());
  wss << L"OK " << wfn << L" [V:" << outMesh.m_numVertex << L" I:" << outMesh.m_numIndex << L"]";
  MESSAGE(L"ModelLoader", L"loadFromFile", wss.str().c_str());
  return true;
}
