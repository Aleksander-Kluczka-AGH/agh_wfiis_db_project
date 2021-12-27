#include "../include/Util.hpp"

namespace ImGui
{
    bool InputTextMultilineWithHint(
        const char* label,
        const char* hint,
        char* buf,
        std::size_t buf_size,
        const ImVec2& size,
        ImGuiInputTextFlags flags,
        ImGuiInputTextCallback callback,
        void* user_data)
    {
        return InputTextEx(label, hint, buf, (int)buf_size, size, flags | ImGuiInputTextFlags_Multiline, callback, user_data);
    }
}
