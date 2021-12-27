#pragma once

#include <imgui_internal.h>

namespace ImGui
{
    // this is missing in imgui API, so have to add it myself
    bool InputTextMultilineWithHint(
        const char* label,
        const char* hint,
        char* buf,
        std::size_t buf_size,
        const ImVec2& size,
        ImGuiInputTextFlags flags = 0,
        ImGuiInputTextCallback callback = __null,
        void* user_data = nullptr);
}
