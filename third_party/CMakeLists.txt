include(FetchContent)

# --- 1. Google Test (GTest) ---
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.15.2
)

FetchContent_MakeAvailable(googletest)

# --- 2. nlohmann_json ---
FetchContent_Declare(
  json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG        v3.11.3
)
FetchContent_MakeAvailable(json)

set(SDL2_INSTALL OFF CACHE BOOL "" FORCE)
set(SDL2IMAGE_INSTALL OFF CACHE BOOL "" FORCE)
set(SDL2TTF_INSTALL OFF CACHE BOOL "" FORCE)

# --- 3. SDL2 ---
FetchContent_Declare(
    SDL2
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-2.30.x
)

FetchContent_MakeAvailable(SDL2)

# --- 3. SDL2 text ---
FetchContent_Declare(
    SDL2_ttf
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
    GIT_TAG release-2.22.x
)

FetchContent_MakeAvailable(SDL2_ttf)

# --- 3. SDL2 image ---
FetchContent_Declare(
    SDL2_image
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
    GIT_TAG release-2.6.x
)

FetchContent_MakeAvailable(SDL2_image)
