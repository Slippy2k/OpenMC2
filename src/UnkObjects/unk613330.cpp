/**********************************************************************
* OpenMC2 - An Open Source Re-Implementation of Midnight Club 2
* Copyright (C) 2016  LRFLEW
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
**********************************************************************/

#include "unk613330.hpp"
#include "../Logging.hpp"
#include "../Game.hpp"
#include <string>

// mc2:0x00659B0C
unk_613330::vtable_t unk_613330::vtable_values = {
    MC2_PROC_MEMBER_PTR<void, void>(0x005ED480),
    MC2_PROC_MEMBER_PTR<void, void, char*, std::uint32_t, char*, char*>(0x00619AB9),
    MC2_PROC_MEMBER_PTR<void, void>(0x00619AB9),
    MC2_PROC_MEMBER_PTR<void, void>(0x00619AB9),
    MC2_PROC_MEMBER_PTR<void, void>(0x005CA940),
    MC2_PROC_MEMBER_PTR<void, void>(0x00406990),
    MC2_PROC_MEMBER_PTR<void, void>(0x00613770),
    &unk_613330::impl_1C,
    &unk_613330::impl_20,
    &unk_613330::impl_24,
    &unk_613330::impl_28,
};

unk_613330::unk_613330() : vtable(&unk_613330::vtable_values) {
    glo_860220 = this;
}

FileHandler *sub_617C40(char *path, bool extension) {
    FileHandler::FuncTable *fileFuncs = extension ? glo_679810 : glo_679814;
    
    HANDLE file = fileFuncs->open_file(path, extension);
    
    if (file == INVALID_HANDLE_VALUE)
        return nullptr;

    if (glo_860AD8 != nullptr && !glo_860AD8(path, extension)) {
        fileFuncs->close_file(file);
        return nullptr;
    }

    return register_file_handle(path, file, fileFuncs);
}

// mc2: 0x00613780
FileHandler *unk_613330::impl_1C(char *unk1, char *unk2, std::uint32_t unk3, bool extension) {
    char buffer[256];
    vir_04(buffer, 256, unk1, unk2);

    return sub_617C40(buffer, extension);
}

// mc2: 0x00613800
FileHandler *unk_613330::impl_20(char *unk1, char *unk2, std::uint32_t unk3) {
    char buffer[256];
    vir_04(buffer, 256, unk1, unk2);

    return sub_617CA0(buffer);
}

// mc2: 0x006134F0
bool unk_613330::impl_24(char *unk1) {
    if (unk1 == nullptr)
        return true;

    if (*unk1 == '\\' || *unk1 == '/')
        return false;

    if (unk1[1] == ':')
        return false;

    return true;
}

// mc2: 0x00613520
void unk_613330::impl_28(char *destination, const char *unk2, const char *extension) {
    safe_strcat(destination, 256, unk2);
    
    const char *extension_loc = std::strrchr(unk2, '.');
    if (extension_loc == nullptr ||
        (extension[0] != '\0' && stricmp(extension_loc + 1, extension) != 0)) {
        safe_strcat(destination, 256, ".");
        safe_strcat(destination, 256, extension);
    }
}

MC2_DEF_GLOBAL(glo_860220, 0x00860220);
