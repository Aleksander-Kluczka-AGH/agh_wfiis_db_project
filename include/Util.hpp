#pragma once

#include <imgui_internal.h>

namespace ImGui
{
    /**
     * @brief Draws text input field with hint
     * 
     * @param label The ID of the scheduled object
     * @param hint The hint displayed if the contents are empty
     * @param buf The buffer holding field's content
     * @param buf_size The total size of the @c buf
     * @param size The custom size of the input field
     * @param flags Flags passed to the handler
     * @param callback The callback function
     * @param user_data The custom user data
     * @return True if currently in use, false otherwise
     * 
     * This is missing in ImGui API, so I had to add it myself
     */
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
