
set(sources
  "Noise.hpp"
  "Noise.cpp"
  "BaseTerrain.hpp"
  "BaseTerrain.cpp"
  "HydraulicErosion.hpp"
  "HydraulicErosion.cpp"
  "WaterPlane.hpp"
  "WaterPlane.cpp"
  "TerrainSettings.hpp"
)

target_relative_sources(${CGRA_PROJECT} ${sources})
