#pragma once


#if defined _DEBUG
constexpr inline bool debugBuild{true};
#else
constexpr inline bool debugBuild{false};
#endif


constexpr inline bool releaseBuild{!debugBuild};
